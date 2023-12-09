const express = require('express');
const checkTessera = require('../controller/controller_tessere');

const router = express.Router();

router.get('/tessera/:id', checkTessera.checkTessera);

module.exports=router;