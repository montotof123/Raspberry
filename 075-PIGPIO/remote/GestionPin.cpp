/*
 * GestionPin.cpp
 *
 *     Created on: 31/05/2020
 *         Author: totof
 * version 2 pour librairie PIGPIO
 */

#include "GestionPin.h"

bool GestionPin::setup = false;

// ****************************************
// Constructeur
// Permet d'appeler une seule fois le setup
// ****************************************
GestionPin::GestionPin() {
	if(!setup) {
		returnInit = pigpio_start("192.168.1.28", "8888");
	}
	setup = true;
}

// ***************************************
// Retourne le pointeur pour les commandes
// @return le pointeur d'initialisation
// ***************************************
int GestionPin::getReturnInit(void) {
	return returnInit;
}

// **********************************************************
// Destructeur
// **********************************************************
GestionPin::~GestionPin() {
}
