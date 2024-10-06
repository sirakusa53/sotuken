#!/bin/bash
set -e # make script fail on first error

SCRIPT_PATH=`dirname $0`
source $SCRIPT_PATH/script.inc

INFO Build SOMns
load_submodule $SCRIPT_PATH/SOMns
pushd $SCRIPT_PATH/SOMns
ant clean; ant clobber; ant compile -Dskip.graal=true
OK SOMns Build Completed.
