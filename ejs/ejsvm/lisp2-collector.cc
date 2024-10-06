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

#ifdef CXX_TRACER_CBV
#error "Lisp2 collector does not except macro; CXX_TRACER_CBV."
#endif /* CXX_TRACER_CBV */
#ifdef CXX_TRACER_RV
#error "Lisp2 coollector does not except macro; CXX_TRACER_RV."
#endif /* CXX_TRACER_RV */

#ifdef GC_DEBUG
static inline void fill_mem(void *p1, void *p2, JSValue v);
#endif /* GC_DEBUG */

/*
 * Constants
 */

enum gc_phase {
  PHASE_INACTIVE,
  PHASE_INITIALISE,
  PHASE_MARK,
  PHASE_WEAK,
  PHASE_CALC_FWD,
  PHASE_UPDATE_ORDINARY,
  PHASE_UPDATE_META,
  PHASE_MOVE,
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

#ifdef GC_PROF
static void count_dead_object(header_t hdr, size_t size)
{
  const cell_type_t type = hdr.type;
  const size_t bytes = size << LOG_BYTES_IN_GRANULE;
  pertype_collect_bytes[type]+= bytes;
  pertype_collect_count[type]++;
}

static void count_live_object(header_t hdr, size_t size)
{
  const cell_type_t type = hdr.type;
  const size_t bytes = size << LOG_BYTES_IN_GRANULE;
  pertype_live_bytes[type]+= bytes;
  pertype_live_count[type]++;
}

#define COUNT_DEAD_OBJECT(hdrp, size) count_dead_object(hdrp, size)
#define COUNT_LIVE_OBJECT(hdrp, size) count_live_object(hdrp, size)
#else /* GC_PROF */
#define COUNT_DEAD_OBJECT(hdrp, size)
#define COUNT_LIVE_OBJECT(hdrp, size)
#endif /* GC_PROF */

static inline void *get_fwd(const void *payload)
{
  const header_t *hdrp = payload_to_header(payload);
  assert(is_marked_cell_header(hdrp));
  assert(hdrp->fwd != NULL);
  return hdrp->fwd;
}

class Lisp2Tracer {
public:
  static constexpr bool is_single_object_scanner = true;
  static constexpr bool is_hcg_mutator = false;
  static void process_edge(JSValue &v) {
    if (is_fixnum(v) || is_special(v))
      return;

    const PTag tag = get_ptag(v);
    const void *p = (const void *) clear_ptag(v);
    assert(p != NULL);

#ifdef USE_EMBEDDED_INSTRUCTION
    /* Constant table of embedded instruction is allocated on FLASH. */
    if (in_mbed_flash(p))
      return;
#endif /* USE_EMBEDDED_INSTRUCTION */

    assert(in_js_space(p));

    const void *fwd = get_fwd(p);
    assert(in_js_space(fwd));

    v = put_ptag((uintptr_t) fwd, tag);
  }
  static void process_edge(void *&p) {
    assert(p != NULL);

    assert(in_js_space((void *) p));

    const void *fwd = get_fwd(p);
    assert(in_js_space(fwd));

    p = (void *) fwd;
  }
  static void process_edge_function_frame(JSValue &v) {
    if ((void *) v == NULL)
      return;

    assert(in_js_space((const void *) v));

    const void *fwd = get_fwd((const void *) v);
    assert(in_js_space(fwd));

    v = (JSValue) (uintptr_t) fwd;
  }
  template <typename T>
  static void process_edge_ex_JSValue_array(T &p, size_t n) {
    if ((void *) p == NULL)
      return;

    assert(in_js_space((const void *) p));

    const void *fwd = get_fwd((const void *) p);
    assert(in_js_space(fwd));

    p = (T) (uintptr_t) fwd;
  }
  template <typename T>
  static void process_edge_ex_ptr_array(T &p, size_t n) {
    if ((void *) p == NULL)
      return;

    assert(in_js_space((const void *) p));

    const void *fwd = get_fwd((const void *) p);
    assert(in_js_space(fwd));

    p = (T) (uintptr_t) fwd;
  }
  static void process_node_JSValue_array(JSValue *p) {
    if (p == NULL)
      return;

    assert(in_js_space((void *) p));

    const header_t *hdrp = payload_to_header(p);
    const size_t payload_granules = hdrp->size - HEADER_GRANULES;
    const size_t slots = payload_granules <<
      (LOG_BYTES_IN_GRANULE - LOG_BYTES_IN_JSVALUE);
    for (size_t i = 0; i < slots; i++)
      process_edge(p[i]);
  }
  static void process_node_ptr_array(void **&p) {
    if (p == NULL)
      return;

    assert(in_js_space((void *) p));

    const header_t *hdrp = payload_to_header(p);
    const size_t payload_granules = hdrp->size - HEADER_GRANULES;
    const size_t slots = payload_granules * (BYTES_IN_GRANULE / sizeof(void *));
    for (size_t i = 0; i < slots; i++) {
      if (p[i] != NULL)
        process_edge(p[i]);
    }
  }
  static void process_weak_edge(JSValue &v) { process_edge(v); }
  static void process_weak_edge(void *&p) { process_edge(p); }

  static void process_mark_stack(void) {}
};


/*
 * GC
 */

static void calc_fwd_phase();
static void update_ordinary_phase(Context *ctx);
static void update_meta_phase();
static void move_phase();
static void copy_object(void *from_hdrp, void *to_hdrp, unsigned int size);

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
  scan_roots<DefaultTracer>(ctx);
  DefaultTracer::process_mark_stack();

  /* weak */
#ifdef TU_DEBUG
  printf("weak\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_WEAK;
  weak_clear<DefaultTracer>(ctx);

  /* calc forwarding pointer */
#ifdef TU_DEBUG
  printf("calc fwd\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_CALC_FWD;
  calc_fwd_phase();

  /* update pointers which is placed in ordinary objects */
#ifdef TU_DEBUG
  printf("update ordinary\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_UPDATE_ORDINARY;
  update_ordinary_phase(ctx);

  /* update pointers which is placed in meta objects */
#ifdef TU_DEBUG
  printf("update meta\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_UPDATE_META;
  update_meta_phase();

  /* move live objects */
#ifdef TU_DEBUG
  printf("move\n");
#endif /* TU_DEBUG */
  gc_phase = PHASE_MOVE;
  move_phase();

  /* finalise */
  gc_phase = PHASE_FINALISE;

#ifdef GC_DEBUG
  fill_mem((void *) js_space.top, (void *) js_space.end, (JSValue) 0xcccccccccccccccc);
#endif /* GC_DEBUG */

  gc_phase = PHASE_INACTIVE;
}

static inline void
merge_free_space_area(uintptr_t start, uintptr_t end)
{
  if (start == end)
    return;
  const size_t bytes = end - start;
  const size_t granules = bytes >> LOG_BYTES_IN_GRANULE;
  header_t *hdrp = (header_t *) start;
#if HEADER_SIZE_BITS < 32
  if (granules > ((static_cast<uintjsv_t>(1) << HEADER_SIZE_BITS) - 1)) {
    hdrp->size = 0;
    *(granule_t *) (start + (HEADER_GRANULES << BYTES_IN_GRANULE)) = granules;
  }
  else
#endif /* HEADER_SIZE_BITS < 32 */
  {
    hdrp->size = granules;
  }
}

static void calc_fwd_phase()
{
  uintptr_t scan = js_space.begin;
  uintptr_t free = scan;
  const uintptr_t end = js_space.top;

  while (scan < end) {
    /* skip free/garbage */
    {
      const uintptr_t first_free = scan;
      const header_t *hdrp = (header_t *) scan;
      while (!is_marked_cell_header(hdrp)) {
        const size_t size = hdrp->size;
        scan += size << LOG_BYTES_IN_GRANULE;
        assert(scan <= end);
        COUNT_DEAD_OBJECT(*hdrp, hdrp->size);
        if (scan == end) {
          merge_free_space_area(first_free, scan);
          return;
        }
        hdrp = (const header_t *) scan;
      }
      merge_free_space_area(first_free, scan);
    }

    /* process live object */
    assert(scan < end);
    header_t *hdrp = (header_t *) scan;
    const header_t *to_hdrp = (header_t *) free;
    void *to = header_to_payload(to_hdrp);

    assert(is_marked_cell_header(hdrp));
    assert(hdrp >= to_hdrp);

#ifdef GC_DEBUG_SHADOW
    if (hdrp->size > HEADER_GRANULES) {
      const header_t **shadow = (const header_t **) (((const header_t *) get_shadow(hdrp)) + 1);
      *shadow = to_hdrp;
    }
#endif /* GC_DEBUG_SHADOW */

    const size_t size = hdrp->size;
    hdrp->fwd = to;
    COUNT_LIVE_OBJECT(*hdrp, size);

    free += size << LOG_BYTES_IN_GRANULE;
    scan += size << LOG_BYTES_IN_GRANULE;
  }

  return;
}

static void update_ordinary_phase(Context *ctx)
{
  scan_roots<Lisp2Tracer>(ctx);

  uintptr_t scan = js_space.begin;
  const uintptr_t end = js_space.top;

  while (scan < end) {
    const header_t *hdrp = (header_t *) scan;

    if (!is_marked_cell_header(hdrp)) {
      size_t size = hdrp->size;
      if (size == 0)
	size = *(granule_t *)(scan + (HEADER_GRANULES << BYTES_IN_GRANULE));

      scan += size << LOG_BYTES_IN_GRANULE;
      continue;
    }

    /* process live object */
    assert(hdrp->fwd != NULL);

#ifdef GC_DEBUG_SHADOW
    if (hdrp->size > HEADER_GRANULES) {
      const header_t **shadow = (const header_t **) (((const header_t *) get_shadow(hdrp)) + 1);
      const void *to = hdrp->fwd;
      assert(*shadow == payload_to_header(to));
    }
#endif /* GC_DEBUG_SHADOW */

    if (!is_hidden_class(hdrp->type)) {
      uintjsv_t from = (uintjsv_t) header_to_payload(hdrp);
      process_node<Lisp2Tracer>(from);
    }

    const size_t size = hdrp->size;
    scan += size << LOG_BYTES_IN_GRANULE;
  }

  return;
}

static void update_meta_phase()
{
  uintptr_t scan = js_space.begin;
  const uintptr_t end = js_space.top;

  while (scan < end) {
    const header_t *hdrp = (header_t *) scan;

    if (!is_marked_cell_header(hdrp)) {
      size_t size = hdrp->size;
      if (size == 0)
	size = *(granule_t *)(scan + (HEADER_GRANULES << BYTES_IN_GRANULE));

      scan += size << LOG_BYTES_IN_GRANULE;
      continue;
    }

    /* process live object */
    assert(hdrp->fwd != NULL);

#ifdef GC_DEBUG_SHADOW
    if (hdrp->size > HEADER_GRANULES) {
      const header_t **shadow = (const header_t **) (((const header_t *) get_shadow(hdrp)) + 1);
      const void *to = hdrp->fwd;
      assert(*shadow == payload_to_header(to));
    }
#endif /* GC_DEBUG_SHADOW */

    if (is_hidden_class(hdrp->type)) {
      uintjsv_t from = (uintjsv_t) header_to_payload(hdrp);
      process_node<Lisp2Tracer>(from);
    }

    const size_t size = hdrp->size;
    scan += size << LOG_BYTES_IN_GRANULE;
  }

  return;
}

static void move_phase()
{
  uintptr_t scan = js_space.begin;
  uintptr_t free = scan;
  const uintptr_t end = js_space.top;

  while (scan < end) {
    header_t *hdrp = (header_t *) scan;

    if (!is_marked_cell_header(hdrp)) {
      size_t size = hdrp->size;
      if (size == 0)
	size = *(granule_t *)(scan + (HEADER_GRANULES << BYTES_IN_GRANULE));

      scan += size << LOG_BYTES_IN_GRANULE;
      continue;
    }

    /* process live object */
    assert(hdrp->fwd != NULL);

#ifdef GC_DEBUG_SHADOW
    if (hdrp->size > HEADER_GRANULES) {
      const header_t **shadow = (const header_t **) (((const header_t *) get_shadow(hdrp)) + 1);
      const void *to = hdrp->fwd;
      assert(*shadow == payload_to_header(to));
    }
#endif /* GC_DEBUG_SHADOW */

    const size_t size = hdrp->size;
    header_t *to_hdrp = payload_to_header(hdrp->fwd);
    unmark_cell_header(hdrp);
    hdrp->fwd = NULL;
    copy_object(hdrp, to_hdrp, size);

#ifdef GC_DEBUG_SHADOW
    {
      header_t *shadow = get_shadow(to_hdrp);
      *shadow = *to_hdrp;
    }
#endif /* GC_DEBUG_SHADOW */

    free += size << LOG_BYTES_IN_GRANULE;
    scan += size << LOG_BYTES_IN_GRANULE;
  }

  js_space.top = free;
  js_space.free_bytes = js_space.end - js_space.top;

  return;
}

static void copy_object(void *from_hdrp, void *to_hdrp, unsigned int size)
{
  if (from_hdrp == to_hdrp)
    return;

  JSValue *from = (JSValue *) from_hdrp;
  JSValue *to = (JSValue *) to_hdrp;
  JSValue * const end = from + size;

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
  JSValue * const end = (JSValue *) p2;
  while (p < end) {
    *p = v;
    ++p;
  }
}
#endif /* GC_DEBUG */

