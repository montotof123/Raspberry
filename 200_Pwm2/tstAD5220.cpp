//============================================================================
// Name        : AD5220.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie AD5220
//============================================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include "GestionAD5220.h"

using namespace std;

// Objets utilisés
PinGPIO Clk = GPIO04;
PinGPIO Ud = GPIO17;
GestionAD5220 ad5220(Clk, Ud, 83000);

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Test du AD5220" << endl;

	ad5220.reInit();
	cout << "Read = " << (int)ad5220.read() << endl;
	cout << "min value = " << ad5220.getMinValue() << endl;
	cout << "max value = " << ad5220.getMaxValue() << endl;
	
	for(int compteur = 0; compteur != 50; compteur++) {
		cout << "Inc = " << ad5220.increment() << endl;
		cout << "Read = " << ad5220.read() << endl;
		cout << "ReadOhm = " << ad5220.readOhm() << endl;
		delay(500);
	}
	for(int compteur = 0; compteur != 50; compteur++) {
		cout << "Dec = " << ad5220.decrement() << endl;
		cout << "Read = " << ad5220.read() << endl;
		delay(500);
	}
	
	cout << "Write = " << ad5220.write(10) << endl;
	cout << "Read = " << ad5220.read() << endl;
	delay(7000);
	cout << "Write = " << ad5220.write(120) << endl;
	cout << "Read = " << ad5220.read() << endl;
	delay(7000);
	cout << "Write = " << ad5220.write(40) << endl;
	cout << "Read = " << ad5220.read() << endl;
	delay(7000);
	ad5220.reInit();
	cout << "Read = " << ad5220.read() << endl;
	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "Inc = " << ad5220.increment() << endl;
		cout << "Read = " << ad5220.read() << endl;
		delay(500);
	}
	for(int compteur = 0; compteur != 20; compteur++) {
		cout << "Dec = " << ad5220.decrement() << endl;
		cout << "Read = " << ad5220.read() << endl;
		delay(500);
	}
	cout << "Write = " << ad5220.write(1) << endl;
	cout << "Read = " << ad5220.read() << endl;
	delay(7000);
	cout << "WriteOhm = " << ad5220.writeOhm(52000) << endl;
	cout << "Read = " << ad5220.read() << endl;
	cout << "ReadOhm = " << ad5220.readOhm() << endl;
	delay(7000);
	
	ad5220.~GestionAD5220();

}
