#ifndef FREELIST_SPACE_H
#define FREELIST_SPACE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef FLONUM_SPACE
#error freelist space does not support FLONUM_SPACE.
#endif /* FLONUM_SPACE */

#ifndef DEFAULT_GC_THRESHOLD
#ifdef EXCESSIVE_GC
#define DEFAULT_GC_THRESHOLD(heap_limit) ((heap_limit) - ((heap_limit) >> 4))
#else  /* EXCESSIVE_GC */
#define DEFAULT_GC_THRESHOLD(heap_limit) ((heap_limit) >> 1)
#endif /* EXCESSIVE_GC */
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
 *  - extra   The number of over-allocated space in granule.
 *  - gen     Generation of this object describing the number of GC cycles
 *            have been performed (modulo field size) befor the allocation
 *            of this object.
 *  - magic   Magic number
 *  - size    Size of the object in granule, including the header and extra.
 */

#ifdef BIT_ALIGN32
#ifdef USE_MBED_EFFICIENT_HEADER
#define HEADER_GRANULES       1
#define HEADER_TYPE_BITS      8
#define HEADER_MARKBIT_BITS   1
#define HEADER_EXTRA_BITS     7
#define HEADER_GEN_BITS       0
#define HEADER_MAGIC_BITS     0
#define HEADER_SIZE_BITS      16
#define HEADER_MAGIC          3
#else /* USE_MBED_EFFICIENT_HEADER */
#ifdef GC_MS_HEADER32
#define HEADER_GRANULES       1
#define HEADER_TYPE_BITS      LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS   1
#define HEADER_EXTRA_BITS     3
#define HEADER_GEN_BITS       0
#define HEADER_MAGIC_BITS     2
#define HEADER_SIZE_BITS      20
#define HEADER_MAGIC          3
#else /* GC_MS_HEADER32 */
#define HEADER_GRANULES       2
#define HEADER_TYPE_BITS      LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS   1
#define HEADER_EXTRA_BITS     3
#define HEADER_GEN_BITS       4
#define HEADER_MAGIC_BITS     16
#define HEADER_SIZE_BITS      32
#define HEADER_MAGIC          0x18
#endif /* GC_MS_HEADER32 */
#endif /* USE_MBED_EFFICIENT_HEADER */
#else /* BIT_ALIGN32 */
#define HEADER_GRANULES       1
#define HEADER_TYPE_BITS      LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS   1
#define HEADER_EXTRA_BITS     3
#define HEADER_GEN_BITS       4
#define HEADER_MAGIC_BITS     16
#define HEADER_SIZE_BITS      18
#define HEADER_MAGIC          0x18
#endif /* BIT_ALIGN32 */

#define MAX_CHUNK_GRANULES ((1LL << HEADER_SIZE_BITS) - 1)

#ifdef USE_MBED_EFFICIENT_HEADER
typedef struct header_t {
  cell_type_t  type:    HEADER_TYPE_BITS;
  unsigned int extra:   HEADER_EXTRA_BITS;
  unsigned int markbit: HEADER_MARKBIT_BITS;
#if HEADER_MAGIC_BITS > 0
  unsigned int magic:   HEADER_MAGIC_BITS;
#endif /* HEADER_MAGIC_BITS */
#if HEADER_GEN_BITS > 0
  unsigned int gen:     HEADER_GEN_BITS;
#endif /* HEADER_GEN_BITS */
  unsigned int size:    HEADER_SIZE_BITS;
} header_t;
#else /* USE_MBED_EFFICIENT_HEADER */
typedef struct header_t {
  cell_type_t  type:    HEADER_TYPE_BITS;
  unsigned int markbit: HEADER_MARKBIT_BITS;
  unsigned int extra:   HEADER_EXTRA_BITS;
#if HEADER_MAGIC_BITS > 0
  unsigned int magic:   HEADER_MAGIC_BITS;
#endif /* HEADER_MAGIC_BITS */
#if HEADER_GEN_BITS > 0
  unsigned int gen:     HEADER_GEN_BITS;
#endif /* HEADER_GEN_BITS */
  unsigned int size:    HEADER_SIZE_BITS;
} header_t;
#endif /* USE_MBED_EFFICIENT_HEADER */

static inline header_t compose_header(size_t granules, size_t extra,
                                      cell_type_t type);

/*
 *  Types
 */

struct free_chunk {
  header_t header;
  struct free_chunk *next;
};

struct space {
  uintptr_t addr;
  size_t bytes;
  size_t free_bytes;
  struct free_chunk* freelist;
  size_t threshold_bytes;
  const char *name;
};

extern struct space js_space;

static inline void *header_to_payload(header_t *hdrp);
static inline header_t *payload_to_header(void *ptr);

static inline void mark_cell_header(header_t *hdrp);
static inline void unmark_cell_header(header_t *hdrp);
static inline int is_marked_cell_header(header_t *hdrp);

/* GC private functions */
static inline void mark_cell(void *p);
static inline int is_marked_cell(void *p);
static inline  int test_and_mark_cell(void *p);
extern void space_init(size_t bytes, size_t threshold_bytes);
extern void *space_alloc(uintptr_t request_bytes, cell_type_t type);
extern void sweep(void);
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

#endif /* FREELIST_SPACE_H */
