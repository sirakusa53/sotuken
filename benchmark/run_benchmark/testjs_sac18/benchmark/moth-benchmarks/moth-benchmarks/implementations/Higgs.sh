#!/bin/bash
SCRIPT_PATH=`dirname $0`
source $SCRIPT_PATH/script.inc

# Ignore the extra_args parameter from ReBench, because we can't handle it
ARG_ARR=($@)
LEN=${#ARG_ARR[@]}
LAST=${ARG_ARR[${LEN}-1]}
BENCH_ARGS=${ARG_ARR[@]:0:${LEN}-1}

INFO Ignoring last parameter to be compatible with ReBench: \"${LAST}\"
INFO If used as standalone script, simply add a dummy parameter at the end

pushd $SCRIPT_PATH/Higgs/source
./higgs ${BENCH_ARGS}; RET=${PIPESTATUS[0]}

if [ $RET != 0 ]
then
    exit 1
fi
