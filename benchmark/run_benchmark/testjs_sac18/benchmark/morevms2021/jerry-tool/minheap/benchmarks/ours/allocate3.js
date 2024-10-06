function constr() {
    this.a1 = 1;
    this.a2 = 1;
    this.a3 = 1;
    this.a4 = 1;
    this.a5 = 1;
    this.a6 = 1;
    this.a7 = 1;
    this.a8 = 1;
    this.a9 = 1;
    this.a10 = 1;
}

function foo() {
    var a = new constr();
    a.a1 = 1;
    a.a2 = 1;
    a.a3 = 1;
    a.a4 = 1;
    a.a5 = 1;
    a.a6 = 1;
    a.a7 = 1;
    a.a8 = 1;
    a.a9 = 1;
    a.a10 = 1;
    return a;
}

function main() {
    var a;
    for (i = 0; i < 1000000; i++) {
	a = foo();
    }
    return a;
}

var start = performance.now();
main();
var end = performance.now();
print((end - start) + " ms");

