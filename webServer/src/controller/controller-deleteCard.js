const connection = require("../utils/db");

module.exports.deleteCard = async function(req, res) {
    connection.execute(
        'SELECT mac from IndirizziMAC WHERE mac=?',                                  //controlla che il mac address ci sia
        [req.params.mac],
        function(err, results, fields) {

            if (results.length > 0 && results[0]['mac'] == req.params.mac) {         //se c'è macaddress cerca la tessera a db
                connection.execute(
                    'SELECT idtessera FROM tessere WHERE idtessera = ?',
                    [req.params.id],
                    function(err, results, fields) {

                        if(results.length > 0) {                                     //se tessera c'è allora cancellala
                            connection.execute(
                                'DELETE FROM tessere WHERE idtessera=?',
                                [req.params.id]
                            )
                            res.setHeader('Content-Type', 'text/plain');
                            res.send("Carta eliminata con successo!");
                        }
                        else {                                                       //se tessera non c'è allora errore
                            res.setHeader('Content-Type', 'text/plain');
                            res.send("ERRORE! Tessera non presente!");
                        }
                    }
                )
            }
            else{                                                                    //se non c'è macAddress allora errore
                res.status(404).send('MAC address non riconosciuto')
            } 
        }
    )
}