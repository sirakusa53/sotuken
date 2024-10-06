#!/bin/bash
SCRIPT_PATH=`dirname $0`
source $SCRIPT_PATH/script.inc
exec $SCRIPT_PATH/Moth/moth "$@"
