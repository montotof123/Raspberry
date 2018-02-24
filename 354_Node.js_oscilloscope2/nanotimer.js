var NanoTimer = require('nanotimer');
var mcp3208 = require('mcp-spi-adc');
var hrtime = require('process.hrtime');

var tension = mcp3208.openMcp3208(7, {speedHz: 2000000}, function (err) { if (err) throw err;});

var temps = [];
var mesure = [];

function main(){
    var timer = new NanoTimer();
 
    timer.setInterval(countDown, '', '140u');
    timer.setTimeout(liftOff, [timer], '10s');
 
 
 
}
 
function countDown(){
	tension.read(function(err, reading) {
		mesure.push(reading.value);
		temps.push(hrtime());
	});
}
 
function liftOff(timer){
    timer.clearInterval();
    console.log(mesure.length + " mesures");
    console.log(temps.length + " mesures (temps)");
	var diffInit = temps[0];
	var diff = temps[temps.length - 1];
	console.log("temps = " + ((diff[0] + diff[1] / 1e9) - (diffInit[0] + diffInit[1] / 1e9)));
	for(var compteur = 0; compteur != mesure.length; compteur++) {
		diff = temps[compteur];
		var horloge = ((diff[0] + diff[1] / 1e9) - (diffInit[0] + diffInit[1] / 1e9)) + "";
		var valeur = (mesure[compteur] * 3.3) + "";
		console.log(horloge.replace(".", ",") + ";" + valeur.replace(".",","));
	}
}
 
main();