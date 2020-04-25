// Parametres de connexion a PostgreSQL
module.exports = {
  HOST: "localhost",
  USER: "postgres",
  PASSWORD: "trucmuche",
  DB: "postgres",
  dialect: "postgres",
  pool: {
    max: 5,
    min: 0,
    acquire: 30000,
    idle: 10000
  }
};
