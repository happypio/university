var z1 = 2;
var z2 = 's';

var z3 = new Number(2);

console.log(typeof z1); //"string"
console.log(typeof z2); //"string"
console.log(typeof z3); //"object"
console.log(z1 instanceof Number); //false
console.log(z2 instanceof String); //false
console.log(z3 instanceof Number); //true

//instance of zwraca true lub false - porownujac, czy
// obiekt jest instancja okreslonego typu (np Number)

//typeof zwraca typ obiektu - prymitywny lub inny (obiekt)
// typy prymitywne: boolean, null, string, number, undefined