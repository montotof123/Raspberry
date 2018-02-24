// Chargement des modules
var express = require('express');
var wiringPi = require('wiringpi-node');

// Initialisation du module Express
var app = express();

// Initialisation du module wiringPi et parametrage de la LED
var LED = 4;
wiringPi.wiringPiSetupGpio();
wiringPi.pinMode(LED, wiringPi.OUTPUT);

// Ecoute de l'adresse /on (en local http://localhost:8080/on)
// Allume la LED
app.get('/on', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.end('Allume la LED');
	wiringPi.digitalWrite(LED, 1);
});

// Ecoute de l'adresse /off (en local http://localhost:8080/off)
// Eteint la LED
app.get('/off', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.end('Eteint la LED');
	wiringPi.digitalWrite(LED, 0);
});

// Ecoute de l'adresse /bascule (en local http://localhost:8080/bascule)
// Change la LED d'etat
app.get('/bascule', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.end('Bascule la LED');
	if(wiringPi.digitalRead(LED)) {
		wiringPi.digitalWrite(LED, 0);
	} else {
 		wiringPi.digitalWrite(LED, 1);
	}
});

// Si vous voulez gérer les erreurs 404, 
// vous devez inclure les lignes suivantes obligatoirement à la fin de votre code
// car les route sont analisees dans l'ordre
// Si vous mettez cette route en prmier, elle sera toujours utilisee et rien ne marchera  
// (juste avant app.listen) :

// ... Tout le code de gestion des routes (app.get) se trouve au-dessus

app.use(function(req, res, next){
    res.setHeader('Content-Type', 'text/plain');
    res.status(404).send('Page introuvable !');
});

console.log('Serveur lancé: CTRL-C pour arrêter');

// Demarre le serveur web sur le port 8080
app.listen(8080);
