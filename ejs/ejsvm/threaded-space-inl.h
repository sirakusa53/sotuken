#ifndef THREADED_SPACE_INL_H
#define THREADED_SPACE_INL_H

static inline header_t compose_header(size_t granules, cell_type_t type)
{
  header_t hdr;
  assert(granules < (1LL << HEADER_SIZE_BITS));
  hdr.identifier = 1;
  hdr.type = type;
  hdr.markbit = 0;
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
  return (js_space.head <= addr && addr < js_space.tail);
}

static inline int in_obj_space(void *addr_)
{
  uintptr_t addr = (uintptr_t) addr_;
  return (js_space.head <= addr && addr <= js_space.begin);
}

static inline int in_hc_space(void *addr_)
{
  uintptr_t addr = (uintptr_t) addr_;
  return (js_space.end <= addr && addr < js_space.tail);
}

#ifdef USE_EMBEDDED_INSTRUCTION
static inline int in_mbed_flash(void *addr_)
{
  extern uintptr_t __ejs_constants_end;

  uintptr_t addr = (uintptr_t) addr_;
  uintptr_t begin = (uintptr_t) 0;
  uintptr_t end = (uintptr_t) &__ejs_constants_end;

  return (begin <= addr && addr < end);
}
#endif /* USE_EMBEDDED_INSTRUCTION */

static inline bool is_hidden_class(cell_type_t type)
{
  switch(type) {
  case CELLT_HASHTABLE:
  case CELLT_TRANSITIONS:
  case CELLT_PROPERTY_MAP:
  case CELLT_SHAPE:
  case CELLT_PROPERTY_MAP_LIST:
    return true;
  default:
    return false;
  }
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
  if (is_marked_cell_header(hdrp))
    return 1;
  mark_cell_header(hdrp);
  return 0;
}

static inline void mark_cell_header(header_t *hdrp)
{
  hdrp->markbit = 1;
}

static inline void unmark_cell_header(header_t *hdrp)
{
  hdrp->markbit = 0;
}

static inline int is_marked_cell_header(header_t *hdrp)
{
  assert(hdrp->identifier == 1);
  return hdrp->markbit;
}

#endif /* THREADED_SPACE_INL_H */
