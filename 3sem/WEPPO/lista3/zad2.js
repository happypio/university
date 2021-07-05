function fib(n) {
    if (n > 1)
        return fib( n - 1 ) + fib( n - 2 );
    return 1;
}

function memo (f) {

    var cache = {};

    return function (n) {

        if ( cache[n] === undefined ) {
            var f_n = f(n);
            cache[n] = f_n;
            return f_n;
            
        } else {
            return cache[n];
        }
    }
}

var fib_m = memo(fib);

console.log("Kiedy wykorzystamy fib_m jest znacznie wolniej")
console.log(fib_m(42));

var fib = memo(fib);

console.log("Kiedy wykorzystamy fib jest znacznie szybciej")
console.log(fib(1000));