DIR=$1

for i in `ls $DIR` ; do
    	path="$DIR$i"
	# 数値の抽出
	number=$(cat "$path" | grep -o -E '[0-9]+')
	# 数値を出力
	echo -n "$number "
done	
