/*
 * GestionMCP4251.cpp
 *
 *  Created on: 15 octobre 2016
 *      Author: totof
 * Controle un MCP4251 avec la librairie wiringPi sur Raspberry Pi
*/
 
// ****************************************************
// Attention: la commande wiringPiSPIDataRW passe les
// octets dans l'ordre 0,1,2 etc, il faut donc inverser
// les octets 0 et 1 dans toutes les commandes 16 bits
// ainsi que dans les résultats
// ****************************************************

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <linux/spi/spidev.h>

#include "GestionMCP4251.h"
#include "GestionSPI.h"

namespace std {

// **************************************
// Constructeur
// Fréquence max
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP4251::GestionMCP4251(Channel pChannel) {
	channel = pChannel;
	Frequence frequence = speed_50;
	wiringPiSPISetup (channel, frequence);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP4251::GestionMCP4251(Channel pChannel, Frequence pFrequence) {
	channel = pChannel;
	wiringPiSPISetup (channel, pFrequence);
}

// **********************************************************
// Reinitialise le composant aux valeurs de mise sous tension
// @return true si commande ok, sinon false
// **********************************************************
bool GestionMCP4251::reset() {
	Pot pot0 = pot_0;
	Pot pot1 = pot_1;
	// Connect les potentiometres
	if (!connect(pot0)) {
		return false;
	}
	if (!connect(pot1)) {
		return false;
	}
	// Deconnecte les potentiometre du shutdown
	if (!unConnectShutdown(pot0)) {
		return false;
	}
	if (!unConnectShutdown(pot1)) {
		return false;
	}
	// Initialise les potentiometre à la valeur moyenne
	if (!write(pot0, MAX_VALUE / 2)) {
		return false;
	}
	if (!write(pot1, MAX_VALUE / 2)) {
		return false;
	}
	return true;
}

// ********************************************
// Incremente la valeur d'un des potentiometres
// @param le potentiometre
// @return true si commande ok, sinon false
// ********************************************
bool GestionMCP4251::increment(Pot pot) {
	unsigned char spiDataUC[1];
	// Commande d'incrementation
	spiDataUC[0] = pot | INCREMENT;
	wiringPiSPIDataRW (channel, spiDataUC, 1);
	if (spiDataUC[0] == COMMAND_OK) {
		// Commande ok
		return true;
	}
	// commande ko
	return false;
}

// ********************************************
// Decremente la valeur d'un des potentiometres
// @param le potentiometre
// @return true si commande ok, sinon false
// ********************************************
bool GestionMCP4251::decrement(Pot pot) {
	unsigned char spiDataUC[1];
	// Commande de decrementation
	spiDataUC[0] = pot | DECREMENT;
	wiringPiSPIDataRW (channel, spiDataUC, 1);
	if (spiDataUC[0] == COMMAND_OK) {
		// Commande ok
		return true;
	}
	// commande ko
	return false;
}

// ****************************************
// Ecrit une valeur pour un potentiometre
// @param le potentiometre
// @param la valeur
// @return true si commande ok, sinon false
// ****************************************
bool GestionMCP4251::write(Pot pot, unsigned short value) {
	// Erreur valeur trop grande
	if(value > MAX_VALUE) {
		return false;
	}
	
	union spiData data;
	data.uSData = value & WRITE_MASK;
	data.uCData[1] |= pot;
	swap(data);
	wiringPiSPIDataRW (channel, data.uCData, 2);
	swap(data);
	// Bit D9 à 0, commande en erreur
	if ((data.uSData & CMDERR_MASK) != ERREUR_COMMANDE) {
		// Commande ok
		return true;
	}
	// commande ko
	return false;
}

// **********************************************
// Lit une valeur pour un potentiometre
// @param la valeur
// @return la valeur si commande ok, sinon 0xFFFF
// **********************************************
unsigned short GestionMCP4251::read(Pot pot) {
	union spiData data;
	data.uSData = READ_MASK;
	data.uCData[1] |= pot;
	swap(data);
	wiringPiSPIDataRW (channel, data.uCData, 2);
	swap(data);
	// Bit D9 à 0, commande en erreur
	if ((data.uSData & CMDERR_MASK) != ERREUR_COMMANDE) {
		// Commande ok
		return data.uSData & RESULT_MASK;
	}
	// commande ko
	return ERREUR_MESURE;
}

// ***************************************************************************************
// Lit l'état de la broche SHDN
// @return l'état du shutdown 1 = shutdown sinon 0 (l'inverse de l'état de la broche SHDN)
//          si erreur 0xFF
// ***************************************************************************************
unsigned char GestionMCP4251::isShutdown(void) {
	union spiData data;
	data.uSData = STATUS;
	swap(data);
	wiringPiSPIDataRW (channel, data.uCData, 2);
	swap(data);
	// Bit D9 à 0, commande en erreur
	if ((data.uSData & CMDERR_MASK) != ERREUR_COMMANDE) {
		// commande ok
		if((data.uSData & MASK_SHUTDOWN) == MASK_SHUTDOWN) {
			return SHUTDOWN;
		} else {
			return NO_SHUTDOWN;
		}
	}
	// Commande ko
	return ERREUR_STATUS;
}

// ************************
// Lit le registre TCON
// @return le registre TCON
// ************************
unsigned short GestionMCP4251::readTCON(void) {
	union spiData data;
	data.uSData = READ_TCON;
	swap(data);
	wiringPiSPIDataRW (channel, data.uCData, 2);
	swap(data);
	// Bit D9 à 0, commande en erreur
	if ((data.uSData & CMDERR_MASK) != ERREUR_COMMANDE) {
		// Commande ok
		return data.uSData & RESULT_MASK;
	}
	// commande ko
	return ERREUR_STATUS;
}

// ********************************************
// Indique si un potentiometre est connecte
// @return true si il est connecte, false sinon
// ********************************************
bool GestionMCP4251::isConnect(Pot pot) {
	unsigned short tCon = readTCON();
	unsigned short mask;
	switch (pot) {
		case pot_0: mask = MASK_TCON_POT_0; break;
		case pot_1: mask = MASK_TCON_POT_1; break;
	}
	if((tCon & mask) == mask) {
		return true;
	} else {
		return false;
	}
}

// **********************************************************************
// Indique si un potentiometre est connecte à la broche SHDN
// @return true si il est connecte, false sinon (inverse du bit résultat)
// **********************************************************************
bool GestionMCP4251::isConnectShutdown(Pot pot) {
	unsigned short tCon = readTCON();
	unsigned short mask;
	switch (pot) {
		case pot_0: mask = MASK_TCON_SHUTDOWN_POT_0; break;
		case pot_1: mask = MASK_TCON_SHUTDOWN_POT_1; break;
	}
	
	if((tCon & mask) == mask) {
		return false;
	} else {
		return true;
	}
}

// ******************************
// Ecrit le registre TCON
// @return true si ok sinon false
// ******************************
bool GestionMCP4251::writeTCON(unsigned short value) {
	union spiData data;
	data.uSData = WRITE_TCON | value;
	swap(data);
	wiringPiSPIDataRW (channel, data.uCData, 2);
	swap(data);
	// Bit D9 à 0, commande en erreur
	if ((data.uSData & CMDERR_MASK) != ERREUR_COMMANDE) {
		// Commande ok
		return true;
	}
	// commande ko
	return false;
}

// ********************************************************************
// Connect un potentiometre(attention: toutes les pates sont connectés)
// @return true si ok sinon false
// ********************************************************************
bool GestionMCP4251::connect(Pot pot) {
	unsigned short tCon = readTCON();
	unsigned short mask;
	switch (pot) {
		case pot_0: mask = MASK_TCON_POT_0; break;
		case pot_1: mask = MASK_TCON_POT_1; break;
	}
	return writeTCON(tCon | mask);
}

// ************************************************************************
// Deconnect un potentiometre(attention: toutes les pates sont deconnectés)
// @return true si ok sinon false
// ************************************************************************
bool GestionMCP4251::unConnect(Pot pot) {
	unsigned short tCon = readTCON();
	unsigned short mask;
	switch (pot) {
		case pot_0: mask = NOT_MASK_TCON_POT_0; break;
		case pot_1: mask = NOT_MASK_TCON_POT_1; break;
	}
	return writeTCON(tCon & mask);
}

// ********************************
// Connect un potentiometre au SHDN
// @return true si ok sinon false
// ********************************
bool GestionMCP4251::connectShutdown(Pot pot) {
	unsigned short tCon = readTCON();
	unsigned short mask;
	switch (pot) {
		case pot_0: mask = NOT_MASK_TCON_SHUTDOWN_POT_0; break;
		case pot_1: mask = NOT_MASK_TCON_SHUTDOWN_POT_1; break;
	}
	return writeTCON(tCon & mask);
}

// **********************************
// Deconnect un potentiometre du SHDN
// @return true si ok sinon false
// **********************************
bool GestionMCP4251::unConnectShutdown(Pot pot) {
	unsigned short tCon = readTCON();
	unsigned short mask;
	switch (pot) {
		case pot_0: mask = MASK_TCON_SHUTDOWN_POT_0; break;
		case pot_1: mask = MASK_TCON_SHUTDOWN_POT_1; break;
	}
	return writeTCON(tCon | mask);
}

// **************************************
// Donne la valeur max du potentiometre
// @return la valeur max du potentiometre
// **************************************
unsigned short GestionMCP4251::getMaxValue(void) {
	return MAX_VALUE;
}

// *********************************
// swap les deux octets d'un spiData
// *********************************
void GestionMCP4251::swap(spiData &data) {
	unsigned char temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}

// ***********
// Destructeur
// ***********
GestionMCP4251::~GestionMCP4251() {
}

} /* namespace std */
