/*
 * GestionBME280Spi.cpp
 *
 *  Created on: 27 may 2017
 *      Author: totof
 * Controle un BME280 en SPI avec la librairie wiringPi sur Raspberry Pi
 */
 
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "GestionBME280Spi.h"
#include "GestionSPI.h"


namespace std {

// **************************************
// Constructeur
// @param pChannel le channel
// Mémorise le canal et initialise le SPI
// **************************************
GestionBME280Spi::GestionBME280Spi(Channel pChannel) {
	channel = pChannel;
	Frequence frequence = speed_50;
	wiringPiSPISetupMode(channel, frequence, 0);
	init();
}

// **************************************
// Constructeur
// @param pChannel le channel
// @param pFrequence la frequence
// Mémorise le canal et initialise le SPI
// **************************************
GestionBME280Spi::GestionBME280Spi(Channel pChannel, Frequence pFrequence) {
	channel = pChannel;
	wiringPiSPISetupMode(channel, pFrequence, 0);
	init();
}

// ****************************
// Lit la valeur d'un registre
// @param pRegistre le registre
// @return la valeur lue
// ****************************
uint8_t GestionBME280Spi::read(Register pRegistre) {
	unsigned char spiData[2] ;
	spiData[0] = (pRegistre & 0x7F) | 0x80;
	spiData[1] = 0x00;
	wiringPiSPIDataRW (channel, spiData, 2);
	return (uint8_t)spiData[1];
}

// *********************************
// Ecrit une valeur dans un registre
// @param pRegistre le registre
// @param la valeur a ecrire
// *********************************
void GestionBME280Spi::write(Register pRegistre, uint8_t pValeur) {
	unsigned char spiData[2] ;
	spiData[0] = pRegistre & 0x7F;
	spiData[1] = (unsigned char)pValeur;
	wiringPiSPIDataRW (channel, spiData, 2);
}

// ***********************************************
// Destructeur
// Met les deux ports en entree pour les securiser
// ***********************************************
GestionBME280Spi::~GestionBME280Spi() {
}

} /* namespace std */
