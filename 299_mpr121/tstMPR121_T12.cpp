#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

#include "GestionMPR121.h"

using namespace std;

GestionMPR121 mpr121;

int main() {
	uint16_t compteur = 0;
	cout << "Init I2C  : " << hex << mpr121.init(ADDRESS_VDD_5A) << dec << endl;
	cout << "Init      : " << mpr121.config12Electrodes() << endl;
	delay(3000);
	while(1) {
		cout << "Num: " << compteur << endl;
		mpr121.getFullData();
		for(Electrode electrode = ELE0; electrode != ELEPROX; ++electrode) {
			cout << "outOfRange" << electrode << " : " << mpr121.isOutOfRangeFromRead(electrode) << endl;
			cout << "Electrode " << electrode << " : statut: " << mpr121.getTouchStatus(electrode) << "  Valeur: " << mpr121.getElectrodeDataFromAllRead(electrode) << endl;
			cout << "BaseLine  " << electrode << " : " << "  Valeur: " << (uint16_t)(mpr121.getBaselineValueFromAllRead(electrode) & 0x00FF) << endl;
		}
		delay(100);
		compteur++;
	}
}
