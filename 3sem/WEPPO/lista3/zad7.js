function fib_it() {
    
    var fib_num = [0,1];

    return {
        next : function() {
            var new_num = fib_num[1] + fib_num[0];
            fib_num  = [fib_num[1] , new_num]
            return {
                value : fib_num[0],
                done  : false
            }
        }
    }
}

function* fib_gen() {
    var fib_num = [0,1];
    while(true){
        var new_num = fib_num[1] + fib_num[0];
        fib_num  = [fib_num[1] , new_num]
        yield fib_num[0];
    }
}


var it = fib_it();
for (var i; i = it.next(), !it.done;){
    if (i.value > 22)
        break;
    console.log( i.value );
}

//w przypadku generatora mozemy iterowac sie po funkcji petla for_of,
//w iteratorze (bez yield) nie
for (const i of fib_gen() ){
    if (i > 22)
        break;
    console.log( i );
}