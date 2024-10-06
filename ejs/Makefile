all: a.js
    node ejsc/js/ejsc.js -O -o a.sbc a.js && \
    build/ejsvm -l a.sbc

sbc: a.js
    node ejsc/js/ejsc.js -O -o a.sbc a.js

build: a.sbc
    build/ejsvm -l a.sbc