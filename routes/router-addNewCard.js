const express = require('express');
const addNewCard = require("../pages/controller-addNewCard");
const router = express.Router();

router.get("/tessere/nuovaTessera/:id-:nome-:cognome-:ruolo", addNewCard.addNewCard);

module.exports = router;