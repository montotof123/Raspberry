var http = require('http');
var fs = require('fs');
var Gpio = require('onoff').Gpio;
var hrtime = require('process.hrtime');

// Parametrage du gpio
var pushButton = new Gpio(26, 'in', 'falling');

var horloge;
var svgHorloge = hrtime();
var frequence;

// Création du serveur web avec chargement du fichier frequencemetre.html affiché au client
// C'est une application monopage, le serveur affichera toujours cette page
var server = http.createServer(function(req, res) {
	console.log(`${req.method} ${req.url}`);
	fs.readFile('./frequencemetre.html', 'utf-8', function(error, content) {
		res.writeHead(200, {"Content-Type": "text/html"});
		res.end(content);
	});
});
var io = require('socket.io').listen(server);

// Gestion des messages
io.sockets.on('connect', function (socket) {
	// Message de connexion sur la console et vers le client
	console.log('Un client est connecté !');
});

// Gestion de l'interruption sur front descendant
pushButton.watch(function(delta) {
	horloge = hrtime();
	frequence = 1 / ((horloge[0] + horloge[1] / 1e9) - (svgHorloge[0] + svgHorloge[1] / 1e9));
	io.emit('affiche', Math.trunc(frequence));
	svgHorloge[0] = horloge[0];
	svgHorloge[1] = horloge[1];
});

// Mise en attente des connections vers le serveur Web
server.listen(8080);