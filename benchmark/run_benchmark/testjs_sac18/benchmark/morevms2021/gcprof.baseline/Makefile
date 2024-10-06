EJSVM_DIR=../ejsvm
.PRECIOUS: %.c %.h %.o

##
## configuration files
##

#DATATYPES = $(EJSVM_DIR)/datatypes/default.def
OPERANDSPEC = $(EJSVM_DIR)/operand-spec/any.spec
# OPERANDSPEC = $(EJSVM_DIR)/operand-spec/fixnum-unspec.spec
#SUPERINSNSPEC = $(EJSVM_DIR)/superinsn-spec/all.si
#SUPERINSNTYPE = 4
#VMDLC_FLAGS=-no-match-opt

##
## compile flags
##

#CPPFLAGS = -m32 -O3 -DNDEBUG -UDEBUG $(HEAPSIZE)
CPPFLAGS = -m32 -Os -DNDEBUG -UDEBUG $(HEAPSIZE)
#CPPFLAGS = -m32 -O0 -gdwarf $(HEAPSIZE)
INSNGEN_FLAGS = -Xgen:pad_cases true -Xcmp:opt_pass MR:S -Xcmp:rand_seed 0
LDFLAGS = -m32

GC_CXX=true

##
## VMDL
##
USE_VMDL=false

##
## commands
##

#CC = gcc
#SED = gsed
SED = sed
#PYTHON = python
PYTHON = python3
# CPP_VMDL = $(CPP) -E -x c -P
COCCINELLE = spatch
# COCCINELLE = spatch --python python3

##
## paths
##

INCLUDES =
# INCLUDES = -I/opt/local/include
LIBS =
# LIBS = -L/opt/local/lib

## 
## options
## 

OPT_REGEXP    = none
# OPT_REGEXP    = oniguruma
#OPT_GC        = native
#OPT_GC        = bibop
# OPT_GC        = none

## heap size in bytes
HEAPSIZE      = -DJS_SPACE_BYTES=10485760

## enable profiling to create customised VM
# CPPFLAGS       += -DPROFILE

## word size
# INSN32/64    -- instruction size
# JSVALUE32/64 -- JSValue size  (>= ponter size)
# ALIGN32/64   -- alignment of heap-allocated data
#CPPFLAGS        += -DBIT_INSN32 -DBIT_ALIGN32 -DBIT_JSVALUE32
#CPPFLAGS        += -DBIT_INSN64 -DBIT_ALIGN64 -DBIT_JSVALUE64

##
## developer options
##

## accept SBC files
CPPFLAGS       += -DUSE_SBC
## GC collects internal nodes in hidden class graph
#CPPFLAGS       += -DHC_SKIP_INTERNAL
#CPPFLAGS       += -DHC_SKIP_INTERNAL_COUNT_BASE
## cache shapes at allocation site
#CPPFLAGS       += -DALLOC_SITE_CACHE
#CPPFLAGS       += -DALLOC_SITE_CACHE_COUNT_BASE
## GC collects unused shapes (effective if ALLOC_SITE_CACHE is specified)
#CPPFLAGS       += -DWEAK_SHAPE_LIST
## Do not hold the list of shapes.  Instead, only the largest shape is held.
#CPPFLAGS       += -DNO_SHAPE_CACHE
## use inlne cache
CPPFLAGS       += -DINLINE_CACHE
CPPFLAGS       += -DINLINE_CACHE_RESET
CPPFLAGS       += -DINLINE_CACHE_WEAK

#CPPFLAGS       += -DEXCESSIVE_GC

## show GC profiling information (make --gc-prof available)
CPPFLAGS       += -DGC_PROF
## show hidden class related profiling information (make --hc-prof available)
#CPPFLAGS       += -DHC_PROF
## print flonum usage
#CPPFLAGS       += -DFLONUM_SPACE

## use explicit mark stack rather than recursive call
CPPFLAGS      += -DMARK_STACK

## Use flonum space (only BiBoP space supports)
#CPPFLAGS       += -DFLONUM_SPACE

## array size strategy
CPPFLAGS       += -DNEW_ASIZE_STRATEGY

##
## BiBoP options
##

## page caches the size of bitmaps
CFALGS       += -DBIBOP_CACHE_BMP_GRANULES
## free pages of size one is linked in a separate list
CPPFLAGS       += -DBIBOP_SEGREGATE_1PAGE
## allocate pages of size one from the bottom of the heap
CPPFLAGS       += -DBIBOP_2WAY_ALLOC
## middle size objects are stored in page but stored with their types so
## multiple types are allocated in the same page.
#CPPFLAGS      += -DBIBOP_MOBJ
## debug
#CPPFLAGS       += -DVERIFY_BIBOP

##
## debug/sanity check options
##

## show values of properties in GETPROP/SETPROP instructions
#CPPFLAGS   += -DDEBUG_GETPROP_VALUE

## GC reports unmatured (not reached the end of HC
## transisiton graph) dead objects
#CPPFLAGS   += -DCHECK_MATURED

## fix rand seed
CPPFLAGS    += -DNO_SRAND
DATATYPES = $(EJSVM_DIR)/datatypes/default_32.def
CC = gcc
CXX = gcc
CPPFLAGS        += -DBIT_INSN32 -DBIT_ALIGN32 -DBIT_JSVALUE32
OPT_GC = threaded
#OPT_GC = native
CPPFLAGS += -DGC_THREADED_BOUNDARY_TAG
CPPFLAGS += -DGC_THREADED_BOUNDARY_TAG_SKIP_SIZE_CHECK
CPPFLAGS += -DGC_THREADED_MERGE_FREE_SPACE
CPPFLAGS += -DGC_THREADED_HEADER32

CPPFLAGS += -DGC_MS_HEADER32
include $(EJSVM_DIR)/common.mk
