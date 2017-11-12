#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <wiringPi.h>

#include "GestionInsecte.h"
#include "ListColorRGB.h"

using namespace std;

GestionInsecte insecte;

pthread_t thDevicesLeft;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	pthread_cancel(thDevicesLeft);
	pthread_join(thDevicesLeft, NULL);
	cout << "Fin" << endl;
	exit(0);
}

// ****************
// Thread de mesure
// ****************
void* devicesLeft(void*) {
	float busVoltage;
	float shuntVoltage;
	float current;
	float index;
	GestionINA219 ina219 = insecte.getControlLeft();
	for(;;) {
		bool conversion = false;
		while(!conversion){
			conversion  = ina219.isConversionOk();
		}
		// Mesure
		busVoltage = ina219.getBusVoltage_V();
		current = ina219.getCurrent_mA();
		shuntVoltage = ina219.getShuntVoltage_mV();
		cout << "Bus voltage V    :" << busVoltage << endl;
		cout << "Current mA       :" << current << endl << endl;
		
		//5.4V -> index 0 -- 4.6V -> index 79
		index = -98.75 * busVoltage + 533.25;
		if(index > 79.0) {
			index = 79.0;
		}
		if(index < 0.0) {
			index = 0.0;
		}
		insecte.getTensionLeft().setColorRGB(niveau[(int)index]);
		insecte.getCurrentLeft().setColorRGB(niveau[(int)(current / 40.0)]);
		
		delay(200);
	}
}

// *****************
// Boucle principale
// *****************
int main() {
	// Ecoute du CTRL-C avec fonction de fin
	signal(SIGINT, fin);
	
	// Initialisation INA219
	insecte.getControlLeft().reset();
	insecte.getControlLeft().setCalibration_3_2A(insecte.getControlLeft()._16V, insecte.getControlLeft().B_12Bits_128S_69MS, insecte.getControlLeft().S_12Bits_128S_69MS, insecte.getControlLeft().ShuntAndBusVoltageContinuous);
	delay(200);
	
	// Creation du thread pour les appareils de droite
	pthread_create(&thDevicesLeft, NULL, &devicesLeft, NULL);
	
	// Boucle principale
	for(;;) {
		insecte.hausse(ROTULE_HAUT, 2000, insecte.getPatteFrontLeft());
		insecte.rotation(BASSIN_AVANT, 2000, insecte.getPatteFrontLeft());
		insecte.hausse(ROTULE_MILIEU, 2000, insecte.getPatteFrontLeft());
		insecte.rotation(BASSIN_ARRIERE, 2000, insecte.getPatteFrontLeft());
		//insecte.translation(GENOUX_INTERIEUR, 2000, insecte.getPatteFrontLeft());
		//insecte.translation(GENOUX_CENTRE, 2000, insecte.getPatteFrontLeft());
	}
}
