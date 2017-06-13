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
	cout << "Test du MCP4822" << endl;

	cout << "Max = " << mcp4822.getMaxValue() << endl;
	cout << "High impedance = " << mcp4822.getHighImpedance() << endl;
	
	for(int compteur = 0; compteur != 50; compteur++) {
		mcp4822.output(dacA, (float)compteur / 12.5);
		delay(1000);
	}

	for(int compteur = 0; compteur != 50; compteur++) {
		mcp4822.output(dacB, (float)compteur / 12.5);
		delay(1000);
	}

	cout << mcp4822.output(dacA, mcp4822.getHighImpedance());
	cout << mcp4822.output(dacB, mcp4822.getHighImpedance());

	mcp4822.~GestionMCP4822();
}
