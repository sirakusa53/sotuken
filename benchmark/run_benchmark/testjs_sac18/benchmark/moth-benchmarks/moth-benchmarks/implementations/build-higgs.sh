#!/bin/bash
set -e # make script fail on first error

SCRIPT_PATH=`dirname $0`
source $SCRIPT_PATH/script.inc

INFO Build Higgs
load_submodule $SCRIPT_PATH/Higgs
pushd $SCRIPT_PATH/Higgs/source
make all
OK Higgs Build Completed.
