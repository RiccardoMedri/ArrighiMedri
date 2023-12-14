const connection = require("../utils/db");

module.exports.limitAcces = async function(req, res) {
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
