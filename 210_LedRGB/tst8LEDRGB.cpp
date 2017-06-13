//============================================================================
// Name        : tstLEDRGB.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test d'une LED RGB
//============================================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>
#include "GestionAD5220.h"

using namespace std;

// Objets utilisés
PinGPIO Clk = GPIO04;
PinGPIO Ud = GPIO17;
PinGPIO CSRed = GPIO05;
PinGPIO CSGreen = GPIO06;
PinGPIO CSBlue = GPIO13;
GestionAD5220 ad5220Red(Clk, Ud, CSRed, 90000);
GestionAD5220 ad5220Green(Clk, Ud, CSGreen, 90000);
GestionAD5220 ad5220Blue(Clk, Ud, CSBlue, 90000);
GestionPinGPIO pinA(GPIO21);
GestionPinGPIO pinB(GPIO20);
GestionPinGPIO pinC(GPIO16);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	pinA.~GestionPinGPIO();
	pinB.~GestionPinGPIO();
	pinC.~GestionPinGPIO();
	ad5220Red.write(ad5220Red.getMinValue());
	ad5220Green.write(ad5220Green.getMinValue());
	ad5220Blue.write(ad5220Blue.getMinValue());
	ad5220Red.~GestionAD5220();
	ad5220Green.~GestionAD5220();
	ad5220Blue.~GestionAD5220();
	cout << "fin" << endl;
	exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Test des 8 LED RGB" << endl;
	
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	int vRed[8];
	int vGreen[8];
	int vBlue[8];
	int cycle;
	
	pinA.out();
	pinB.out();
	pinC.out();

	ad5220Red.write(ad5220Red.getMaxValue());
	ad5220Green.write(ad5220Green.getMaxValue());
	ad5220Blue.write(ad5220Blue.getMaxValue());

	for(int compteur = 0; compteur != 100000000; compteur++) {
		if(compteur % 40000 == 0) {
			cout << "Changement: " << compteur / 40000 << endl;
			for(int cptLed = 0; cptLed != 8; cptLed++) {
				vRed[cptLed] = rand() % 128;
				vGreen[cptLed] = rand() % 128;
				vBlue[cptLed] = rand() % 128;
				// Affichage des couleurs
				cout << "Rouge: " << vRed[cptLed];
				// Alignement du vert
				if (vRed[cptLed] < 10) {
					cout << " ";
				}
				if (vRed[cptLed] < 100) {
					cout << " ";
				}
				
				cout << " Vert: " << vGreen[cptLed];
				// Alignement du bleu
				if (vGreen[cptLed] < 10) {
					cout << " ";
				}
				if (vGreen[cptLed] < 100) {
					cout << " ";
				}

				cout << " Bleu: " << vBlue[cptLed] << endl;	  		
			}
			cout << endl;
		}
		cycle = compteur % 8;
		ad5220Red.write(vRed[cycle]);
		ad5220Green.write(vGreen[cycle]);
		ad5220Blue.write(vBlue[cycle]);
		switch(cycle){
			case 0: pinA.off(); pinB.off(); pinC.off(); break;
			case 1: pinA.off(); pinB.off(); pinC.on(); break;
			case 2: pinA.off(); pinB.on(); pinC.off(); break;
			case 3: pinA.off(); pinB.on(); pinC.on(); break;
			case 4: pinA.on(); pinB.off(); pinC.off(); break;
			case 5: pinA.on(); pinB.off(); pinC.on(); break;
			case 6: pinA.on(); pinB.on(); pinC.off(); break;
			case 7: pinA.on(); pinB.on(); pinC.on(); break;
		}
	}
	
	fin(0);
}
