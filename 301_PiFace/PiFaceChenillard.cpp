//===================================
// Name        : PiFaceChenillard.cpp
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

	cout << "Chenillard sur PiFace" << endl;
	// Active la gestion des adresses si plusieurs circuits branchés
	mcp23S17.writeConfiguration(mcp23S17.createConfiguration(HaEn));
	
	// Allumage des LED
	mcp23S17.allBitOutput(PortA);
	for(;;) {
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit0));
		delay(100);
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit1));
		delay(100);
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit2));
		delay(100);
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit3));
		delay(100);
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit4));
		delay(100);
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit5));
		delay(100);
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit6));
		delay(100);
		mcp23S17.writePort(PortA, mcp23S17.createValue(Bit7));
		delay(100);
	}
}
