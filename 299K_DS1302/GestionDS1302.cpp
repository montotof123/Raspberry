/*
 * GestionDS1302.cpp
 *
 *  Created on: 08 juillet 2018
 *      Author: totof
 * Controle un circuit DS1302
 */
 
#include "GestionDS1302.h"
#include <ds1302.h>

// *****************
// Constructeur vide
// *****************
GestionDS1302::GestionDS1302() {
}

// *******************************
// Constructeur
// @Param GPIO de la broche clock
// @Param GPIO de la broche data
// @Param GPIO de la broche select
// *******************************
GestionDS1302::GestionDS1302(PinGPIO pGpioClock, PinGPIO pGpioData, PinGPIO pGpioSelect) {
	init(pGpioClock, pGpioData, pGpioSelect);
}

// *******************************
// initialisation
// @Param GPIO de la broche clock
// @Param GPIO de la broche data
// @Param GPIO de la broche select
// *******************************
void GestionDS1302::init(PinGPIO pGpioClock, PinGPIO pGpioData, PinGPIO pGpioSelect) {
	wiringPiSetupGpio() ;
	ds1302setup(pGpioClock, pGpioData, pGpioSelect);
	ds1302clockRead(initClock);
	ds1302clockRead(clock);
}

// *************************************************
// initialise l'horloge
// indispensable avant toute lecture
// a faire une seule fois pour une lecture coherente
// *************************************************
void GestionDS1302::getClock(void) {
	ds1302clockRead(clock);
}

// ******************
// Donne les secondes
// @Return second
// ******************
unsigned int GestionDS1302::getSecondes(void) {
	return bcdToD (clock[0], masks[0]);
}

// ******************
// Donne les minutes
// @Return minutes
// ******************
unsigned int GestionDS1302::getMinutes(void) {
	return bcdToD (clock[1], masks[1]);
}

// ****************
// Donne les heures
// @Return heures
// ******************
unsigned int GestionDS1302::getHeures(void) {
	return bcdToD (clock[2], masks[2]);
}

// **********************
// Donne le jours du mois
// @Return jours du mois
// **********************
unsigned int GestionDS1302::getJourMois(void) {
	return bcdToD (clock[3], masks[3]);
}

// *************
// Donne le mois
// @Return mois
// *************
unsigned int GestionDS1302::getMois(void) {
	return bcdToD (clock[4], masks[4]);
}

// ***************
// Donne l'annee
// @Return l'annee
// ***************
unsigned int GestionDS1302::getAnnee(void) {
	return bcdToD (clock[6], masks[6]) + 2000;
}

// ***************************
// Donne le jour de la semaine
// (0 pour dimanche)
// @Return jour de la semaine
// ***************************
unsigned int GestionDS1302::getJourSemaine(void) {
	return bcdToD (clock[5], masks[5]);
}

// ****************************
// Donne les secondes initiales
// @Return seconde initiales
// ****************************
unsigned int GestionDS1302::getInitSecondes(void) {
	return bcdToD (initClock[0], masks[0]);
}

// ***************************
// Donne les minutes initiales
// @Return minutes initiales
// ***************************
unsigned int GestionDS1302::getInitMinutes(void) {
	return bcdToD (initClock[1], masks[1]);
}

// **************************
// Donne les heures initiales
// @Return heures initiales
// **************************
unsigned int GestionDS1302::getInitHeures(void) {
	return bcdToD (initClock[2], masks[2]);
}

// ******************************
// Donne le jour du mois initiale
// @Return jour du mois initiale
// ******************************
unsigned int GestionDS1302::getInitJourMois(void) {
	return bcdToD (initClock[3], masks[3]);
}

// **********************
// Donne le mois initiale
// @Return mois initiale
// **********************
unsigned int GestionDS1302::getInitMois(void) {
	return bcdToD (initClock[4], masks[4]);
}

// ************************
// Donne l'annee initiale
// @Return l'annee initiale
// ************************
unsigned int GestionDS1302::getInitAnnee(void) {
	return bcdToD (initClock[6], masks[6]) + 2000;
}

// ************************************
// Donne le jour de la semaine initiale
// @Return jour de la semaine initiale
// ************************************
unsigned int GestionDS1302::getInitJourSemaine(void) {
	return bcdToD (initClock[5], masks[5]);
}

// **********************************************************************************************************
// Donne le nombre de seconde entre clockInit initialise par le constructeur et clock initialise par getClock
// @Return le nombre de secondes entre getInitClock et getClock
// **********************************************************************************************************
unsigned int GestionDS1302::getDeltaSecondes(void) {
	int nbJour = Datation (getJourMois(), getMois(), getAnnee()) - Datation (getInitJourMois(), getInitMois(), getInitAnnee()); 
	return 86400 * nbJour + getHeures() * 3600 + getMinutes() * 60 + getSecondes() - getInitHeures() * 3600 - getInitMinutes() * 60 - getInitSecondes();
}

// **********************************
// decode une valeur bcd avec un mask
// @Param la valeur
// @Param le mask
// @Return la valeur decode
// **********************************
int GestionDS1302::bcdToD (unsigned int byte, unsigned int mask) {
	byte &= mask;
	unsigned int b1 = byte & 0x0F;
	unsigned int b2 = ((byte >> 4) & 0x0F) * 10;
	return b1 + b2;
}

// **************************
// Nombre de jour d'une date
// @Param le jour
// @Param le mois
// @Param l'annee
// @return le nombre de jours
// **************************
long GestionDS1302::Datation (long j, long m, long a) {
	long n = a*365 + (m-1)*31 + j;
	if (m <= 2) {
		a--;
	}
	n = n + a/4 - a/100 + a/400;
	if (m > 2) {
		n = n - (int)((m-1)*0.4+2.7);
	}
	return n;
}