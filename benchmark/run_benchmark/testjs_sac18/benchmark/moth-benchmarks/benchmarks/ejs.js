Object.create = function(proto) {
    var ctor = function() {};
    ctor.prototype = proto;
    return new ctor();
};

Function.prototype.call = function(tis) {
    var a = [];
    for (var i = 1; i < arguments.length; i++)
	a[i-1] = arguments[i];
    this.apply(tis, a);
};

Array.prototype.forEach = function(f) {
    for (var i = 0; i < this.length; i++)
	f(this[i]);
}
