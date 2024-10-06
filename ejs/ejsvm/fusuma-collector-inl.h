/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef FUSUMA_COLLECTOR_INL_H
#define FUSUMA_COLLECTOR_INL_H


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
static void copy_object_reverse(uintptr_t from,
				uintptr_t from_end, uintptr_t to_end);

#ifdef GC_FUSUMA_BOUNDARY_TAG
static inline uintptr_t make_free_cell(uintptr_t end, size_t granules)
{
  uintptr_t p = end - (granules << LOG_BYTES_IN_GRANULE);
  header_t *hdrp = (header_t *) p;
  *hdrp = compose_hidden_class_header(granules, CELLT_FREE);
#ifdef GC_DEBUG_SHADOW
  {
    header_t *shadow = get_shadow(hdrp);
    *shadow = *hdrp;
  }
#endif /* GC_DEBUG_SHADOW */
  write_boundary_tag(end, granules);
  return p;
}
#endif /* GC_FUSUMA_BOUNDARY_TAG */

static inline void
merge_free_space_in_hidden_class_area(uintptr_t start, uintptr_t end,
				      uintptr_t first_free)
{
  /*
   *  do merge
   *  start                  first   end
   *   | free  | free  | free | free |
   *
   *  do not merge (1): single free cell
   *  first == start          end
   *   |         free          |
   *
   *  do not merge (2): no free cell
   *  first                   end == start
   *   |         live          |
   */
  if (first_free <= start)
    return;
  size_t bytes = end - start;
  size_t granules = bytes >> LOG_BYTES_IN_GRANULE;
#ifdef GC_FUSUMA_BOUNDARY_TAG
  if (granules > BOUNDARY_TAG_MAX_SIZE) {
    while (end - start >
	   ((BOUNDARY_TAG_MAX_SIZE + HEADER_GRANULES) <<
	    LOG_BYTES_IN_GRANULE))
      end = make_free_cell(end, BOUNDARY_TAG_MAX_SIZE);
    if (end - start > BOUNDARY_TAG_MAX_SIZE)
      end = make_free_cell(end, HEADER_GRANULES);
    granules = (end - start) >> LOG_BYTES_IN_GRANULE;
  }
#endif /* BOUNDARY_TAG_MAX_SIZE */
  header_t *hdrp = (header_t *) start;
  hdrp->hc.size_lo = granules;
  write_boundary_tag(end, granules);
}

static inline void
merge_free_space_in_ordinary_area(uintptr_t start, uintptr_t end);

/* Defined at threadedcompactor-collector.cc */
static inline int skip_and_merge_garbage_in_ordinary_area(uintptr_t &scan, uintptr_t end);
static inline size_t get_merged_garbage_size(header_t *hdrp);

static inline uintptr_t get_first_region_scan(void) { return js_space.head; }
static inline uintptr_t get_first_region_end(void) { return js_space.begin; }
static inline uintptr_t get_first_region_free(uintptr_t scan, uintptr_t /* end */ ) { return scan; }
static inline void set_first_region_end(uintptr_t /* scan */, uintptr_t /* end */, uintptr_t free) { js_space.begin = free; }

static inline uintptr_t get_second_region_scan(void) {
  uintptr_t scan = js_space.tail;
#ifdef GC_FUSUMA_BOUNDARY_TAG
  /* There is an object header at the end of the heap, holding the
   * size of the last object */
  scan -= HEADER_GRANULES << LOG_BYTES_IN_GRANULE;
#endif /* GC_FUSUMA_BOUNDARY_TAG */
  return scan;
}
static inline uintptr_t get_second_region_end(void) { return js_space.end; }
static inline uintptr_t get_second_region_free(uintptr_t scan, uintptr_t /* end */ ) { return scan; }
static inline void set_second_region_end(uintptr_t /* scan */, uintptr_t /* end */, uintptr_t free) { js_space.end = free; }

static inline void update_space_free_bytes() {
  js_space.free_bytes = js_space.end - js_space.begin;
}

static inline void scan_first_region_ufr_phase(
  uintptr_t scan, uintptr_t end, uintptr_t free
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

    {
      process_node<ThreadTracer>((uintptr_t) from);
    }

    free += size << LOG_BYTES_IN_GRANULE;
    scan += size << LOG_BYTES_IN_GRANULE;
  }
}

static inline void scan_second_region_ufr_phase(uintptr_t scan, uintptr_t end, uintptr_t free)
{
  while (scan > end) {
    /*
     * In this loop, scan, size, and hdrp are updated nimultaneously
     * so that they hold:
     *   hdrp             scan
     *    V                V
     *   |hd|   payload   |bt|
     *    <---  size  --->
     */

    scan -= BOUNDARY_TAG_GRANULES << LOG_BYTES_IN_GRANULE;
    size_t size = read_boundary_tag(scan);
    header_t *hdrp = (header_t *) (scan - (size << LOG_BYTES_IN_GRANULE));

    /* skip free/garbage */
    uintptr_t free_end = scan;
    uintptr_t first_free = (uintptr_t) hdrp;
    uintptr_t last_free = scan;
    while (!is_reference(*(void ***) hdrp) && !is_marked_cell_header(hdrp)) {
      COUNT_DEAD_OBJECT(*hdrp, size);
      scan = (uintptr_t) hdrp;
      last_free = scan;
      assert(scan >= end);
      if (scan == end) {
	merge_free_space_in_hidden_class_area(last_free, free_end, first_free);
	return;
      }
      scan -= BOUNDARY_TAG_GRANULES << LOG_BYTES_IN_GRANULE;
      size = read_boundary_tag(scan);
      hdrp = (header_t *) (scan - (size << LOG_BYTES_IN_GRANULE));
    }
    merge_free_space_in_hidden_class_area(last_free, free_end, first_free);

    /* process live object */
    assert(((uintptr_t) hdrp) >= end);
    assert(get_threaded_header_markbit(hdrp));
    COUNT_LIVE_OBJECT(get_threaded_header(hdrp), size);
    free -= (size + BOUNDARY_TAG_GRANULES) << LOG_BYTES_IN_GRANULE;
    void *from = header_to_payload(hdrp);
    header_t *to_hdrp = (header_t *) free;
    void *to = header_to_payload(to_hdrp);
#ifdef GC_DEBUG_SHADOW
    if (size > 1) {
      header_t **shadow = (header_t **) &(((header_t *) get_shadow(hdrp))[1]);
      *shadow = to_hdrp;
    }
#endif /* GC_DEBUG_SHADOW */
    update_reference(0, from, to);
    process_node<ThreadTracer>((uintptr_t) from);
    scan = (uintptr_t) hdrp;
  }

#ifdef GC_FUSUMA_BOUNDARY_TAG
  assert(read_boundary_tag(scan) == 0);
#endif /* GC_FUSUMA_BOUNDARY_TAG */
}

static inline void scan_first_region_ubr_phase(uintptr_t scan, uintptr_t end, uintptr_t &free)
{
  while (scan < end) {
    header_t *hdrp = (header_t *) scan;
    size_t size;

    if (get_threaded_header_markbit(hdrp)) {
      header_t *to_hdrp = (header_t *) free;
      void *to = header_to_payload(to_hdrp);
      void *from = header_to_payload(hdrp);

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

static inline void scan_second_region_ubr_phase(uintptr_t scan, uintptr_t end,  uintptr_t &free)
{
  while (scan > end) {
    /* skip boundary tag */
    scan -= BOUNDARY_TAG_GRANULES << LOG_BYTES_IN_GRANULE;
    /* scan points to the next address of the last byte of the object */
    size_t size = read_boundary_tag(scan);
    header_t *hdrp = (header_t *) (scan - (size << LOG_BYTES_IN_GRANULE));

    if (get_threaded_header_markbit(hdrp)) {
      free -= BOUNDARY_TAG_GRANULES << LOG_BYTES_IN_GRANULE;
      header_t *to_hdrp = (header_t *) (free - (size << LOG_BYTES_IN_GRANULE));
      void *from = header_to_payload(hdrp);
      void *to = header_to_payload(to_hdrp);
#ifdef GC_DEBUG_SHADOW
      if (size > 1) {
        header_t **shadow = (header_t **) &(((header_t *) get_shadow(hdrp))[1]);
        assert(*shadow == to_hdrp);
      }
#endif /* GC_DEBUG_SHADOW */
      update_reference(0, from, to);
      copy_object_reverse((uintptr_t) hdrp, scan, free);
      unmark_cell_header(to_hdrp);
      write_boundary_tag(free, size);
#ifdef GC_DEBUG_SHADOW
      {
        header_t *shadow = get_shadow(to_hdrp);
        *shadow = *to_hdrp;
	if (hdrp->size > 1)
	  ((uintptr_t *)shadow)[1] = (uintptr_t) from;
      }
#endif /* GC_DEBUG_SHADOW */
      free = (uintptr_t) to_hdrp;
    }
    scan = (uintptr_t) hdrp;
  }

#ifdef GC_FUSUMA_BOUNDARY_TAG
  assert(read_boundary_tag(scan) == 0);
  write_boundary_tag(free, 0);
#endif /* GC_FUSUMA_BOUNDARY_TAG */
}

static void copy_object_reverse(uintptr_t from,
				uintptr_t from_end, uintptr_t to_end)
{
  if (from_end == to_end)
    return;
  granule_t *p = (granule_t *) from_end;
  granule_t *q = (granule_t *) to_end;
  granule_t *end = (granule_t *) from;
  while(end < p)
    *--q = *--p;
}


#endif /* FUSUMA_COLLECTOR_INL_H */
