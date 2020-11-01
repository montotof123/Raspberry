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
		returnInit = gpioInitialise();
	}
	setup = true;
}

// **********************************************************
// Destructeur
// **********************************************************
GestionPin::~GestionPin() {
}
