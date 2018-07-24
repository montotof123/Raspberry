var Gpio = require('onoff').Gpio;

var inter = new Gpio(17, 'in', 'both');

inter.watch(function (err, value) {
	if(err) {
		console.log("erreur");
		return;
	}
	console.log("Interrupteur actif");
});

function unexportOnClose() {
	inter.unexport();
};

process.on('SIGINT', unexportOnClose);
