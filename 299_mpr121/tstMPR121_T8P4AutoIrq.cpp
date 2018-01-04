#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

#include "GestionMPR121.h"

using namespace std;

GestionMPR121 mpr121;
uint16_t compteur = 0;

void gestIntr(void) {
		cout << "Num: " << compteur << endl;
		mpr121.getFullData();
		for(Electrode electrode = ELE0; electrode != ELEPROX; ++electrode) {
			cout << "outOfRange" << electrode << " : " << mpr121.isOutOfRangeFromRead(electrode) << endl;
			cout << "Electrode " << electrode << " : statut: " << mpr121.getTouchStatus(electrode) << "  Valeur: " << mpr121.getElectrodeDataFromAllRead(electrode) << endl;
			cout << "BaseLine  " << electrode << " : " << "  Valeur: " << (uint16_t)(mpr121.getBaselineValueFromAllRead(electrode) & 0x00FF) << endl;
		}
		compteur++;
	
}

int main() {
	cout << "Init I2C  : " << hex << mpr121.init(ADDRESS_VDD_5A, GPIO14) << dec << endl;
	cout << "Init      : " << mpr121.configAuto8Electrodes4prox() << endl;
	GestionPinGPIO interrupt = mpr121.getInterrupt();
	interrupt.fctInterrupt(Falling, &gestIntr);
	delay(1000);
	while(1) {
		delay(100);
	}
}
