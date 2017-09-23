#include <wiringPi.h>

#include "GestionLedPCA9685.h"
#include "GestionLedRGBPCA9685.h"
#include "ListColorRGB.h"

using namespace std;

GestionLedRGBPCA9685 ledRGB1(LED_3, LED_2, LED_1, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB2(LED_6, LED_5, LED_4, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB3(LED_9, LED_8, LED_7, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB4(LED_12, LED_11, LED_10, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB5(LED_15, LED_14, LED_13, CommonAnode, ADDR_41);
GestionLedPCA9685 led1(LED_0, ADDR_41);

int main() {
	// Test couleurs primaires
	for(int val = 0; val != 10; val++) {
		ledRGB1.setColorRGB(0, 0, 255);
		ledRGB2.setColorRGB(0, 0, 255);
		ledRGB3.setColorRGB(0, 0, 255);
		ledRGB4.setColorRGB(0, 0, 255);
		ledRGB5.setColorRGB(0, 0, 255);
		delay(300);
		ledRGB1.setColorRGB(255, 0, 0);
		ledRGB2.setColorRGB(255, 0, 0);
		ledRGB3.setColorRGB(255, 0, 0);
		ledRGB4.setColorRGB(255, 0, 0);
		ledRGB5.setColorRGB(255, 0, 0);
		delay(300);
		ledRGB1.setColorRGB(0, 255, 0);
		ledRGB2.setColorRGB(0, 255, 0);
		ledRGB3.setColorRGB(0, 255, 0);
		ledRGB4.setColorRGB(0, 255, 0);
		ledRGB5.setColorRGB(0, 255, 0);
		delay(300);
	}
	
	// Couleurs définies
	ledRGB1.setColorRGB(Bleu_celeste);
	ledRGB2.setColorRGB(Coquille_d_oeuf);
	ledRGB3.setColorRGB(Rouge_tomette);
	ledRGB4.setColorRGB(Rose_Mountbatten);
	ledRGB5.setColorRGB(Mandarine);
	led1.setValue(128);
	delay(5000);
	
	// Allumé éteint
	for(int i = 0; i != 10; i++) {
		if( i % 2 == 0) {
			ledRGB1.setColorRGB(0, 0, 0);
			ledRGB2.setColorRGB(0, 0, 0);
			ledRGB3.setColorRGB(0, 0, 0);
			ledRGB4.setColorRGB(0, 0, 0);
			ledRGB5.setColorRGB(0, 0, 0);
			led1.setValue(255);
		} else {
			ledRGB1.setColorRGB(255, 255, 255);
			ledRGB2.setColorRGB(255, 255, 255);
			ledRGB3.setColorRGB(255, 255, 255);
			ledRGB4.setColorRGB(255, 255, 255);
			ledRGB5.setColorRGB(255, 255, 255);
			led1.setValue(0);
		}
		delay(400);
	}
	
	// Pourcentage
	float v1, v2, v3;
	v1 = 0;
	v2 = 0;
	v3 = 100;
	for(int compteur = 0; compteur != 100; compteur++) {
		ledRGB1.setPercentRGB(v1, v2, v3);
		ledRGB2.setPercentRGB(v2, v3, v1);
		ledRGB3.setPercentRGB(v3, v2, v1);
		ledRGB4.setPercentRGB(v1, v3, v2);
		ledRGB5.setPercentRGB(v2, v1, v3);
		led1.setPercent(v1);
		v1 = v1 + 1;
		v2 = v2 + 1;
		v3 = v3 - 1;
		delay(50);
	}
	
	// Valeur
	for(int compteur1 = 0; compteur1 != ledRGB1.getMaxValue(); compteur1 += 17) {
		for(int compteur2 = 0; compteur2 != ledRGB2.getMaxValue(); compteur2 += 17) {
			for(int compteur3 = 0; compteur3 != ledRGB3.getMaxValue(); compteur3 += 17) {
				ledRGB1.setColorRGB(compteur1, compteur2, compteur3);
				ledRGB2.setColorRGB(compteur2, compteur3, compteur1);
				ledRGB3.setColorRGB(compteur3, compteur2, compteur1);
				ledRGB4.setColorRGB(compteur1, compteur3, compteur2);
				ledRGB5.setColorRGB(compteur2, compteur1, compteur3);
				led1.setValue(compteur2);
				delay(1);
			}
		}
	}
}
