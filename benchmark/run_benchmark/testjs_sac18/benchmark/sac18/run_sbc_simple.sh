#!/bin/bash

if [ $# -lt 3 ]; then
  echo "usage: ./run_sbc_simple.sh ejsvm-path sbc-file iteration"
  echo "example: ./run_sbc_simple.sh ../ejsvm/build_default/ejsvm aaa.sbc 3"
  exit 1
fi

VM=$1
SBC=$2
N=$3


exec_and_get_cpu_time() {
  $vm_cmd | gawk 'NR == 1 {print gensub(/^total CPU time = ([0-9|\.]+) msec.*/,"\\1",1,$0)}'
}


# warm up
$VM warmup.sbc >> /dev/null

vm_cmd="$VM -u $SBC"
i=0
sum=0
while [ $i -lt $N ]
do
  result=`exec_and_get_cpu_time`
  sum=`echo "scale=3; $sum + $result" | bc`
  i=$(expr $i + 1)
done
avg=`echo "scale=3; $sum / $N" | bc`
echo $avg

