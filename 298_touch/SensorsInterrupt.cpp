#include <iostream>
#include <wiringPi.h>

#include "GestionPinGPIO.h"
#include <signal.h>

using namespace std;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	cout << "Fin" << endl;
	exit(0);
}

void touchOn(void) {
	cout << "Touch Sensor ON  " << endl;	
}

void touchOff(void) {
	cout << "Touch Sensor OFF  " << endl;	
}

void switchOn(void) {
	cout << "Touch Switch ON  " << endl;	
}

void switchOff(void) {
	cout << "Touch Switch OFF  " << endl;	
}

int main() {
	GestionPinGPIO touchSensorOn(GPIO21);
	GestionPinGPIO touchSensorOff(GPIO20);
	GestionPinGPIO touchSwitchOn(GPIO05);
	GestionPinGPIO touchSwitchOff(GPIO06);
	touchSensorOn.in();
	touchSensorOff.in();
	touchSwitchOn.in();
	touchSwitchOff.in();
	touchSensorOn.fctInterrupt(Rising, &touchOn);
	touchSensorOff.fctInterrupt(Falling, &touchOff);
	touchSwitchOn.fctInterrupt(Rising, &switchOn);
	touchSwitchOff.fctInterrupt(Falling, &switchOff);
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);
	while(1) {
	}
}
