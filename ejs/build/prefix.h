/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef PREFIX_H_
#define PREFIX_H_

#include "prefix-generated.h"

/*
  compilation options
*/

#ifndef NDEBUG
#ifndef DEBUG
#define DEBUG 1
#endif /* DEBUG */
#ifndef DEBUG_PRINT
#define DEBUG_PRINT
#endif /* DEBUG_PRINT */
#endif /* NDEBUG */

#ifndef NDEBUG
#define GC_DEBUG 1

#ifdef USE_MBED
#undef GC_DEBUG_SHADOW
#else /* USE_MBED */
#define GC_DEBUG_SHADOW
#endif /* USE_MBED */

#define STATIC        /* make symbols global for debugger */
#define STATIC_INLINE /* make symbols global for debugger */
#else /* NDEBUG */
#undef GC_DEBUG
#undef GC_DEBUG_SHADOW
#define STATIC static
#define STATIC_INLINE static inline
#endif /* NDEBUG */

#ifdef DEBUG
#ifndef WITH_SOURCE_LOCATION
#define WITH_SOURCE_LOCATION
#endif /* WITH_SOURCE_LOCATION */
#endif /* DEBUG */

#define STROBJ_HAS_HASH

/* #define CALC_TIME */
/* #define USE_PAPI */
/* #define USE_FASTGLOBAL */
/* #define CALC_CALL */

#define HIDDEN_CLASS

#ifdef CALC_CALL
#define CALLCOUNT_UP() callcount++
#else
#define CALLCOUNT_UP()
#endif

#if defined(ALLOC_SITE_CACHE) || defined(INLINE_CACHE) || defined(LOAD_HCG) || defined(PROFILE) || defined(DUMP_HCG)
#define NEED_INSTRUCTION_CACHE
#endif /* defined(ALLOC_SITE_CACHE) || defined(INLINE_CACHE) || defined(LOAD_HCG) || defined(PROFILE) */

#endif /* PREFIX_H_ */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
