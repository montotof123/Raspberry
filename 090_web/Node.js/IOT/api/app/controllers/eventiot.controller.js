const db = require("../models");
const EventIOT = db.eventiot;
const Op = db.Sequelize.Op;
const {Sequelize} = require('sequelize');

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
  return (dateGMT);
}

// Recupere toutes les informations de la table
// ex: http://192.168.1.100:8082/api/eventiot
exports.findAll = (req, res) => {
  const title = req.query.title;
  EventIOT.findAll({  })
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

// Recupere les informations entre deux dates
// ex: http://192.168.1.100:8082/api/eventiot/findBetweenDates?dateMin=2020/04/20&timeMin=12:00&dateMax=2020/04/23&timeMax=20:00
// Attention: l'horaire est en GMT
exports.findBetweenDates = (req, res) => {
  EventIOT.findAll({ attributes: ['horaire', 'id'],
                  where: { horaire: {
                           [Op.gte]: dateUTC(req.query.dateMin, req.query.timeMin),
                           [Op.lte]: dateUTC(req.query.dateMax, req.query.timeMax)}
                           }})
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Recupere les informations de la derniere valeur
// ex: http://192.168.1.100:8082/api/eventiot/findLast
// Attention: l'horaire est en GMT
exports.findLast = (req, res) => {
  EventIOT.findAll({ attributes: ['horaire', 'id'],
                  order: ['horaire DESC'],
                  limit:1
                  })  
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Recupere les informations de la dernière valeur de chaque Id
// ex: http://192.168.1.100:8082/api/eventiot/findLastAllId
// Attention: le jour et l'heure sont donnees en heure locale, par contre le nombre de seconde est en fonction de l'heure GMT
exports.findLastAllId = (req, res) => {
  EventIOT.findAll({ attributes: [Sequelize.fn('MAX', Sequelize.col('horaire')), 'id'],
                  group: ['id'],
				  raw:true,
                  })  
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};


// Recupere tous les Id
// ex: http://192.168.1.100:8082/api/eventiot/findAllId
// Attention: l'horaire est en GMT
exports.findAllId = (req, res) => {
  EventIOT.aggregate( 'id', 'DISTINCT', {plain:false})  
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Recupere toutes les information d'un Id
// ex: http://192.168.1.100:8082/api/eventiot/findAllById?id=PorteEntrée
// Attention: l'horaire est en GMT
exports.findAllById = (req, res) => {
  EventIOT.findAll({ attributes: ['horaire', 'id'],
                  order: ['horaire DESC'],
                  where: { id: req.query.id}
                  })
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};

// Recupere la dernière valeur d'un Id
// ex: http://192.168.1.100:8082/api/eventiot/findLastById?id=PorteEntrée
// Attention: l'horaire est en GMT
exports.findLastById = (req, res) => {
  EventIOT.findAll({ attributes: ['horaire', 'id'],
                  order: ['horaire DESC'],
                  limit:1,
                  where: { id: req.query.id}
                  })  
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });  
};


// Stocke les informations dans une ligne de la base de donnees
// ex: http://192.168.1.100:8082/api/eventiot
// les donnees doivent être passees dans le Body dans une structure JSON
// {id:'porteEntrée'}
// Attention: la requete doit etre envoyee en POST
exports.createValue = (req, res) => {
  // Validation de la requete
  if (!req.body.id) {
    res.status(400).send({
      message: "Données manquantes dans le Body"
    });
    return;
  }

  // Stockage d'une ligne
  const ligne = {
    horaire: db.sequelize.literal('CURRENT_TIMESTAMP'),
    id: req.body.id
  };

  // Save Tutorial in the database
  EventIOT.create(ligne)
    .then(data => {
      res.send(data);
    })
    .catch(err => {
      // Erreur technique 500
      res.status(500).send({
        message:
          err.message || "Une erreur est survenue."
      });
    });
};