#include <wiringPi.h>

#include "GestionLedPCA9685.h"

using namespace std;

GestionLedPCA9685 led1(LED_0, ADDR_41);

int main() {
	// Valeur définie
	led1.setValue(30);
	delay(1000);
	led1.setValue(128);
	delay(1000);
	led1.setValue(230);
	delay(1000);
	led1.setValue(83);
	delay(1000);
	
	// Allumé éteint
	for(int i = 0; i != 14; i++) {
		if( i % 2 == 0) {
			led1.setValue(255);
		} else {
			led1.setValue(0);
		}
		delay(600);
	}
	
	// Pourcentage
	float v1;
	v1 = 0;
	for(int compteur = 0; compteur != 100; compteur++) {
		led1.setPercent(v1);
		v1 = v1 + 1;
		delay(20);
	}
	
	// Valeur
	for(int compteur1 = 0; compteur1 != led1.getMaxValue(); compteur1 += 5) {
		for(int compteur2 = 0; compteur2 != led1.getMaxValue(); compteur2 += 5) {
			led1.setValue(compteur2);
			delay(7);
		}
	}
}
