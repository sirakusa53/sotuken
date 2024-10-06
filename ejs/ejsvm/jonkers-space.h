#ifndef JONKERS_SPACE_H
#define JONKERS_SPACE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef GC_JONKERS_SEPARATE_META_SIZE
#define GC_JONKERS_SEPARATE_META
#endif /* GC_JONKERS_SEPARATE_META_SIZE */

#ifndef GC_JONKERS_SEPARATE_META
#define GC_JONKERS_MIX
#endif /* !GC_JONKERS_SEPARATE_META */

/*
 * Object header layout
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
 *  - id      Identifier bit to determine header value is threaded.
 */

#ifdef BIT_ALIGN32
#ifdef USE_MBED_EFFICIENT_HEADER
#define HEADER_GRANULES        1
#define HEADER_IDENTIFIER_BITS 1
#define HEADER_TYPE_BITS       8
#define HEADER_MARKBIT_BITS    1
#define HEADER_GEN_BITS        0
#define HEADER_MAGIC_BITS      7
#define HEADER_SIZE_BITS       15
#define HEADER_MAGIC           14
#else /* USE_MBED_EFFICIENT_HEADER */
#ifdef GC_JONKERS_HEADER32
#define HEADER_GRANULES        1
#define HEADER_IDENTIFIER_BITS 1
#define HEADER_TYPE_BITS       LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS    1
#define HEADER_GEN_BITS        0
#define HEADER_MAGIC_BITS      4
#define HEADER_SIZE_BITS       20
#define HEADER_MAGIC           14
#else /* GC_JONKERS_HEADER32 */
#define HEADER_GRANULES        2
#define HEADER_IDENTIFIER_BITS 1
#define HEADER_TYPE_BITS       LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS    1
#define HEADER_GEN_BITS        7
#define HEADER_MAGIC_BITS      15
#define HEADER_SIZE_BITS       32
#define HEADER_MAGIC           0x18
#endif /* GC_JONKERS_HEADER32 */
#endif /* USE_MBED_EFFICIENT_HEADER */
#else /* BIT_ALIGN32 */
#define HEADER_GRANULES        1
#define HEADER_IDENTIFIER_BITS 1
#define HEADER_TYPE_BITS       LOG_MAX_NUM_CELL_TYPES
#define HEADER_MARKBIT_BITS    1
#define HEADER_GEN_BITS        7
#define HEADER_MAGIC_BITS      15
#define HEADER_SIZE_BITS       32
#define HEADER_MAGIC           0x18
#endif /* BIT_ALIGN32 */

#ifdef USE_MBED_EFFICIENT_HEADER
typedef struct header_t {
  union {
    uintptr_t threaded;
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
      unsigned int identifier: HEADER_IDENTIFIER_BITS;
    };
    struct {
      cell_type_t  type:       HEADER_TYPE_BITS;
      unsigned int markbit:    HEADER_MARKBIT_BITS;
#if HEADER_MAGIC_BITS > 0
      unsigned int magic:      HEADER_MAGIC_BITS;
#endif /* HEADER_MAGIC_BITS */
#if HEADER_GEN_BITS > 0
      unsigned int gen:        HEADER_GEN_BITS;
#endif /* HEADER_GEN_BITS */
      unsigned int size_lo:    HEADER_SIZE_BITS;
      unsigned int identifier: HEADER_IDENTIFIER_BITS;
    } hc;
  };
} header_t;
#else /* USE_MBED_EFFICIENT_HEADER */
typedef struct header_t {
  union {
    uintptr_t threaded;
    struct {
      unsigned int identifier: HEADER_IDENTIFIER_BITS;
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
  };
} header_t;
#endif /* USE_MBED_EFFICIENT_HEADER */

static inline header_t compose_header(size_t granules, cell_type_t type);

#define BOUNDARY_TAG_GRANULES 0

/*
 *  Types
 */

#ifdef GC_JONKERS_USING_QUEUE
struct hcrecord {
  header_t *hdrp;  /* pointer to the header at the original position */
  void *to;        /* new address that points to the payload */
};
#endif /* GC_JONKERS_USING_QUEUE */

#ifdef __cplusplus
}
#endif

#endif /* JONKERS_SPACE_H */
