#!/bin/bash
set -e # make script fail on first error

SCRIPT_PATH=`dirname $0`
source $SCRIPT_PATH/script.inc

INFO Build Java Benchmarks
pushd $SCRIPT_PATH/../benchmarks/Java
ant jar
OK Java Benchmarks Build Completed.
