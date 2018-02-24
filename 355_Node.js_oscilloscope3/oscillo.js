var http = require('http');
var fs = require('fs');
var mcp3208 = require('mcp-spi-adc');
var sync = require('child_process').spawnSync;
var readline = require("./public/node-readline.js")

var temps = [];
var mesure = [];
var tension = mcp3208.openMcp3208(7, {speedHz: 2000000}, function (err) { if (err) throw err;});


// Création du serveur web avec chargement du fichier html affiché au client
// C'est une application monopage, le serveur affichera toujours cette page
var server = http.createServer(function(req, res) {
	console.log(`${req.method} ${req.url}`);
	if(req.url.endsWith(".js")) {
		fs.readFile(__dirname + req.url, 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "application/javascript"});
			res.end(content);
		});
	} else {
		fs.readFile('./oscillo.html', 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "text/html"});
			res.end(content);
		});
	}
});
var io = require('socket.io').listen(server); 

// Lancement des mesures apres appui sur bouton
io.sockets.on('connect', function (socket) {
	socket.on('startMesure', function (param) {
		console.log("start mesure canal:" + param.canal);
		var ls = sync('./mesures', [param.canal, param.nombre]);
		console.log("end mesure canal:" + param.canal);
	});
	socket.on('afficheMesure', function () {
		var r=readline.fopen("./mesures.csv", "r");
		var mesure = [];
		var temps = [];
		while (!readline.eof(r)) {
			var line = readline.fgets(r);
			if(line != false) {
				var colonnes = line.split(";");
				temps.push(colonnes[0] / 1000000);
				mesure.push(colonnes[1]);
			}
		}
		readline.fclose(r);
		
		result = [];		
		for(var compteur = 0; compteur != mesure.length; compteur++) {
			var myResult = {};
			myResult.valeur = mesure[compteur];
			myResult.horloge = temps[compteur] - temps[0];
			result.push(myResult);
		}
		io.emit("afficheMesure", result);
	});
});

// Mise en attente des connections vers le serveur Web
server.listen(8080);
