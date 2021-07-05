console.log("Evaluating modul_zad3.js");
exports.variable = 0;
let zad3 = require("./zad3.js");
console.log(`In m_zad3, zad3.variable = ${zad3.variable}`);
exports.variable = 1;
console.log("end of m_zad3");
//let e = require("./modul_zad3.js"); odwolanie sie do siebie
//require nie "reloaduje" pliku, tylko go pamieta i uzywa na nowo