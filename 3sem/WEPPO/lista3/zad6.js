function createGenerator(n) {

    return function() {
        var _state = 0;
    
        return {
            next : function() {
                return {
                    value : _state,
                    done : _state++ >= n
                }
            }
        }
    }
}

var foo1 = {
    [Symbol.iterator] : createGenerator(5)
};

var foo2 = {
    [Symbol.iterator] : createGenerator(10)
};

var foo3 = {
    [Symbol.iterator] : createGenerator(15)
};

console.log("foo1, dla parametru 5:")
for ( var f of foo1 )
    process.stdout.write(f + " ");

console.log("\nfoo2, dla parametru 10:")
for ( var f of foo2 )
    process.stdout.write(f + " ");

console.log("\nfoo3, dla parametru 15:")
for ( var f of foo3 )
    process.stdout.write(f + " ");