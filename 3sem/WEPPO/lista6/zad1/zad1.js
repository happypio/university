var http = require('http');
var express = require('express');
var multer = require('multer');

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.disable('etag');

app.get('/', (req, res) => {
     res.render("index.ejs");
});

const srg = multer.diskStorage({
    destination: function(req, file, cb) {
        cb(null, __dirname + '/uploads');
        
    },
    filename: function (req, file, cb) {
        cb(null, file.fieldname + '1');
      }
})

var upload = multer({ storage: srg });
app.post('/', upload.single('file'), (req, res) => {
    res.render("index.ejs");
});

http.createServer(app).listen(3000);

console.log("started");


//npm init -y
//npm install express
//npm install ejs
//npm install multer
