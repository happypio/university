var http = require('http');
var express = require('express');
var session = require('express-session');
var cookieParser = require('cookie-parser');

//do sprawdzenia czy przegladarka ma cookies
var html = require('html');
var jsdom = require("jsdom");
var JSDOM = jsdom.JSDOM;
global.document = new JSDOM(html).window.document;
global.navigator = new JSDOM(html).window.navigator;
//*****


var FileStore = require('session-file-store')(session);
var fso = {};

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.disable('etag');

app.use(cookieParser());
app.use(express.urlencoded ({
    extended: true
}));

app.use(
    session({resave: true, saveUninitialized: true, secret: "secret", store: new FileStore(fso)})
);
var sessionValue = 1;
app.use('/', (req, res) => {

    var cookieValue;
    if (!req.cookies.cookie) {
        cookieValue = new Date().toString();
        res.cookie('cookie', cookieValue); //dodawanie ciasteczka
        //odczyt ciasteczka w index.ejs

    } else {
        cookieValue = req.cookies.cookie; // wyswietlanie wczesniejszego ciasteczka
        res.cookie('cookie', cookieValue, {maxAge: -1}); // usuwanie ciastczka
        // przy odswiezeniu lub post
    }

    if (!req.session.sessionValue) {
        sessionValue = 1;
        req.session.sessionValue = sessionValue;
    } else {
        req.session.sessionValue += 1; //modyfikacja wartosci w kontenerze sesjii
        if (req.session.sessionValue >= 10)
            req.session.sessionValue = 1; // wyzerowanie licznika po 10 odswiezeniach
        sessionValue = req.session.sessionValue;

    }

    var car = {
        name: "car",
        options: [
            {value : 1, text: "Porshe"},
            {value : 2, text: "McLaren"},
            {value : 3, text: "Ferrari"},
            {value : 4, text: "Lamborghini"},
            {value : 5, text: "Mercedes"},
            {value : 6, text: "BMW"},
            {value : 7, text: "Bugatti"},
            {value : 8, text: "Audi"},
            {value : 9, text: "Honda"}
        ]
    }
     res.render("index.ejs", {car: car, cookieValue: cookieValue, sessionValue: sessionValue});
     var cookies = ("cookie" in document && (document.cookie.length > 0 ||
        (document.cookie = "test").indexOf.call(document.cookie, "test") > -1));
    //sprawdzenie na dwa sposoby (1 jest lepszy) czy strona ma wlaczone ciasteczka (true jesli tak wpp. false)
    //console.log(cookies);
    //console.log(navigator.cookieEnabled);
});

http.createServer(app).listen(3000);


//npm init -y
//npm install express
//npm install ejs