var http = require('http');
var express = require('express');

var app = express();
var imie_nazwisko = 0;
var nazwa_zajec = 0;
var z1 = 0; var z2 = 0; var z3 = 0;
var z4 = 0; var z5 = 0; var z6 = 0;
var z7 = 0; var z8 = 0; var z9 = 0;
var z10 = 0;
app.set('view engine', 'ejs');
app.set('views', './views');

app.use(express.urlencoded({extended:true}));

app.get( '/', (req, res, next) => {
    res.render('index', {
        imie_nazwisko: '',
        nazwa_zajec: '',
        z1: '',z2: '',z3: '',z4: '',z5: '',
        z6: '',z7: '',z8: '',z9: '',z10: ''
    });
});
app.post('/', (req, res) => {
    imie_nazwisko = req.body.imie_nazwisko;
    nazwa_zajec = req.body.nazwa_zajec;
    z1 = req.body.z1; z2 = req.body.z2; z3 = req.body.z3;
    z4 = req.body.z4; z5 = req.body.z5; z6 = req.body.z6;
    z7 = req.body.z7; z8 = req.body.z8; z9 = req.body.z9;
    z10 = req.body.z10;
    if(!imie_nazwisko || !nazwa_zajec)
        res.render('index', {
            imie_nazwisko: '',
            nazwa_zajec: '',
            z1: '',z2: '',z3: '',z4: '',z5: '',
            z6: '',z7: '',z8: '',z9: '',z10: ''
        });
    else
        res.redirect('/print');
});
app.get('/print', (req, res) => {
    res.render('print', {
        imie_nazwisko: imie_nazwisko,
        nazwa_zajec: nazwa_zajec,
        z1: z1 || '0',z2: z2 || '0',z3: z3 || '0',z4: z4 || '0',
        z5: z5 || '0',z6: z6 || '0',z7: z7 || '0',z8: z8 || '0',
        z9: z9 || '0',z10: z10 || '0',
    });
});

http.createServer(app).listen(3000)