var http = require('http');
var fs = require('fs');
var wiringPi = require('wiringpi-node');

// Parametrage du wiringPi avec les GPIO de la LED et du bouton
var LED = 4;
var BUTTON = 17;
wiringPi.wiringPiSetupGpio();
wiringPi.pinMode(LED, wiringPi.OUTPUT);
wiringPi.pinMode(BUTTON, wiringPi.INPUT);

// Création du serveur web avec chargement du fichier led.html affiché au client
// Ces une application monopage, le serveur affichera toujours cette page
//    sauf pour les javascript et les images qui sont traités à part
var server = http.createServer(function(req, res) {
	console.log(`${req.method} ${req.url}`);
	if(req.url.endsWith(".js")) {
		fs.readFile(__dirname + req.url, 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "application/javascript"});
			res.end(content);
		});
	} else if(req.url.endsWith(".jpg")) {
		fs.readFile(__dirname + req.url, function(error, content) {
			res.writeHead(200, {"Content-Type": "image/jpeg"});
			res.end(content);
		});
	} else {
		fs.readFile('./led.html', 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "text/html"});
			res.end(content);
		});
	}
});
var io = require('socket.io').listen(server);

// Gestion du clignotement de la LED
var clignote = 0;

// Gestion des messages
io.sockets.on('connect', function (socket) {
	// Message de connexion sur la console et vers le client
	console.log('Un client est connecté !');
	socket.emit('toclient', 'Vous êtes bien connecté !');

	// Affiche l'état de la LED a la connexion d'un client
	if(wiringPi.digitalRead(LED)) {
		io.emit('Led', 'On');
	} else {
		io.emit('Led', 'Off');
	}
	
    // Reception du message ledOn suite au clic sur le bouton ledon  
	// message sur la console, arrêt du clignotement si necessaire et allumage de la LED
    socket.on('ledOn', function (message) {
        console.log(message);
		clearInterval(clignote);
		wiringPi.digitalWrite(LED, 1);
    });	
	
    // Reception du message ledOff suite au clic sur le bouton ledoff    
	// message sur la console, arrêt du clignotement si necessaire et extinction de la LED
    socket.on('ledOff', function (message) {
        console.log(message);
		clearInterval(clignote);
		wiringPi.digitalWrite(LED, 0);
    });	
	
    // Reception du message ledBasc suite au clic sur le bouton ledbasc  
	// Message sur la console, arrêt du clignotement si necessaire, bascule de la LED 
	//   et réenvoie d'un message au client pour mise à jour du dessin de la LED
    socket.on('ledBasc', function (message) {
        console.log(message);
		clearInterval(clignote);
		if(wiringPi.digitalRead(LED)) {
			wiringPi.digitalWrite(LED, 0);
			io.emit('Led', 'Off');
		} else {
			wiringPi.digitalWrite(LED, 1);
			io.emit('Led', 'On');
		}
	});	
	
    // Reception du message ledClign suite au clic sur le bouton ledclign 
	// Message sur la console, arrêt du clignotement si necessaire afin d'éviter des clignotement multiple, 
	// clignotement de la LED et envoie de messages au client à chaque changement d'état
	// pour mise à jour du dessin de la LED
	socket.on('ledClign', function (message) {
		console.log(message);
		clearInterval(clignote);
		clignote = setInterval(function() {
			if(wiringPi.digitalRead(LED)) {
				wiringPi.digitalWrite(LED, 0);
				io.emit('Led', 'Off');
			} else {
				wiringPi.digitalWrite(LED, 1);
				io.emit('Led', 'On');
			}
		 }, 250);
	});
});

// Gestion de l'interruption si activation du bouton
// Message sur la console, allumage de la led et envoie d'un message au client
wiringPi.wiringPiISR(BUTTON, wiringPi.INT_EDGE_FALLING, function(delta) {
	console.log('Pin 17 changed to LOW (', delta, ')');
	clearInterval(clignote);	
	wiringPi.digitalWrite(LED, 1);
	io.emit('switch', 'LOW');
});

// Mise en attente des connections vers le serveur Web
server.listen(8080);