const express = require('express');
const checkTessera = require('../controller/controller-tessere');
const deleteCard= require('../controller/controller-deleteCard');

const router = express.Router();

router.get('/tessera/:id-:mac', checkTessera.checkTessera);
router.get('/tessera/deleteCard/:id-:mac', deleteCard.deleteCard);

module.exports=router;