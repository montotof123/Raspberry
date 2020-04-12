const http = require('http');
const fs = require('fs');
const { Pool } = require("pg");

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
		const find = '/';
		const reg = new RegExp(find, 'g');
		let request = "SELECT to_char(horaire, 'YYYY-MM-DD') AS jour, to_char(horaire, 'HH24:MI') AS heure, extract(epoch from horaire) - extract(epoch from timestamp '" 
		+ param.date_min.replace(reg, "-") + " " + param.time_min + "') as nbsec, ";
		switch(param.mesure) {
			case "temperature": request += "temperature "; break;
			case "pression": request += "pression_niveau_mer "; break;
			case "humidite": request += "humidite "; break;
		}
		request += "FROM raspberry.meteo WHERE horaire BETWEEN '" + param.date_min.replace(reg, "-") + " " + param.time_min + "'::timestamp AND '" + param.date_max.replace(reg, "-") + " " + param.time_max + "'::timestamp order by 1, 2";
		// Exécution de la requete
		// Attention code asynchrone:
		//   Le programme passe instantannément à la suite et le bloc pool.query s'exécute quand la requête renvoit le résultat
		let result = [];		
		const pool = new Pool({user: "postgres", host: "localhost", database: "postgres", password: "trucmuche", port: "5432"});
		pool.query(request, (err, res) => {
			if (err) {
				console.error(err);
				return;
			}
			// Récuperation des données
			for (let row of res.rows) {
				// Chaque ligne est envoyée dans un objet résultat contenant
				// - Le jour
				// - L'heure
				// - Le nombre de seconde par rapport à la date et l'heure de début renseignées dans l'ihm
				//   Ce nombre de seconde permet de positionner la mesure sur la courbe plus facilement
				// - La mesure demandée
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
			pool.end();
			io.emit("afficheMesure", result);
		});
	});
});

// Mise en attente des connections vers le serveur Web
server.listen(8080);
