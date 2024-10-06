#!/bin/bash
SCRIPT_PATH=`dirname $0`
source $SCRIPT_PATH/script.inc
exec java "$@"
