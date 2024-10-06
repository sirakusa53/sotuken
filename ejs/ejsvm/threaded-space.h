#ifndef THREADED_SPACE_H
#define THREADED_SPACE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef FLONUM_SPACE
#error threaded space does not support FLONUM_SPACE.
#endif /* FLONUM_SPACE */

#ifndef DEFAULT_GC_THRESHOLD
#ifdef EXCESSIVE_GC
#error threaded space does not support EXCESSIVE_GC.
#else  /* EXCESSIVE_GC */
#define DEFAULT_GC_THRESHOLD(heap_limit) ((heap_limit) >> 4)
#endif /* EXCESSIVE_GC */
#endif /* DEFAULT_GC_THRESHOLD */

/*
 *  Types
 */

struct space {
  uintptr_t head;
  uintptr_t tail;
  uintptr_t begin;
  uintptr_t end;
  size_t bytes;
  size_t free_bytes;
  size_t threshold_bytes;
  const char *name;
};

extern struct space js_space;

static inline void *header_to_payload(header_t *hdrp);
static inline header_t *payload_to_header(void *ptr);

static inline bool is_hidden_class(cell_type_t type);

static inline void mark_cell_header(header_t *hdrp);
static inline void unmark_cell_header(header_t *hdrp);
static inline int is_marked_cell_header(header_t *hdrp);

/* GC private functions */
static inline void mark_cell(void *p);
static inline int is_marked_cell(void *p);
static inline  int test_and_mark_cell(void *p);
extern void space_init(size_t bytes, size_t threshold_bytes);
extern void *space_alloc(uintptr_t request_bytes, cell_type_t type);
static inline int space_check_gc_request();
static inline int in_js_space(void *addr_);
static inline cell_type_t space_get_cell_type(uintptr_t ptr);
#ifdef GC_DEBUG
extern void space_print_memory_status(void);
#endif /* GC_DEBUG */

#ifdef GC_DEBUG_SHADOW
header_t *get_shadow(void *ptr);
#endif /* GC_DEBUG_SHADOW */

#ifdef __cplusplus
}
#endif

#endif /* THREADED_SPACE_H */
