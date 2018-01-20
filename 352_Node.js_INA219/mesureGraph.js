var http = require('http');
var fs = require('fs');
var ina219 = require('ina219');

// Initialisation de l'INA219 
ina219.init(0x45);
ina219.enableLogging(false);
ina219.calibrate32V1A(function () {});
	  
// Création du serveur web avec chargement du fichier ina219.html affiché au client
// C'est une application monopage, le serveur affichera toujours cette page
//    sauf pour les javascript
var server = http.createServer(function(req, res) {
	console.log(`${req.method} ${req.url}`);
	if(req.url.endsWith(".js")) {
		fs.readFile(__dirname + req.url, 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "application/javascript"});
			res.end(content);
		});
	} else {
		fs.readFile('./ina219.html', 'utf-8', function(error, content) {
			res.writeHead(200, {"Content-Type": "text/html"});
			res.end(content);
		});
	}
});
var io = require('socket.io').listen(server); 

setInterval(function () {
    
    ina219.getBusVoltage_V(function (volts) {
		io.emit('Tension', volts); 
    });	
	
    ina219.getCurrent_mA(function (current){
		io.emit('Courant', current);     
	});
}, 3000);
  
// Mise en attente des connections vers le serveur Web
server.listen(8080);
