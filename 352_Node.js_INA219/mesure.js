  var ina219 = require('ina219');
 
  ina219.init(0x45);
  ina219.enableLogging(false);
  
  ina219.calibrate32V1A(function () {});
	  
  setInterval(function () {
    
    ina219.getBusVoltage_V(function (volts) {
      
      console.log("Voltage: " + volts);
      ina219.getCurrent_mA(function (current){
  			
        console.log("Current (mA): " + current );
      });	
    });
  }, 50);
  

