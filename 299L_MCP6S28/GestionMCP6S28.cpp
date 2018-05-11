/*
 * GestionMCP6S28.cpp
 *
 *  Created on: 10 may 2018
 *      Author: totof
 * Controle un MCP6S28 en SPI avec la librairie wiringPi sur Raspberry Pi
 */
 
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "GestionMCP6S28.h"

namespace std {

// **************************************
// Constructeur
// @param pChannel le channel
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP6S28::GestionMCP6S28(Channel pChannel) {
	init(pChannel);
}

// **************************************
// Constructeur
// @param pChannel le channel
// @param pFrequence la frequence
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP6S28::GestionMCP6S28(Channel pChannel, Frequence pFrequence) {
	init(pChannel, pFrequence);
}

// ******************
// Paramètre l'entrée
// @Param l'entrée
// ******************
void GestionMCP6S28::setCanal(In in) {
	write(CANAL, in);
}

}
