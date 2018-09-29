/*
 * GestionMCP23S17.cpp
 *
 *  Created on: 13 novembre 2016
 *      Author: totof
 * Controle un MCP23S17 avec la librairie wiringPi sur Raspberry Pi
 */
 
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <linux/spi/spidev.h>

#include "GestionMCP23S17.h"
#include "GestionSPI.h"

namespace std {

// ***********************************************
// Constructeur
// @param pChannel le channel
// Mémorise le canal et initialise le SPI
// l'adresse de base à 0 et le bank initiale Bank0
// ***********************************************
GestionMCP23S17::GestionMCP23S17(Channel pChannel) {
	channel = pChannel;
	Frequence frequence = speed_50;
	wiringPiSPISetup (channel, frequence);
	adresse = Adr0;
	bank = Bank0;
}

// ***********************************************
// Constructeur
// @param pChannel le channel
// @param pFrequence la frequence
// Mémorise le canal et initialise le SPI
// l'adresse de base à 0 et le bank initiale Bank0
// ***********************************************
GestionMCP23S17::GestionMCP23S17(Channel pChannel, Frequence pFrequence) {
	channel = pChannel;
	wiringPiSPISetup (channel, pFrequence);
	adresse = Adr0;
	bank = Bank0;
}

// *************************************************
// Constructeur
// @param pChannel le channel
// @param pAdresse l'adresse
// Mémorise le canal, l'adresse et initialise le SPI
// et le bank initiale Bank0
// *************************************************
GestionMCP23S17::GestionMCP23S17(Channel pChannel, Adresse pAdresse) {
	channel = pChannel;
	Frequence frequence = speed_50;
	wiringPiSPISetup (channel, frequence);
	adresse = pAdresse;
	bank = Bank0;
}

// *************************************************
// Constructeur
// @param pChannel le channel
// @param pFrequence la frequence
// @param pAdresse l'adresse
// Mémorise le canal, l'adresse et initialise le SPI
// et le bank initiale Bank0
// *************************************************
GestionMCP23S17::GestionMCP23S17(Channel pChannel, Frequence pFrequence, Adresse pAdresse) {
	channel = pChannel;
	wiringPiSPISetup (channel, pFrequence);
	adresse = pAdresse;
	bank = Bank0;
}

// ****************************
// Lit la valeur d'un registre
// @param pRegistre le registre
// @return la valeur lue
// ****************************
unsigned char GestionMCP23S17::read(Registre pRegistre) {
	unsigned char spiData[3] ;
	spiData[0] = 0x40 | (adresse << 1) | 0x01;
	spiData[1] = pRegistre;
	spiData[2] = 0x00;
	wiringPiSPIDataRW (channel, spiData, 3);
	return spiData[2];
}

// *********************************
// Ecrit une valeur dans un registre
// @param pRegistre le registre
// @param la valeur a ecrire
// *********************************
void GestionMCP23S17::write(Registre pRegistre, unsigned char pValeur) {
	unsigned char spiData[3] ;
	spiData[0] = 0x40 | (adresse << 1) | 0x00;
	spiData[1] = pRegistre;
	spiData[2] = pValeur;
	wiringPiSPIDataRW (channel, spiData, 3);
}

// ***********************************************
// Destructeur
// Met les deux ports en entree pour les securiser
// ***********************************************
GestionMCP23S17::~GestionMCP23S17() {
	writeDirection(PortA, 0xFF);
	writeDirection(PortB, 0xFF);
}

} /* namespace std */
