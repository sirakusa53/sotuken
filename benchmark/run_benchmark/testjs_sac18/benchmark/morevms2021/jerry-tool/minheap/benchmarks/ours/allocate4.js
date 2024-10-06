function foo() {
    var a = {a1: 1,
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
