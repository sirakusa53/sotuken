#!/bin/bash

N=100
vms=( "ejsvm_original" "ejsvm_noinline" "ejsvm_inlined" "ejsvm_case_expansion" )
#vms=( "ejsvm_noinline" )
DIR_TESTS=./sbc
OPTION="-u"
TESTS=( "3d-cube" "access-binary-trees" "access-fannkuch" "access-nbody" "access-nsieve" "bitops-3bit-bits-in-byte" "bitops-bits-in-byte" "bitops-bitwise-and" "controlflow-recursive" "math-cordic" "math-partial-sums" "math-spectral-norm" "string-base64" "string-fasta" "string-validate-input" )
#TESTS=( "3d-cube" "access-binary-trees" "access-nbody" "access-nsieve" "bitops-3bit-bits-in-byte" "bitops-bitwise-and" "controlflow-recursive" "math-cordic" "math-partial-sums" "math-spectral-norm")
rm -f results_time.txt
for vm in ${vms[@]}
do
  for TEST in ${TESTS[@]}
  do
    echo ${TEST}
    outpath="./result_${vm}_${TEST}.txt"
    rm -f ${outpath}
    for i in `seq 1 ${N}`
    do
      echo "${i}"
      ./${vm} ${OPTION} ${DIR_TESTS}/${TEST}.sbc | grep "total CPU time" | cut -d " " -f 5 &>> ${outpath}
    done
    awk -v "flg=${outpath}" -e '{sum+=$1} END{print "file=" flg " : " sum/NR}' ${outpath} >> results_time.txt
  done
done
