const { Pool } = require("pg");

const pool = new Pool({
  user: "postgres",
  host: "localhost",
  database: "postgres",
  password: "trucmuche",
  port: "5432"
});

pool.query("SELECT nb_patte, nom, utilisation, alimentation	FROM raspberry.composants", (err, res) => {
    if (err) {
        console.error(err);
        return;
    }
    for (let row of res.rows) {
		let nbPatte = row.nb_patte;
		let nom = row.nom;
		let utilisation = row.utilisation;
		let alimentation = row.alimentation;
        console.log(nbPatte + " " + nom + " " + utilisation + " " + alimentation);
    }
    pool.end();
});