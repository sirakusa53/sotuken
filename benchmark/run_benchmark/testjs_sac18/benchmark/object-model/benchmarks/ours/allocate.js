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
    a = {}
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

function bar() {
    a = {a1: 1,
	 a2: 1,
	 a3: 1,
	 a4: 1,
	 a5: 1,
	 a6: 1,
	 a7: 1,
	 a8: 1,
	 a9: 1,
	 a10: 1};
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

function baz() {
    a = new constr();
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

function bazz() {
    //    a = {}
    a = {a1: 1,
	 a2: 1,
	 a3: 1,
	 a4: 1,
	 a5: 1,
	 a6: 1,
	 a7: 1,
	 a8: 1,
	 a9: 1,
	 a10: 1};
    
    a["a1"] = 1;
    a["a2"] = 1;
    a["a3"] = 1;
    a["a4"] = 1;
    a["a5"] = 1;
    a["a6"] = 1;
    a["a7"] = 1;
    a["a8"] = 1;
    a["a9"] = 1;
    a["a10"] = 1;
    return a;
}

for (i = 0; i < 1000000; i++) {
    foo();
    bar();
    baz();
    bazz();
}

var start = performance.now();
for (i = 0; i < 1000000; i++)
    foo();
var end = performance.now();
print((end - start) + " ms");

var start = performance.now();
for (i = 0; i < 1000000; i++)
    bar();
var end = performance.now();
print((end - start) + " ms");

var start = performance.now();
for (i = 0; i < 1000000; i++)
    baz();
var end = performance.now();
print((end - start) + " ms");

var start = performance.now();
for (i = 0; i < 1000000; i++)
    bazz();
var end = performance.now();
print((end - start) + " ms");
