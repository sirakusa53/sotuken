#!/bin/bash

if [ $# -lt 3 ]; then
  echo "usage: ./run.sh ejsvm-path sbc-dir result-dir"
  echo "example: ./run.sh ../ejsvm/build_default/ejsvm sbc result/default"
  exit 1
fi

VM=$1
SBC_DIR=$2
RESULT_DIR=$3
#RESULT_DIR=result/`date +%Y%m%d_%H-%M-%S`
N=$4

AVG_FILE=average.csv

mkdir -p $RESULT_DIR
echo "program time" >> $RESULT_DIR/$AVG_FILE

exec_and_get_cpu_time() {
  #(time -p $vm_cmd >> /dev/null) 2>&1 | gawk 'NR == 2 {print gensub(/^user ([0-9|\.]+)/,"\\1",1,$0)}'
  $vm_cmd | gawk 'NR == 1 {print gensub(/^total CPU time = ([0-9|\.]+) msec.*/,"\\1",1,$0)}'
}

echo "VM=$VM"
echo ">> $RESULT_DIR"

# warm up
$VM warmup.sbc >> /dev/null

for sbc in `ls $SBC_DIR`
do
  vm_cmd="$VM -u $SBC_DIR/$sbc"
  echo "$SBC_DIR/$sbc"
  i=0
  sum=0
  while [ $i -lt $N ]
  do
    result=`exec_and_get_cpu_time`
    echo $result >> $RESULT_DIR/${sbc%.sbc}
    sum=`echo "scale=3; $sum + $result" | bc`
    i=$(expr $i + 1)
  done
  avg=`echo "scale=3; $sum / $N" | bc`
  echo "AVERAGE=$avg"
  echo "${sbc%.sbc} $avg" >> $RESULT_DIR/$AVG_FILE
done

