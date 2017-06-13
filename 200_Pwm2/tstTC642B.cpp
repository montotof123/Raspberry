//============================================================================
// Name        : AD5220.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test du TC642B
//============================================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include "GestionAD5220.h"

using namespace std;

// Objets utilisés
PinGPIO Clk = GPIO04;
PinGPIO Ud = GPIO17;
GestionAD5220 ad5220(Clk, Ud, 90000);

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Test du TC642B" << endl;

	delay(10000);
	cout << "0 : " << ad5220.write(ad5220.getMinValue()) << endl;
	delay(10000);
	cout << "128 : " << ad5220.write(ad5220.getMaxValue()) << endl;
	delay(10000);
	
	for(int compteur = 0; compteur != 128; compteur++) {
		cout << "Dec = " << ad5220.decrement() << endl;
		cout << "Read = " << ad5220.read() << endl;
		cout << "ReadOhm = " << ad5220.readOhm() << endl;
		delay(500);
	}
	for(int compteur = 0; compteur != 128; compteur++) {
		cout << "Inc = " << ad5220.increment() << endl;
		cout << "Read = " << ad5220.read() << endl;
		cout << "ReadOhm = " << ad5220.readOhm() << endl;
		delay(500);
	}
	
	ad5220.~GestionAD5220();

}
