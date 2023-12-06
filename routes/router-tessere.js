const express = require('express');
const path = require('path');
const fs = require('fs');

const router = express.Router();

router.get('/tessere', (req,res) => {
    const filePath = path.join(__dirname, '../pages/tessere.json');

    fs.readFile(filePath, 'utf8', (err, data) => {
        if(err) {
            console.error(err);
            res.status(500).send('Errore durante lettura json');
            return;
        }

        const jsonData = JSON.parse(data);

        res.json(jsonData);
    });
});

module.exports=router;