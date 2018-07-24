var RaspiSensors = require('raspi-sensors');

var BMP180 = new RaspiSensors.Sensor({
    type    : "BMP180",
    address : 0X77
}, "barometer");

BMP180.fetch(function(err, data) {
    if(err) {
        console.error("An error occured!");
        console.error(err.cause);
        return;
    }
 
    // Log the values
    console.log(data);
});
