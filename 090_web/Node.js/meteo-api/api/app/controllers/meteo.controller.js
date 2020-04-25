const db = require("../models");
const Meteo = db.meteo;
const Op = db.Sequelize.Op;

// Donne une date Javascript par rapport aux parametres date et heure de l'URL
let dateUTC = function(pDate, pTime) {
  let dateGMT = new Date();
  let paramDate = pDate.split('/');
  let paramTime = pTime.split(':');
  dateGMT.setDate(paramDate[2]);
  dateGMT.setMonth(paramDate[1] - 1);
  dateGMT.setFullYear(paramDate[0]);
  dateGMT.setHours(paramTime[0]);
  dateGMT.setMinutes(paramTime[1]);
  dateGMT.setSeconds(0);
  return (new Date(dateGMT.getTime() - dateGMT.getTimezoneOffset() * 60 * 1000));
}

// Recupère toutes les information de la table
// ex: http://192.168.1.100:8081/api/meteo
exports.findAll = (req, res) => {
  const title = req.query.title;
  Meteo.findAll({  })
    // Requete OK status 200
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue"
      });
    });  
};

// Recupere les informations pour la trace de courbe de temperature
// ex: http://192.168.1.100:8081/api/meteo/courbeTemperature?dateMin=2020/04/20&timeMin=12:00&dateMax=2020/04/23&timeMax=20:00
exports.findCourbeTemperature = (req, res) => {
  let results;
  db.sequelize.query("SELECT to_char(horaire, 'YYYY-MM-DD') AS jour, to_char(horaire, 'HH24:MI') AS heure, extract(epoch from horaire) - extract(epoch from timestamp '" 
    + req.query.dateMin + " " + req.query.timeMin + "') as nbsec, temperature FROM raspberry.meteo WHERE horaire BETWEEN '" 
    + req.query.dateMin + " " + req.query.timeMin + "'::timestamp AND '" + req.query.dateMax + " " + req.query.timeMax + "'::timestamp order by 1, 2", { type: db.sequelize.QueryTypes.SELECT })
  .then(results => {
    res.send(results);
  })
  .catch(err => {
    res.status(500).send({
      message: err.message || "Une erreur est survenue"
    });
  }); 
};

// Recupere les informations pour la trace de courbe de pression
// ex: http://192.168.1.100:8081/api/meteo/courbePression?dateMin=2020/04/20&timeMin=12:00&dateMax=2020/04/23&timeMax=20:00
exports.findCourbePression = (req, res) => {
  let results;
  db.sequelize.query("SELECT to_char(horaire, 'YYYY-MM-DD') AS jour, to_char(horaire, 'HH24:MI') AS heure, extract(epoch from horaire) - extract(epoch from timestamp '" 
    + req.query.dateMin + " " + req.query.timeMin + "') as nbsec, pression_niveau_mer FROM raspberry.meteo WHERE horaire BETWEEN '" 
    + req.query.dateMin + " " + req.query.timeMin + "'::timestamp AND '" + req.query.dateMax + " " + req.query.timeMax + "'::timestamp order by 1, 2", { type: db.sequelize.QueryTypes.SELECT })
  .then(results => {
    res.send(results);
  })
  .catch(err => {
    res.status(500).send({
      message: err.message || "Une erreur est survenue"
    });
  }); 
};

// Recupere les informations pour la trace de courbe d'humidite
// ex: http://192.168.1.100:8081/api/meteo/courbeHumidite?dateMin=2020/04/20&timeMin=12:00&dateMax=2020/04/23&timeMax=20:00
exports.findCourbeHumidite = (req, res) => {
  let results;
  db.sequelize.query("SELECT to_char(horaire, 'YYYY-MM-DD') AS jour, to_char(horaire, 'HH24:MI') AS heure, extract(epoch from horaire) - extract(epoch from timestamp '" 
    + req.query.dateMin + " " + req.query.timeMin + "') as nbsec, humidite FROM raspberry.meteo WHERE horaire BETWEEN '" 
    + req.query.dateMin + " " + req.query.timeMin + "'::timestamp AND '" + req.query.dateMax + " " + req.query.timeMax + "'::timestamp order by 1, 2", { type: db.sequelize.QueryTypes.SELECT })
  .then(results => {
    res.send(results);
  })
  .catch(err => {
    res.status(500).send({
      message: err.message || "Une erreur est survenue"
    });
  }); 
};

// Envoie les informations brute de temperature entre deux dates
// ex: http://192.168.1.100:8081/api/meteo/temperature?dateMin=2020/04/20&timeMin=12:00&dateMax=2020/04/23&timeMax=20:00
exports.findTemperature = (req, res) => {
  Meteo.findAll({ attributes: ['horaire', 'temperature'],
                  where: { horaire: {
                           [Op.gte]: dateUTC(req.query.dateMin, req.query.timeMin),
                           [Op.lte]: dateUTC(req.query.dateMax, req.query.timeMax)}
                           }})
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Envoie les informations brute de pression entre deux dates
// ex: http://192.168.1.100:8081/api/meteo/pression?dateMin=2020/04/20&timeMin=12:00&dateMax=2020/04/23&timeMax=20:00
exports.findPression = (req, res) => {
  Meteo.findAll({ attributes: ['horaire', 'pression_niveau_mer'],
                  where: { horaire: {
                           [Op.gte]: dateUTC(req.query.dateMin, req.query.timeMin),
                           [Op.lte]: dateUTC(req.query.dateMax, req.query.timeMax)}
                           }})
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Envoie les informations brute d'humidite entre deux dates
// ex: http://192.168.1.100:8081/api/meteo/humidite?dateMin=2020/04/20&timeMin=12:00&dateMax=2020/04/23&timeMax=20:00
exports.findHumidite = (req, res) => {
  Meteo.findAll({ attributes: ['horaire', 'humidite'],
                  where: { horaire: {
                           [Op.gte]: dateUTC(req.query.dateMin, req.query.timeMin),
                           [Op.lte]: dateUTC(req.query.dateMax, req.query.timeMax)}
                           }})
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Envoie les informations brute de la derniere temperature
// ex: http://192.168.1.100:8081/api/meteo/currentTemperature
exports.findCurrentTemperature = (req, res) => {
  Meteo.findAll({ attributes: ['horaire', 'temperature'],
                  order: ['horaire DESC'],
                  limit:1
                  })
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Envoie les informations brute de la derniere pression
// ex: http://192.168.1.100:8081/api/meteo/currentPression
exports.findCurrentPression = (req, res) => {
  Meteo.findAll({ attributes: ['horaire', 'pression_niveau_mer'],
                  order: ['horaire DESC'],
                  limit:1
                  })  
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Envoie les informations brute de la derniere humidite
// ex: http://192.168.1.100:8081/api/meteo/currentHumidite
exports.findCurrentHumidite = (req, res) => {
  Meteo.findAll({ attributes: ['horaire', 'humidite'],
                  order: ['horaire DESC'],
                  limit:1
                  })  
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Envoie les informations brute de la derniere mesure
// ex: http://192.168.1.100:8081/api/meteo/currentAll
exports.findCurrentAll = (req, res) => {
  Meteo.findAll({ attributes: ['horaire', 'temperature', 'pression_niveau_mer', 'humidite'],
                  order: ['horaire DESC'],
                  limit:1
                  })  
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};
