const dbConfig = require("../config/db.config.js");

const Sequelize = require("sequelize");
const sequelize = new Sequelize(dbConfig.DB, dbConfig.USER, dbConfig.PASSWORD, {
  host: dbConfig.HOST,
  dialect: dbConfig.dialect,
  schema: 'raspberry',
  // Evite les doubles quotes dans la requete, mauvais pour la securite car cela permet l'injection SQL, 
  //   mais PostgreSQL ne fonctionne pas avec les doubles quotes
  quoteIdentifiers: false,
  dialectOptions: {
    useUTC: false, //for reading from database
    dateStrings: true,
    typeCast: true
    },
    timezone: '+01:00', //for writing to database

  pool: {
    max: dbConfig.pool.max,
    min: dbConfig.pool.min,
    acquire: dbConfig.pool.acquire,
    idle: dbConfig.pool.idle
  }
});

const db = {};

db.Sequelize = Sequelize;
db.sequelize = sequelize;

db.eventiot = require("./eventiot.model.js")(sequelize, Sequelize);

module.exports = db;
