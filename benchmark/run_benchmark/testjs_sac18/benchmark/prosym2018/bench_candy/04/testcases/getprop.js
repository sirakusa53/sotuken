var f = function () {
    var x;
    return x = 10;
}

for (var i = 0; i < 1024; i++) {
    for (var j = 0; j < 1024; j++) {
        f();
    }
}
