//============================================================================
// Name        : AD5220.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie AD5220
//============================================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <string.h>
#include "GestionPinGPIO.h"

using namespace std;

// Objets utilisés
PinGPIO Clk = GPIO04;
PinGPIO Ud = GPIO17;
GestionPinGPIO clk(Clk);
GestionPinGPIO ud(Ud);

// ******************
// Fonction pricipale
// ******************
int main() {
	string valeur;

	cout << "Test de la librairie PinGPIO" << endl;
	ud.out();
	clk.out();
	ud.on();
	for(int compteur = 0; compteur != 128; compteur++) {
		clk.on();
		clk.off();	
		delay(200);
	}
	
	clk.~GestionPinGPIO();
	ud.~GestionPinGPIO();
}
