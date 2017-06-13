/*
 * GestionMCP3208.cpp
 *
 *  Created on: 2 août 2016
 *      Author: totof
 */
 
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>
#include <linux/spi/spidev.h>

#include "GestionMCP3208.h"

namespace std {

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP3208::GestionMCP3208(int pChannel, int pSpeed) {
	channel = pChannel;
	wiringPiSPISetup (channel, pSpeed);
}

// **************************************
// Lecture d'une valeur sur un voie
// @param la voie
// @return la valeur lu (entre 0 et 4095)
// **************************************
int GestionMCP3208::readValue(uint8_t pVoie) {
	int conversion = 0, configuration = 0;
	unsigned char spiData[3] ;

	configuration = (pVoie<<6)|0x0600;			// configuration du mumero de voie & bit de start et single mode Ã  1 (voir documentation MCP3208)
	spiData[0] = configuration>>8;				// les 8 bits de msb de configuration sont ranges dans spiData[0]
	spiData[1] = configuration;				    // les 8 bits de lsb de configuration sont ranges dans spiData[1]
	spiData[2] = 0x00;					        // spiData[2] permet juste de generer la clock pour recuperer le resultat de conversion
	wiringPiSPIDataRW (channel, spiData, 3); 			    // envoi des trois octets via le spi
	conversion = (int)(((spiData[1]&0x0F)<<8)|spiData[2]);	// masquage et mise en forme du resultat de conversion (0 a FFF)
	return conversion;
}

// *******************************************
// Lit une tension
// @param la voie
// @param la tension d'alimentation analogique
// *******************************************
float GestionMCP3208::readTension(uint8_t pVoie, float pAlim) {
	return (float)readValue(pVoie) * pAlim / NOMBRE_VALEUR;
}

// ***********
// Destructeur
// ***********
GestionMCP3208::~GestionMCP3208() {
}

} /* namespace std */
