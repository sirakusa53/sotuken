#ifndef LISP2_SPACE_INL_H
#define LISP2_SPACE_INL_H

#if 0
static inline header_t compose_header(size_t granules, cell_type_t type)
{
  header_t hdr;
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
  hdr.fwd = NULL;
  return hdr;
}
#else /* 0 */
static inline void compose_header(header_t *hdrp, size_t granules, cell_type_t type)
{
  hdrp->type = type;
  hdrp->markbit = 0;
#if HEADER_MAGIC_BITS > 0
  hdrp->magic = HEADER_MAGIC;
#endif /* HEADER_MAGIC_BITS */
#if HEADER_GEN_BITS > 0
#ifdef GC_DEBUG
  hdrp->gen = generation;
#else /* GC_DEBUG */
  hdrp->gen = 0;
#endif /* GC_DEBUG */
#endif /* HEADER_GEN_BITS */
  hdrp->size  = granules;
  hdrp->fwd = NULL;
}
#endif /* 0 */

static inline void *header_to_payload(const header_t *hdrp)
{
  return (void *) (hdrp + 1);
}

static inline header_t *payload_to_header(const void *ptr)
{
  return ((header_t *) ptr) - 1;
}

static inline int in_js_space(const void *addr_)
{
  uintptr_t addr = (uintptr_t) addr_;
  return (js_space.begin <= addr && addr < js_space.end);
}

#ifdef USE_EMBEDDED_INSTRUCTION
static inline int in_mbed_flash(const void *addr_)
{
  extern uintptr_t __ejs_constants_end;

  uintptr_t addr = (uintptr_t) addr_;
  uintptr_t begin = (uintptr_t) 0;
  uintptr_t end = (uintptr_t) &__ejs_constants_end;

  return (begin <= addr && addr < end);
}
#endif /* USE_EMBEDDED_INSTRUCTION */

static inline cell_type_t space_get_cell_type(uintptr_t ptr)
{
  return payload_to_header((void *) ptr)->type;
}

static inline int is_hidden_class(cell_type_t type)
{
  switch(type) {
  case CELLT_HASHTABLE:
  case CELLT_TRANSITIONS:
  case CELLT_PROPERTY_MAP:
  case CELLT_SHAPE:
  case CELLT_PROPERTY_MAP_LIST:
    return 1;
  default:
    return 0;
  }
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

static inline int is_marked_cell(const void *p)
{
  const header_t *hdrp = payload_to_header(p);
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

static inline int is_marked_cell_header(const header_t *hdrp)
{
  return hdrp->markbit;
}

static inline void check_header(const header_t *hdrp)
{
#ifdef GC_DEBUG_SHADOW
  {
    const header_t *shadow = get_shadow(hdrp);
#if HEADER_MAGIC_BITS > 0
    assert(hdrp->magic == HEADER_MAGIC);
#endif /* HEADER_MAGIC_BITS */
    assert(hdrp->type == shadow->type);
    assert(hdrp->size == shadow->size);
#if HEADER_GEN_BITS > 0
    assert(hdrp->gen == shadow->gen);
#endif /* HEADER_GEN_BITS */
  }
#endif /* GC_DEBUG_SHADOW */
}

#endif /* LISP2_SPACE_INL_H */
