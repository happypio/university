var http = require('http');
var express = require('express');

var app = express();
app.use( (req, res) => {
    res.header('Content-disposition', 'attachment; filename = "data.txt"');
    res.end('data');
});
http.createServer(app).listen(3000)