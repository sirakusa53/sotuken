#ifndef FREELIST_SPACE_INL_H
#define FREELIST_SPACE_INL_H

static inline header_t compose_header(size_t granules, size_t extra,
                                      cell_type_t type)
{
  header_t hdr;
  hdr.type = type;
  hdr.markbit = 0;
  hdr.extra = extra;
#if HEADER_MAGIC_BITS > 0
  hdr.magic = HEADER_MAGIC;
#endif /* HEADER_MAGIC_BITS */
#if HEADER_GEN_BITS > 0
#ifdef GC_DEBUG
  hdr.gen = generation;
#else /* GC_DEBUG */
  hdr.gen = 0;
#endif /* GC_DEBUG */
#endif /* HEADER_GEN_BITS */
  hdr.size  = granules;
  return hdr;
}

static inline void *header_to_payload(header_t *hdrp)
{
  return (void *) (hdrp + 1);
}

static inline header_t *payload_to_header(void *ptr)
{
  return ((header_t *) ptr) - 1;
}

static inline int in_js_space(void *addr_)
{
  uintptr_t addr = (uintptr_t) addr_;
  return (js_space.addr <= addr && addr < js_space.addr + js_space.bytes);
}

static inline cell_type_t space_get_cell_type(uintptr_t ptr)
{
  return payload_to_header((void *) ptr)->type;
}

static inline int space_check_gc_request()
{
  return (js_space.free_bytes < js_space.threshold_bytes);
}

static inline void mark_cell(void *p)
{
  header_t *hdrp = payload_to_header(p);
  mark_cell_header(hdrp);
}

static inline void unmark_cell (void *p) __attribute__((unused));
static inline void unmark_cell (void *p)
{
  header_t *hdrp = payload_to_header(p);
  unmark_cell_header(hdrp);
}

static inline int is_marked_cell(void *p)
{
  header_t *hdrp = payload_to_header(p);
  return is_marked_cell_header(hdrp);
}

static inline int test_and_mark_cell(void *p)
{
  header_t *hdrp;
  assert(in_js_space(p));
  hdrp = payload_to_header(p);
  if (is_marked_cell_header(hdrp)) {
    return 1;
  }
  mark_cell_header(hdrp);
  return 0;
}

static inline void mark_cell_header(header_t *hdrp)
{
#ifdef GC_DEBUG_SHADOW
  {
    header_t *shadow = get_shadow(hdrp);
#if HEADER_MAGIC_BITS > 0
    assert(hdrp->magic == HEADER_MAGIC);
#endif /* HEADER_MAGIC_BITS */
    assert(hdrp->type == shadow->type);
    assert(hdrp->size - hdrp->extra ==
           shadow->size - shadow->extra);
#if HEADER_GEN_BITS > 0
    assert(hdrp->gen == shadow->gen);
#endif /* HEADER_GEN_BITS */
  }
#endif /* GC_DEBUG_SHADOW */
  hdrp->markbit = 1;
}

static inline void unmark_cell_header(header_t *hdrp)
{
  hdrp->markbit = 0;
}

static inline int is_marked_cell_header(header_t *hdrp)
{
  return hdrp->markbit;
}

#endif /* FREELIST_SPACE_INL_H */
