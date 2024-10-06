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
 * Variables
 */

/*
 * prototype
 */


/*
 * Header operation
 */

/*
 *  Space
 */
void create_space(struct space *space, size_t bytes, size_t threshold_bytes, const char *name)
{
  uintptr_t addr;
#ifdef USE_MBED
  addr = (uintptr_t) &__jsheap_start;
#else /* USE_MBED */
  addr = (uintptr_t) malloc(bytes);
#endif /* USE_MBED */
  space->head = (uintptr_t) addr;
  space->begin = space->head;
  space->tail = (uintptr_t) addr + bytes;
  space->end = space->tail;
#ifdef GC_FUSUMA_BOUNDARY_TAG
  space->end -= HEADER_GRANULES << LOG_BYTES_IN_GRANULE;
  *((header_t *) space->end) = compose_hidden_class_header(0, CELLT_FREE);
  write_boundary_tag(space->end, 0);
#endif /* GC_FUSUMA_BOUNDARY_TAG */
  space->bytes = bytes;
  space->free_bytes = space->end - space->begin;
  space->threshold_bytes = threshold_bytes;
  space->name = name;
}

/*
 * Returns a pointer to the first address of the memory area
 * available to the VM. The header precedes the area.
 */
STATIC_INLINE void* js_space_alloc(struct space *space,
                                   size_t request_bytes, cell_type_t type)
{
#if LOG_BYTES_IN_GRANULE != LOG_BYTES_IN_JSVALUE
#error "LOG_BYTES_IN_JSVALUE != LOG_BYTES_IN_GRANULE"
#endif

  size_t alloc_granules =
    BYTE_TO_GRANULE_ROUNDUP(request_bytes) + HEADER_GRANULES;
  size_t bytes = (alloc_granules << LOG_BYTES_IN_GRANULE);
  header_t *hdrp;

  if (!is_hidden_class(type)) {
    uintptr_t next = space->begin + bytes;
    if (next > space->end)
      goto js_space_alloc_out_of_memory;
    hdrp = (header_t *) space->begin;
    space->begin = next;
    *hdrp = compose_header(alloc_granules, type);
  }
  else
  {
    uintptr_t alloc_end =
      space->end - (BOUNDARY_TAG_GRANULES << LOG_BYTES_IN_GRANULE);
    hdrp = (header_t *) (alloc_end - bytes);
    if (space->begin > (uintptr_t) hdrp)
      goto js_space_alloc_out_of_memory;
    space->end = (uintptr_t) hdrp;
    *hdrp = compose_hidden_class_header(alloc_granules, type);
    write_boundary_tag(alloc_end, alloc_granules);
    bytes += (BOUNDARY_TAG_GRANULES << LOG_BYTES_IN_GRANULE);
  }

  space->free_bytes -= bytes;
  return header_to_payload(hdrp);

js_space_alloc_out_of_memory:
#ifdef DEBUG
  LOG("js_space.head  = %zu\n", js_space.head);
  LOG("js_space.begin = %zu\n", js_space.begin);
  LOG("js_space.end   = %zu\n", js_space.end);
  LOG("js_space.tail  = %zu\n", js_space.tail);
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

/* Local Variables: */
/* mode: c */
/* c-basic-offset: 2 */
/* indent-tabs-mode: nil */
/* End: */
