function Foo() {
    console.log("new Foo obj");
}

Foo.prototype.Bar = function() {
    var Qux = function() {console.log('Private Qux'); }
    Qux();
}

var foo1 = new Foo(1,2);
foo1.Bar();
// foo1.Qux(); // nie mozemy sie tak odwolac 