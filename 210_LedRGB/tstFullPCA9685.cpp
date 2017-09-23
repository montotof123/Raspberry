#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

#include "GestionPCA9685.h"

using namespace std;

GestionPCA9685 pca9685(ADDR_41);

int main() {
	// clignotement
	for(int compteur = 0; compteur != 10; compteur++) {
		if(compteur % 2 == 0) {
			pca9685.setFullAllOff();
		} else {
			pca9685.setFullAllOn();
		}
		delay(300);
	}
	
	// allumé vers éteint
	for(uint16_t compteur1 = 0; compteur1 < pca9685.getPWMScale(); compteur1 ++) {
		pca9685.setAllPWM (compteur1);
		delay(5);
	}
	
	// clignotement
	for(int compteur2 = 0; compteur2 != 10; compteur2++) {
		if(compteur2 % 2 == 0) {
			pca9685.setFullAllOff();
		} else {
			pca9685.setFullAllOn();
		}
		delay(300);
	}
}
