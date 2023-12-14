const connection = require('../utils/db.js');

module.exports.checkTessera = async function(req, res){
    connection.execute(
        'SELECT mac from IndirizziMAC WHERE mac=?',
        [req.params.mac],
        function(err, results, fields) {

            if (results.length > 0 && results[0]['mac'] == req.params.mac) {
                connection.execute(
                    'SELECT idtessera, ruolo from tessere WHERE idtessera=?',
                    [req.params.id],
                    function(err, results, fields) {

                        if (results.length > 0 && results[0]['idtessera'] == req.params.id) {
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