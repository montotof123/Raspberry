const Gpio = require('pigpio').Gpio;
 
const red = new Gpio(14, {mode: Gpio.OUTPUT});
red.digitalWrite(1);
const green = new Gpio(15, {mode: Gpio.OUTPUT});
green.digitalWrite(1);
const blue = new Gpio(18, {mode: Gpio.OUTPUT});
blue.digitalWrite(1);
const sensor = new Gpio(16, {mode: Gpio.INPUT, pullUpDown: Gpio.PUD_UP, edge: Gpio.EITHER_EDGE});

let compteur = 0;

function getRandomInt(max) {
  return Math.floor(Math.random() * Math.floor(max));
}

sensor.on('interrupt', (level) => {
	console.log(compteur);
	console.log(compteur % 10);
	switch(compteur % 10) {
		case 0: 
			red.digitalWrite(0);
			green.digitalWrite(0);
			blue.digitalWrite(0);
			break;
		case 1:
			red.digitalWrite(0);
			green.digitalWrite(0);
			blue.digitalWrite(1);
			break;
		case 2:
			red.digitalWrite(0);
			green.digitalWrite(1);
			blue.digitalWrite(0);
			break;
		case 3:
			red.digitalWrite(0);
			green.digitalWrite(1);
			blue.digitalWrite(1);
			break;
		case 4:
			red.digitalWrite(1);
			green.digitalWrite(0);
			blue.digitalWrite(0);
			break;
		case 5:
			red.digitalWrite(1);
			green.digitalWrite(0);
			blue.digitalWrite(1);
			break;
		case 6:
			red.digitalWrite(1);
			green.digitalWrite(1);
			blue.digitalWrite(0);
			break;
		case 7:
			red.digitalWrite(1);
			green.digitalWrite(1);
			blue.digitalWrite(1);
			break;
		case 8:
			red.pwmRange(100);
			green.pwmRange(100);
			blue.pwmRange(100);
			red.pwmFrequency(400);
			green.pwmFrequency(400);
			blue.pwmFrequency(400);
			red.pwmWrite(getRandomInt(100));
 			green.pwmWrite(getRandomInt(100));
 			blue.pwmWrite(getRandomInt(100));
			break;
		case 9:
			break;
	}
	compteur++;
});