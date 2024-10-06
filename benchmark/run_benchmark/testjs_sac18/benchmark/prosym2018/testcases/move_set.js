var f = function (x) {
    return x = 10;
}

for (var i = 0; i < 1024; i++) {
    for (var i = 0; i < 1024; i++) {
        f(1);
    }
}
