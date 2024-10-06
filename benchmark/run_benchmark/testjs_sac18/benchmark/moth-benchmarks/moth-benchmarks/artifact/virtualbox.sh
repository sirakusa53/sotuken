#!/bin/bash
set -e # make script fail on first error

# make SCRIPT_PATH absolute
pushd `dirname $0` > /dev/null
SCRIPT_PATH=`pwd`
popd > /dev/null

source ${SCRIPT_PATH}/../implementations/script.inc
source ${SCRIPT_PATH}/config.inc

## Make sure we have all dependencies
check_for "packer" "Packer does not seem available. We tested with packer version 1.4 from https://www.packer.io/downloads.html"

INFO Compose a VirtualBox Image
pushd ${SCRIPT_PATH}

INFO "Get Paper Repository for Evaluation Material"
git clone --depth=1 ${PAPER_REPO} paper

tar cjvf eval.tar.bz2 paper/evaluation paper/eval-description

packer build -force packer.json
mv eval.tar.bz2 ~/artifacts/${BOX_NAME}/eval.tar.bz2

echo File Size
ls -sh ~/artifacts/${BOX_NAME}/*

echo MD5
md5sum ~/artifacts/${BOX_NAME}/*

chmod a+r ~/artifacts/${BOX_NAME}/*
