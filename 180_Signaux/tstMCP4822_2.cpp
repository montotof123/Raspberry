//============================================================================
// Name        : tstMCP4822.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie MCP4822
//============================================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> // La wiringPi
#include "GestionMCP4822.h"
#include "GestionSPI.h"

using namespace std;

// Objets utilisés
Channel channel = channel_0;
Dac dacA = A;
Dac dacB = B;
GestionMCP4822 mcp4822(channel);

// ******************
// Fonction pricipale
// ******************
int main() {
	float valeur;
	cout << "Test du MCP4822" << endl;
	
	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "valeur A n°" << compteur << ": ";
		cin >> valeur;
		cout << mcp4822.output(dacA, valeur) << endl;
	}

	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "valeur B n°" << compteur << ": ";
		cin >> valeur;
		cout << mcp4822.output(dacB, valeur) << endl;
	}

	mcp4822.~GestionMCP4822();
}
