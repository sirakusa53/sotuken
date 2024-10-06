#!/bin/bash

## VM
#readonly EJSVM="../../ejs/ejsvm/ejsvm_t"
readonly EJSVM_OPT="-l"

## benchmarking software
readonly TESTCASES_LIST_FILE="testcases"

## result
readonly RESULT_DIR="test-result"


if [ "$EJSVM" == "" ] ; then
  echo "please set the ejsvm path"
  exit 0
fi


mkdir -p $RESULT_DIR
for i in `cat $TESTCASES_LIST_FILE` ; do
  sbc_path=$i
  sbc_fname="${sbc_path##*/}"
  result_file="$RESULT_DIR/${sbc_fname%.*}.txt"
  cmd="$EJSVM $EJSVM_OPT $sbc_path"
  echo "====== $result_file ======"
  echo $cmd
  $cmd > $result_file 2>&1
done
