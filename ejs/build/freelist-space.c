/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include "prefix.h"
#define EXTERN extern
#include "header.h"

/*
 * If the remaining room is smaller than a certain size,
 * we do not use the remainder for efficiency.  Rather,
 * we add it below the chunk being allocated.  In this case,
 * the size in the header includes the extra words.
 *
 * MINIMUM_FREE_CHECK_GRANULES >= HEADER_GRANULES + roundup(pointer granules)
 * MINIMUM_FREE_CHUNK_GRANULES <= 2^HEADER_EXTRA_BITS
 */
#define MINIMUM_FREE_CHUNK_GRANULES 4

/*
 * Variables
 */
struct space js_space;
#ifdef GC_DEBUG_SHADOW
STATIC struct space debug_js_shadow;
#endif /* GC_DEBUG_SHADOW */

/*
 * prototype
 */
/* space */
STATIC void create_space(struct space *space, size_t bytes, size_t threshold_bytes, const char *name);
#ifdef GC_DEBUG_SHADOW
STATIC header_t *get_shadow(void *ptr);
#endif /* GC_DEBUG_SHADOW */
/* GC */
#ifdef GC_DEBUG
STATIC void check_invariant(void);
STATIC void print_memory_status(void);
#endif /* GC_DEBUG */


/*
 * Header operation
 */

STATIC_INLINE size_t get_payload_granules(header_t *hdrp) __attribute((unused));
STATIC_INLINE size_t get_payload_granules(header_t *hdrp)
{
  header_t hdr = *hdrp;
  return hdr.size - hdr.extra - HEADER_GRANULES;
}

/*
 * utility
 */
STATIC_INLINE struct free_chunk **
freelist_append_free_chunk(struct free_chunk **p, uintptr_t free_start,
                           size_t chunk_granules)
{
  while (chunk_granules > MAX_CHUNK_GRANULES + MINIMUM_FREE_CHUNK_GRANULES) {
    struct free_chunk *chunk = (struct free_chunk *) free_start;
    chunk->header = compose_header(MAX_CHUNK_GRANULES, 0, CELLT_FREE);
    *p = chunk;
    p = &chunk->next;
    free_start += MAX_CHUNK_GRANULES << LOG_BYTES_IN_GRANULE;
    chunk_granules -= MAX_CHUNK_GRANULES;
#ifdef GC_DEBUG
    {
      char *p;
      for (p = (char *) (chunk + 1); p < (char *) free_start; p++)
        *p = 0xcc;
    }
#endif /* GC_DEBUG */
  }
  if (chunk_granules > MAX_CHUNK_GRANULES) {
    struct free_chunk *chunk = (struct free_chunk *) free_start;
    chunk->header = compose_header(MINIMUM_FREE_CHUNK_GRANULES, 0, CELLT_FREE);
    *p = chunk;
    p = &chunk->next;
    free_start += MINIMUM_FREE_CHUNK_GRANULES << LOG_BYTES_IN_GRANULE;
    chunk_granules -= MINIMUM_FREE_CHUNK_GRANULES;
#ifdef GC_DEBUG
    {
      char *p;
      for (p = (char *) (chunk + 1); p < (char *) free_start; p++)
        *p = 0xcc;
    }
#endif /* GC_DEBUG */
  }
  assert(chunk_granules >= MINIMUM_FREE_CHUNK_GRANULES); {
    struct free_chunk *chunk = (struct free_chunk *) free_start;
    chunk->header = compose_header(chunk_granules, 0, CELLT_FREE);
    *p = chunk;
    p = &chunk->next;
#ifdef GC_DEBUG
    {
      char *p;
      free_start += chunk_granules << LOG_BYTES_IN_GRANULE;
      for (p = (char *) (chunk + 1); p < (char *) free_start; p++)
        *p = 0xcc;
    }
#endif /* GC_DEBUG */
  }
  return p;
}

/*
 *  Space
 */
STATIC void create_space(struct space *space, size_t bytes, size_t threshold_bytes, const char *name)
{
  uintptr_t addr;
  struct free_chunk **p;
#ifdef USE_MBED
  addr = (uintptr_t) &__jsheap_start;
#else /* USE_MBED */
  addr = (uintptr_t) malloc(bytes + BYTES_IN_GRANULE - 1);
#endif /* USE_MBED */
  space->addr = (addr + BYTES_IN_GRANULE - 1) & ~(BYTES_IN_GRANULE - 1);
  space->bytes = bytes;
  space->free_bytes = bytes;
  p = freelist_append_free_chunk(&space->freelist, space->addr,
                                 bytes >> LOG_BYTES_IN_GRANULE);
  *p = NULL;
  space->threshold_bytes = threshold_bytes;
  space->name = name;
}

#ifdef GC_DEBUG_SHADOW
header_t *get_shadow(void *ptr)
{
  if (in_js_space(ptr)) {
    uintptr_t a = (uintptr_t) ptr;
    uintptr_t off = a - js_space.addr;
    return (header_t *) (debug_js_shadow.addr + off);
  } else
    return NULL;
}
#endif /* GC_DEBUG_SHADOW */

/*
 * Returns a pointer to the first address of the memory area
 * available to the VM.  The header precedes the area.
 * The header has the size of the chunk including the header,
 * the area available to the VM, and extra bytes if any.
 * Other header bits are zero
 */
STATIC_INLINE void* js_space_alloc(struct space *space,
                                   size_t request_bytes, cell_type_t type)
{
  size_t  alloc_granules;
  struct free_chunk **p;
  
  alloc_granules = BYTE_TO_GRANULE_ROUNDUP(request_bytes);
  alloc_granules += HEADER_GRANULES;

  /* allocate from freelist */
  for (p = &space->freelist; *p != NULL; p = &(*p)->next) {
    struct free_chunk *chunk = *p;
    size_t chunk_granules = chunk->header.size;
    if (chunk_granules >= alloc_granules) {
      if (chunk_granules >= alloc_granules + MINIMUM_FREE_CHUNK_GRANULES) {
        /* This chunk is large enough to leave a part unused.  Split it */
        size_t remaining_granules = chunk_granules - alloc_granules;
        header_t *hdrp = (header_t *)
          (((uintptr_t) chunk) + (remaining_granules << LOG_BYTES_IN_GRANULE));
        *hdrp = compose_header(alloc_granules, 0, type);
        chunk->header.size = remaining_granules;
        space->free_bytes -= alloc_granules << LOG_BYTES_IN_GRANULE;
        return header_to_payload(hdrp);
      } else {
        /* This chunk is too small to split. */
        header_t *hdrp = (header_t *) chunk;
        *p = (*p)->next;
        *hdrp = compose_header(chunk_granules,
                               chunk_granules - alloc_granules, type);
        space->free_bytes -= chunk_granules << LOG_BYTES_IN_JSVALUE;
        return header_to_payload(hdrp);
      }
    }
  }

#ifdef DEBUG
  {
    struct free_chunk *chunk;
    for (chunk = space->freelist; chunk != NULL; chunk = chunk->next)
      LOG(" %u", chunk->header.size * BYTES_IN_GRANULE);
  }
  LOG("\n");
  LOG("js_space.bytes = %zu\n", js_space.bytes);
  LOG("js_space.free_bytes = %zu\n", js_space.free_bytes);
  LOG("request = %zu\n", request_bytes);
  LOG("type = 0x%x\n", type);
  LOG("memory exhausted\n");
#endif /* DEBUG */
  return NULL;
}


/*
 * GC interface
 */

void space_init(size_t bytes, size_t threshold_bytes)
{
  create_space(&js_space, bytes, threshold_bytes, "js_space");
#ifdef GC_DEBUG_SHADOW
  create_space(&debug_js_shadow, bytes, threshold_bytes, "debug_js_shadow");
#endif /* GC_DEBUG_SHADOW */
}

void* space_alloc(uintptr_t request_bytes, cell_type_t type)
{
  void* addr = js_space_alloc(&js_space, request_bytes, type);
#ifdef GC_DEBUG_SHADOW
  if (addr != NULL) {
    header_t *hdrp = payload_to_header(addr);
    header_t *shadow = get_shadow(hdrp);
    *shadow = *hdrp;
  }
#endif /* GC_DEBUG_SHADOW */
  return addr;
}

/*
 * GC
 */

STATIC void sweep_space(struct space *space)
{
  struct free_chunk **p;
  uintptr_t scan = space->addr;
  uintptr_t free_bytes = 0;

  space->freelist = NULL;
  p = &space->freelist;
  while (scan < space->addr + space->bytes) {
    uintptr_t last_used = 0;
    uintptr_t free_start;
    /* scan used area */
    while (scan < space->addr + space->bytes &&
           is_marked_cell_header((header_t *) scan)) {
      header_t *hdrp = (header_t *) scan;
#if HEADER_MAGIC_BITS > 0
      assert(hdrp->magic == HEADER_MAGIC);
#endif /* HEADER_MAGIC_BITS */
#ifdef GC_PROF
      {
        cell_type_t type = hdrp->type;
        size_t bytes =
          (hdrp->size - hdrp->extra) << LOG_BYTES_IN_GRANULE;
        pertype_live_bytes[type]+= bytes;
        pertype_live_count[type]++;
      }
#endif /* GC_PROF */
      unmark_cell_header((header_t *) scan);
      last_used = scan;
      scan += hdrp->size << LOG_BYTES_IN_GRANULE;
    }
    free_start = scan;
    while (scan < space->addr + space->bytes &&
           !is_marked_cell_header((header_t *) scan)) {
      header_t *hdrp = (header_t *) scan;
#if HEADER_MAGIC_BITS > 0
      assert(hdrp->magic == HEADER_MAGIC);
#endif /* HEADER_MAGIC_BITS */
#ifdef GC_PROF
      {
        cell_type_t type = hdrp->type;
        size_t bytes =
          (hdrp->size - hdrp->extra) << LOG_BYTES_IN_GRANULE;
        pertype_collect_bytes[type]+= bytes;
        pertype_collect_count[type]++;
      }
#endif /* GC_PROF */
      scan += hdrp->size << LOG_BYTES_IN_GRANULE;
    }
    if (free_start < scan) {
      size_t chunk_granules;
      if (last_used != 0) {
        /* Previous chunk may have extra bytes. Take them back. */
        header_t *last_hdrp = (header_t *) last_used;
        size_t extra = last_hdrp->extra;
        free_start -= extra << LOG_BYTES_IN_GRANULE;
        last_hdrp->size -= extra;
        last_hdrp->extra = 0;
      }
      chunk_granules = (scan - free_start) >> LOG_BYTES_IN_GRANULE;
      if (chunk_granules >= MINIMUM_FREE_CHUNK_GRANULES) {
        p = freelist_append_free_chunk(p, free_start, chunk_granules);
        free_bytes += scan - free_start;
      } else  {
        /* Too small to make a chunk.
         * Append it at the end of previous chunk, if any */
        if (last_used != 0) {
          header_t *last_hdrp = (header_t *) last_used;
          assert(last_hdrp->extra == 0);
          last_hdrp->size += chunk_granules;
          last_hdrp->extra = chunk_granules;
        } else
          *(header_t *) free_start =
            compose_header(chunk_granules, 0, CELLT_FREE);
      }
    }
  }
  (*p) = NULL;
  space->free_bytes = free_bytes;
}

void sweep(void)
{
#ifdef GC_DEBUG
  check_invariant();
#endif /* GC_DEBUG */
  sweep_space(&js_space);
}

#ifdef GC_DEBUG
#define OFFSET_OF(T, F) (((uintptr_t) &((T *) 0)->F) >> LOG_BYTES_IN_JSVALUE)

STATIC void check_invariant_nobw_space(struct space *space)
{
  uintptr_t scan = space->addr;

  while (scan < space->addr + space->bytes) {
    header_t *hdrp = (header_t *) scan;
    uintptr_t payload = (uintptr_t) header_to_payload(hdrp);
    uintptr_t next_scan;
    switch (hdrp->type) {
    case CELLT_STRING:
    case CELLT_FLONUM:
    case CELLT_ARRAY_DATA:
    case CELLT_HASHTABLE:
    /* case CELLT_HASH_CELL: */ // No longer used
      break;
    case CELLT_PROPERTY_MAP:
      {
        PropertyMap *pm = (PropertyMap *) payload;
        Shape *os;
        if (is_pm_ordinary(pm)) {
          for (os = pm->u.ord.shapes; os != NULL; os = os->next)
            assert(payload_to_header(os)->type == CELLT_SHAPE);
        }
        goto DEFAULT;
      }
    default:
    DEFAULT:
      if (is_marked_cell_header(hdrp)) {
        /* this object is black; should not contain a pointer to white */
        size_t payload_bytes =
          get_payload_granules(hdrp) << LOG_BYTES_IN_GRANULE;
        size_t i;
#if BYTES_IN_JSVALUE >= BYTES_IN_GRANULE
#define STEP_BYTES BYTES_IN_GRANULE
#else
#define STEP_BYTES BYTES_IN_JSVALUE
#endif
        for (i = 0; i < payload_bytes; i += STEP_BYTES) {
          JSValue v = *(JSValue *) (payload + i);
          uintjsv_t x = (uintjsv_t) v;
          void * p = (void *) (uintptr_t) clear_ptag(v);
          /* weak pointers */
          /*
          if (HEADER0_GET_TYPE(header) == CELLT_STR_CONS) {
            if (i == OFFSET_OF(StrCons, str))
              continue;
          }
          */
          if (IS_POINTER_LIKE_UINTJSV(x) &&
              (has_htag(x) || get_ptag(x).v == 0) &&
              in_js_space(p))
            assert(is_marked_cell(p));
        }
      }
      break;
    }

    next_scan = scan + (hdrp->size << LOG_BYTES_IN_GRANULE);
    if (next_scan < space->addr + space->bytes)
      assert(((header_t *)next_scan)->magic == HEADER_MAGIC);
    scan = next_scan;
  }
}

STATIC void check_invariant(void)
{
  check_invariant_nobw_space(&js_space);
}

STATIC void print_free_list(void)
{
  struct free_chunk *p;
  for (p = js_space.freelist; p; p = p->next)
    printf("%d ", p->header.size * BYTES_IN_GRANULE);
  printf("\n");
}

#endif /* GC_DEBUG */

#ifdef GC_DEBUG
STATIC void space_print_memory_status(void)
{
  printf("  free_bytes = %zu\n", js_space.free_bytes);
}
#endif /* GC_DEBUG */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
