#include <iostream>
#include <pigpio.h>
#include <signal.h>

#include "GestionADXL362.h"
#include "GestionSPI.h"
#include "GestionPinGPIO.h"

using namespace std;

GestionPinGPIO int1(GPIO26);
GestionPinGPIO int2(GPIO21);

GestionADXL362 adxl362(GestionSpi::channel_0);

void intInt1(int gpio, int level, uint32_t tick) {
	adxl362.getStatus();
	cout << "Int1: " << level << endl;
}

void intInt2(int gpio, int level, uint32_t tick) {
	adxl362.getStatus();
	cout << "Int2: " << level << endl;
}

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
	cout << "Fin" << endl;
	exit(0);
}

int main(void) {
	// Ecoute du CTRL-C avec fonction à lancer
	// Indispensable car sinon un CTRL-C bloque le bus spi obligeant à un reboot du Rpi
	signal(SIGINT, fin);

	// Interruption a chaque appui sur le bouton
	int1.in();
	int1.pullUp();
	int1.fctInterrupt(intInt1);

	int2.in();
	int2.pullUp();
	int2.fctInterrupt(intInt2);

	adxl362.softReset();
	cout << "Device ID = " << hex << (int)adxl362.getDevId() << endl;
	cout << "MEMS      = " << hex << (int)adxl362.getMicroElectroMechanicalSystemId() << endl;
	cout << "Part Id   = " << dec << (int)adxl362.getPartId() << endl;
	cout << "Rev Id    = " << hex << (int)adxl362.getRevId() << endl;
	cout << "ADXL362   = " << dec << adxl362.isADXL362Device() << endl << endl;
	
	adxl362.sampleInit2();
	
	for(int compteur = 0; compteur != 1800; compteur++) { // 3 mn
		//cout << "X axis = " << dec << adxl362.getXAxisG() << endl;
		//cout << "Y axis = " << dec << adxl362.getYAxisG() << endl;
		//cout << "Z axis = " << dec << adxl362.getZAxisG() << endl;
		//cout << "Temperature = " << dec << adxl362.getTemperatureCelcius() << endl << endl;
		gpioDelay(100000); // 100ms
	}
}