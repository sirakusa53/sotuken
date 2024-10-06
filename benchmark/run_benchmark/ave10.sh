#!/bin/bash

## VM
EJSVM="../../ejs/build/ejsvm"
readonly EJSVM_OPT="-u"

## benchmarking software
readonly TESTCASES_DIR="testcases"

## result
RESULT_DIR="test-result"

REPEAT_TIME=100
OPT=0
## select vm by command line

if [ $# -eq 0 ] ; then
    echo "vm unspecified"
fi

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
if [ $1 == "opt" ] ; then
    echo "opt"
    EJSVM="../../ejs/build-opt/ejsvm"
    RESULT_DIR="opt-result"
    OPT=1
fi

if [ ! -e $EJSVM ] ; then
  echo "no ejsvm file"
  exit 0
fi

if [ ! -e $TESTCASES_DIR ] ; then
  echo "no testcases dir"
  exit 0
fi
num1=5
num2=7
result=$((num1 + num2))
echo "Result: $result"

echo $RESULT_DIR
mkdir -p $RESULT_DIR
for i in `ls $TESTCASES_DIR` ; do
  sbc_path=$i
  sbc_fname="${sbc_path##*/}"
  result_file="$RESULT_DIR/${sbc_fname%.*}.txt"
  spec_path=""
  if [ $OPT == 1 ] ; then
     spec_path="../../ejs/opt-threaded-switch/$2/${sbc_fname%.*}.spec"
  fi
  echo "spec_path : $spec_path"
  cmd="$EJSVM $EJSVM_OPT $TESTCASES_DIR/$sbc_path $spec_path"
  echo "====== $result_file ======"
  echo $cmd
  cpu_time=0
  gc_time=0
  for ((i = 0; i < $REPEAT_TIME; i++)); do      
      result=`$cmd`
      reg=`echo $result | grep -oP '\d+.\d+'`
#      echo $reg
      reg1=`echo $result | grep -oP 'CPU time = \K\d+.\d+'`
#      echo $reg1
      cpu_time=$(echo "$reg1 + $cpu_time" | bc)
      reg2=`echo $result | grep -oP 'GC time = \K\d+.\d+'`
#      echo $reg2
      gc_time=$(echo "$reg2 + $gc_time" | bc)
#      echo $cpu_time
#      echo $gc_time
  done
  cpu_time=$(echo "scale=3; $cpu_time / $REPEAT_TIME" | bc)
  gc_time=$(echo "scale=3; $gc_time / $REPEAT_TIME" | bc)
  echo -e "$cpu_time\n$gc_time" 
  echo -e "$cpu_time\n$gc_time" > $result_file 

done
