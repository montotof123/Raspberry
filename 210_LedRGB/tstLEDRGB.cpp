//============================================================================
// Name        : tstLEDRGB.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test d'une LED RGB
//============================================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
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

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Test de la LED RGB" << endl;
	
	int vRed;
	int vGreen;
	int vBlue;

	cout << "Max rouge : " << ad5220Red.write(ad5220Red.getMaxValue()) << endl;
	cout << "Max vert : " << ad5220Green.write(ad5220Green.getMaxValue()) << endl;
	cout << "Max bleu : " << ad5220Blue.write(ad5220Blue.getMaxValue()) << endl;
	
	for(int compteur = 0; compteur != 50; compteur++) {
		cout << "Boucle n°" << compteur << endl;
		cout << "Rouge : ";
		cin >> vRed;
		cout << "Vert : ";
		cin >> vGreen;
		cout << "Bleu : ";
		cin >> vBlue;
		ad5220Red.write(vRed);
		ad5220Green.write(vGreen);
		ad5220Blue.write(vBlue);
	}
	
	ad5220Red.~GestionAD5220();
	ad5220Green.~GestionAD5220();
	ad5220Blue.~GestionAD5220();
}
