/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include <stdlib.h>
#include <stdio.h>
#include "prefix.h"
#define EXTERN extern
#include "header.h"
#include "log.h"


/*
 * Constants
 */

enum gc_phase {
  PHASE_INACTIVE,
  PHASE_INITIALISE,
  PHASE_MARK,
  PHASE_WEAK,
  PHASE_FWDREF,
  PHASE_BWDREF,
  PHASE_FINALISE,
};

/*
 * Variables
 */
static enum gc_phase gc_phase = PHASE_INACTIVE;

static Context *the_context;
#include "gc-visitor-inl.h"

/*
 * Tracer
 */
#include "mark-tracer.h"
#include "threaded-tracer.h"

#ifdef DUMP_HCG
extern "C" {
extern void count_hc_instance_hook(void*);  /* object.c */
}
typedef DefaultTracerWithHook<count_hc_instance_hook> MarkPhaseTracer;
#else /* DUMP_HCG */
typedef DefaultTracerWithHook<nullptr> MarkPhaseTracer;
#endif /* DUMP_HCG */
typedef DefaultTracer WeakPhaseTracer;


#ifdef GC_PROF
static void count_dead_object(header_t hdr, size_t size)
{
  cell_type_t type = hdr.type;
  size_t bytes = (size + BOUNDARY_TAG_GRANULES) << LOG_BYTES_IN_GRANULE;
  pertype_collect_bytes[type]+= bytes;
  pertype_collect_count[type]++;
}

static void count_live_object(header_t hdr, size_t size)
{
  cell_type_t type = hdr.type;
  size_t bytes = (size + BOUNDARY_TAG_GRANULES) << LOG_BYTES_IN_GRANULE;
  pertype_live_bytes[type]+= bytes;
  pertype_live_count[type]++;
}

#define COUNT_DEAD_OBJECT(hdrp, size) count_dead_object(hdrp, size)
#define COUNT_LIVE_OBJECT(hdrp, size) count_live_object(hdrp, size)
#else /* GC_PROF */
#define COUNT_DEAD_OBJECT(hdrp, size)
#define COUNT_LIVE_OBJECT(hdrp, size)
#endif /* GC_PROF */

#include "threaded-functions-inl.h"
#ifdef JONKERS
#include "jonkers-collector-inl.h"
#endif /* JONKERS */
#ifdef FUSUMA
#include "fusuma-collector-inl.h"
#endif /* FUSUMA */

/*
 * GC
 */

static void update_forward_reference(Context *ctx);
static void update_backward_reference();

#ifdef GC_DEBUG
static void fill_mem(void *p1, void *p2, JSValue v);
#endif /* GC_DEBUG */

void garbage_collection(Context *ctx)
{
  /* initialise */
  gc_phase = PHASE_INITIALISE;
  the_context = ctx;

  /* mark */
#ifdef TU_DEBUG
  printf("mark\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_MARK;
  scan_roots<MarkPhaseTracer>(ctx);
  MarkPhaseTracer::process_mark_stack();

  /* weak */
#ifdef TU_DEBUG
  printf("weak\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_WEAK;
  weak_clear<WeakPhaseTracer>(ctx);

  /* forwarding reference */
#ifdef TU_DEBUG
  printf("froward\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_FWDREF;
  update_forward_reference(ctx);

  /* backwarding reference */
#ifdef TU_DEBUG
  printf("backward\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_BWDREF;
  update_backward_reference();

  /* finalise */
  gc_phase = PHASE_FINALISE;

#ifdef GC_DEBUG
  fill_mem((void *) js_space.begin, (void *) js_space.end, (JSValue) 0xcccccccccccccccc);
#endif /* GC_DEBUG */

  gc_phase = PHASE_INACTIVE;
}

static inline void
merge_free_space_in_ordinary_area(uintptr_t start, uintptr_t end)
{
  if (start == end)
    return;
  size_t bytes = end - start;
  size_t granules = bytes >> LOG_BYTES_IN_GRANULE;
  header_t *hdrp = (header_t *) start;
#if HEADER_SIZE_BITS < 32
  if (granules > ((static_cast<uintjsv_t>(1) << HEADER_SIZE_BITS) - 1)) {
    hdrp->size = 0;
    void *payload = header_to_payload(hdrp);
    *((granule_t *) payload) = (granule_t) granules;
  } else
#endif /* HEADER_SIZE_BITS < 32 */
    hdrp->size = granules;
}

static inline int skip_and_merge_garbage_in_ordinary_area(uintptr_t &scan, uintptr_t end) {
  uintptr_t first_free = scan;
  header_t *hdrp = (header_t *) scan;

  while (!get_threaded_header_markbit(hdrp)) {
    const size_t size = hdrp->size;
    scan += size << LOG_BYTES_IN_GRANULE;
    assert(scan <= end);
    COUNT_DEAD_OBJECT(*hdrp, hdrp->size);
    if (scan == end) {
      merge_free_space_in_ordinary_area(first_free, scan);
      return FALSE;
    }
    hdrp = (header_t *) scan;
  }

  merge_free_space_in_ordinary_area(first_free, scan);

  return TRUE;
}

static inline size_t get_merged_garbage_size(header_t *hdrp) {
  const size_t size = hdrp->size;
#if HEADER_SIZE_BITS < 32
  if (size != 0)
#endif /* HEADER_SIZE_BITS < 32 */
    return size;

#if HEADER_SIZE_BITS < 32
  void *payload = header_to_payload(hdrp);
  return (size_t) *((granule_t *) payload);
#endif /* HEADER_SIZE_BITS < 32 */

}

static void update_forward_reference(Context *ctx)
{
  scan_roots<ThreadTracer>(ctx);

  const uintptr_t scan1 = get_first_region_scan();
  const uintptr_t end1 = get_first_region_end();
  const uintptr_t free1 = get_first_region_free(scan1, end1);

#ifdef GC_JONKERS_USING_QUEUE
  const uintptr_t tail = js_space.tail;
  uintptr_t hcrec = js_space.end;

  scan_first_region_ufr_phase(scan1, end1, free1, hcrec, tail);
#else /* GC_JONKERS_USING_QUEUE */
  scan_first_region_ufr_phase(scan1, end1, free1);
#endif /* GC_JONKERS_USING_QUEUE */


  /* hidden class area */
#ifdef GC_JONKERS_USING_QUEUE
  uintptr_t hcr = js_space.end;

  scan_second_region_mix_ufr_phase(hcr, hcrec);
  assert(hcrec <= js_space.tail);

/*
 now;
 end                  hcrec   tail
  | <- for live meta -> |      |
*/
  set_second_region_end(hcr, hcrec, /* dummy */ 0);
/*
 after;
        end                   tail
         | <- for live meta -> |
*/
#else /* GC_JONKERS_USING_QUEUE */

  const uintptr_t scan2 = get_second_region_scan();
  const uintptr_t end2 = get_second_region_end();
  const uintptr_t free2 = get_second_region_free(scan2, end2);

  scan_second_region_ufr_phase(scan2, end2, free2);
#endif /* GC_JONKERS_USING_QUEUE */
  return;
}

static void update_backward_reference()
{
#ifdef GC_JONKERS_USING_QUEUE
  /* Only nofusuma algorithm; update all references before starting of moving objects */
  scan_pre_first_region_mix_ubr_phase(js_space.head, js_space.begin, js_space.head);
#endif /* GC_JONKERS_USING_QUEUE */

  const uintptr_t scan1 = get_first_region_scan();
  const uintptr_t end1 = get_first_region_end();
  uintptr_t free1 = get_first_region_free(scan1, end1);

  scan_first_region_ubr_phase(scan1, end1, free1);

  set_first_region_end(scan1, end1, free1);


#ifndef GC_JONKERS_MIX
  const uintptr_t scan2 = get_second_region_scan();
  const uintptr_t end2 = get_second_region_end();
  uintptr_t free2 = get_second_region_free(scan2, end2);

  scan_second_region_ubr_phase(scan2, end2, free2);

  set_second_region_end(scan2, end2, free2);
#endif /* !GC_JONKERS_MIX */

  update_space_free_bytes();
}

static void copy_object(void *from_, void *to_, unsigned int size)
{
  if (from_ == to_)
    return;

  JSValue *from = (JSValue *) from_;
  JSValue *to = (JSValue *) to_;
  JSValue *end = from + size;

  while(from < end) {
    /*
     * Unfortunately, compiler may be eliminate these code.
     * This compile-time memory barrier will prevent elimination.
     */
    __asm__ __volatile__( " " : : : "memory");

    *to = *from;
    ++from;
    ++to;
  }
}

#ifdef GC_DEBUG
static void fill_mem(void *p1, void *p2, JSValue v)
{
  JSValue *p = (JSValue *) p1;
  JSValue *end = (JSValue *) p2;
  while (p < end) {
    *p = v;
    ++p;
  }
}
#endif /* GC_DEBUG */

