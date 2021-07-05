function createFs(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    
    function f(x) {
        return function () {
            return x
        };
    } //domkniecie funkcji i powiazanie zmiennej z niezmienna
    // w zakresie innej funkcji powoduje ze "i" pozostaje dobra
    
    for ( var i=0; i<n; i++ ) {

        //console.log(i);
        fs[i] = f(i);
    }
    i = 20; // teraz wszystkie funkcje by zwracały 20
    // i jest "aktywna" przez cala petle for 
    // w przypadku let za kazdym przejsciem petli i jest "inicjowane"
    //stad nie ma problemu z wynikiem fs[i]
    return fs;
}
var myfs = createFs(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );// 10 10 10

