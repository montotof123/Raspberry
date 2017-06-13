//===================================================
// Name        : tstmcp23017.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie Gestionmcp23017
//===================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> 
#include <signal.h>
#include "GestionMCP23x17.h"
#include "GestionMCP23017.h"
#include "GestionMAN74A.h"

using namespace std;

// Objets utilisés
GestionMCP23017 mcp23017(0x20);

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

	cout << "Test du MCP23017" << endl;
	// Deja fait a l'allumage, mais on ne sais jamais ce qu'il y a eu avant...
	mcp23017.allBitInput(PortB);
	// Control de la direction
	cout << "Direction = " << (int)mcp23017.readDirection(PortB) << endl;
	// Activation des resistances de pullup (sinon la lecture est toujours a 0 si il n'y a pas de resistance physique)
	mcp23017.writePullUpResistor(PortB, AllBit);
	// Lecture du port
	cout << "Valeur = " << (int)mcp23017.readPort(PortB) << endl;
	
		// Allumage des LED
	mcp23017.allBitOutput(PortA);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit0));
	delay(1000);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit1));
	delay(1000);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit2));
	delay(1000);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit3));
	delay(1000);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit4));
	delay(1000);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit5));
	delay(1000);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit6));
	delay(1000);
	mcp23017.writePort(PortA, mcp23017.createValue(Bit7));
	delay(1000);
	
	// Affichage des valeurs Hexa
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_0());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_1());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_2());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_3());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_4());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_5());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_6());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_7());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_8());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_9());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_A());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_B());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_C());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_D());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_E());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_F());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_0_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_1_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_2_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_3_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_4_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_5_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_6_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_7_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_8_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_9_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_A_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_B_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_C_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_D_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_E_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_F_POINT());
	delay(500);	
	mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_POINT());
	delay(500);
	for(;;) {
		int valeur = (int)mcp23017.readPort(PortB);
		int nb1 = 0;
		for(int position = 0; position != 8; position++) {
					if(((1 << position) & valeur) >> position) {
						nb1++;
					}
		}
		switch(nb1) {
			case 0: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_0()); break;
			case 1: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_1()); break;
			case 2: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_2()); break;
			case 3: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_3()); break;
			case 4: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_4()); break;
			case 5: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_5()); break;
			case 6: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_6()); break;
			case 7: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_7()); break;
			case 8: mcp23017.writePort(PortA, mcp23017.MAN_74A_AFF_8()); break;
		}
	}

}
