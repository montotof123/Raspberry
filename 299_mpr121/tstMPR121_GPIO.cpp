#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

#include "GestionMPR121.h"

using namespace std;

GestionMPR121 mpr121;

int main() {
	uint16_t compteur = 0;
	cout << "Init I2C  : " << hex << mpr121.init(ADDRESS_VDD_5A) << dec << endl;
	cout << "Init      : " << mpr121.config4Electrodes8Gpio() << endl;
	delay(1000);
	
	cout << "Init GPIO : " << mpr121.setGPIOFunction(GPIOOutput, GPIOOutput, GPIOOutput, GPIOOutput, GPIOInputPullUp, GPIOInputPullUp, GPIOInputPullUp, GPIOInputPullUp) << endl;
	
	// Fait clignoter les LED D7->D4
	cout << "Clignoter" << endl << "allume LED : " << mpr121.setGPIOData(D7, D6, D5, D4) << endl;
	delay(200);
	for(int compteur = 0; compteur != 31; compteur++){
		cout << "Num: " << compteur << endl;
		cout << "bascule LED : " << mpr121.toggleGPIOData(D7, D6, D5, D4) << endl;
		delay(200);
	}
	
	// PWM des LED D7->D4
	// Attention: il faut partir d'un etat SET pour faire du PWM, le CLEAR bloque le PWM
	cout << "PWM" << endl << "allume LED : " << mpr121.setGPIOData(D7, D6, D5, D4) << endl;
	for(int boucle = 0; boucle != 6; boucle++) {
		for(int compteur = 1; compteur != 16; compteur++){
			cout << "Num: " << compteur << endl;
			cout << "PWM LED : " << mpr121.setPwm(D7, static_cast<PwmValues>(compteur)) << endl;
			cout << "PWM LED : " << mpr121.setPwm(D6, static_cast<PwmValues>(compteur)) << endl;
			cout << "PWM LED : " << mpr121.setPwm(D5, static_cast<PwmValues>(compteur)) << endl;
			cout << "PWM LED : " << mpr121.setPwm(D4, static_cast<PwmValues>(compteur)) << endl;
			delay(50);
		}
		cout << "PWM" << endl << "allume LED : " << mpr121.setGPIOData(D7, D6, D5, D4) << endl;
		delay(50);
		for(int compteur = 15; compteur != 0; compteur--){
			cout << "Num: " << compteur << endl;
			cout << "PWM LED : " << mpr121.setPwm(D7, static_cast<PwmValues>(compteur)) << endl;
			cout << "PWM LED : " << mpr121.setPwm(D6, static_cast<PwmValues>(compteur)) << endl;
			cout << "PWM LED : " << mpr121.setPwm(D5, static_cast<PwmValues>(compteur)) << endl;
			cout << "PWM LED : " << mpr121.setPwm(D4, static_cast<PwmValues>(compteur)) << endl;
			delay(50);
		}
	}
	cout << "PWM" << endl << "éteint LED : " << mpr121.clearGPIOData(D7, D6, D5, D4) << endl;
	
	// Lecture des entrées D0->D3
	while(1) {
		cout << "Lecture entrées : " << ((uint16_t)mpr121.getGPIOData() & 0x00FF) << endl;
		cout << "Lecture D0: " << mpr121.isGPIODataOn(D0) << endl;
		cout << "Lecture D1: " << mpr121.isGPIODataOn(D1) << endl;
		cout << "Lecture D2: " << mpr121.isGPIODataOn(D2) << endl;
		cout << "Lecture D3: " << mpr121.isGPIODataOn(D3) << endl;
		delay(100);
	}
}
