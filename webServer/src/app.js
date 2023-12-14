const express = require("express");
const app = express();
const port = 3000;
const home = require('./routes/router-home.js');
const tessere = require('./routes/router-tessere.js');
const newCard = require('./routes/router-addNewCard.js');
const acces = require('./routes/router-limitAcces.js');

app.use(express.static('public'));

app.use(home);
app.use(tessere);
app.use(newCard);
app.use(acces);

app.use(function(req,res,next){
    res.setHeader('Content-Type', 'text/plain');
    res.status(404).send('Ops... Pagina non trovata');
});

app.listen(port, function () {
    console.log('Listening on port ' + port);
});
