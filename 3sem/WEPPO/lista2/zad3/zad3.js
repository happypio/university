//OBIEKTY, Z KTORYCH WYBIERAMY LITERY

console.log(([![]]+[][[]])) // false + undefined jako jeden string;
//undefined - z pustej tablicy chcemy wziac 0 element
console.log(![] + []) // pusta tablica z ! - daje false , po dodaniu
//pustej tablicy wciaz mamy wartosc boolean


//LICZBY POTRZEBNE DO ITERACJI BO OBIEKTACH WYZEJ, w ten sposob - obiekt[liczba]

console.log(+[]) // konwertuje pusta tablice do liczby - 0

console.log(+!+[]); // +[] konwertuje pusta tablice do liczby 0
// !+[] konwertuje zero do true i w koncu +!+[] konwertuje true do 1

console.log(!+[]+!+[]) // dodaje do wartosci liczbowej 1 true - wychodzi 2

console.log(+!+[]+[+[]]) // 1 + tablica, ktora konwertuje sie do stringa '0'
//zatem wynikiem jest string 10

console.log((![]+[])[+[]] + (![]+[])[+!+[]] + ([![]]+[][[]])[+!+[]+[+[]]] + (![]+[])[!+[]+!+[]]);