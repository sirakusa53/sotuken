sed -i '' -e 's/private/method/' $1
sed -i '' -e 's/public/method/' $1
sed -i '' -e 's/\[/\{/' $1
sed -i '' -e 's/\]/\}/' $1
sed -i '' -e 's/: {/.{/' $1
sed -i '' -e 's/\^/return/' $1
sed -i '' -e 's/nil/Done/' $1
sed -i '' -e 's/: /\(/' $1
sed -i '' -e 's/::=/:=/' $1
# sed -i '' -e 's/method\(.*\):=/var\1:=/' $1
# sed -i '' -e 's/method\(.*\)=/def\1=/' $1
sed -i '' -e 's/(\* /\/\/ /' $1
