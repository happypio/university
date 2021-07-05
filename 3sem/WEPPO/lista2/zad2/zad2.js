//a------------------------------
var foo = {};
var p = {
    toString: function()
    {
        return "fajna nazwa";
    }
};
foo['la la'] = 2;
foo.lala = 1;  // po kropce nie mozna uzyc bialego znaku
foo[p] = 3;
foo.p = 3.5; // po kropce p traktowany jest jako tekst nie obiekt
console.log(foo);

//b----------------------------------
console.log(foo[1234]); //nie zainicjalizowane pole
foo[p] = 3; // 3 przypisywana jest do zwracanej wartosci metody toString()
//lub gdy nie ma takiej do [object Object]
foo[1234] = 0; // 1234 jest przekonwertowane do string
console.log(Object.keys(foo));

//c---------------------------------------
foo['napis'] = 2; // klucz 'napis' ma wartosc 2
foo[p] = 3; // 3 przypisywana jest do zwracanej wartosci metody toString()
//lub gdy nie ma takiej do [object Object]
console.log(foo);

var tablica = ['w',2,false];
tablica['n'] = 3; // n nie jest indeksem w tablicy, n bedzie wlasnoscia obiektu tablica
console.log(tablica);
console.log(tablica.length);
//da sie ustawic wartosc length
tablica.length = 10; // tablica jest powiekszana pustymi komorkami
console.log(tablica);
tablica.length = 2; //usuwane sa elemnty od konca do drugiego
console.log(tablica);




