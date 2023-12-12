const connection = require('../utils/db.js');

module.exports.checkTessera = async function(req, res){
    connection.execute(
        'SELECT mac from IndirizziMAC WHERE mac=?',
        [req.params.mac],
        function(err, results, fields) {
            if (results.length > 0 && results[0]['mac'] == req.params.mac) {
                connection.execute(
                    'SELECT idtessera, ruolo, limite from tessere WHERE idtessera=?',
                    [req.params.id],
                    function(err, results, fields) {
                        if (results.length > 0 && results[0]['idtessera'] == req.params.id) {
                            dataNow = new Date().toISOString().slice(0, 10);
                            connection.execute( // se l'idtessera esiste faccio partire la connessione al db
                            // per verificare se il numero massimo di timbrature è stato raggiunto
                                `SELECT data FROM ingressi WHERE data = (SELECT MAX(data) FROM ingressi) AND idtessera = 100 ORDER BY data DESC`,
                                // faccio una query innestata: nella query interna chiedo la data più recente
                                // nella query esterna prendo tutte le date relative all'idtessera e all'ultima data
                                [],
                                function(err, resData, fields) {
                                    if(resData.length > 0) { // se esistono delle timbrature
                                        check = true;
                                        for(i = 0; i < dataNow.length; ++i) { // ciclo per verificare se oggi ha già effettuato timbrature
                                            if(dataNow[i] != resData[0]['data'][i]) {
                                                check = false; // l'ultima data a bd è precedente alla data di oggi
                                            }
                                        }
                                        if(check) { // se oggi ci sono già state timbrature
                                            countNBadge = 0
                                            for(; countNBadge < resData.length; ++countNBadge); // conto il numero di timbrature

                                            if(countNBadge < Number(results[0]['limite'])) { // se posso fare ancora timbrature
                                                // parte il connection.execute per inserire la timbratura
                                            }
                                            else {
                                                res.send("Numero massimo di timbrature raggiunto");
                                            }
                                        }
                                        else { // check == false
                                            // inserire la timbratura
                                        }
                                    }
                                    else { // se non esistono ti,brature
                                        // inserisci la timbratura
                                    }
                                }
                            )
                            const data = new Date().toISOString().slice(0, 10);
                            const orario = new Date().toLocaleTimeString();
                            connection.execute(
                                'INSERT INTO ingressi (idtessera, data, orario) VALUES (?, ?, ?)',
                                [req.params.id, data, orario],
                                function(insertErr, insertResults, insertFields) {
                                    if (insertErr) {
                                        console.error(insertErr);
                                        return res.status(500).send('Registrazione ingresso non riuscita');
                                    }
                                    res.status(200).send('Ingresso registrato');
                                }
                            )
                        }
                        else {
                            res.status(404).send('Tessera non riconosciuta');
                        }
                    }
                )
            }
            else{
                res.status(404).send('MAC address non riconosciuto')
            }
        }
    )
}