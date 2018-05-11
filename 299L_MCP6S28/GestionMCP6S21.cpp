/*
 * GestionMCP6S21.cpp
 *
 *  Created on: 10 may 2018
 *      Author: totof
 * Controle un MCP6S21 en SPI avec la librairie wiringPi sur Raspberry Pi
 */
 
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "GestionMCP6S21.h"

namespace std {

// *****************
// Constructeur vide
// *****************
GestionMCP6S21::GestionMCP6S21() {
}

// **************************************
// Constructeur
// @param pChannel le channel
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP6S21::GestionMCP6S21(Channel pChannel) {
	init(pChannel);
}

// **************************************
// Constructeur
// @param pChannel le channel
// @param pFrequence la frequence
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP6S21::GestionMCP6S21(Channel pChannel, Frequence pFrequence) {
	init(pChannel, pFrequence);
}

// **************************************
// Initialisation
// @param pChannel le channel
// Mémorise le canal et initialise le SPI
// **************************************
void GestionMCP6S21::init(Channel pChannel) {
	channel = pChannel;
	wiringPiSPISetupMode(channel, speed_50, 0);
}

// **************************************
// Initialisation
// @param pChannel le channel
// @param pFrequence la frequence
// Mémorise le canal et initialise le SPI
// **************************************
void GestionMCP6S21::init(Channel pChannel, Frequence pFrequence) {
	channel = pChannel;
	wiringPiSPISetupMode(channel, pFrequence, 0);
}

// ****************
// Arrête le module
// ****************
void GestionMCP6S21::shutdown(void) {
	unsigned char spiData[2] ;
	spiData[0] = SHUTDOWN;
	spiData[1] = 0x00;
	wiringPiSPIDataRW (channel, spiData, 2);
}

// *****************
// Paramètre le gain
// @Param le gain
// *****************
void GestionMCP6S21::setGain(Gain gain) {
	write(GAIN, gain);
}

// ******************
// Paramètre l'entrée
// @Param l'entrée
// ******************
void GestionMCP6S21::setCanal(In in) {
	write(CANAL, in);
}

// ****************************
// Ecrit 16 bits dans le module
// @Param l'action
// @Param la valeur
// ****************************
void GestionMCP6S21::write(char val0, char val1) {
	unsigned char spiData[2] ;
	spiData[0] = val0;
	spiData[1] = val1;
	wiringPiSPIDataRW (channel, spiData, 2);	
}

}

