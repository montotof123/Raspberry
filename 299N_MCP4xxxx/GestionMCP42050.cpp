/*
 * GestionMCP42050.cpp
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle du MCP42050
 */

#include "GestionMCP42050.h"

#define VALUE 50000.0

// **************************************
// Constructeur vide
// **************************************
GestionMCP42050::GestionMCP42050(void) {
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// **************************************
GestionMCP42050::GestionMCP42050(Channel pChannel) {
	init(pChannel);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @param la broche reset
// **************************************
GestionMCP42050::GestionMCP42050(Channel pChannel, PinGPIO pReset) {
	init(pChannel, pReset);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @param la broche reset
// @param la broche shutdown
// **************************************
GestionMCP42050::GestionMCP42050(Channel pChannel, PinGPIO pReset, PinGPIO pShutdown) {
	init(pChannel, pReset, pShutdown);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @Return true si init ok, sinon false
// **************************************
bool GestionMCP42050::init(Channel pChannel) {
	return GestionMCP42xxx::init(pChannel, VALUE);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @param la broche reset
// @Return true si init ok, sinon false
// **************************************
bool GestionMCP42050::init(Channel pChannel, PinGPIO pReset) {
	return GestionMCP42xxx::init(pChannel, VALUE, pReset);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @param la broche reset
// @param la broche shutdown
// @Return true si init ok, sinon false
// **************************************
bool GestionMCP42050::init(Channel pChannel, PinGPIO pReset, PinGPIO pShutdown) {
	return GestionMCP42xxx::init(pChannel, VALUE, pReset, pShutdown);
}

// ***********
// Destructeur
// ***********
GestionMCP42050::~GestionMCP42050() {
}

