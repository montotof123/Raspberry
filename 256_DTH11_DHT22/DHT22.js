var RaspiSensors = require('raspi-sensors');

var DHT22 = new RaspiSensors.Sensor({
  type : "DHT22",
  pin  : 0
}, "DHT22"); 

DHT22.fetchInterval(function(err, data) {
    if(err) {
        console.error("An error occured!");
        console.error(err.cause);
        return;
    }
 
    // Log the values
    console.log(data);
}, 2);
