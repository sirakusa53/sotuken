/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef HEADER_H_
#define HEADER_H_

#if 0
#ifndef ALLOC_SITE_CACHE
#warning DUMP_HCG is enabled. ALLOC_SITE_CACHE is turned on
#define ALLOC_SITE_CACHE
#endif /* ALLOC_SITE_CACHE */
#ifdef SKIP_INTERNAL
#warning DUMP_HCG is enabled. SKIP_INTERNAL is turned off
#undef SKIP_INTERNAL
#endif /* SKIP_INTERNAL */
#ifdef WEAK_SHAPE_LIST
#warning DUMP_HCG is enabled. WEAK_SHAPE_LIST is turned off
#undef WEAK_SHAPE_LIST
#endif /* WEAK_SHAPE_LIST */
#endif

#ifdef DUMP_HCG
#ifndef HC_PROF
#warning DUMP_HCG is enabled. HC_PROF is turned on
#define HC_PROF
#endif /* HC_PROF */
#endif /* DUMP_HCG */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/time.h>
#include <sys/resource.h>
#ifdef __cplusplus
}
#endif
#include <setjmp.h>

#ifdef USE_BOEHMGC
#include <gc.h>
#endif

#ifndef __USE_GNU
#define __USE_GNU
#endif /* __USE_GNU */
#ifdef DEBUG
#define DEBUG_NAME(name) name
#else /* DEBUG */
#define DEBUG_NAME(name) ""
#endif /* DEBUG */

#ifdef USE_BOEHMGC
/* #define malloc(n) GC_malloc(n) */
#define malloc(n) GC_MALLOC(n)
#define realloc(p, size) do { memcpy(malloc((size)), (p), (size));} while (0)
#define free GC_FREE
#endif /* USE_BOEHMGC */

#define SUCCESS  1
#define FAIL     0

#define TRUE     1
#define FALSE    0

#define HINT_NUMBER 1
#define HINT_STRING 0

#define PHASE_INIT   0
#define PHASE_VMLOOP 1

#define FILE_OBC   1
#define FILE_SBC   2

#include "prefix.h"
#include "types.h"
#include "context.h"
#include "util.h"
#include "gc.h"

#ifdef FREELIST
#include "freelist-space.h"
#endif /* FREELIST */
#ifdef BIBOP
#include "bibop-space.h"
#endif /* BIBOP */
#ifdef COPYGC
#include "copy-collector.h"
#endif /* COPYGC */
#ifdef THREADED
#ifdef JONKERS
#include "jonkers-space.h"
#endif /* JONKERS */
#ifdef FUSUMA
#include "fusuma-space.h"
#endif /* FUSUMA */
#include "threaded-space.h"
#include "threadedcompact-collector.h"
#endif /* THREADED */
#ifdef LISP2
#include "lisp2-space.h"
#endif /* THREADED */

#include "hash.h"
#include "log.h"
#include "instructions.h"
#include "builtin.h"
#include "globals.h"
#include "extern.h"
#ifdef USE_VMDL
#include "vmdl-helper.h"
#endif /* USE_VMDL */


#include "context-inl.h"
#include "types-inl.h"
#include "util-inl.h"
#include "gc-inl.h"

#ifdef FREELIST
#include "freelist-space-inl.h"
#endif /* FREELIST */
#ifdef BIBOP
#include "bibop-space-inl.h"
#endif /* BIBOP */
#ifdef THREADED
#include "threaded-space-inl.h"
#ifdef JONKERS
#include "jonkers-space-inl.h"
#endif /* JONKERS */
#ifdef FUSUMA
#include "fusuma-space-inl.h"
#endif /* FUSUMA */
#endif /* THREADED */
#ifdef LISP2
#include "lisp2-space-inl.h"
#endif /* LISP2 */


#endif /* HEADER_H_ */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
