//===================================================
// Name        : tstMCP23S17.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie GestionMCP23S17
//===================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> 
#include <signal.h>
#include "GestionMCP23x17.h"
#include "GestionMCP23S17.h"
#include "GestionSPI.h"
#include "GestionMAN74A.h"

using namespace std;

// Objets utilisés
Channel channel = channel_0;
GestionMCP23S17 mcp23S17_0(channel, Adr0);
GestionMCP23S17 mcp23S17_1(channel, Adr1);

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
	
	// Active la gestion des adresses
	mcp23S17_0.writeConfiguration(mcp23S17_0.createConfiguration(HaEn));
	mcp23S17_1.writeConfiguration(mcp23S17_1.createConfiguration(HaEn));

	cout << "Test du MCP23S17" << endl;
	// Deja fait a l'allumage, mais on ne sais jamais ce qu'il y a eu avant...
	mcp23S17_0.allBitInput(PortB);
	mcp23S17_1.allBitInput(PortB);
	// Control de la direction
	cout << "Direction = " << (int)mcp23S17_0.readDirection(PortB) << endl;
	cout << "Direction = " << (int)mcp23S17_1.readDirection(PortB) << endl;
	// Activation des resistances de pullup (sinon la lecture est toujours a 0 si il n'y a pas de resistance physique)
	mcp23S17_0.writePullUpResistor(PortB, AllBit);
	mcp23S17_1.writePullUpResistor(PortB, AllBit);
	// Lecture du port
	cout << "Valeur = " << (int)mcp23S17_0.readPort(PortB) << endl;
	cout << "Valeur = " << (int)mcp23S17_1.readPort(PortB) << endl;
}
