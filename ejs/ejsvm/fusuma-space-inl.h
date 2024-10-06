#ifndef FUSUMA_SPACE_INL_H
#define FUSUMA_SPACE_INL_H

static inline header_t
compose_hidden_class_header(size_t granules, cell_type_t type)
{
  header_t hdr;
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
#ifdef GC_FUSUMA_BOUNDARY_TAG
  hdr.hc.size_hi = 0;
#endif /* GC_FUSUMA_BOUNDARY_TAG */
  hdr.hc.size_lo = granules;
  return hdr;
}

#ifdef GC_FUSUMA_BOUNDARY_TAG
static inline void write_boundary_tag(uintptr_t alloc_end, size_t granules)
{
  header_t *hdrp = (header_t *) alloc_end;
  assert(granules <= BOUNDARY_TAG_MAX_SIZE);
  assert(hdrp->identifier == 1);
  hdrp->hc.size_hi = granules;
}
static inline size_t read_boundary_tag(uintptr_t alloc_end)
{
  header_t *hdrp = (header_t *) alloc_end;
  return hdrp->hc.size_hi;
}
#else /* GC_FUSUMA_BOUNDARY_TAG */
static inline void write_boundary_tag(uintptr_t alloc_end, size_t granules)
{
  granule_t *tagp = (granule_t *) alloc_end;
  *tagp = granules;
}
static inline size_t read_boundary_tag(uintptr_t alloc_end)
{
  granule_t *tagp = (granule_t *) alloc_end;
  return *tagp;
}
#endif /* GC_FUSUMA_BOUNDARY_TAG */

static inline void check_header(header_t *hdrp)
{
#ifdef GC_DEBUG_SHADOW
  {
    header_t *shadow = get_shadow(hdrp);
    assert(hdrp->identifier == 1);
#if HEADER_MAGIC_BITS > 0
    assert(hdrp->magic == HEADER_MAGIC);
#endif /* HEADER_MAGIC_BITS */
    assert(hdrp->type == shadow->type);

#ifdef GC_FUSUMA_BOUNDARY_TAG
    if (in_hc_space(hdrp))
      assert(hdrp->hc.size_lo == shadow->hc.size_lo);
    else
      assert(hdrp->size == shadow->size);
#else /* GC_FUSUMA_BOUNDARY_TAG */
    assert(hdrp->size == shadow->size);
#endif /* GC_FUSUMA_BOUNDARY_TAG */

#if HEADER_GEN_BITS > 0
    assert(hdrp->gen == shadow->gen);
#endif /* HEADER_GEN_BITS */
  }
#endif /* GC_DEBUG_SHADOW */
}


#endif /* FUSUMA_SPACE_INL_H */
