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
int main(int argc, char** argv) {
	char terminer[20];
	
	float value = atof(argv[1]);
	mcp4822.output(dacA, value);

	cout << "Enter pour terminer: ";
	cin.getline(terminer, 20); 

	mcp4822.~GestionMCP4822();
}
