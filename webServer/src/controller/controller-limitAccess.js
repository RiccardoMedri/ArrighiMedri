const connection = require("../utils/db");

module.exports.limitAcces = async function(req, res) {
    connection.execute(
        `INSERT INTO Tessere(limite) VALUES(?)`,
        [req.params.limit],
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
