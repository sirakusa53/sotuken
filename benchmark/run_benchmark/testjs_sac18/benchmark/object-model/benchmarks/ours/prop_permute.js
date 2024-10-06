function now() {
}

function foo(x) {
    a = {};
    if (x % 5 == 0)
	a.x = 0;
    if (x % 5== 1)
	a.y = 0;
    if (x % 5== 2)
	a.z = 0;
    if (x % 5 == 3)
	a.u = 0;
    if (x % 5 == 4)
	a.v = 0;
    a.x = 0;
    a.y = 0;
    a.z = 0;
    a.u = 0;
    a.v = 0;
    return a;
}

for (i = 0; i < 10; i++) {
    a = foo(i);
    var start = performance.now();
    for (j = 0; j < 10000000; j++)
	a.x++;
    var end = performance.now();
    print("i = "+i+": "+(end - start)+"ms");
}
