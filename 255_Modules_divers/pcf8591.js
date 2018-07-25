var i2c = require('i2c-bus'),
  i2c1 = i2c.openSync(1);
 
const PCF8591_ADDR = 0x48;
const CONV_DA = 0x40;
const ADC0 = 0x00;
const ADC1 = 0x01;
const ADC2 = 0x02;
const ADC3 = 0x03;

const BUFFER_SIZE = 2;

(function () {
	const buffer = new Buffer(BUFFER_SIZE);

  // Convertisseur DA
  i2c1.writeByteSync(PCF8591_ADDR, CONV_DA, 255);
  wait(5000);
  
  // Convertisseur AD lire le canal 0
  // Il faut le lire 2 fois car la première fois, le circuit renvoie la mesure précédente
  //    Il fait ensuite une demande de mesure et renvoie la bonne valeur au deuxième coup
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC0, BUFFER_SIZE, buffer);
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC0, BUFFER_SIZE, buffer);
  console.log("canal 0: " + buffer[1]);
  
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC1, BUFFER_SIZE, buffer);
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC1, BUFFER_SIZE, buffer);
  console.log("canal 1: " + buffer[1]);
  
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC2, BUFFER_SIZE, buffer);
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC2, BUFFER_SIZE, buffer);
  console.log("canal 2: " + buffer[1]);
  
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC3, BUFFER_SIZE, buffer);
  i2c1.readI2cBlockSync(PCF8591_ADDR, ADC3, BUFFER_SIZE, buffer);
  console.log("canal 3: " + buffer[1]);
  
  i2c1.closeSync();
}());

function wait(ms, cb) {
  var waitDateOne = new Date();
  while ((new Date()) - waitDateOne <= ms) {
    //Nothing
  }
  if (cb) {
    eval(cb);
  }
}