#!/bin/bash

VM=$1
TEST_DIR=$2
RESULT_DIR=$3
N=$4
AVG_FILE=average.csv

mkdir -p $RESULT_DIR

echo "program time" >> $RESULT_DIR/$AVG_FILE

exec_and_get_cpu_time() {
  $vm_cmd | gawk 'NR == 1 {print gensub(/^cputime=([0-9|\.]+)/,"\\1",1,$0)}'
}

echo "VM=$VM"
echo ">> $RESULT_DIR"

// warmup
$VM warmup.js >> /dev/null

for js_file in `ls $TEST_DIR`
do
  vm_cmd="$VM $TEST_DIR/$js_file"
  echo $vm_cmd
  i=0
  sum=0
  while [ $i -lt $N ]
  do
    result=`exec_and_get_cpu_time`
    echo $result >> $RESULT_DIR/${js_file%.js}
    sum=`echo "scale=3; $sum + $result" | bc`
    i=$(expr $i + 1)
  done
  avg=`echo "scale=3; $sum / $N" | bc`
  echo "AVERAGE=$avg"
  echo "${js_file%.js} $avg" >> $RESULT_DIR/$AVG_FILE
done

