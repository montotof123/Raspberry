const SerialPort = require('serialport');
var GPS = require('gps');

var gps = new GPS;
const Readline = SerialPort.parsers.Readline;
const port = new SerialPort('/dev/serial0');


gps.on('data', function (data) {
     console.log(data, gps.state);
});

port.on('data', function(data) {
  gps.updatePartial(data);
});

