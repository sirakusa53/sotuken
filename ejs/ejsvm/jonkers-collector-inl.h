/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef JONKERS_COLLECTOR_INL_H
#define JONKERS_COLLECTOR_INL_H


#if defined(GC_JONKERS_MIX) && defined(GC_JONKERS_SEPARATE_META)
#error "GC_JONKERS_MIX and GC_JONKERS_SEPARATE_META cannot be used at the same time"
#endif /* GC_JONKERS_MIX && GC_JONKERS_SEPARATE_META */

#if defined(GC_JONKERS_USING_QUEUE) && !defined(GC_JONKERS_MIX)
#error "GC_JONKERS_USING_QUEUE cannot be used without GC_JONKERS_MIX"
#endif /* GC_JONKERS_USING_QUEUE && !GC_JONKERS_MIX */


/*
 * Constants
 */

/*
 * Variables
 */

/*
 * Tracer
 */

/*
 * GC
 */

static void copy_object(void *from, void *to, unsigned int size);

static inline void
merge_free_space_in_ordinary_area(uintptr_t start, uintptr_t end);

/* Defined at threadedcompactor-collector.cc */
static inline int skip_and_merge_garbage_in_ordinary_area(uintptr_t &scan, uintptr_t end);
static inline size_t get_merged_garbage_size(header_t *hdrp);

#ifdef GC_JONKERS_USING_QUEUE
static inline void
record_hidden_class(uintptr_t hcrec, header_t *hdrp, void *to)
{
  struct hcrecord *hcr = (struct hcrecord *) hcrec;
  hcr->hdrp = hdrp;
  hcr->to = to;
}
#endif /* GC_JONKERS_USING_QUEUE */

static inline uintptr_t get_first_region_scan(void) { return js_space.head; }
static inline uintptr_t get_first_region_end(void) { return js_space.begin; }
static inline uintptr_t get_first_region_free(uintptr_t scan, uintptr_t /* end */) { return scan; }
static inline void set_first_region_end(uintptr_t /* scan */, uintptr_t /* end */, uintptr_t free) { js_space.begin = free; }

#ifndef GC_JONKERS_USING_QUEUE
#ifdef GC_JONKERS_SEPARATE_META
static inline uintptr_t get_second_region_scan(void) {return js_space.end; }
static inline uintptr_t get_second_region_end(void) { return js_space.tail; }
#else /* GC_JONKERS_SEPARATE_META */
static inline uintptr_t get_second_region_scan(void) {return js_space.head; }
static inline uintptr_t get_second_region_end(void) { return js_space.begin; }
#endif /* GC_JONKERS_SEPARATE_META */
static inline uintptr_t get_second_region_free(uintptr_t scan, uintptr_t /* end */ ) { return scan; }
#endif /* !GC_JONKERS_USING_QUEUE */

#ifdef GC_JONKERS_SEPARATE_META
static inline void set_second_region_end(uintptr_t /* scan */, uintptr_t /* end */, uintptr_t free) { js_space.tail = free; }
#else /* GC_JONKERS_SEPARATE_META */
#ifdef GC_JONKERS_USING_QUEUE
static inline void set_second_region_end(uintptr_t /* scan */, uintptr_t end, uintptr_t /* free */) { js_space.end += js_space.tail - end; }
#else /* GC_JONKERS_USING_QUEUE */
static inline void set_second_region_end(uintptr_t /* scan */, uintptr_t /* end */, uintptr_t /* free */) { /* Nothing to do */; }
#endif /* GC_JONKERS_USING_QUEUE */
#endif /* GC_JONKERS_SEPARATE_META */

static inline void update_space_free_bytes() {
  uintptr_t free_bytes = js_space.end - js_space.begin;
#ifdef GC_JONKERS_SEPARATE_META
  free_bytes -= js_space.tail - js_space.end;
#endif /* GC_JONKERS_SEPARATE_META */
  js_space.free_bytes = free_bytes;
}

static inline void scan_first_region_ufr_phase(
#ifdef GC_JONKERS_USING_QUEUE
  uintptr_t scan, uintptr_t end, uintptr_t free, uintptr_t& hcrec, uintptr_t tail
#else /* GC_JONKERS_USING_QUEUE */
  uintptr_t scan, uintptr_t end, uintptr_t free
#endif /* GC_JONKERS_USING_QUEUE */
)
{
  while (scan < end) {
    /* skip free/garbage */
    if (!skip_and_merge_garbage_in_ordinary_area(scan, end))
      return;

    header_t *hdrp = (header_t *) scan;

    /* process live object */
    assert((uintptr_t) hdrp < end);
    assert(get_threaded_header_markbit(hdrp));
    void *from = header_to_payload(hdrp);
    header_t *to_hdrp = (header_t *) free;
    void *to = header_to_payload(to_hdrp);

#ifdef GC_DEBUG_SHADOW
    if (get_threaded_header(hdrp).size > 1) {
      header_t **shadow = (header_t **) &(((header_t *) get_shadow(hdrp))[1]);
      *shadow = to_hdrp;
      header_t raw = get_threaded_header(hdrp);
      header_t cpy = *((header_t *) get_shadow(hdrp));
      assert(raw.identifier == 1);
      assert(cpy.identifier == 1);
      assert(cpy.markbit == 0); cpy.markbit = 1;
      assert(raw.threaded == cpy.threaded);
    }
#endif /* GC_DEBUG_SHADOW */

    header_t hdr = get_threaded_header(hdrp);
    uintjsv_t tag = get_ptag_value_by_cell_type(hdr.type);
    update_reference(tag, from, to);
    size_t size = hdrp->size;
    COUNT_LIVE_OBJECT(hdr, size);

    if (is_hidden_class(hdr.type)) {
#ifdef GC_JONKERS_USING_QUEUE
      if (hcrec >= tail)
        LOG_EXIT("HC record area overflow\n");

      record_hidden_class(hcrec, hdrp, to);
      hcrec += sizeof(struct hcrecord);
#endif /* GC_JONKERS_USING_QUEUE */
    }
    else
    {
      process_node<ThreadTracer>((uintptr_t) from);
    }

    free += size << LOG_BYTES_IN_GRANULE;
    scan += size << LOG_BYTES_IN_GRANULE;
  }
}

#ifdef GC_JONKERS_SEPARATE_META
#define scan_second_region_ufr_phase(scan, end, free) \
    scan_first_region_ufr_phase(scan, end, free)
#else /* GC_JONKERS_SEPARATE_META */
static inline void scan_second_region_ufr_phase(uintptr_t scan, uintptr_t end, uintptr_t free)
{
  while (scan < end) {
    header_t *hdrp = (header_t *) scan;

    /* skip free */
    if (!get_threaded_header_markbit(hdrp)) {
      const size_t size = get_merged_garbage_size(hdrp);
      scan += size << LOG_BYTES_IN_GRANULE;
      assert(scan <= end);
      continue;
    }

    /* process live object */
    assert((uintptr_t) hdrp < end);
    assert(get_threaded_header_markbit(hdrp));
    void *from = header_to_payload(hdrp);
    header_t *to_hdrp = (header_t *) free;
    void *to = header_to_payload(to_hdrp);

#ifdef GC_DEBUG_SHADOW
    if (get_threaded_header(hdrp).size > 1) {
      header_t **shadow = (header_t **) &(((header_t *) get_shadow(hdrp))[1]);
      *shadow = to_hdrp;
      header_t raw = get_threaded_header(hdrp);
      header_t cpy = *((header_t *) get_shadow(hdrp));
      assert(raw.identifier == 1);
      assert(cpy.identifier == 1);
      assert(cpy.markbit == 0); cpy.markbit = 1;
      assert(raw.threaded == cpy.threaded);
    }
#endif /* GC_DEBUG_SHADOW */

    header_t hdr = get_threaded_header(hdrp);
    uintjsv_t tag = get_ptag_value_by_cell_type(hdr.type);
    update_reference(tag, from, to);
    size_t size = hdrp->size;

    if (is_hidden_class(hdr.type)) {
      process_node<ThreadTracer>((uintptr_t) from);
    }

    free += size << LOG_BYTES_IN_GRANULE;
    scan += size << LOG_BYTES_IN_GRANULE;
  }
}
#endif /* GC_JONKERS_SEPARATE_META */

#ifdef GC_JONKERS_USING_QUEUE
static inline void scan_second_region_mix_ufr_phase(uintptr_t hcr, uintptr_t& hcrec)
{
  while (hcr < hcrec) {
    struct hcrecord *p = (struct hcrecord *) hcr;
    header_t *hdrp = p->hdrp;
    void *to = p->to;

    assert(get_threaded_header_markbit(hdrp));
    void *from = header_to_payload(hdrp);

    header_t hdr = get_threaded_header(hdrp);
    uintjsv_t tag = get_ptag_value_by_cell_type(hdr.type);
    update_reference(tag, from, to);

    process_node<ThreadTracer>((uintptr_t) from);
    hcr += sizeof(struct hcrecord);
  }
}
#endif /* GC_JONKERS_USING_QUEUE */

#ifndef GC_JONKERS_SEPARATE_META
static inline void scan_pre_first_region_mix_ubr_phase(uintptr_t scan, uintptr_t end, uintptr_t free)
{
  while (scan < end) {
    header_t *hdrp = (header_t *) scan;
    size_t size;

    if (get_threaded_header_markbit(hdrp)) {
      void *from = header_to_payload(hdrp);
      header_t *to_hdrp = (header_t *) free;
      void *to = header_to_payload(to_hdrp);

#ifdef GC_DEBUG_SHADOW
      if (get_threaded_header(hdrp).size > 1) {
        header_t **shadow = (header_t **) &(((header_t *) get_shadow(hdrp))[1]);
        assert(*shadow == to_hdrp);
      }
#endif /* GC_DEBUG_SHADOW */
      header_t hdr = get_threaded_header(hdrp);
      uintjsv_t tag = get_ptag_value_by_cell_type(hdr.type);
      update_reference(tag, from, to);
      size = hdrp->size;
      free += size << LOG_BYTES_IN_GRANULE;
    } else
      size = get_merged_garbage_size(hdrp);

    scan += size << LOG_BYTES_IN_GRANULE;
  }
}
#endif /* !GC_JONKERS_SEPARATE_META */

static inline void scan_first_region_ubr_phase(uintptr_t scan, uintptr_t end, uintptr_t &free)
{
  while (scan < end) {
    header_t *hdrp = (header_t *) scan;
    size_t size;

    if (get_threaded_header_markbit(hdrp)) {
      header_t *to_hdrp = (header_t *) free;
#ifndef GC_JONKERS_USING_QUEUE
      void *to = header_to_payload(to_hdrp);
      void *from = header_to_payload(hdrp);
#endif /* !GC_JONKERS_USING_QUEUE */

#ifdef GC_DEBUG_SHADOW
      if (get_threaded_header(hdrp).size > 1) {
        header_t **shadow = (header_t **) &(((header_t *) get_shadow(hdrp))[1]);
        assert(*shadow == to_hdrp);
      }
#endif /* GC_DEBUG_SHADOW */
#ifndef GC_JONKERS_USING_QUEUE
      header_t hdr = get_threaded_header(hdrp);
      uintjsv_t tag = get_ptag_value_by_cell_type(hdr.type);
      update_reference(tag, from, to);
#endif /* !GC_JONKERS_USING_QUEUE */
      size = hdrp->size;
      unmark_cell_header(hdrp);
      copy_object(hdrp, to_hdrp, size);
#ifdef GC_DEBUG_SHADOW
      {
        header_t *shadow = get_shadow(to_hdrp);
        *shadow = *to_hdrp;
	if (hdrp->size > 1)
	  *((void **) (&(shadow[1]))) = header_to_payload(hdrp);
      }
#endif /* GC_DEBUG_SHADOW */
      free += size << LOG_BYTES_IN_GRANULE;
    } else
      size = get_merged_garbage_size(hdrp);

    scan += size << LOG_BYTES_IN_GRANULE;
  }
}

#ifdef GC_JONKERS_SEPARATE_META
#define scan_second_region_ubr_phase(scan, end, free) \
    scan_first_region_ubr_phase(scan, end, free)
#endif /* GC_JONKERS_SEPARATE_META */


#endif /* JONKERS_COLLECTOR_INL_H */
