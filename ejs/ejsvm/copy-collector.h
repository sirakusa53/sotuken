typedef struct header_t {
  size_t size: 22;
  cell_type_t type: 8;
  int forwarded: 1;
} header_t;

#define HEADER_GRANULES 1

struct copy_space {
  uintptr_t ss0, ss1;
  size_t bytes;
  size_t total_bytes;
  uintptr_t from, end, to, free, scan;
  size_t threshold_bytes;
};

extern struct copy_space space;

#ifndef DEFAULT_GC_THRESHOLD
#define DEFAULT_GC_THRESHOLD(heap_limit) (20 * 1024)
#endif /* DEFAULT_GC_THRESHOLD */

extern void space_init(size_t bytes, size_t threshold_bytes);
extern void *space_alloc(uintptr_t request_bytes, cell_type_t type);
static inline header_t *payload_to_header(uintptr_t ptr) {
  return ((header_t *) ptr) - 1;
}
static inline void *header_to_payload(header_t *hdrp) {
  return hdrp + 1;
}
static inline int space_check_gc_request() {
  return space.end - space.free < space.threshold_bytes;
}
static inline cell_type_t space_get_cell_type(uintptr_t ptr) {
  header_t *hdrp = payload_to_header(ptr);
  return hdrp->type;
}

static uintptr_t get_forwarding_pointer(uintptr_t ptr) {
  return *(uintptr_t *) ptr;
}

#ifdef GC_DEBUG
extern void space_print_memory_status(void);
#endif /* GC_DEBUG */
