#!/bin/bash
# Top-level executable for "Are We Fast Yet" benchmarks
#   Originally developed by Stefan Marr
#   https://gitlab.soft.vub.ac.be/stefan.marr/awfy-runs
#
# Adapted by Richard Roberts
rebench -f codespeed.conf all

## Archive results

DATA_ROOT=~/benchmark-results/moth-benchmarks

REV=`git rev-parse HEAD | cut -c1-8`

NUM_PREV=`ls -l $DATA_ROOT | grep ^d | wc -l`
NUM_PREV=`printf "%03d" $NUM_PREV`

TARGET_PATH=$DATA_ROOT/$NUM_PREV-$REV
LATEST=$DATA_ROOT/latest

mkdir -p $TARGET_PATH
bzip2 benchmark.data
mv benchmark.data.bz2 $TARGET_PATH/
rm $LATEST
ln -s $TARGET_PATH $LATEST
echo Data archived to $TARGET_PATH
