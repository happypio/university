var fs = require('fs');

fs.readFile('./a.txt', 'utf-8', function(err, data) {
    console.log("\nKlasyczny interfejs:\n" + data);
});

var readfile = function(f, c) {
    return new Promise ( (res, rej) => {
        fs.readFile(f, c, (err, data) => {
            if (err) 
                rej(err)
            else
                res(data)
        });
    });
}
readfile('./a.txt', 'utf-8').then( data => {
    console.log("\nRęcznie napisana funkcja:\n" + data);
});

var util = require('util');

var read_promisify = util.promisify(fs.readFile);
read_promisify('./a.txt', 'utf-8').then( data => {
    console.log("\nPromisify: \n" + data);
});

fs.promises.readFile('./a.txt', 'utf-8').then(data => {
    console.log("\nPromises: \n" + data)
});

(function () {
    var data = fs.promises.readFile('./a.txt', 'utf-8');
    data.then( data => {
        console.log("\nPromises z then: \n" + data);
    });
})();

(async function() {
    var data = await fs.promises.readFile('./a.txt', 'utf-8');
    console.log("\nPromises z async/await: \n" + data)
})();