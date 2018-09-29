//===================================
// Name        : PiFaceReadSwitch.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test du PiFace
// Date        : 29/09/2018
//===================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> 
#include <signal.h>
#include "GestionMCP23x17.h"
#include "GestionMCP23S17.h"
#include "GestionSPI.h"

using namespace std;

// Objets utilisés
Channel channel = channel_0;
GestionMCP23S17 mcp23S17(channel);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	cout << "Test du PiFace" << endl;
	// Active la gestion des adresses si plusieurs circuits branchés
	mcp23S17.writeConfiguration(mcp23S17.createConfiguration(HaEn));
	// Deja fait a l'allumage, mais on ne sais jamais ce qu'il y a eu avant...
	mcp23S17.allBitInput(PortB);
	// Control de la direction
	cout << "Direction = " << (int)mcp23S17.readDirection(PortB) << endl;
	// Activation des resistances de pullup (sinon la lecture est toujours a 0 si il n'y a pas de resistance physique)
	mcp23S17.writePullUpResistor(PortB, AllBit);
	// Lecture du port
	for(;;) {
		cout << "Valeur = " << (int)mcp23S17.readPort(PortB) << endl;
	}
}
