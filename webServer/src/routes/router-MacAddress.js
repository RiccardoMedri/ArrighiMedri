const express = require('express');
const MacAddress = require('../controller/controller-MacAddress');

const router = express.Router();

router.get('/macAddress/nuovoMacAddress/:mac-:macAddress', MacAddress.addMacAddress);
router.get('/macAddress/deleteMacAddress/:mac-:macAddress', MacAddress.removeMacAddress);

module.exports=router;