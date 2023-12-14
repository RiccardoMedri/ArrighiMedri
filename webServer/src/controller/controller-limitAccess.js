const connection = require("../utils/db");

module.exports.limitAcces = async function(req, res) {
    connection.execute(
        'SELECT mac from IndirizziMAC WHERE mac=?',                                  //controlla che il mac address ci sia
        [req.params.mac],
        function(err, results, fields) {
            
            if (results.length > 0 && results[0]['mac'] == req.params.mac) {
                connection.execute(
                    `UPDATE tessere SET limite = ? WHERE idtessera = ?`,
                    [req.params.limit, req.params.idtessera],
                    function(err, results, fields) {
                        res.setHeader('Content-Type', 'text/plain');
                        if(!err) {
                            res.send("Limite numero di accessi inserito");
                        }
                        else {
                            res.send(err);
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
