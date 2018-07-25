var RaspiSensors = require('raspi-sensors');

var DHT11 = new RaspiSensors.Sensor({
  type : "DHT11",
  pin  : 0
}, "DHT11"); 

DHT11.fetchInterval(function(err, data) {
    if(err) {
        console.error("An error occured!");
        console.error(err.cause);
        return;
    }
 
    // Log the values
    console.log(data);
}, 5);
