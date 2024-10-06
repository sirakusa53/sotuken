#ifndef LISP2_SPACE_H
#define LISP2_SPACE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef FLONUM_SPACE
#error lisp2 space does not support FLONUM_SPACE.
#endif /* FLONUM_SPACE */

#ifndef DEFAULT_GC_THRESHOLD
#define DEFAULT_GC_THRESHOLD(heap_limit) ((heap_limit) >> 4)
#endif /* DEFAULT_GC_THRESHOLD */

/*
 * Object header layout
 *
 * Heap objects are aligned in `granule' boundary.  Header may consist
 * of multiple granules.  HEADER_GRANULES gives the number of granules
 * in a header.
 *
 * Header fields
 *  - type    Cell type
 *  - markbit Mark bit for GC
 *  - gen     Generation of this object describing the number of GC cycles
 *            have been performed (modulo field size) befor the allocation
 *            of this object.
 *  - magic   Magic number
 *  - size    Size of the object in granule, including the header and extra.
 *  - fwd     Forwarding pointer
 */

#ifdef BIT_ALIGN32
#ifdef GC_LISP2_HEADER32
#define HEADER_GRANULES        2
#define HEADER_TYPE_BITS       LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS    1
#define HEADER_GEN_BITS        0
#define HEADER_MAGIC_BITS      5
#define HEADER_SIZE_BITS       20
#define HEADER_MAGIC           30
#else /* GC_LISP2_HEADER32 */
#define HEADER_GRANULES        3
#define HEADER_TYPE_BITS       LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS    1
#define HEADER_GEN_BITS        8
#define HEADER_MAGIC_BITS      16
#define HEADER_SIZE_BITS       32
#define HEADER_MAGIC           0x18
#endif /* GC_LISP2_HEADER32 */
#else /* BIT_ALIGN32 */
#define HEADER_GRANULES        2
#define HEADER_TYPE_BITS       LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS    1
#define HEADER_GEN_BITS        8
#define HEADER_MAGIC_BITS      16
#define HEADER_SIZE_BITS       32
#define HEADER_MAGIC           0x18
#endif /* BIT_ALIGN32 */

typedef struct header_t {
  struct {
    cell_type_t  type:       HEADER_TYPE_BITS;
    unsigned int markbit:    HEADER_MARKBIT_BITS;
#if HEADER_MAGIC_BITS > 0
    unsigned int magic:      HEADER_MAGIC_BITS;
#endif /* HEADER_MAGIC_BITS */
#if HEADER_GEN_BITS > 0
    unsigned int gen:        HEADER_GEN_BITS;
#endif /* HEADER_GEN_BITS */
    unsigned int size:       HEADER_SIZE_BITS;
  };
  void *fwd;
} header_t;

#if 0
static inline header_t compose_header(size_t granules, cell_type_t type);
#else /* 0 */
static inline void compose_header(header_t *hdrp, size_t granules, cell_type_t type);
#endif /* 0 */

/*
 *  Types
 */

struct space {
  uintptr_t begin;
  uintptr_t top;
  uintptr_t end;
  size_t bytes;
  size_t free_bytes;
  size_t threshold_bytes;
  const char *name;
};

extern struct space js_space;

static inline void *header_to_payload(const header_t *hdrp);
static inline header_t *payload_to_header(const void *ptr);

static inline void mark_cell_header(header_t *hdrp);
static inline void unmark_cell_header(header_t *hdrp);
static inline int is_marked_cell_header(const header_t *hdrp);

static inline int is_hidden_class(cell_type_t type);

/* GC private functions */
static inline void mark_cell(void *p);
static inline int is_marked_cell(const void *p);
static inline  int test_and_mark_cell(void *p);
extern void space_init(size_t bytes, size_t threshold_bytes);
extern void *space_alloc(uintptr_t request_bytes, cell_type_t type);
extern void sweep(void);
static inline int space_check_gc_request();
static inline int in_js_space(const void *addr_);
static inline cell_type_t space_get_cell_type(uintptr_t ptr);
#ifdef GC_DEBUG
extern void space_print_memory_status(void);
#endif /* GC_DEBUG */

#ifdef GC_DEBUG_SHADOW
header_t *get_shadow(const void *ptr);
#endif /* GC_DEBUG_SHADOW */

#ifdef __cplusplus
}
#endif

#endif /* LISP2_SPACE_H */
