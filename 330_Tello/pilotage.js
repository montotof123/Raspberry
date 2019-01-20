// Modules
var i2c = require('i2c-bus');
var MPU6050 = require('..');
const got = require('got');
const eol = require('os').EOL;
const readline = require('readline');
var fs = require('fs');
const dgram = require('dgram');

// Accelerometre
var address = 0x68;
var i2c1 = i2c.openSync(1);
var sensor = new MPU6050(i2c1, address);

// Boucle de pilotage
var orderInterval = setInterval(orderPilot, 200); //Read command every 100ms

// Valiable indiquant si le drone est en vol
var enVol = false;

// Connexion au drone
var PORT = 8889;
var HOST = '192.168.10.1';
const client = dgram.createSocket('udp4');
client.bind(8001);
// Activation des commandes
CommandRequest();

// Boucle de commande
function orderPilot() {
	// Lecture de l'accelerometre 
	let data = sensor.readAccelSync();
	// Calcul des angles
	let angleXZ = Math.atan2(data.x, data.z) * 180.0 / Math.PI;
	let angleYZ = Math.atan2(data.y, data.z) * 180.0 / Math.PI;

	// 60° ou plus vers l'avant --> decollage
	if(angleXZ <= -60) {
		if(!enVol) {
			console.log("Decollage");
			enVol = true;
			TakeoffRequest();
		}
	}
	// 60° ou plus vers l'arriere --> atterrissage
	if(angleXZ >= 60) {
		if(enVol) {
			console.log("Atterissage");
			enVol = false;
			LandRequest();
		}
	}
	// Entre 30 et 60° vers l'avant, avance lente
	if(angleXZ < -30 && angleXZ > -60) {
		if(enVol) {
			console.log("avant");
			let dis = 20;
			let message = new Buffer( 'forward '+ dis );
			client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
				if (err) throw err;
			});			
		}
	}
	// Entre 30 et 60° vers l'arriere, recule lentement
	if(angleXZ > 30 && angleXZ < 60) {
		if(enVol) {
			console.log("arriere");
			let dis = 20;
			let message = new Buffer( 'back '+ dis );
			client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
				if (err) throw err;
			});			
		}
	}
	// Entre 30 et 60° vers la droite, a droite lentement
	if(angleYZ < -30 && angleYZ > -60) {
		if(enVol) {
			console.log("droite");
			let dis = 20;
			let message = new Buffer( 'right '+ dis );
			client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
				if (err) throw err;
			});
		}
	}
	// Entre 30 et 60° vers la gauche, a gauche lentement
	if(angleYZ > 30 && angleYZ < 60) {
		if(enVol) {
			console.log("gauche");
			let dis = 20;
			let message = new Buffer( 'left '+ dis );
			client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
				if (err) throw err;
			});
		}
	}
}

// Arrêt boucle si necessaire
function endPilot() { //function to stop pilot
  clearInterval(orderInterval); // Stop pilot intervals
}

// Mode commande
function CommandRequest(){

	var message = new Buffer('command');

	client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
		if (err) throw err;
	});
	
	client.on('message', (msg,info) => {
		console.log('Data received from server : ' + msg.toString());
		console.log('Received %d bytes from %s:%d\n',msg.length, info.address, info.port);
	});								
	
}

// Decollage
function TakeoffRequest(){
	
	let message = new Buffer('takeoff');

	client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
		if (err) throw err;
	});
}

// Atterrissage
function LandRequest(){

	let message = new Buffer('land');

	client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
		if (err) throw err;
	});
}


