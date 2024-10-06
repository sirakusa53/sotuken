#!/bin/bash
set -e # make script fail on first error

SCRIPT_PATH=`dirname $0`
source $SCRIPT_PATH/script.inc

INFO Build Moth
load_submodule $SCRIPT_PATH/Moth
pushd $SCRIPT_PATH/Moth
ant clean; ant clobber; ant -Dskip.graal=true
OK Moth Build Completed.
