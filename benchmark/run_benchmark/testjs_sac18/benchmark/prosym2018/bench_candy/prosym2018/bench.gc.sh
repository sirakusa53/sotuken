#!/bin/bash

VERSIONS=('old' 'omit_arguments' 'omit_frame')
IGNORE_FILES=() # ('3d-morph' 'access-nbody' 'math-partial-sums')

function benchmark() {
  name=${1%.js}
  csv=$name
  out=$result_path/${name}.txt

  echo ======== $name ========
  echo ======== $name ======== > $out
  csv+=,`measure .sbc`

  if [ $version = 'old' ]; then
    echo $csv >> $CSV
    return
  fi

  echo >> $out

  echo ======== ${name} Optimisation ======== >> $out
  csv+=,`measure .omit.sbc`

  echo $csv >> $CSV
}

function measure() {
  # choise VM
  vm="tool/ejsvm -u"
  if [ $version = 'old' ]; then vm="tool/ejsvm.old -u"; fi
  # ignore file
  if [ $version = 'omit_frame' ]; then
    for file in "${IGNORE_FILES[@]}"
    do
      if [ $name = $file ]; then echo 0; return; fi
    done
  fi
  # measure
  sum=0
  for i in {0..59}
  do
    result=`$vm $sbc_path/${name}${1} 2>&1`
    echo $i: $result >> $out 2>&1

    num=${result#*GC\ time\ \=\ }
    num=`echo ${num# }`
    sum=`echo "$sum + ${num%% *}"| bc -l | sed -e "s/^\./0\./g"`
  done
  echo "scale=4;$sum / 60" | bc -l | sed -e "s/^\./0\./g"
}

# Version select
version='omit_frame'
for v in "${VERSIONS[@]}"
do
  if [ $# -eq 0 ]; then break; fi
  if [ $1 = $v ]; then version=$v; fi
done

# Compile js file
sbc_path="sbcfiles/$version"
mkdir -p $sbc_path
if [ $version = 'old' ]; then
  compiler='compiler.old.jar'
  for i in testcases/*
  do
    file=${i##*/}
    echo java -jar tool/$compiler ${i} -o $sbc_path/${file%.js}.sbc
    java -jar tool/$compiler ${i} -o $sbc_path/${file%.js}.sbc
  done
else
  compiler='compiler.jar'
  for i in testcases/*
  do
    if [ $version = 'omit_arguments' ]; then
      flag='-omit-arguments'
    else
      flag='-omit-frame'
    fi
    file=${i##*/}
    echo java -jar tool/$compiler ${i} -o $sbc_path/${file%.js}.sbc
    java -jar tool/$compiler ${i} -o $sbc_path/${file%.js}.sbc
    echo java -jar tool/$compiler $flag ${i} -o $sbc_path/${file%.js}.omit.sbc
    java -jar tool/$compiler $flag ${i} -o $sbc_path/${file%.js}.omit.sbc
  done
fi
# benchmark
mkdir -p results
CSV="results/results.$version.csv"
if [ $version = 'old' ]; then
  echo filename,$version > $CSV
else
  echo filename,$version,$version \(with optimisation\) > $CSV
fi
result_path="results/$version"
mkdir -p $result_path
for i in testcases/*
do
  benchmark ${i##*/}
done

