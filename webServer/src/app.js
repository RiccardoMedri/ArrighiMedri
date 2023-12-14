const express = require("express");
const app = express();
const port = 3000;
const home = require('./routes/router-home.js');
const card = require('./routes/router-card.js');
const MacAddress = require('./routes/router-MacAddress.js');

app.use(express.static('public'));

app.use(home);
app.use(card);
app.use(MacAddress);

app.use(function(req,res,next){
    res.setHeader('Content-Type', 'text/plain');
    res.status(404).send('Ops... Pagina non trovata');
});

app.listen(port, function () {
    console.log('Listening on port ' + port);
});
