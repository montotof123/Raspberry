/*
 * GestionMCP41010.cpp
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle du MCP41010
 */

#include "GestionMCP41010.h"

#define VALUE 10000.0

// *****************
// Constructeur vide
// *****************
GestionMCP41010::GestionMCP41010(void) {
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// **************************************
GestionMCP41010::GestionMCP41010(Channel pChannel) {
	init(pChannel);
}

// **************************************
// Constructeur
// Mémorise le canal et initialise le SPI
// @Param le canal
// @Return true si init ok, sinon false
// **************************************
bool GestionMCP41010::init(Channel pChannel) {
	return GestionMCP41xxx::init(pChannel, VALUE);
}

// ***********
// Destructeur
// ***********
GestionMCP41010::~GestionMCP41010() {
}

