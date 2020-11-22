const express = require("express");
const bodyParser = require("body-parser");
const cors = require('cors');
const app = express();

app.use(cors());

// L'API repond en content-type - application/json
app.use(bodyParser.json());

// L'API repond en content-type - application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));

// Charge le model (fait un CREATE TABLE IF NOT EXISTS)
// ATTENTION: un parametre force: true dans la fonction sync fera un DROP TABLE IF EXISTS et detruira la table si elle existe
const db = require("./app/models");
db.sequelize.sync();

// Message pour la racine du serveur
// ex: http://192.168.1.100:8082
app.get("/", (req, res) => {
  res.json({ message: "Welcome to IOT application." });
});

// Charge les routes
require("./app/routes/eventiot.routes")(app);

// Lance le serveur HTTP sur un port
const PORT = process.env.PORT || 8082;
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}.`);
});
