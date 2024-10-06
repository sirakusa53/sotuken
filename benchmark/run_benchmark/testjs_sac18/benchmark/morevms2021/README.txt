ejs: a8181aa1aab95570d4ed040db2d0fcd76d93bc5f (morevms2021)

* minimum heap size の計測

size.baseline/
size.optimized/

それぞれでmakeして、このディレクトリの ejs-minheap.py を実行する。
min_heap.txt が作られる
※ Makefile を編集して ejsvm のディレクトリを指定する


* ヒープ使用量の内訳

gcprof.baseline/
gcprof.optimized/

--gc-prof をつけて実行する
※ Makefile を編集して ejsvm のディレクトリを指定する


* 実行時間の計測

object-mode/ を利用する。
script/exec-time2.py で生の実行時間が得られる

JerryScript:
git@github.com:jerryscript-project/jerryscript.git
commit 9254cd4e7a614354841e484de726a5508dca3776
Author: kisbg <kisbg@inf.u-szeged.hu>
Date:   Fri Mar 5 09:40:17 2021 +0000

* サイズの計測

jerry-tool/jerryscript に JerryScript を clone し
jerry-tool/minheap/minheap.py を実行する。
min_heap.txt が作られる

* 実行時間の計測
jerry-tool/jerryscript に JerryScript を clone し
jerry-tool/exectime/exectime.py を実行する。
exec_time.txt が作られる

