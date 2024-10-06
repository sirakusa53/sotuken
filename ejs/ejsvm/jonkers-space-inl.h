#ifndef JONKERS_SPACE_INL_H
#define JONKERS_SPACE_INL_H

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

    assert(hdrp->size == shadow->size);

#if HEADER_GEN_BITS > 0
    assert(hdrp->gen == shadow->gen);
#endif /* HEADER_GEN_BITS */
  }
#endif /* GC_DEBUG_SHADOW */
}


#endif /* JONKERS_SPACE_INL_H */
