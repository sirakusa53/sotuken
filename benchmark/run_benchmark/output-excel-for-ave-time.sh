#!/bin/bash
DIR=$1

echo "DIR : $1"
cpu_time=""
gc_time=""
for i in `ls $DIR` ; do
    ln=0
    while IFS= read -r line; do
	# echo "$line"
	# echo "$ln"
	if [ $ln = 0 ] ; then
	    cpu_time="$cpu_time$line "
	else
	    gc_time="$gc_time$line "
	fi
	ln=$((ln + 1))
    done < "$DIR$i"
done
echo $cpu_time
echo $gc_time

