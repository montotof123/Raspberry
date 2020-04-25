module.exports = app => {
  const meteo = require("../controllers/meteo.controller.js");

  var router = require("express").Router();

  // Routes pour recuperer les informations de meteo
  router.get("/", meteo.findAll);
  router.get("/temperature", meteo.findTemperature);
  router.get("/pression", meteo.findPression);
  router.get("/humidite", meteo.findHumidite);
  router.get("/courbeTemperature", meteo.findCourbeTemperature);
  router.get("/courbePression", meteo.findCourbePression);
  router.get("/courbeHumidite", meteo.findCourbeHumidite);
  router.get("/currentAll", meteo.findCurrentAll);
  router.get("/currentTemperature", meteo.findCurrentTemperature);
  router.get("/currentPression", meteo.findCurrentPression);
  router.get("/currentHumidite", meteo.findCurrentHumidite);

  // Route racine
  app.use("/api/meteo", router);
};
