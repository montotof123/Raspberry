/*
 * GestionMCP41100.cpp
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle du MCP41100
 */

#include "GestionMCP41100.h"

#define VALUE 100000.0

// *****************
// Constructeur vide
// *****************
GestionMCP41100::GestionMCP41100(void) {
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// **************************************
GestionMCP41100::GestionMCP41100(Channel pChannel) {
	init(pChannel);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @Return true si init ok, sinon false
// **************************************
bool GestionMCP41100::init(Channel pChannel) {
	return GestionMCP41xxx::init(pChannel, VALUE);
}

// ***********
// Destructeur
// ***********
GestionMCP41100::~GestionMCP41100() {
}

