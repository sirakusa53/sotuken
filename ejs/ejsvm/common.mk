.PHONY: check clean

######################################################

ifeq ($(EJSVM_DIR),)
    EJSVM_DIR=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
endif

UNAME := $(shell uname -s)

######################################################
# default values

ifeq ($(CC),cc)
    CC = clang
endif
ifeq ($(CXX),cc)
    CC = clang
endif

ifeq ($(SED),)
ifeq ($(UNAME), Linux)
    SED = sed
endif
ifeq ($(UNAME), Darwin)
    SED = gsed
endif
endif

ifeq ($(PYTHON),)
ifeq ($(UNAME), Linux)
    PYTHON = python3
endif
ifeq ($(UNAME), Darwin)
    PYTHON = python
endif
endif

ifeq ($(CPP_VMDL),)
    CPP_VMDL=$(CC) -E -x c -P
endif

ifeq ($(COCCINELLE),)
    COCCINELLE = spatch --python $(PYTHON)
endif

ifeq ($(OPT_GC),)
# GC=native|jonkers|fusuma|lisp2|copy|bibop|none
    OPT_GC=native
endif

#ifeq ($(SUPERINSNSPEC),)
#    SUPERINSNSPEC=none
#endif
#ifeq ($(SUPERINSNTYPE),)
#    SUPERINSNTYPE=4
#endif

ifeq ($(OPT_REGEXP),)
# REGEXP=oniguruma|none
    OPT_REGEXP=none
endif

ifeq ($(SKIP_EMBEDDING_SPEC_INTO_EJSC),)
SKIP_EMBEDDING_SPEC_INTO_EJSC = false
endif

######################################################
# commands and paths

GOTTA_ARG = --otspec $(OPERANDSPEC) --insndef $(EJSVM_DIR)/instructions.def
GOTTA_REQUIRE = $(EJSVM_DIR)/gotta.py $(OPERANDSPEC) $(EJSVM_DIR)/instructions.def
ifneq ($(SUPERINSNTYPE),)
GOTTA_ARG += --sispec $(SUPERINSNSPEC) --sitype $(SUPERINSNTYPE)
GOTTA_REQUIRE += $(SUPERINSNSPEC)
endif
GOTTA=$(PYTHON) $(EJSVM_DIR)/gotta.py $(GOTTA_ARG)

#SILIST=$(GOTTA) --silist --sispec
SILIST=$(SED) -e 's/^.*: *//'

EJSC_DIR=$(EJSVM_DIR)/../ejsc
EJSC=$(EJSC_DIR)/newejsc.jar

VMGEN_DIR=$(EJSVM_DIR)/../vmgen
VMGEN=$(VMGEN_DIR)/vmgen.jar

VMDL_DIR=$(EJSVM_DIR)/../vmdl
VMDL=$(VMDL_DIR)/vmdlc.jar
ifeq ($(USE_VMDL),true)
VMDL_WORKSPACE=vmdl_workspace
VMDL_INSN_REQ_SPEC_DIR=$(VMDL_WORKSPACE)/requires/insns
VMDL_BUILTIN_REQ_SPEC_DIR=$(VMDL_WORKSPACE)/requires/builtins
VMDL_INLINE=$(VMDL_WORKSPACE)/inlines.inline
VMDL_FUNCANYSPEC=$(VMDL_WORKSPACE)/any.spec
VMDL_FUNCNEEDSPEC=$(VMDL_WORKSPACE)/funcs-need.spec
VMDL_FUNCDEPENDENCY=$(VMDL_WORKSPACE)/dependency.ftd
VMDL_GENERATED_H=vmdl-generated.h
VMDL_EXTERN=vmdl-extern.h
VMDL_FUNCDPECCREQUIRE=$(VMDL_WORKSPACE)/funcscrequire.spec
endif

EJSI_DIR=$(EJSVM_DIR)/../ejsi
EJSI=$(EJSI_DIR)/ejsi

INSNGEN_VMGEN=java -Xss4M -cp $(VMGEN) vmgen.InsnGen
TYPESGEN_VMGEN=java -cp $(VMGEN) vmgen.TypesGen
INSNGEN_VMDL=java -jar $(VMDL)
FUNCGEN_VMDL=$(INSNGEN_VMDL)
BUILTINGEN_VMDL=$(INSNGEN_VMDL)
SPECGEN_VMDL=$(INSNGEN_VMDL)
TYPESGEN_VMDL=java -cp $(VMDL) vmdlc.TypesGen

ifeq ($(USE_VMDL),true)
SPECGEN=java -cp $(VMDL) vmdlc.SpecFileGen
SPECGEN_JAR=$(VMDL)
else
SPECGEN=java -cp $(VMGEN) vmgen.SpecFileGen
SPECGEN_JAR=$(VMGEN)
endif

ifeq ($(JSSRC_PATH),)
JSSRC_PATH=$(EJSVM_DIR)/mbed/common/sample_script.js
endif

ifeq ($(USE_MBED),true)
USE_OBC=false
USE_SBC=false
endif

ifeq ($(filter true,$(USE_OBC) $(USE_SBC)),)
USE_EMBEDDED_INSTRUCTION=true
else
USE_EMBEDDED_INSTRUCTION=false
endif

ifeq ($(LD_SCRIPT_RAW),)
LD_SCRIPT_RAW=x86_64.ld.raw
endif

EMBEDDED_INSTRUCTION_INC_PATH=embedded_instructions.inc
LD_SCRIPT_INC_PATH=embedded_instructions.inc.ld
ifeq ($(USE_EMBEDDED_INSTRUCTION),true)
EMBEDDED_INSTRUCTION_INC=$(EMBEDDED_INSTRUCTION_INC_PATH)
LD_SCRIPT_INC=$(LD_SCRIPT_INC_PATH)
LD_SCRIPT_FILE=linker_script.ld
LD_SCRIPT=-Wl,-T"$(LD_SCRIPT_FILE)"
else
EMBEDDED_INSTRUCTION_INC=
LD_SCRIPT_INC=
LD_SCRIPT_FILE=
LD_SCRIPT=
endif

CPP=$(CC) -E

INCLUDES +=
LIBS += -lm

CFLAGS += -std=gnu89
CXXFLAGS = -std=c++11
CPPFLAGS += -Wall $(INCLUDES)

ifeq ($(USE_VMDL),true)
CPPFLAGS += -DUSE_VMDL
ifeq ($(ICC_PROF),true)
CPPFLAGS += -DICC_PROF
endif
endif

ifeq ($(USE_OBC),true)
CPPFLAGS += -DUSE_OBC
endif
ifeq ($(USE_SBC),true)
CPPFLAGS += -DUSE_SBC
endif

ifeq ($(USE_EMBEDDED_INSTRUCTION),true)
CPPFLAGS += -DUSE_EMBEDDED_INSTRUCTION
CPPFLAGS += -DJS_SRC_PATH="$(JSSRC_PATH)"
endif

ifeq ($(BITWIDTH_INSN),32)
CPPFLAGS += -DBIT_INSN32
else
CPPFLAGS += -DBIT_INSN64
endif
ifeq ($(BITWIDTH_ALIGN),32)
CPPFLAGS += -DBIT_ALIGN32
else
CPPFLAGS += -DBIT_ALIGN64
endif
ifeq ($(BITWIDTH_JSVALUE),32)
CPPFLAGS += -DBIT_JSVALUE32
else
CPPFLAGS += -DBIT_JSVALUE64
endif

ifeq ($(JS_HEAP_SIZE),)
ifeq ($(USE_MBED),true)
JS_HEAP_SIZE = 0x00020000
else
JS_HEAP_SIZE = 0x00a00000
endif
endif

CPPFLAGS += -DJS_SPACE_BYTES=$(JS_HEAP_SIZE)

######################################################
# superinstructions

ifeq ($(SUPERINSNTYPE),1)      # S1 in Table 1 in JIP Vol.12 No.4 p.5
    SUPERINSN_MAKEINSN=true
    SUPERINSN_CUSTOMIZE_OT=false
    SUPERINSN_PSEUDO_IDEF=false
    SUPERINSN_REORDER_DISPATCH=false
else ifeq ($(SUPERINSNTYPE),2) # S4 in Table 1 in JIP Vol.12 No.4 p.5
    SUPERINSN_MAKEINSN=true
    SUPERINSN_CUSTOMIZE_OT=true
    SUPERINSN_PSEUDO_IDEF=false
    SUPERINSN_REORDER_DISPATCH=false
else ifeq ($(SUPERINSNTYPE),3) # S5 in Table 1 in JIP Vol.12 No.4 p.5
    SUPERINSN_MAKEINSN=true
    SUPERINSN_CUSTOMIZE_OT=true
    SUPERINSN_PSEUDO_IDEF=true
    SUPERINSN_REORDER_DISPATCH=false
else ifeq ($(SUPERINSNTYPE),4) # S3 in Table 1 in JIP Vol.12 No.4 p.5
    SUPERINSN_MAKEINSN=false
    SUPERINSN_CUSTOMIZE_OT=false
    SUPERINSN_PSEUDO_IDEF=false
    SUPERINSN_REORDER_DISPATCH=true
else ifeq ($(SUPERINSNTYPE),5) # S2 in Table 1 in JIP Vol.12 No.4 p.5
    SUPERINSN_MAKEINSN=false
    SUPERINSN_CUSTOMIZE_OT=false
    SUPERINSN_PSEUDO_IDEF=false
    SUPERINSN_REORDER_DISPATCH=false
endif

ifeq ($(USE_VMDL_INLINE_EXPANSION),true)
VMDL_OPTION_INLINE=-func-inline-opt $(VMDL_INLINE)
endif
ifeq ($(USE_VMDL_CASE_SPLIT),true)
VMDL_OPTION_CASE_SPLIT=-case-split $(ICCSPEC)
endif
ifeq ($(USE_VMDL_IFSTYLE),true)
VMDL_OPTION_IFSTYLE=-Xgen:if_style true
endif
ifeq ($(USE_VMDL_DIRECT_GOTO),true)
VMDL_OPTION_DIRECT_GOTO=-Xgen:direct_goto true
endif

VMDL_OPTION_FLAGS = $(VMDL_OPTION_INLINE) $(VMDL_OPTION_CASE_SPLIT) $(VMDL_OPTION_IFSTYLE) $(VMDL_OPTION_DIRECT_GOTO)


SPECGEN_OPTION =
ifeq ($(USE_SBC),true)
SPECGEN_OPTION += --accept-sbc
endif
ifeq ($(USE_OBC),true)
SPECGEN_OPTION += --accept-obc
endif
ifeq ($(USE_EMBEDDED_INSTRUCTION),true)
SPECGEN_OPTION += --accept-ei
endif


######################################################
# Detect build option conflict

ifeq ($(OPT_GC),bibop)
ifeq ($(USE_EMBEDDED_INSTRUCTION),true)
$(error Cannot use BiBoP GC with embedded instruction)
endif
endif

ifeq ($(SUPERINSNTYPE),3)
ifeq ($(USE_VMDL),true)
$(error Cannot build SUPERINSNTYPE=3 with VMDL)
endif
endif

ifeq ($(USE_MBED),true)
ifeq ($(MBED_TARGET),)
$(error USE_MBED is true, but MBED_TARGET is empty.)
endif
ifeq ($(wildcard $(EJSVM_DIR)/mbed/$(MBED_TARGET)),)
$(error USE_MBED is true, but "$(EJSVM_DIR)/mbed/$(MBED_TARGET)" dose not found.)
endif
endif


######################################################
# files

GENERATED_HFILES = \
    prefix-generated.h \
    instructions-opcode.h \
    instructions-table.h \
    instructions-label.h \
    specfile-fingerprint.h

HFILES = $(GENERATED_HFILES) \
    prefix.h \
    context.h \
    header.h \
    builtin.h \
    hash.h \
    instructions.h \
    types.h \
    globals.h \
    extern.h \
    log.h \
    util.h \
    gc.h \
    context-inl.h \
    types-inl.h \
    util-inl.h \
    gc-inl.h
ifeq ($(USE_VMDL),true)
HFILES += vmdl-helper.h
endif

SUPERINSNS = $(shell $(GOTTA) --list-si)
SUPERINSNS_REQUIRE = $(GOTTA_REQUIRE)

OFILES = \
    allocate.o \
    builtin-array.o \
    builtin-boolean.o \
    builtin-global.o \
    builtin-math.o \
    builtin-number.o \
    builtin-object.o \
    builtin-regexp.o \
    builtin-string.o \
    builtin-function.o \
    builtin-performance.o \
    cstring.o \
    call.o \
    context.o \
    conversion.o \
    hash.o \
    init.o \
    string.o \
    object.o \
    operations.o \
    util.o \
    vmloop.o \
    gc.o \
    log.o \
    hcgloader.o \
    main.o
ifeq ($(USE_VMDL),true)
OFILES += vmdl-helper.o
ifeq ($(ICC_PROF),true)
OFILES += iccprof.o
endif
endif
ifeq ($(USE_MBED),true)
OFILES += mbed_util.o
else
ifneq ($(USE_EMBEDDED_INSTRUCTION),true)
OFILES += codeloader.o
endif
endif

ifeq ($(SUPERINSN_MAKEINSN),true)
    INSN_SUPERINSNS = $(patsubst %,insns/%.inc,$(SUPERINSNS))
    INSN_SUPERINSNS_REQUIRE = $(SUPERINSNS_REQUIRE)
endif

INSN_HANDCRAFT =

BUILTINS := $(shell ls $(EJSVM_DIR)/builtins-vmdl)

FUNCS := $(shell ls $(EJSVM_DIR)/funcs-vmdl)

VMDL_HEADERS = $(shell ls $(EJSVM_DIR)/header-vmdl)

INSNS = \
    add \
    bitand \
    bitor \
    call \
    construct \
    div \
    eq \
    equal \
    getprop \
    leftshift \
    lessthan \
    lessthanequal \
    mod \
    mul \
    rightshift \
    setprop \
    sub \
    tailcall \
    unsignedrightshift \
    fixnum \
    geta \
    getnewa \
    getarg \
    geterr \
    getglobal \
    getglobalobj \
    getlocal \
    instanceof \
    isobject \
    isundef \
    jump \
    jumpfalse \
    jumptrue \
    localcall \
    makeclosure \
    makeiterator \
    move \
    newframe \
    nextpropnameidx \
    not \
    bigprim \
    pushhandler \
    seta \
    setarg \
    setfl \
    setglobal \
    setlocal \
    specconst \
    typeof \
    end \
    localret \
    nop \
    pophandler \
    poplocal \
    ret \
    throw \
    unknown \
	exitframe

INSN_GENERATED = $(patsubst %,insns/%.inc,$(INSNS))
FUNC_GENERATED = $(patsubst %.vmd,funcs/%.inc,$(FUNCS))
BUILTIN_GENERATED = $(patsubst %.vmd,builtins/%.inc,$(BUILTINS))
INSNS_VMD = $(patsubst %,insns-vmdl/%.vmd,$(INSNS))
FUNCS_VMD = $(patsubst %.vmd,funcs-vmdl/%.vmd,$(FUNCS))
BUILTINS_VMD = $(patsubst %.vmd,builtins-vmdl/%.vmd,$(BUILTINS))
INSN_REQUIRED_FUNCSPECS  = $(patsubst %,$(VMDL_INSN_REQ_SPEC_DIR)/%_require.spec,$(INSNS))
BUILTIN_REQUIRED_FUNCSPECS  = $(patsubst %.vmd,$(VMDL_BUILTIN_REQ_SPEC_DIR)/%_require.spec,$(BUILTINS))
REQUIRED_FUNCSPECS = $(INSN_REQUIRED_FUNCSPECS) $(BUILTIN_REQUIRED_FUNCSPECS)

CFILES = $(patsubst %.o,%.c,$(OFILES))
CHECKFILES = $(patsubst %.c,$(CHECKFILES_DIR)/%.c,$(CFILES))
INSN_FILES = $(INSN_SUPERINSNS) $(INSN_GENERATED) $(INSN_HANDCRAFT)
FUNCS_FILES =
BUILTINS_FILES =
ifeq ($(USE_VMDL),true)
FUNCS_FILES += $(FUNC_GENERATED)
BUILTINS_FILES += $(BUILTIN_GENERATED)
endif

######################################################

CXX_FILES = gc.cc
HFILES    += gc-visitor-inl.h
ifeq ($(OPT_GC),native)
    CPPFLAGS+=-DUSE_NATIVEGC=1 -DMARKSWEEP -DFREELIST
    CXX_FILES+=marksweep-collector.cc
    OFILES+=marksweep-collector.o freelist-space.o
    HFILES+=freelist-space.h freelist-space-inl.h mark-tracer.h
endif
ifeq ($(OPT_GC),bibop)
    CPPFLAGS+=-DUSE_NATIVEGC=1 -DMARKSWEEP -DBIBOP
    CXX_FILES+=marksweep-collector.cc
    OFILES+=marksweep-collector.o bibop-space.o
    HFILES+=bibop-space.h bibop-space-inl.h mark-tracer.h
endif
ifeq ($(OPT_GC),copy)
    CPPFLAGS+=-DUSE_NATIVEGC=1 -DCOPYGC
    CXX_FILES+=copy-collector.cc
    OFILES+=copy-collector.o
    HFILES+=copy-collector.h
endif
ifeq ($(OPT_GC),jonkers)
    CPPFLAGS+=-DUSE_NATIVEGC=1 -DTHREADED -DJONKERS
    CXX_FILES+=threadedcompact-collector.cc
    OFILES+=threadedcompact-collector.o threaded-space.o jonkers-space.o
    HFILES+=threadedcompact-collector.h jonkers-collector-inl.h threaded-functions-inl.h jonkers-space.h threaded-space.h jonkers-space-inl.h threaded-space-inl.h threaded-tracer.h mark-tracer.h
endif
ifeq ($(OPT_GC),fusuma)
    CPPFLAGS+=-DUSE_NATIVEGC=1 -DTHREADED -DFUSUMA
    CXX_FILES+=threadedcompact-collector.cc
    OFILES+=threadedcompact-collector.o threaded-space.o fusuma-space.o
    HFILES+=threadedcompact-collector.h fusuma-collector-inl.h threaded-functions-inl.h fusuma-space.h threaded-space.h fusuma-space-inl.h threaded-space-inl.h threaded-tracer.h mark-tracer.h
endif
ifeq ($(OPT_GC),lisp2)
    CPPFLAGS+=-DUSE_NATIVEGC=1 -DLISP2
    CXX_FILES+=lisp2-collector.cc
    OFILES+=lisp2-collector.o lisp2-space.o
    HFILES+=lisp2-space.h lisp2-space-inl.h mark-tracer.h
endif

ifeq ($(OPT_REGEXP),oniguruma)
    CPPFLAGS+=-DUSE_REGEXP=1
    LIBS+=-lonig
endif

ifeq ($(DATATYPES),)
    GENERATED_HFILES += types-handcraft.h
else
    CPPFLAGS += -DUSE_TYPES_GENERATED=1
    GENERATED_HFILES += types-generated.h
endif

ifeq ($(USE_MBED),true)
CXX_FILES += mbed_util.cc
endif


CPPMACROS = $(filter -D%,$(CPPFLAGS)) $(filter -U%,$(CPPFLAGS))
CPPOPTS = $(filter-out $(CPPMACROS),$(CPPFLAGS))
CMACROS = $(filter -D%,$(CFLAGS)) $(filter -U%,$(CFLAGS))
COPTS = $(filter-out $(CMACROS),$(CFLAGS))
CXXMACROS = $(filter -D%,$(CXXFLAGS)) $(filter -U%,$(CXXFLAGS))
CXXOPTS = $(filter-out $(CXXMACROS),$(CXXFLAGS))

CHECKFILES_DIR = checkfiles
GCCHECK_PATTERN = $(EJSVM_DIR)/gccheck.cocci

######################################################

define vmdl_funcs_preprocess
	$(FUNCGEN_VMDL) $(VMDLC_FLAGS) -Xgen:type_label true \
		-d $(DATATYPES) -o $(VMDL_FUNCANYSPEC) \
		-i $(EJSVM_DIR)/instructions.def -preprocess \
		-write-fi ${VMDL_INLINE} -write-ftd ${VMDL_FUNCDEPENDENCY} -write-extern $(VMDL_GENERATED_H) $(VMDL_EXTERN)\
		-write-opspec-creq $(VMDL_FUNCDPECCREQUIRE)\
		$(1) \
		|| (rm -f $(VMDL_INLINE); rm -f $(VMDL_FUNCDEPENDENCY); rm -f $(VMDL_GENERATED_H); rm -f $(VMDL_EXTERN); exit 1)

endef


######################################################
ifeq ($(USE_MBED),true)
all: ejsvm.bin connect_mbed
CPPFLAGS += -DUSE_MBED
else
all: ejsvm ejsc.jar ejsi
endif

ejsc.jar: $(EJSC)
	cp $< $@

ejsi: $(EJSI)
	cp $< $@

ifeq ($(USE_EMBEDDED_INSTRUCTION),true)
only-code: $(filter-out $(patsubst %.cc,%.c,$(CXX_FILES)),$(CFILES)) $(CXX_FILES) $(HFILES) vmloop-cases.inc $(EMBEDDED_INSTRUCTION_INC) $(LD_SCRIPT_FILE) $(INSN_FILES) $(VMDL_EXTERN)
endif

ejsvm :: $(OFILES) ejsvm.spec $(LD_SCRIPT_FILE)
	$(CC) $(LDFLAGS) -o $@ $(OFILES) $(LIBS) $(LD_SCRIPT)

instructions-opcode.h: $(GOTTA_REQUIRE)
	($(GOTTA) --gen-insn-opcode -o $@) || (rm -f $@; exit 1)

instructions-table.h: $(GOTTA_REQUIRE)
	($(GOTTA) --gen-insn-table -o $@) || (rm -f $@; exit 1)

instructions-label.h: $(GOTTA_REQUIRE)
	($(GOTTA) --gen-insn-label -o $@) || (rm -f $@; exit 1)

vmloop-cases.inc: $(GOTTA_REQUIRE)
	($(GOTTA) --gen-vmloop-cases -o $@) || (rm -f $@; exit 1)

$(LD_SCRIPT_FILE): $(LD_SCRIPT_RAW) $(LD_SCRIPT_INC) $(HFILES)
	( \
		(cat $(LD_SCRIPT_RAW) | $(CC) $(CPPOPTS) -E -P $(addprefix -imacros ,$(filter-out gc-visitor-inl.h,$(HFILES))) -Ui386 -o $@ - ) \
		&& ($(SED) -i -e '/^ *$$/d' $@) \
	) || (rm -f $@; exit 1)

ifeq ($(SUPERINSNTYPE),)
ejsvm.spec specfile-fingerprint.h: $(EJSVM_DIR)/instructions.def $(SPECGEN_JAR)
	($(SPECGEN) --datatype $(DATATYPES) --insndef $(EJSVM_DIR)/instructions.def \
		--bitwidth-insn $(BITWIDTH_INSN) --bitwidth-jsv $(BITWIDTH_JSVALUE) --bitwidth-align $(BITWIDTH_ALIGN) \
		--fingerprint specfile-fingerprint.h $(SPECGEN_OPTION) -o ejsvm.spec \
	) || (rm -f ejsvm.spec specfile-fingerprint.h; exit 1)
else
ejsvm.spec specfile-fingerprint.h: $(EJSVM_DIR)/instructions.def $(SPECGEN_JAR) $(SUPERINSNSPEC)
	($(SPECGEN) --datatype $(DATATYPES) --insndef $(EJSVM_DIR)/instructions.def \
		--bitwidth-insn $(BITWIDTH_INSN) --bitwidth-jsv $(BITWIDTH_JSVALUE) --bitwidth-align $(BITWIDTH_ALIGN) \
		--sispec $(SUPERINSNSPEC) --fingerprint specfile-fingerprint.h $(SPECGEN_OPTION) -o ejsvm.spec \
	) || (rm -f ejsvm.spec specfile-fingerprint.h; exit 1)
endif

$(INSN_HANDCRAFT):insns/%.inc: $(EJSVM_DIR)/insns-handcraft/%.inc
	mkdir -p insns
	cp $< $@

header-vmdl/%.vmdh: $(EJSVM_DIR)/header-vmdl/%.vmdh prefix.h prefix-generated.h
	mkdir -p header-vmdl
	cp $< $@

insns-vmdl/%.vmd: $(EJSVM_DIR)/insns-vmdl/%.vmd $(addprefix header-vmdl/,$(VMDL_HEADERS))
	mkdir -p insns-vmdl
	cp $< $@.tmp
	($(CPP_VMDL) -o $@ $@.tmp && rm $@.tmp) || (rm -f $@ $@.tmp; exit 1)

funcs-vmdl/%.vmd: $(EJSVM_DIR)/funcs-vmdl/%.vmd $(addprefix header-vmdl/,$(VMDL_HEADERS))
	mkdir -p funcs-vmdl
	cp $< $@.tmp
	($(CPP_VMDL) -o $@ $@.tmp && rm $@.tmp) || (rm -f $@ $@.tmp; exit 1)

builtins-vmdl/%.vmd: $(EJSVM_DIR)/builtins-vmdl/%.vmd $(addprefix header-vmdl/,$(VMDL_HEADERS))
	mkdir -p builtins-vmdl
	cp $< $@.tmp
	($(CPP_VMDL) -o $@ $@.tmp && rm $@.tmp) || (rm -f $@ $@.tmp; exit 1)

ifeq ($(DATATYPES),)
$(INSN_GENERATED):insns/%.inc: $(EJSVM_DIR)/insns-handcraft/%.inc
	mkdir -p insns
	cp $< $@
else
ifeq ($(SUPERINSN_REORDER_DISPATCH),true)
INSN_CMP_TREE_LAYER = `$(GOTTA) --print-dispatch-order $(patsubst insns/%.inc,%,$@)`
INSN_CMP_TREE_LAYER_REQUIRE = $(GOTTA_REQUIRE)
else
INSN_CMP_TREE_LAYER = p0:p1:p2:h0:h1:h2
INSN_CMP_TREE_LAYER_REQUIRE =
endif
ifeq ($(USE_VMDL), true)
$(VMDL_FUNCANYSPEC):
	mkdir -p $(VMDL_WORKSPACE)
	cp $(EJSVM_DIR)/function-spec/any.spec $@
$(VMDL_FUNCNEEDSPEC): $(VMDL) $(VMDL_FUNCDEPENDENCY) $(REQUIRED_FUNCSPECS)
	mkdir -p $(VMDL_WORKSPACE)
	($(FUNCGEN_VMDL) -ftd $(VMDL_FUNCDEPENDENCY) -gen-funcspec $(REQUIRED_FUNCSPECS) > $@) || (rm -f $@; exit 1)
$(VMDL_FUNCDEPENDENCY) $(VMDL_GENERATED_H) $(VMDL_EXTERN) $(VMDL_FUNCDPECCREQUIRE): $(VMDL_INLINE)
$(VMDL_INLINE): $(VMDL) $(FUNCS_VMD) $(VMDL_FUNCANYSPEC)
	mkdir -p $(VMDL_WORKSPACE)
	rm -f $(VMDL_INLINE)
	rm -f $(VMDL_FUNCDEPENDENCY)
	rm -f $(VMDL_GENERATED_H)
	rm -f $(VMDL_EXTERN)
	rm -f $(VMDL_FUNCDPECCREQUIRE)
	touch $(VMDL_FUNCDEPENDENCY)
	$(foreach FILE_VMD, $(FUNCS_VMD), $(call vmdl_funcs_preprocess,$(FILE_VMD)))
$(INSN_REQUIRED_FUNCSPECS):$(VMDL_INSN_REQ_SPEC_DIR)/%_require.spec: insns/%.inc
$(INSN_GENERATED):insns/%.inc: insns-vmdl/%.vmd $(VMDL) $(VMDL_INLINE) $(VMDL_FUNCDPECCREQUIRE) $(INSN_CMP_TREE_LAYER_REQUIRE)
	mkdir -p $(VMDL_INSN_REQ_SPEC_DIR)
	cp -n $(VMDL_FUNCDPECCREQUIRE) $(patsubst insns/%.inc,$(VMDL_INSN_REQ_SPEC_DIR)/%_require.spec,$@)
	mkdir -p insns
	($(INSNGEN_VMDL) $(VMDLC_FLAGS) $(VMDL_OPTION_FLAGS) \
		-Xgen:type_label true \
		-Xcmp:tree_layer $(INSN_CMP_TREE_LAYER) \
		-d $(DATATYPES) -o $(OPERANDSPEC) -i $(EJSVM_DIR)/instructions.def \
		-update-funcspec $(patsubst insns/%.inc,$(VMDL_INSN_REQ_SPEC_DIR)/%_require.spec,$@) $< > $@ \
	) || (rm -f $@ $(patsubst insns/%.inc,$(VMDL_INSN_REQ_SPEC_DIR)/%_require.spec,$@); exit 1)
$(BUILTIN_REQUIRED_FUNCSPECS):$(VMDL_BUILTIN_REQ_SPEC_DIR)/%_require.spec: builtins/%.inc
$(BUILTIN_GENERATED):builtins/%.inc: builtins-vmdl/%.vmd $(VMDL) $(VMDL_INLINE) $(VMDL_FUNCDPECCREQUIRE) $(INSN_CMP_TREE_LAYER_REQUIRE)
	mkdir -p $(VMDL_BUILTIN_REQ_SPEC_DIR)
	cp -n $(VMDL_FUNCDPECCREQUIRE) $(patsubst builtins/%.inc,$(VMDL_BUILTIN_REQ_SPEC_DIR)/%_require.spec,$@)
	mkdir -p builtins
	($(BUILTINGEN_VMDL) $(VMDLC_FLAGS) $(VMDL_OPTION_FLAGS) \
		-Xgen:type_label true \
		-Xcmp:tree_layer $(INSN_CMP_TREE_LAYER) \
		-d $(DATATYPES) -o $(BUILTINSPEC) -i $(EJSVM_DIR)/instructions.def \
		-update-funcspec $(patsubst builtins/%.inc,$(VMDL_BUILTIN_REQ_SPEC_DIR)/%_require.spec,$@) $< > $@ \
	) || (rm -f $@ $(patsubst builtins/%.inc,$(VMDL_BUILTIN_REQ_SPEC_DIR)/%_require.spec,$@); exit 1)
$(FUNC_GENERATED):funcs/%.inc: funcs-vmdl/%.vmd $(VMDL) $(VMDL_FUNCNEEDSPEC) $(INSN_CMP_TREE_LAYER_REQUIRE)
	mkdir -p funcs
	($(FUNCGEN_VMDL) $(VMDLC_FLAGS) $(VMDL_OPTION_INLINE) $(VMDL_OPTION_IFSTYLE)\
		-Xgen:type_label true \
		-Xcmp:tree_layer $(INSN_CMP_TREE_LAYER) \
	-d $(DATATYPES) -o $(VMDL_FUNCNEEDSPEC) -i $(EJSVM_DIR)/instructions.def $< > $@) || (rm -f $@; exit 1)
else
$(INSN_GENERATED):insns/%.inc: $(EJSVM_DIR)/insns-def/%.idef $(VMGEN) $(INSN_CMP_TREE_LAYER_REQUIRE)
	mkdir -p insns
	($(INSNGEN_VMGEN) $(INSNGEN_FLAGS) \
		-Xgen:type_label true \
		-Xcmp:tree_layer $(INSN_CMP_TREE_LAYER) \
		$(DATATYPES) $< $(OPERANDSPEC) insns \
	) || (rm -f $@; exit 1)
endif
endif

# generate si-otspec/*.ot for each superinsns
SI_OTSPEC_DIR = si/otspec
SI_OTSPECS = $(patsubst %,$(SI_OTSPEC_DIR)/%.ot,$(SUPERINSNS))
SI_OTSPECS_REQUIRE = $(SUPERINSNS_REQUIRE)
ifeq ($(SUPERINSN_CUSTOMIZE_OT),true)
$(SI_OTSPECS): $(SI_OTSPECS_REQUIRE)
	mkdir -p $(SI_OTSPEC_DIR)
	($(GOTTA) --gen-ot-spec $(patsubst $(SI_OTSPEC_DIR)/%.ot,%,$@) -o $@) || (rm -f $@; exit 1)
else
$(SI_OTSPECS): $(SI_OTSPECS_REQUIRE)
	mkdir -p $(SI_OTSPEC_DIR)
	cp $< $@
endif


# generate insns/*.inc for each superinsns
ifeq ($(DATATYPES),)
$(INSN_SUPERINSNS):
	echo "Superinstruction needs DATATYPES specified"
	exit 1
else

SI_IDEF_DIR = si/idefs
orig_insn = \
    $(shell $(GOTTA) --print-original-insn-name $(patsubst insns/%.inc,%,$1))
tmp_idef = $(SI_IDEF_DIR)/$(patsubst insns/%.inc,%,$1)

SI_CMP_TREE_LAYER = p0:p1:p2:h0:h1:h2
ifeq ($(SUPERINSN_PSEUDO_IDEF),true)
ifeq ($(USE_VMDL), true)
$(INSN_SUPERINSNS):insns/%.inc: $(EJSVM_DIR)/insns-vmdl/* $(INSN_SUPERINSNS_REQUIRE) $(GOTTA_REQUIRE) $(SI_OTSPEC_DIR)/%.ot $(VMDL)
	mkdir -p $(SI_IDEF_DIR)
	($(GOTTA) \
		--gen-pseudo-vmdl $(call orig_insn,$@) $(patsubst insns/%.inc,%,$@) \
		-o $(call tmp_idef,$@).vmd) || (rm -f $(call tmp_idef,$@).vmd; exit 1)
	mkdir -p insns
	($(INSNGEN_VMDL) $(VMDLC_FLAGS) \
		-Xgen:label_prefix $(patsubst insns/%.inc,%,$@) \
		-Xcmp:tree_layer $(SI_CMP_TREE_LAYER) \
		-d $(DATATYPES) \
		-i $(EJSVM_DIR)/instructions.def \
		-o $(patsubst insns/%.inc,$(SI_OTSPEC_DIR)/%.ot,$@) \
		$(call tmp_idef,$@).vmd > $@) || (rm -f $@; exit 1)
else
$(INSN_SUPERINSNS):insns/%.inc: $(EJSVM_DIR)/insns-def/* $(INSN_SUPERINSNS_REQUIRE) $(GOTTA_REQUIRE) $(SI_OTSPEC_DIR)/%.ot $(VMGEN)
	mkdir -p $(SI_IDEF_DIR)
	($(GOTTA) \
		--gen-pseudo-idef $(call orig_insn,$@) \
		-o $(call tmp_idef,$@).idef) || (rm -f $(call tmp_idef,$@).idef; exit 1)
	mkdir -p insns
	($(INSNGEN_VMGEN) $(INSNGEN_FLAGS) \
		-Xgen:label_prefix $(patsubst insns/%.inc,%,$@) \
		-Xcmp:tree_layer $(SI_CMP_TREE_LAYER) \
		$(DATATYPES) \
		$(call tmp_idef,$@).idef \
		$(patsubst insns/%.inc,$(SI_OTSPEC_DIR)/%.ot,$@) > $@) || (rm -f $@; exit 1)
endif
else
ifeq ($(USE_VMDL), true)
$(INSN_SUPERINSNS):insns/%.inc: $(EJSVM_DIR)/insns-vmdl/* $(INSN_SUPERINSNS_REQUIRE) $(GOTTA_REQUIRE) $(SI_OTSPEC_DIR)/%.ot $(VMDL) insns-vmdl/*.vmd
	mkdir -p insns
	($(INSNGEN_VMDL) $(VMDLC_FLAGS) \
		-Xgen:label_prefix $(patsubst insns/%.inc,%,$@) \
		-Xcmp:tree_layer $(SI_CMP_TREE_LAYER) \
		-d $(DATATYPES) \
		-i $(EJSVM_DIR)/instructions.def \
		-o $(patsubst insns/%.inc,$(SI_OTSPEC_DIR)/%.ot,$@) \
		insns-vmdl/$(call orig_insn,$@).vmd > $@) || (rm -f $@; exit 1)
else
$(INSN_SUPERINSNS):insns/%.inc: $(EJSVM_DIR)/insns-def/* $(INSN_SUPERINSNS_REQUIRE) $(GOTTA_REQUIRE) $(SI_OTSPEC_DIR)/%.ot $(VMGEN)
	mkdir -p insns
	($(INSNGEN_VMGEN) $(INSNGEN_FLAGS) \
		-Xgen:label_prefix $(patsubst insns/%.inc,%,$@) \
		-Xcmp:tree_layer $(SI_CMP_TREE_LAYER) \
		$(DATATYPES) \
		$(EJSVM_DIR)/insns-def/$(call orig_insn,$@).idef \
		$(patsubst insns/%.inc,$(SI_OTSPEC_DIR)/%.ot,$@) > $@) || (rm -f $@; exit 1)
endif
endif
endif

$(EMBEDDED_INSTRUCTION_INC_PATH) $(LD_SCRIPT_INC_PATH): target-gen-embedded-instruction

ifeq ($(USE_LEGACY_EJSC_PARSER),true)
target-gen-embedded-instruction: ejsc.jar ejsvm.spec $(JSSRC_PATH)
	(java -jar ejsc.jar --out-ei --spec ejsvm.spec $(EJSC_OPT) -o $(EMBEDDED_INSTRUCTION_INC) $(JSSRC_PATH)) \
	|| (rm -f $(EMBEDDED_INSTRUCTION_INC_PATH) $(LD_SCRIPT_INC_PATH); exit 1)
else
target-gen-embedded-instruction: ejsc.jar ejsvm.spec $(JSSRC_PATH)
#	node $(EJSC_DIR)/js/ejsc.js ejsc.jar --out-ei --spec ejsvm.spec $(EJSC_OPT) -o $(EMBEDDED_INSTRUCTION_INC) $(JSSRC_PATH)
	(node $(EJSC_DIR)/js/ejsc.js --out-ei --spec ejsvm.spec $(EJSC_OPT) -o $(EMBEDDED_INSTRUCTION_INC) $(JSSRC_PATH)) \
	|| (rm -f $(EMBEDDED_INSTRUCTION_INC_PATH) $(LD_SCRIPT_INC_PATH); exit 1)
endif

instructions.h: instructions-opcode.h instructions-table.h

ifeq ($(USE_VMDL),true)
extern.h: $(VMDL_GENERATED_H)
endif

prefix-generated.h: $(MAKEFILE_LIST)
	(echo "#ifndef DEFINITIONS_H" > $@ \
	&& echo "#define DEFINITIONS_H" >> $@ \
	&& echo "#ifdef __cplusplus" >> $@ \
	&& printf '$(foreach name,$(filter -D%,$(CXXMACROS)),#define $(subst =, ,$(patsubst -D%,%,$(name)))\n)' | $(SED) -e 's/^\s*//g' >> $@ \
	&& printf '$(foreach name,$(filter -U%,$(CXXMACROS)),#undef $(subst =, ,$(patsubst -U%,%,$(name)))\n)' | $(SED) -e 's/^\s*//g' >> $@ \
	&& echo "#else  /* __cplusplus */" >> $@ \
	&& printf '$(foreach name,$(filter -D%,$(CMACROS)),#define $(subst =, ,$(patsubst -D%,%,$(name)))\n)' | $(SED) -e 's/^\s*//g' >> $@ \
	&& printf '$(foreach name,$(filter -U%,$(CMACROS)),#undef $(subst =, ,$(patsubst -U%,%,$(name)))\n)' | $(SED) -e 's/^\s*//g' >> $@ \
	&& echo "#endif /* __cplusplus */" >> $@ \
	&& printf '$(foreach name,$(filter -D%,$(CPPMACROS)),#define $(subst =, ,$(patsubst -D%,%,$(name)))\n)' | $(SED) -e 's/^\s*//g' >> $@ \
	&& printf '$(foreach name,$(filter -U%,$(CPPMACROS)),#undef $(subst =, ,$(patsubst -U%,%,$(name)))\n)' | $(SED) -e 's/^\s*//g' >> $@ \
	&& echo "#endif /* DEFINITIONS_H */" >> $@ \
	&& echo $^ \
	) || (rm -f $@; exit 1)

$(CXX_FILES):%.cc: $(EJSVM_DIR)/%.cc
	cp $< $@

%.c:: $(EJSVM_DIR)/%.c $(FUNCS_FILES)
	cp $< $@

%.h:: $(EJSVM_DIR)/%.h
	cp $< $@

$(patsubst %.cc,%.o,$(CXX_FILES)):%.o:%.cc $(HFILES)
	$(CXX) -c $(CPPOPTS) $(CXXOPTS) -o $@ $<

vmloop.o: vmloop.c vmloop-cases.inc $(EMBEDDED_INSTRUCTION_INC) $(INSN_FILES) $(HFILES) $(VMDL_EXTERN)
	$(CC) -c $(CPPOPTS) $(COPTS) -o $@ $<

conversion.o: conversion.c $(FUNCS_FILES) $(HFILES) $(VMDL_EXTERN)
	$(CC) -c $(CPPOPTS) $(COPTS) -o $@ $<

builtin-%.o: builtin-%.c $(BUILTINS_FILES) $(HFILES) $(VMDL_EXTERN)
	$(CC) -c $(CPPOPTS) $(COPTS) -o $@ $<

%.o: %.c $(HFILES)
	$(CC) -c $(CPPOPTS) $(COPTS) -o $@ $<


#### mbed
MBED_DIR = mbed_build
MBED_DIR_DUMMY = $(MBED_DIR)/.dummy

MBED_CFILES = $(filter-out $(patsubst %.cc,%.c,$(CXX_FILES)),$(CFILES))
MBED_CXXFILES = $(patsubst %.cc,%.cpp,$(CXX_FILES))
MBED_VMGEN_FILES = $(INSN_FILES)
MBED_VMDL_FILES = $(INSN_FILES) $(VMDL_EXTERN) $(VMDL_GENERATED_H) $(FUNCS_FILES) $(BUILTINS_FILES)
MBED_INC_FILES = vmloop-cases.inc embedded_instructions.inc embedded_instructions.inc.ld
ifeq ($(USE_VMDL),true)
MBED_FILES = $(addprefix $(MBED_DIR)/,$(HFILES) $(MBED_CFILES) $(MBED_CXXFILES) $(MBED_INC_FILES) $(MBED_VMDL_FILES))
else
MBED_FILES = $(addprefix $(MBED_DIR)/,$(HFILES) $(MBED_CFILES) $(MBED_CXXFILES) $(MBED_INC_FILES) $(MBED_VMGEN_FILES))
endif


MBED_SRC_DIR=$(EJSVM_DIR)/mbed

MBED_OS=$(MBED_SRC_DIR)/mbed-os
MBED_BUILD_MBED_OS=$(MBED_SRC_DIR)/BUILD/mbed-os
MBED_CONFIG=$(MBED_SRC_DIR)/common/mbed_config.h
MBED_LINKER_SCRIPT=$(MBED_SRC_DIR)/$(MBED_TARGET)/linker_script_raw.ld
MBED_APP=$(MBED_SRC_DIR)/common/mbed_app.json
MBED_DOT_MBED=$(MBED_SRC_DIR)/common/.mbed

export CXX_FLAGS = $(CPPOPTS) $(CXXOPTS)
export C_FLAGS = $(CPPOPTS) $(COPTS)
export EJS_LD_FLAGS = $(addprefix -imacros ,$(filter-out gc-visitor-inl.h,$(HFILES)))
export LINKER_SCRIPT = ../../$(MBED_LINKER_SCRIPT)

ejsvm.bin: $(MBED_DIR)/Makefile
	$(MAKE) -C $(MBED_DIR) $(MBED_DIR).bin
	cp $(MBED_DIR)/BUILD/$(MBED_DIR).bin $@

$(MBED_DIR)/Makefile: $(MBED_DIR_DUMMY) $(MBED_FILES)
	(cd $(MBED_DIR); mbed export -m $(MBED_TARGET) -i make_gcc_arm)
	($(SED) -i 's/^\(.\+\? -Og\)$$/#\1/g' $@ \
	&& $(SED) -i 's/ -Og / /g' $@ \
	&& $(SED) -i 's/$$(PREPROC)/$$(PREPROC) $$(EJS_LD_FLAGS) -I $$(abspath $$(dir $$@)..\/)/g' $@ \
	) || (rm -f $@; exit 1)

$(MBED_DIR_DUMMY):
#	mbed new $(MBED_DIR)
	(mkdir -p $(MBED_DIR) \
	&& mkdir -p $(MBED_DIR)/BUILD \
	&& cp $(MBED_DOT_MBED) $(MBED_DIR)/.mbed \
	&& ln -sf $(abspath $(MBED_CONFIG)) $(MBED_DIR)/mbed_config.h \
	&& cp $(MBED_APP) $(MBED_DIR)/mbed_app.json \
	&& ln -sf $(abspath $(MBED_OS)) $(MBED_DIR)/mbed-os \
	&& ln -sf $(abspath $(MBED_BUILD_MBED_OS)) $(MBED_DIR)/BUILD/mbed-os \
	&& touch $@ \
	) || (\
	if [ -L $(MBED_DIR)/mbed-config.h ]; then unlink $(MBED_DIR)/mbed-config.h; fi; \
	if [ -L $(MBED_DIR)/mbed-os ]; then unlink $(MBED_DIR)/mbed-os; fi; \
	if [ -L $(MBED_DIR)/BUILD/mbed-os ]; then unlink $(MBED_DIR)/BUILD/mbed-os; fi; \
	rm -rf $(MBED_DIR); \
	exit 1 \
	)

$(MBED_DIR)/%.h: %.h $(MBED_DIR_DUMMY)
	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	cp $< $@
$(MBED_DIR)/%.c: %.c $(MBED_DIR_DUMMY)
	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	cp $< $@
$(MBED_DIR)/%.cpp: %.cc $(MBED_DIR_DUMMY)
	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	cp $< $@
$(MBED_DIR)/%.inc: %.inc $(MBED_DIR_DUMMY)
	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	cp $< $@

$(MBED_DIR)/$(EMBEDDED_INSTRUCTION_INC_PATH): $(EMBEDDED_INSTRUCTION_INC) $(MBED_DIR_DUMMY)
	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	cp $< $@

$(MBED_DIR)/$(LD_SCRIPT_INC_PATH): $(LD_SCRIPT_INC) $(MBED_DIR_DUMMY)
	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	cp $< $@


connect_mbed: $(EJSVM_DIR)/mbed/common/reset_and_read.c
	$(CC) -O -o connect_mbed $(EJSVM_DIR)/mbed/common/reset_and_read.c

#### vmgen
.PHONY: build-vmgen
build-vmgen: $(VMGEN)

$(VMGEN):
	(cd $(VMGEN_DIR); ant)

#### vmdl
.PHONY: build-vmdlc
build-vmdlc: $(VMDL)

$(VMDL):
	(cd $(VMDL_DIR); ant)

#### ejsc
.PHONY: build-ejsc
build-ejsc: $(EJSC)

ifeq ($(SKIP_EMBEDDING_SPEC_INTO_EJSC), true)
# For running CI
$(EJSC): $(VMGEN)
	(cd $(EJSC_DIR); ant clean; ant)
else
$(EJSC): $(VMGEN) ejsvm.spec
	(cd $(EJSC_DIR); ant clean; ant -Dspecfile=$(CURDIR)/ejsvm.spec)
endif

#### ejsi
.PHONY: build-ejsi
build-ejsi: $(EJSI)

$(EJSI):
	make -C $(EJSI_DIR)

#### check

CHECKFILES   = $(patsubst %.c,$(CHECKFILES_DIR)/%.c,$(CFILES))
CHECKRESULTS = $(patsubst %.c,$(CHECKFILES_DIR)/%.c.checkresult,$(CFILES))
CHECKTARGETS = $(patsubst %.c,%.c.check,$(CFILES))

ifeq ($(USE_VMDL),true)
types-generated.h: $(DATATYPES) $(VMDL)
	($(TYPESGEN_VMDL) $< > $@) || (rm -f $@; exit 1)
else
types-generated.h: $(DATATYPES) $(VMGEN)
	($(TYPESGEN_VMGEN) $< > $@) || (rm -f $@; exit 1)
endif

$(CHECKFILES):$(CHECKFILES_DIR)/%.c: %.c $(HFILES)
	mkdir -p $(CHECKFILES_DIR)
	$(CPP) $(CPPOPTS) $(COPTS) -DCOCCINELLE_CHECK=1 $< > $@ || (rm -f $@; exit 1)

$(CHECKFILES_DIR)/vmloop.c: vmloop-cases.inc $(INSN_FILES)

.PHONY: %.check
$(CHECKTARGETS):%.c.check: $(CHECKFILES_DIR)/%.c
	$(COCCINELLE) --sp-file $(GCCHECK_PATTERN) $< || (rm -f $@; exit 1)

$(CHECKRESULTS):$(CHECKFILES_DIR)/%.c.checkresult: $(CHECKFILES_DIR)/%.c
	$(COCCINELLE) --sp-file $(GCCHECK_PATTERN) $< > $@ || (rm -f $@; exit 1)

check: $(CHECKRESULTS)
	cat $^

#### clean

clean: clean-mbed-build
	rm -f *.o $(GENERATED_HFILES) vmloop-cases.inc *.c *.cc *.h *.ld *.inc
	rm -rf insns
	rm -rf funcs
	rm -f *.checkresult
	rm -rf $(CHECKFILES_DIR)
	rm -rf si
	rm -rf header-vmdl
	rm -rf insns-vmdl
	rm -rf funcs-vmdl
	rm -rf builtins
	rm -rf builtins-vmdl
	rm -rf vmdl_workspace
	rm -f ejsvm ejsvm.spec ejsi ejsc.jar ejsvm.bin connect_mbed

cleanest: clean clean-vmgen clean-vmdl clean-ejsc clean-ejsi clean-mbed-os
cleanest-no-mbed-os: clean clean-vmgen clean-vmdl clean-ejsc clean-ejsi

clean-vmgen:
	(cd $(VMGEN_DIR); ant clean)
	rm -f $(VMGEN)

clean-vmdl:
	(cd $(VMDL_DIR); ant clean)
	rm -f $(VMDL)

clean-ejsc:
	(cd $(EJSC_DIR); ant clean)
	rm -f $(EJSC)

clean-ejsi:
	make -C $(EJSI_DIR) clean

clean-mbed-build:
	if [ -L $(MBED_DIR)/mbed-os ]; then unlink $(MBED_DIR)/mbed-os; fi
	if [ -L $(MBED_DIR)/BUILD/mbed-os ]; then unlink $(MBED_DIR)/BUILD/mbed-os; fi
	if [ -L $(MBED_DIR)/mbed-config.h ]; then unlink $(MBED_DIR)/mbed-config.h; fi;
	rm -rf $(MBED_DIR)

clean-mbed-os:
	rm -rf $(MBED_BUILD_MBED_OS)/*
