#!/bin/bash

now=`date +%Y%m%d_%H-%M-%S`
program=$1
N=$2


tag=result/${now}_${program%.js}
jsdir=tests
jsdirv7=tests

mkdir -p tmp
sbc=tmp/${program%.js}.sbc
rm -r $sbc
echo "tag=$tag"
echo "sbc=$sbc"
java -jar ./compiler/compiler.jar $jsdir/$program -o $sbc
./run_sbc_simple.sh ./vm/arm/ejsvm/ejsvm-default-Os     $sbc $N | gawk '{print "default "$1}'     >> $tag
./run_sbc_simple.sh ./vm/arm/ejsvm/ejsvm-array-tag-Os   $sbc $N | gawk '{print "array-tag "$1}'   >> $tag
./run_sbc_simple.sh ./vm/arm/ejsvm/ejsvm-string-only-Os $sbc $N | gawk '{print "string-only "$1}' >> $tag
#./run_sbc_simple.sh ./vm/arm/ejsvm/ejsvm-str-unspec-Os  $sbc $N | gawk '{print "str-unspec "$1}'  >> $tag
./run_sbc_simple.sh ./vm/arm/ejsvm/ejsvm-handcraft-Os   $sbc $N | gawk '{print "handcraft "$1}'   >> $tag
./run_sbc_simple.sh ./vm/arm/ejsvm/ejsvm-predicate-Os   $sbc $N | gawk '{print "predicate "$1}'   >> $tag

./run_js_simple.sh ./vm/arm/jerry/jerry $jsdir/$program   $N | gawk '{print "jerry "$1}'  >> $tag
./run_js_simple.sh ./vm/arm/v7/v7       $jsdirv7/$program $N | gawk '{print "v7 "$1}'     >> $tag
