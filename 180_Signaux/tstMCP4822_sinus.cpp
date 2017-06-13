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
#include <signal.h>   // signal de fin de programme
#include <math.h>     // bibliotheque mathematique
#include "GestionMCP4822.h"
#include "GestionSPI.h"

using namespace std;

// Objets utilisés
Channel channel = channel_0;
Dac dacA = A;
Dac dacB = B;
GestionMCP4822 mcp4822(channel);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	mcp4822.~GestionMCP4822();
	exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Generation d'un signal sinusoidal par la sortie A du MCP4822" << endl;
	cout << "CTRL-C pour stopper le programme" << endl;
	
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	float compteur = 0.0;
	while(true) {
		mcp4822.output(dacA, sin(compteur) * 2.0 + 2.048);
		compteur += 0.3;
	}
}
