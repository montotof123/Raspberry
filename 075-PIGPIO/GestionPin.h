/*
 * GestionPinGPIO.h
 *
 *     Created on: 31/05/2020
 *         Author: totof
 * version 2 pour librairie PIGPIO
 */

#ifndef GESTIONPIN_H_
#define GESTIONPIN_H_

#include <pigpio.h>

// Classe de gestion des pin
class GestionPin {
public:
	GestionPin();
	virtual ~GestionPin();

private:
	static bool setup;
	int returnInit;
};

#endif /* GESTIONPIN_H_ */
