const express = require('express');
const acces = require('../controller/controller-limitAccess');

const router = express.Router();

router.get('/tessera/limitaAccessi/:limit', acces.limitAcces);
router.get('/prova', acces.prova);

module.exports=router;