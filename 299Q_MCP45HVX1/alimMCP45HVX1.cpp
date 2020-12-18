#include <iostream>
#include <stdlib.h>
#include <string>

#include "GestionMCP45HVX1.h"
#include "GestionINA219.h"

#include <pigpio.h>

using namespace std;

GestionMCP45HVX1 mcp45hv51;
GestionINA219 ina219;

int main(void) {
	string enter;
	
	if(!mcp45hv51.InitMCP45HVX1(mcp45hv51.ADRESSE_0x3C, mcp45hv51.R5K)) {
		exit(0);
	}
	
	double tension;
	
	cout << "donnez la tension voulue: ";
	cin >> tension;
	
	mcp45hv51.connect();
	
	mcp45hv51.setValue((int)((tension - 2.1) * 284.855769));
	
	cout << "Valeur potentiomètre = " <<  dec << mcp45hv51.getValue() << endl;
	ina219.init(ADDR_40);
	ina219.reset();
	ina219.setCalibration_0_4A(_16V, B_12Bits_128S_69MS, S_12Bits_128S_69MS, ShuntAndBusVoltageContinuous);
	bool conversion = false;
	while(!conversion){
		conversion  = ina219.isConversionOk();
	}
	cout <<  "Tension bus   = " << ina219.getBusVoltage_V()  << endl;
	cout <<  "Tension shunt = " << ina219.getShuntVoltage_mV() << endl;

	// getline (cin, enter);
	cin >> enter;
}
