DIR=$1
OPT=$2


if [ "$OPT" = "-n" ]; then
    for i in `ls $DIR` ; do
	path="$DIR$i"

	echo "====== $path ======="

	cat $path
    done
else
    for i in `ls $DIR` ; do
	path="$DIR$i"

	echo "====== $path ======="

	cat $path
    done
fi
