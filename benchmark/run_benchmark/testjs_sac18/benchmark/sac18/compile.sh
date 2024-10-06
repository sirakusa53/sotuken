#!/bin/bash

if [ $# -lt 3 ]; then
  echo "usage: ./compile.sh compile-command source(.js)-dir target(.sbc)-dir"
  echo "example: ./compile.sh \"java -jar ../ejsc/compiler.jar\" tests sbc"
  exit 1
fi

COMPILE_CMD=$1
TARGET_JS_DIR=$2
SBC_DIR=$3


mkdir -p $SBC_DIR
rm -f $SBC_DIR/*
for jsfile in `ls $TARGET_JS_DIR`
do
  sbcfile=${jsfile%.js}.sbc
  cmd="$COMPILE_CMD -o $SBC_DIR/$sbcfile $TARGET_JS_DIR/$jsfile"
  echo $cmd
  $cmd
done
