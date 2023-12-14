const express = require('express');
const acces = require('../controller/controller-limitAccess');

const router = express.Router();

router.get('/tessera/limitaAccessi/:idtessera-:limit-:mac', acces.limitAcces);

module.exports=router;