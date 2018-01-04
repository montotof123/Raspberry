#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

#include "GestionMPR121.h"

using namespace std;

GestionMPR121 mpr121;

int main() {
	uint16_t compteur = 0;
	cout << "Init I2C  : " << hex << mpr121.init(ADDRESS_VDD_5A) << dec << endl;
	cout << "Init      : " << mpr121.configAllElectrodeProximity() << endl;
	delay(3000);
	while(1) {
		cout << "Num: " << compteur << endl;
		cout << "Val: " << mpr121.getAllTouchStatus() << endl;
		cout << "Electrode " << ELEPROX << " : " << mpr121.getTouchStatus(ELEPROX) << endl;
		delay(100);
		compteur++;
	}
}
