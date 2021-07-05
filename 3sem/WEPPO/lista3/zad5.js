function sum(...tab) {
    var acc = 0;
    // mozna tak:
    /*(for (const a of arguments){
        acc += a;
    }*/
    // lub tak
    for (const a of tab){
        acc += a;
    }
    return acc;
    
}
console.log(sum(1,2,3));
// 6
console.log(sum(1,2,3,4,5));
// 15