function* fib() {
    var fib_num = [0,1];
    while(true){
        var new_num = fib_num[1] + fib_num[0];
        fib_num  = [fib_num[1] , new_num]
        yield fib_num[0];
    }
}

function* take(it, top) {
    /*var i = 1
    for (const a of it ){
        if (i > top)
            break;
        yield a;
        i ++;
    }*/
    //mozna tez tak:
    for (let i = 0; i < top; i++){
        yield it.next().value;
    }
}
// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take( fib(), 10 ) ) {
    console.log(num);
}