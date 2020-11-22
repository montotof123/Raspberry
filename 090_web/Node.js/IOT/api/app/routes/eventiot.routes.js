module.exports = app => {
  const eventiot = require("../controllers/eventiot.controller.js");

  var router = require("express").Router();

  // Routes pour recuperer les informations de eventiot
  router.get("/", eventiot.findAll);
  router.get("/findBetweenDates", eventiot.findBetweenDates);
  router.get("/findLast", eventiot.findLast);
  router.get("/findLastAllId", eventiot.findLastAllId);
  router.get("/findAllId", eventiot.findAllId);
  router.get("/findAllById", eventiot.findAllById);
  router.get("/findLastById", eventiot.findLastById);

  // Route pour stocker une mesure
  router.post("/", eventiot.createValue);

  // Route racine
  app.use("/api/eventiot", router);
};
