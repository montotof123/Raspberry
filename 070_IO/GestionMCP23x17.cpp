/*
 * GestionMCP23x17.cpp
 *
 *  Created on: 13 novembre 2016
 *      Author: totof
 * Controle un MCP23017 ou un MCP23S17 avec la librairie wiringPi sur Raspberry Pi
 * Cette classe n'est pas instanciable, elle doit être associée à la classe GestionMCP23017 ou GestionMCP23S17 pour fonctionner
*/
 
#include "GestionMCP23x17.h"

namespace std {

// ***********************
// Constructeur par defaut
// ***********************
GestionMCP23x17::GestionMCP23x17() {
}

// ********************************
// Lecture du registre de direction
// @param pPort, le port
// @return la direction du port
// ********************************
unsigned char GestionMCP23x17::readDirection(Port pPort) {
	return read(getRegistre(IODIR, pPort));
}

// **********************************
// Ecriture du registre de direction
// @param pPort, le port
// @param pValeur, la valeur à écrire
// **********************************
void GestionMCP23x17::writeDirection(Port pPort, unsigned char pValeur) {
	return write(getRegistre(IODIR, pPort), pValeur);
}

// ****************************
// Met un port entier en entree
// @param pPort, le port
// ****************************
void GestionMCP23x17::allBitInput(Port pPort) {
	writeDirection(pPort, AllBit);
}

// ****************************
// Met un port entier en sortie
// @param pPort, le port
// ****************************
void GestionMCP23x17::allBitOutput(Port pPort){
	writeDirection(pPort, NoBit);
}

	// *******************************
// Lecture du registre de polarité
// @param pPort, le port
// @return la direction du port
// *******************************
unsigned char GestionMCP23x17::readPolarity(Port pPort) {
	return read(getRegistre(IPOL, pPort));
}

// **********************************
// Ecriture du registre de polarité
// @param pPort, le port
// @param pValeur, la valeur à écrire
// **********************************
void GestionMCP23x17::writePolarity(Port pPort, unsigned char pValeur) {
	return write(getRegistre(IPOL, pPort), pValeur);
}

// **************************************
// Lecture du registre Interrup on change
// @param pPort, le port
// @return la direction du port
// **************************************
unsigned char GestionMCP23x17::readInterruptOnChange(Port pPort) {
	return read(getRegistre(GPINTEN, pPort));
}

// ******************************************
// Ecriture du registre de Interrup on change
// @param pPort, le port
// @param pValeur, la valeur à écrire
// ******************************************
void GestionMCP23x17::writeInterruptOnChange(Port pPort, unsigned char pValeur) {
	return write(getRegistre(GPINTEN, pPort), pValeur);
}

// *******************************************************
// Lecture du registre de valeur de comparaison par defaut
// @param pPort, le port
// @return la direction du port
// *******************************************************
unsigned char GestionMCP23x17::readDefaultCompare(Port pPort) {
	return read(getRegistre(DEFVAL, pPort));
}

// ********************************************************
// Ecriture du registre de valeur de comparaison par defaut
// @param pPort, le port
// @param pValeur, la valeur à écrire
// ********************************************************
void GestionMCP23x17::writeDefaultCompare(Port pPort, unsigned char pValeur) {
	return write(getRegistre(DEFVAL, pPort), pValeur);
}

// *********************************************
// Lecture du registre de control d'interruption
// @param pPort, le port
// @return la direction du port
// *********************************************
unsigned char GestionMCP23x17::readInterruptControl(Port pPort) {
	return read(getRegistre(INTCON, pPort));
}

// **********************************************
// Ecriture du registre de control d'interruption
// @param pPort, le port
// @param pValeur, la valeur à écrire
// **********************************************
void GestionMCP23x17::writeInterruptControl(Port pPort, unsigned char pValeur) {
	return write(getRegistre(INTCON, pPort), pValeur);
}

// ************************************
// Lecture du registre de configuration
// @param pPort, le port
// @return la direction du port
// ************************************
unsigned char GestionMCP23x17::readConfiguration() {
	return read(getRegistre(IOCON, PortA));
}

// *************************************
// Ecriture du registre de configuration
// @param pPort, le port
// @param pValeur, la valeur à écrire
// *************************************
void GestionMCP23x17::writeConfiguration(unsigned char pValeur) {
	return write(getRegistre(IOCON, PortA), pValeur);
}

// **************************************************************
// Lecture du registre de configuration des resistance de pull-up
// @param pPort, le port
// @return la direction du port
// **************************************************************
unsigned char GestionMCP23x17::readPullUpResistor(Port pPort) {
	return read(getRegistre(GPPU, pPort));
}

// ***************************************************************
// Ecriture du registre de configuration des resistance de pull-up
// @param pPort, le port
// @param pValeur, la valeur à écrire
// ***************************************************************
void GestionMCP23x17::writePullUpResistor(Port pPort, unsigned char pValeur) {
	return write(getRegistre(GPPU, pPort), pValeur);
}

// ********************************************
// Lecture du registre des flags d'interruption
// @param pPort, le port
// @return la direction du port
// ********************************************
unsigned char GestionMCP23x17::readInterruptFlag(Port pPort) {
	return read(getRegistre(INTF, pPort));
}

// ********************************************************
// Lecture du registre de capture des vaeurs d'interruption
// @param pPort, le port
// @return la direction du port
// ********************************************************
unsigned char GestionMCP23x17::readInterrupCapture(Port pPort) {
	return read(getRegistre(INTCAP, pPort));
}

// *************************************
// Lecture du registre de valeur du port
// @param pPort, le port
// @return la direction du port
// *************************************
unsigned char GestionMCP23x17::readPort(Port pPort) {
	return read(getRegistre(GPIO, pPort));
}

// **************************************
// Ecriture du registre de valeur du port
// @param pPort, le port
// @param pValeur, la valeur à écrire
// **************************************
void GestionMCP23x17::writePort(Port pPort, unsigned char pValeur) {
	return write(getRegistre(GPIO, pPort), pValeur);
}

// **********************************************************
// Lecture du registre des bascules de memorisation de sortie
// @param pPort, le port
// @return la direction du port
// **********************************************************
unsigned char GestionMCP23x17::readOutputLatch(Port pPort) {
	return read(getRegistre(OLAT, pPort));
}

// ***********************************************************
// Ecriture du registre des bascules de memorisation de sortie
// @param pPort, le port
// @param pValeur, la valeur à écrire
// ***********************************************************
void GestionMCP23x17::writeOutputLatch(Port pPort, unsigned char pValeur) {
	return write(getRegistre(OLAT, pPort), pValeur);
}

// *******************************************************
// Fait l'aguillage pour connaitre l'adresse d'un registre
// en fonction de son type, du port et du bank sélectionné
// @param pTypeRegistre le type de registre
// @param pPort le port
// @return le registre sélectionné
// *******************************************************
Registre GestionMCP23x17::getRegistre(TypeRegistre pTypeRegistre, Port pPort) {
	Registre registre;

	switch(bank) {
		case Bank0:
		switch(pTypeRegistre) {
			case IODIR:
			switch(pPort) {
				case PortA: registre = IODIRA0; break;
				case PortB: registre = IODIRB0; break;
			}
			break;
			case IPOL:
			switch(pPort) {
				case PortA: registre = IPOLA0; break;
				case PortB: registre = IPOLB0; break;
			}
			break;
			case GPINTEN:
			switch(pPort) {
				case PortA: registre = GPINTENA0; break;
				case PortB: registre = GPINTENB0; break;
			}
			break;
			case DEFVAL:
			switch(pPort) {
				case PortA: registre = DEFVALA0; break;
				case PortB: registre = DEFVALB0; break;
			}
			break;
			case INTCON:
			switch(pPort) {
				case PortA: registre = INTCONA0; break;
				case PortB: registre = INTCONB0; break;
			}
			break;
			case IOCON:
			switch(pPort) {
				case PortA: registre = IOCON0; break;
				case PortB: registre = IOCON0; break;
			}
			break;
			case GPPU:
			switch(pPort) {
				case PortA: registre = GPPUA0; break;
				case PortB: registre = GPPUB0; break;
			}
			break;
			case INTF:
			switch(pPort) {
				case PortA: registre = INTFA0; break;
				case PortB: registre = INTFB0; break;
			}
			break;
			case INTCAP:
			switch(pPort) {
				case PortA: registre = INTCAPA0; break;
				case PortB: registre = INTCAPB0; break;
			}
			break;
			case GPIO:
			switch(pPort) {
				case PortA: registre = GPIOA0; break;
				case PortB: registre = GPIOB0; break;
			}
			break;
			case OLAT:
			switch(pPort) {
				case PortA: registre = OLATA0; break;
				case PortB: registre = OLATB0; break;
			}
			break;
		}
		break;
		case Bank1:
		switch(pTypeRegistre) {
			case IODIR:
			switch(pPort) {
				case PortA: registre = IODIRA1; break;
				case PortB: registre = IODIRB1; break;
			}
			break;
			case IPOL:
			switch(pPort) {
				case PortA: registre = IPOLA1; break;
				case PortB: registre = IPOLB1; break;
			}
			break;
			case GPINTEN:
			switch(pPort) {
				case PortA: registre = GPINTENA1; break;
				case PortB: registre = GPINTENB1; break;
			}
			break;
			case DEFVAL:
			switch(pPort) {
				case PortA: registre = DEFVALA1; break;
				case PortB: registre = DEFVALB1; break;
			}
			break;
			case INTCON:
			switch(pPort) {
				case PortA: registre = INTCONA1; break;
				case PortB: registre = INTCONB1; break;
			}
			break;
			case IOCON:
			switch(pPort) {
				case PortA: registre = IOCON1; break;
				case PortB: registre = IOCON1; break;
			}
			break;
			case GPPU:
			switch(pPort) {
				case PortA: registre = GPPUA1; break;
				case PortB: registre = GPPUB1; break;
			}
			break;
			case INTF:
			switch(pPort) {
				case PortA: registre = INTFA1; break;
				case PortB: registre = INTFB1; break;
			}
			break;
			case INTCAP:
			switch(pPort) {
				case PortA: registre = INTCAPA1; break;
				case PortB: registre = INTCAPB1; break;
			}
			break;
			case GPIO:
			switch(pPort) {
				case PortA: registre = GPIOA1; break;
				case PortB: registre = GPIOB1; break;
			}
			break;
			case OLAT:
			switch(pPort) {
				case PortA: registre = OLATA1; break;
				case PortB: registre = OLATB1; break;
			}
			break;
		}
		break;
	}
	return registre;
}

// *******************************************************
// Creation d'une valeur de configuration
// @param pBitA l'un des bits de configuration
// @param pBitB l'un des bits de configuration (optionnel)
// @param pBitC l'un des bits de configuration (optionnel)
// @param pBitD l'un des bits de configuration (optionnel)
// @param pBitE l'un des bits de configuration (optionnel)
// @param pBitF l'un des bits de configuration (optionnel)
// @param pBitG l'un des bits de configuration (optionnel)
// @return la valeur de la configuration
// *******************************************************
unsigned char GestionMCP23x17::createConfiguration(BitIOCON pBitA, BitIOCON pBitB, BitIOCON pBitC, BitIOCON pBitD, BitIOCON pBitE, BitIOCON pBitF, BitIOCON pBitG) {
	return pBitA | pBitB | pBitC | pBitD | pBitE | pBitF | pBitG;
}

// **************************************
// Creation d'une valeur
// @param pBitA l'un des bits
// @param pBitB l'un des bits (optionnel)
// @param pBitC l'un des bits (optionnel)
// @param pBitD l'un des bits (optionnel)
// @param pBitE l'un des bits (optionnel)
// @param pBitF l'un des bits (optionnel)
// @param pBitG l'un des bits (optionnel)
// @param pBitH l'un des bits (optionnel)
// @return la valeur
// *************************************
unsigned char GestionMCP23x17::createValue(Bit pBitA, Bit pBitB, Bit pBitC, Bit pBitD, Bit pBitE, Bit pBitF, Bit pBitG, Bit pBitH) {
	return pBitA | pBitB | pBitC | pBitD | pBitE | pBitF | pBitG | pBitH;	
}

// ***********
// Destructeur
// ***********
GestionMCP23x17::~GestionMCP23x17() {
}

} /* namespace std */
