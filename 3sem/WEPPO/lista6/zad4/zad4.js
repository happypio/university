var http = require('http');
var express = require('express');
var csurf = require('csurf');
var crypto = require('crypto');
var cookieParser = require('cookie-parser')
var bodyParser = require('body-parser')

var secret = 'big secret';
var parameter = '123';
var hmac = 
    crypto
        .createHmac('sha256', secret)
        .update(parameter)
        .digest('hex');
console.log(hmac);
var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');

var csrfProtection = csurf({ cookie: true })
var parseForm = bodyParser.urlencoded({ extended: false })
app.use(cookieParser())

app.get('/', csrfProtection, function (req, res) {
    res.render('index.ejs', { csrfToken: req.csrfToken() })
  })

//ignorowanie zadan ktorym brakuje ukrytej wartosci, badz jest zla
//na podstawie csurf token

app.post('/load', parseForm, csrfProtection, function (req, res) {
    res.send('loading...')
  })

//good url:
// /plik/123?mac=16066a3297b40494e3278220fe6f2cada0edaeb1c73b218d2346f5e6438dee62
app.use(express.urlencoded({ extended: true }));
app.get("/plik/:id(\\d+)",
    (req, res) => {
        var id = req.params.id;
        var mac = req.query.mac;
        if (!mac)
            res.render('404.ejs', { url: req.url });
        else 
        {
            var mac_to_check = 
                crypto
                .createHmac('sha256', secret)
                .update(id)
                .digest('hex');
            if (mac_to_check === mac)
                res.end(`dynamicznie generowany plik: ${req.params.id}`);
            else
                res.render('404.ejs', { url: req.url });
        }
    }
    );

app.use((req, res, next) => {
    res.render('404.ejs', { url: req.url });
});


http.createServer(app).listen(3000);


//npm init -y
//npm install express
//npm install ejs