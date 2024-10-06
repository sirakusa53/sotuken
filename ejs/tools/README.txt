./ejsvm --dump-hcg aaa.hc aaa.sbc
python hcopt.py --ohc aaa.ohc --dot aaa.dot aaa.hc
dot -Tpdf aaa.dot > aaa.pdf
./ejsvm --load-hcg aaa.ohc aaa.sbc

