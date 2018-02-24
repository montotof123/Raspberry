var http = require('http');
var fs = require('fs');
var mcp3208 = require('mcp-spi-adc');
var hrtime = require('process.hrtime');

var tension = mcp3208.openMcp3208(7, {speedHz: 2000000}, function (err) { if (err) throw err;});

// Création du serveur web avec chargement du fichier oscillo.html affiché au client
// C'est une application monopage, le serveur affichera toujours cette page
//    sauf pour les javascript
var server = http.createServer(function(req, res) {
	console.log(`${req.method} ${req.url}`);
	fs.readFile('./oscillo.html', 'utf-8', function(error, content) {
		res.writeHead(200, {"Content-Type": "text/html"});
		res.end(content);
	});
});
var io = require('socket.io').listen(server); 

io.sockets.on('connect', function (socket) {
	socket.on('startMesure', function (message) {
		const nombreMesure = 60000; 
		console.log("start mesure");
		
		var temps = [];
		var mesure = [];
		var compteur;   
		
		// Système un peu tordu pour avoir les mesures.
		// Sinon, le tableau est vide car les appels à read
		// n'ont en fait pas encore été lancé
		// Faire gaffe au callback
		function finMesure() {
			if(mesure.length == nombreMesure) {
				io.emit("Mesure", "Début enregistrement");
				clearInterval(testFin);
				console.log("fin mesure");
				var diffInit = temps[0];
				for(compteur = 0; compteur != nombreMesure; compteur++) {
					var valeur = (mesure[compteur] * 3.3) + "";
					var diff = temps[compteur];
					var horloge = ((diff[0] + diff[1] / 1e9) - (diffInit[0] + diffInit[1] / 1e9)) + "";
					console.log((horloge.replace(".", ",")) + ";" + (valeur.replace(".", ",")));
				}
				io.emit("Mesure", "Enregistrement terminées");
			}
		}
		testFin = setInterval(finMesure, nombreMesure / 8);
		console.log("début mesure");
		for(compteur = 0; compteur != nombreMesure; compteur++) {
			tension.read(function (err, reading) {
				temps.push(hrtime());
				mesure.push(reading.value);
			});
		} 
			
	});
});
 
 
// Mise en attente des connections vers le serveur Web
server.listen(8080);
