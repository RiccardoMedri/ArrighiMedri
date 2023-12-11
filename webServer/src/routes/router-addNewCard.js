const express = require('express');
const addNewCard = require("../controller/controller-addNewCard");
const router = express.Router();

router.get("/tessera/nuovaTessera/:id-:nome-:cognome-:ruolo-:mac", addNewCard.addNewCard);

module.exports = router;