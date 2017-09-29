#include <iostream>

#include "GestionPCA9685.h"

using namespace std;

GestionPCA9685 pca9685(ADDR_41);

int main() {
	pca9685.setPWMFreq(50);
	pca9685.setFullOff(LED_0);	
	while(1) {
		uint16_t valeur;
		cin >> valeur;
		pca9685.setPWM(LED_0, valeur);
	}
}
