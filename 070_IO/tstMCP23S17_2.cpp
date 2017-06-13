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
GestionMCP23S17 mcp23S17(channel, Adr1);

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

	cout << "Test du MCP23S17" << endl;
	// Active la gestion des adresses si plusieurs circuits branchés
	mcp23S17.writeConfiguration(mcp23S17.createConfiguration(HaEn));
	// Deja fait a l'allumage, mais on ne sais jamais ce qu'il y a eu avant...
	mcp23S17.allBitInput(PortB);
	// Control de la direction
	cout << "Direction = " << (int)mcp23S17.readDirection(PortB) << endl;
	// Activation des resistances de pullup (sinon la lecture est toujours a 0 si il n'y a pas de resistance physique)
	mcp23S17.writePullUpResistor(PortB, AllBit);
	// Lecture du port
	cout << "Valeur = " << (int)mcp23S17.readPort(PortB) << endl;
	
	// Allumage des LED
	mcp23S17.allBitOutput(PortA);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit0));
	delay(1000);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit1));
	delay(1000);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit2));
	delay(1000);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit3));
	delay(1000);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit4));
	delay(1000);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit5));
	delay(1000);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit6));
	delay(1000);
	mcp23S17.writePort(PortA, mcp23S17.createValue(Bit7));
	delay(1000);
	
	// Affichage des valeurs Hexa
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_0());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_1());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_2());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_3());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_4());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_5());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_6());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_7());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_8());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_9());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_A());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_B());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_C());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_D());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_E());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_F());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_0_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_1_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_2_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_3_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_4_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_5_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_6_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_7_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_8_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_9_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_A_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_B_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_C_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_D_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_E_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_F_POINT());
	delay(500);	
	mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_POINT());
	delay(500);
	for(;;) {
		int valeur = (int)mcp23S17.readPort(PortB);
		int nb1 = 0;
		for(int position = 0; position != 8; position++) {
					if(((1 << position) & valeur) >> position) {
						nb1++;
					}
		}
		switch(nb1) {
			case 0: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_0()); break;
			case 1: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_1()); break;
			case 2: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_2()); break;
			case 3: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_3()); break;
			case 4: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_4()); break;
			case 5: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_5()); break;
			case 6: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_6()); break;
			case 7: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_7()); break;
			case 8: mcp23S17.writePort(PortA, mcp23S17.MAN_74A_AFF_8()); break;
		}
	}
}
