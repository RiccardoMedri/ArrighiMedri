const connection = require("../utils/db");

module.exports.addNewCard = async function(req, res) {
    connection.execute(
        'SELECT idtessera FROM tessere WHERE idtessera = ?',
        [req.params.id],
        function(err, results, fields) {
            if(results.length > 0) {
                res.setHeader('Content-Type', 'text/plain');
                res.send("ERRORE! Tessera già esistente!");
            }
            else {
                connection.execute(
                    'INSERT INTO tessere(idtessera, nome, cognome, ruolo) VALUES (?, ?, ?, ?)',
                    [req.params.id, req.params.nome, req.params.cognome, req.params.ruolo]
                )
                res.setHeader('Content-Type', 'text/plain');
                res.send("Carta aggiunta con successo!");
            }
        }
    )
}