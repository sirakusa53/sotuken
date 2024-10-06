var f = function () {
    var y;
    return y;
}

for (var i = 0; i < 1024; i++) {
    for (var j = 0; j < 1024; j++) {
        f();
    }
}
