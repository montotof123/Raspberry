const http = require('http');
const fs = require('fs');
const axios = require("axios");

// Création du serveur web avec chargement du fichier html affiché au client
// C'est une application monopage, le serveur affichera toujours la même page html
const server = http.createServer(function(req, res) {
	console.log(`${req.method} ${req.url}`);
	if(req.url.endsWith(".js")) {
		fs.readFile(__dirname + req.url, 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "application/javascript"});
			res.end(content);
		});
	} else if(req.url.endsWith(".css")) {
		fs.readFile(__dirname + req.url, 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "text/css"});
			res.end(content);
		});
	} else{
		fs.readFile('./meteo.html', 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "text/html"});
			res.end(content);
		});
	}
});

// A mettre aprés la création du serveur
const io = require('socket.io').listen(server); 

// Lancement de l'écoute des actions
io.sockets.on('connect', function (socket) {
	// Lancement des mesures après appui sur le bouton "afficheMesure"
	socket.on('afficheMesure', function (param) {
		//Construction de la requête avec un filtre en fonction de la mesure voulue et des dates et heures renseignées dans l'ihm
		let requestURL;
		switch(param.mesure) {
			case "temperature": requestURL = "http://192.168.1.100:8081/api/meteo/courbeTemperature?dateMin=" +
											param.date_min + "&timeMin=" + 
											param.time_min + "&dateMax=" + 
											param.date_max + "&timeMax=" + 
											param.time_max;
				break;
			case "pression": requestURL = "http://192.168.1.100:8081/api/meteo/courbePression?dateMin=" +
											param.date_min + "&timeMin=" + 
											param.time_min + "&dateMax=" + 
											param.date_max + "&timeMax=" + 
											param.time_max;
				break;
			case "humidite": requestURL = "http://192.168.1.100:8081/api/meteo/courbeHumidite?dateMin=" +
											param.date_min + "&timeMin=" + 
											param.time_min + "&dateMax=" + 
											param.date_max + "&timeMax=" + 
											param.time_max;
				break;
		}
		// Exécution de la requete
		// Attention code asynchrone:
		//   Le programme passe instantannément à la suite et le la Promise s'exécute quand la requête renvoit le résultat
		let result = [];		
		axios.get(requestURL)
		.then(function (response) {
		  	// handle success
		  	for (let row of response.data) {
				let myResult = {};
				myResult.jour = row.jour;
				myResult.heure = row.heure;
				myResult.nbsec = row.nbsec;
				switch(param.mesure) {
					case "temperature": myResult.valeur = row.temperature; break;
					case "pression": myResult.valeur = row.pression_niveau_mer; break;
					case "humidite": myResult.valeur = row.humidite; break;
				}
				result.push(myResult);
		  	}
			io.emit("afficheMesure", result);
		})
		.catch(function (error) {
		  // handle error
		  console.log(error);
		})
		.finally(function () {
		  // always executed
		});
	});
});

// Mise en attente des connections vers le serveur Web
server.listen(8080);
