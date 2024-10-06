#!/bin/bash

## VM
EJSVM="../../ejs/build/ejsvm"
readonly EJSVM_OPT="-u"

## benchmarking software
readonly TESTCASES_DIR="testcases"

## result
RESULT_DIR="test-result"

## select vm by command line
if [ $# == 1 ] ; then
    echo "vm specified"
if [ $1 == "threaded" ] ; then
    echo "threaded"
    EJSVM="../../ejs/build-threaded/ejsvm"
    RESULT_DIR="threaded-result"
fi
if [ $1 == "switch" ] ; then
    echo "switch"
    EJSVM="../../ejs/build-switch/ejsvm"
    RESULT_DIR="switch-result"
fi
fi

if [ ! -e $EJSVM ] ; then
  echo "no ejsvm file"
  exit 0
fi

if [ ! -e $TESTCASES_DIR ] ; then
  echo "no testcases dir"
  exit 0
fi

echo $RESULT_DIR
mkdir -p $RESULT_DIR
for i in `ls $TESTCASES_DIR` ; do
  sbc_path=$i
  sbc_fname="${sbc_path##*/}"
  result_file="$RESULT_DIR/${sbc_fname%.*}.txt"
  cmd="$EJSVM $EJSVM_OPT $TESTCASES_DIR/$sbc_path"
  echo "====== $result_file ======"
  echo $cmd
  $cmd > $result_file
done
