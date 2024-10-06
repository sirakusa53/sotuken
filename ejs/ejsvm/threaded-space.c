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
struct space debug_js_shadow;
#endif /* GC_DEBUG_SHADOW */

/*
 * prototype
 */

/* space */

/* Defined at jonkers-space.c / fusuma-space.c */
extern void create_space(struct space *space, size_t bytes, size_t threshold_bytes, const char *name);

#ifdef GC_DEBUG_SHADOW
header_t *get_shadow(void *ptr);
#endif /* GC_DEBUG_SHADOW */

/* GC */
#ifdef GC_DEBUG
void print_memory_status(void);
#endif /* GC_DEBUG */


/*
 *  Space
 */


#ifdef GC_DEBUG_SHADOW
header_t *get_shadow(void *ptr)
{
  if (in_js_space(ptr)) {
    uintptr_t a = (uintptr_t) ptr;
    uintptr_t off = a - js_space.head;
    return (header_t *) (debug_js_shadow.head + off);
  } else {
    printf("Warn : get_shadow return NULL;");
    printf(" ptr = %p, js_space.head = %p, js_space.end = %p\n", ptr, (void *) js_space.head, (void *) js_space.end);
	fflush(stdout);
    return NULL;
  }
}
#endif /* GC_DEBUG_SHADOW */

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

/* Defined at jonkers-space.c / fusuma-space.c */
extern void* space_alloc(uintptr_t request_bytes, cell_type_t type);

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
