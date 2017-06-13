/*
 * GestionMCP23017.cpp
 *
 *  Created on: 14 novembre 2016
 *      Author: totof
 * Controle un MCP23017 avec la librairie wiringPi sur Raspberry Pi
 */
 
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "GestionMCP23017.h"

namespace std {

// *******************************
// Constructeur
// @param pDevice le device
// Memorise le filehandle du setup
// le bank initial est a Bank0
// *******************************
GestionMCP23017::GestionMCP23017(int pDevice) {
	fd = wiringPiI2CSetup (pDevice);
	bank = Bank0;
}

// ****************************
// Lit la valeur d'un registre
// @param pRegistre le registre
// @return la valeur lue
// ****************************
unsigned char GestionMCP23017::read(Registre pRegistre) {
	return (char)wiringPiI2CReadReg8(fd, pRegistre);
}

// *********************************
// Ecrit une valeur dans un registre
// @param pRegistre le registre
// @param la valeur a ecrire
// *********************************
void GestionMCP23017::write(Registre pRegistre, unsigned char pValeur) {
	wiringPiI2CWriteReg8(fd, pRegistre, pValeur);
}

// ***********************************************
// Destructeur
// Met les deux ports en entree pour les securiser
// ***********************************************
GestionMCP23017::~GestionMCP23017() {
	writeDirection(PortA, 0xFF);
	writeDirection(PortB, 0xFF);
}

} /* namespace std */
