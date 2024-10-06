#!/bin/bash

arch=$1

now=`date +%Y%m%d_%H-%M-%S`
N=1;


# ejsc sunspider

tag=result/${arch}_${now}
jsdir=tests_loop
jsdirv7=tests_loop_for_v7

sbc=sunspider_ejsc_sbc
rm -r $sbc
./compile.sh "java -jar ./compiler/compiler.jar"        $jsdir $sbc

./run_sbc.sh vm/$arch/ejsvm/ejsvm-default-Os     $sbc $tag/default      $N
./run_sbc.sh vm/$arch/ejsvm/ejsvm-array-tag-Os   $sbc $tag/array-tag    $N
./run_sbc.sh vm/$arch/ejsvm/ejsvm-string-only-Os $sbc $tag/string-progs $N
./run_sbc.sh vm/$arch/ejsvm/ejsvm-handcraft-Os   $sbc $tag/handcraft   $N
./run_sbc.sh vm/$arch/ejsvm/ejsvm-predicate-Os   $sbc $tag/predicate   $N

#./run_js.sh  vm/$arch/jerry/jerry    $jsdir     $tag/jerry  $N
#./run_js.sh  vm/$arch/v7/v7          $jsdirv7   $tag/v7     $N
