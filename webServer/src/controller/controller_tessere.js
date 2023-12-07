const connection = require('../utils/db.js');

module.exports.checkTessera = async function(req, res){
    connection.execute(
        'SELECT idtessera, ruolo from tessere WHERE idtessera=?',
        [req.params.id],
        function(err, results, fields) {
            if (results.length > 0 && results[0]['idtessera'] == req.params.id) {
                console.log('tessera presente');
                res.json(results);

                const data = new Date().toISOString().slice(0, 10);
                const orario = new Date().toLocaleTimeString();

                connection.execute(
                    'INSERT INTO ingressi (idtessera, data, orario) VALUES (?, ?, ?)',
                    [req.params.id, data, orario],
                    function(insertErr, insertResults, insertFields) {
                        if (insertErr) {
                            console.error(insertErr);
                            return res.status(500).json({ error: 'Inserimento a ingressi table non riuscito' });
                        }
                        console.log('Ingresso registrato');
                    }
                );
            }
            else {
                console.log('errore');
                res.status(404).json({ error: 'Tessera non presente' });
            }
        }
    )
}