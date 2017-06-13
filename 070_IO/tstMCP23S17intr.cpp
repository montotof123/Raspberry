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
GestionMCP23S17 mcp23S17(channel);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	mcp23S17.writeConfiguration(mcp23S17.createConfiguration(Odr));
	exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	cout << "Test du MCP23S17" << endl;
	// Active la gestion des adresses si plusieurs circuits branchés
	// Interruption active high
	mcp23S17.writeConfiguration(mcp23S17.createConfiguration(HaEn, IntPol));
	// Deja fait a l'allumage, mais on ne sais jamais ce qu'il y a eu avant...
	mcp23S17.allBitInput(PortB);
	// Control de la direction
	cout << "Direction = " << (int)mcp23S17.readDirection(PortB) << endl;
	// Activation des resistances de pullup (sinon la lecture est toujours a 0 si il n'y a pas de resistance physique)
	mcp23S17.writePullUpResistor(PortB, AllBit);
	// Lecture du port
	cout << "Pour que l'interruption fonctionne, ouvrir tous les interrupteurs (Doit donner 255 sur le portB)" << endl;
	cout << "Valeur = " << (int)mcp23S17.readPort(PortB) << endl;
	
	// Active les interruptions sur tous le port B
	mcp23S17.writeInterruptOnChange(PortB, AllBit);
	// Valeur de comparaison pour les inetrruptions
	mcp23S17.writeDefaultCompare(PortB, AllBit);
	// Les interruptions se feront en comparaison avec le registre DEFVALB
	mcp23S17.writeInterruptControl(PortB, AllBit);
	
	cout << "Tout changement dans les interrupteurs occasionnera l'allumage de la LED cablée sur INTB" << endl;
	
	for(;;) {}
	
}
