# JSC = ../../../ejs/compiler/tjs-c/tjs-c/tjscompiler
# JSC = java -classpath ../../../ejs/ejsc/compiler.jar Main
FLAGS =

jsfiles = 3d-cube.sbc \
  3d-morph.sbc \
  3d-raytrace.sbc \
  access-binary-trees.sbc \
  access-fannkuch.sbc \
  access-nbody.sbc \
  access-nsieve.sbc \
  bitops-3bit-bits-in-byte.sbc \
  bitops-bits-in-byte.sbc \
  bitops-bitwise-and.sbc \
  bitops-nsieve-bits.sbc \
  controlflow-recursive.sbc \
  crypto-aes.sbc \
  crypto-md5.sbc \
  crypto-sha1.sbc \
  math-cordic.sbc \
  math-partial-sums.sbc \
  math-spectral-norm.sbc \
  regexp-dna.sbc \
  string-base64.sbc \
  string-fasta.sbc \
  string-unpack-code.sbc \
  string-validate-input.sbc

ifdef JSC
%.sbc: %.js
	$(JSC) $(FLAGS) $<

all: $(jsfiles)

else
all:
	echo please set compiler path \"JSC\"
endif

clean:
	rm *.sbc
