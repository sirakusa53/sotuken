EJSC=../../../ejs/build/ejsc.jar
EJSC_FLAGS = -O

BENCHMARKS = DeltaBlue.sbc Havlak.sbc CD.sbc Bounce.sbc Richards.sbc List.sbc Mandelbrot.sbc NBody.sbc Permute.sbc Queens.sbc Sieve.sbc Storage.sbc Towers.sbc Json.sbc

PATCH_FILES = CD.patch Richards.patch Queens.patch Json.patch

DYN_PATCH = CD.dyn.patch DeltaBlue.dyn.patch
# Bounce

COMMON_JS = ejs.js benchmark.js harness.js som.js

all: $(BENCHMARKS)
alljs: $(patsubst %.sbc, %-all.js, $(BENCHMARKS))
nodejs: $(patsubst %.sbc, %-node.js, $(BENCHMARKS))
alldyn: $(patsubst %.dyn.patch, %-dyn.sbc, $(DYN_PATCH))
alldynjs: $(patsubst %.dyn.patch, %-dyn-all.js, $(DYN_PATCH))

$(patsubst %.patch, %.ejs.js, $(PATCH_FILES)): %.ejs.js: %.js
	patch $< -o $@ < $*.patch

%.ejs.js: %.js
	cp $< $@

$(patsubst %.dyn.patch, %-dyn.ejs.js, $(DYN_PATCH)): %-dyn.ejs.js: %.ejs.js
	patch $< -o $@ < $*.dyn.patch

#%-dyn.sbc: %-dyn.ejs.js
#	java -jar $(EJSC) $(COMMON_JS) $< $(EJSC_FLAGS) -o $@

%.sbc: %.ejs.js $(COMMON_JS)
	java -jar $(EJSC) $(COMMON_JS) $< $(EJSC_FLAGS) -o $@

%-all.js: %.ejs.js $(COMMON_JS)
	cat $(COMMON_JS) $< > $@

%-node.js: %.ejs.js $(COMMON_JS) node-header.js
	cat node-header.js $(COMMON_JS) $< > $@
