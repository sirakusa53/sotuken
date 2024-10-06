#!/bin/bash

if [ $# -lt 3 ]; then
  echo "usage: ./run.sh ejsvm-path sbc-dir result-dir"
  echo "example: ./run.sh ../ejsvm/build_default/ejsvm sbc result/default"
  exit 1
fi

VM=$1
JS=$2
N=$3


exec_and_get_cpu_time() {
  $vm_cmd | gawk 'NR == 1 {print gensub(/^cputim=([0-9|\.]+)/,"\\1",1,$0)}'
}


# warm up
$VM warmup.sbc >> /dev/null

vm_cmd="$VM $JS"
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

