+
#!/bin/bash

## EJSC
readonly EJSC="../../ejs/ejsc/js/ejsc.js"
#readonly EJSC="testcases.txt"
## benchmarking software
TESTJS_DIR="testjs_sac18/benchmark/sac18/tests"

## result
RESULT_DIR="testcases"

if [ ! -e $EJSC ] ; then
  echo "no ejsc file"
  exit 0
fi

if [ ! -e $TESTJS_DIR ] ; then
  echo "no testjs dir"
  exit 0
fi

if [ ! -e $RESULT_DIR ] ; then
  echo "no result dir"
  exit 0
fi

mkdir -p $RESULT_DIR
for i in `ls $TESTJS_DIR` ; do
  js_path=$i
  js_fname="${js_path##*/}"
  result_file="$RESULT_DIR/${js_fname%.*}.sbc"
  cmd="node $EJSC -O -o $result_file $TESTJS_DIR/$js_path"
  echo "====== $result_file ======"
  echo $cmd
  $cmd > $result_file
done
