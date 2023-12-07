const express = require('express');
const path = require('path');        //importa il modulo path di Node.js per la manipolazione di percorsi di file e directory

const router = express.Router();

router.get('/', (req,res) => {
    const filePath = path.join(__dirname, '../pages/home.html');    //__dirname è una variabile globale in node che rappresenta il percorso assoluto della directory del file corrente.

    res.sendFile(filePath);
});



module.exports=router;