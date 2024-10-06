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
struct space js_space;
#ifdef GC_DEBUG_SHADOW
STATIC struct space debug_js_shadow;
#endif /* GC_DEBUG_SHADOW */

/*
 * prototype
 */
/* space */
void create_space(struct space *space, size_t bytes, size_t threshold_bytes, const char *name);

/* GC */
#ifdef GC_DEBUG
void print_memory_status(void);
#endif /* GC_DEBUG */


/*
 * Header operation
 */

static inline size_t get_payload_granules(const header_t *hdrp) __attribute((unused));
static inline size_t get_payload_granules(const header_t *hdrp)
{
  return hdrp->size - HEADER_GRANULES;
}

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
  space->begin = addr;
  space->top = addr;
  space->end = addr + bytes;
  space->bytes = bytes;
  space->free_bytes = space->end - space->begin;
  space->threshold_bytes = threshold_bytes;
  space->name = name;
}

#ifdef GC_DEBUG_SHADOW
header_t *get_shadow(const void *ptr)
{
  if (in_js_space(ptr)) {
    uintptr_t a = (uintptr_t) ptr;
    uintptr_t off = a - js_space.begin;
    return (header_t *) (debug_js_shadow.begin + off);
  } else {
    printf("Warn : get_shadow return NULL;");
    printf(" ptr = %p, js_space.begin = %p, js_space.end = %p\n", ptr, (void *) js_space.begin, (void *) js_space.end);
    fflush(stdout);
    return NULL;
  }
}
#endif /* GC_DEBUG_SHADOW */

/*
 * Returns a pointer to the first address of the memory area
 * available to the VM. The header precedes the area.
 */
static inline void* js_space_alloc(struct space *space,
                                   size_t request_bytes, cell_type_t type)
{
#if LOG_BYTES_IN_GRANULE != LOG_BYTES_IN_JSVALUE
#error "LOG_BYTES_IN_JSVALUE != LOG_BYTES_IN_GRANULE"
#endif

  const size_t alloc_granules =
    BYTE_TO_GRANULE_ROUNDUP(request_bytes) + HEADER_GRANULES;
  const size_t bytes = (alloc_granules << LOG_BYTES_IN_GRANULE);
  header_t *hdrp;

  const uintptr_t next = space->top + bytes;
  if (next > space->end)
    goto js_space_alloc_out_of_memory;
  hdrp = (header_t *) space->top;
  space->top = next;
#if 0
  *hdrp = compose_header(alloc_granules, type);
#else /* 0 */
  compose_header(hdrp, alloc_granules, type);
#endif /* 0 */

  space->free_bytes -= bytes;
  return header_to_payload(hdrp);

js_space_alloc_out_of_memory:
#ifdef DEBUG
  LOG("js_space.begin = %zu\n", js_space.begin);
  LOG("js_space.top   = %zu\n", js_space.top);
  LOG("js_space.end   = %zu\n", js_space.end);
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
    const header_t *hdrp = payload_to_header(addr);
    header_t *shadow = get_shadow(hdrp);
    *shadow = *hdrp;
  }
#endif /* GC_DEBUG_SHADOW */
  return addr;
}

#ifdef GC_DEBUG
void space_print_memory_status(void)
{
  printf(" free_bytes = %zu\n", js_space.free_bytes);
}
#endif /* GC_DEBUG */

/* Local Variables: */
/* mode: c */
/* c-basic-offset: 2 */
/* indent-tabs-mode: nil */
/* End: */
