/*
 * GestionSPI16.cpp
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle du bus SPI avec mot de 16 bits
 */

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "GestionSPI16.h"

// **************************
// Constructeur vide
// **************************
GestionSPI16::GestionSPI16(void) {
}

// **************************
// Constructeur
// @Param pChannel le channel
// **************************
GestionSPI16::GestionSPI16(Channel pChannel) {
	init(pChannel, speed_33);
}

// **************************
// Constructeur
// @Param pChannel le channel
// @Param pFrequence la frequence
// **************************
GestionSPI16::GestionSPI16(Channel pChannel, Frequence pFrequence) {
	init(pChannel, pFrequence);
}

// **************************************
// Initialisation
// @Param pChannel le channel
// Mémorise le canal et initialise le SPI
// **************************************
bool GestionSPI16::init(Channel pChannel) {
	return init(pChannel, speed_33);
}

// **************************************
// Initialisation
// @Param pChannel le channel
// @Param pFrequence la frequence
// @Return true si ok, sinon false
// Mémorise le canal et initialise le SPI
// **************************************
bool GestionSPI16::init(Channel pChannel, Frequence pFrequence) {
	channel = pChannel;
	if(wiringPiSPISetupMode(channel, pFrequence, 2) >= 0) {
		return true;
	} else {
		return false;
	}
}

// *********************************************
// Ecrit une valeur de 16 bits dans le canal SPI
// @param la valeur a ecrire
// *********************************************
bool GestionSPI16::write(uint16_t pValeur) {
	spiData data;
	data.uSData = pValeur;
	swap(data);
	if(wiringPiSPIDataRW (channel, data.uCData, 2) >= 0) {
		return true;
	} else {
		return false;
	}
}

// *********************************************
// swap les deux octets d'un spiData
// @param un pointeur sur la structure à swapper
// *********************************************
void GestionSPI16::swap(spiData &data) {
	unsigned char temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}

// ***********************************************
// Destructeur
// ***********************************************
GestionSPI16::~GestionSPI16() {
}
