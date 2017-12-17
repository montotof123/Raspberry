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

int main() {
	GestionPinGPIO touchSensor(GPIO21);
	GestionPinGPIO touchSwitch(GPIO05);
	touchSensor.in();
	touchSwitch.in();
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);
	while(1) {
		if(touchSensor.isOn()) {
			cout << "Touch Sensor ON  ";
		} else {
			cout << "Touch Sensor OFF ";
		}
		if(touchSwitch.isOn()) {
			cout << "Touch Switch ON  " << endl;
		} else {
			cout << "Touch Switch OFF " << endl;
		}
	}
}
