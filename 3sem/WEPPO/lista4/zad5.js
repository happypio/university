var fs = require('fs');

/*fs.readFile('./text.txt', 'utf8', (error, data) => {
    if(error) throw error;
    console.log(data)
});*/ // mozna tak (ale tu czytamy i jednoczesnie wypisujemy) lub lepiej :

var content = fs.readFileSync("./text.txt").toString();
console.log(content);