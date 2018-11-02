/*
 * GestionMCP41050.cpp
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle du MCP41050
 */

#include "GestionMCP41050.h"

#define VALUE 50000.0

// *****************
// Constructeur vide
// *****************
GestionMCP41050::GestionMCP41050(void) {
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// **************************************
GestionMCP41050::GestionMCP41050(Channel pChannel) {
	init(pChannel);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @Return true si init ok, sinon false
// **************************************
bool GestionMCP41050::init(Channel pChannel) {
	return GestionMCP41xxx::init(pChannel, VALUE);
}

// ***********
// Destructeur
// ***********
GestionMCP41050::~GestionMCP41050() {
}

