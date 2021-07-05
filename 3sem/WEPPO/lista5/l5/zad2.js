var fs = require('fs');
var https = require('https');
(async function() {
    var pfx = await fs.promises.readFile('klucz.pfx');
    var server = https.createServer({
        pfx: pfx,
        passphrase: '1234'
    },
    (req, res) => {
        res.setHeader('Content-type', 'text/html; charset=utf-8');
        res.end(`hello world ${new Date()}`);
    });

    server.listen(8000);
    console.log('started');
})();
