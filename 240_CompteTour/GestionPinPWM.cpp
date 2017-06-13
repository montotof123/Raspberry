/*
 * GestionPinPWM.cpp
 *
 *  Created on: 23 décembre 2016
 *      Author: totof
 */

#include <wiringPi.h>
#include "GestionPinPWM.h"

#define diviseurMax 4096
#define precisionMax 1024

// ***********************
// Constructeur
// Constructeur par defaut
// ***********************
GestionPinPWM::GestionPinPWM() {
}

// ******************************************************
// Méthode init en cas d'appel au constructeur par défaut
// Mémorise le numéro de pin utilisé
// Met la pin en PWM
// @param numéro de pin
// ******************************************************
void GestionPinPWM::init(PinPWM pPinNumber) {
	pinNumber = pPinNumber;	
	pinMode(pinNumber, PWM_OUTPUT);
}

// *********************************
// Constructeur
// Mémorise le numéro de pin utilisé
// Met la pin en PWM
// @param numéro de pin
// *********************************
GestionPinPWM::GestionPinPWM(PinPWM pPinNumber) {
	pinNumber = pPinNumber;
	pinMode(pinNumber, PWM_OUTPUT);
}

// ***************************************************
// Nombre de pas à l'état haut du PWM pour une période
// @param nombre de pas
// @return 0 si OK -1 si valeur hors possibilite
// ***************************************************
int GestionPinPWM::setValue(unsigned int pValue) {
	if(pValue < precisionMax) {
		pwmWrite(pinNumber, pValue); // Entre 0 et 1023
		pwmValue = pValue;
		return 0;
	} else {
		return -1;
	}
}

// ***************************
// Renvoie la valeur actuelle
// @return pwmValue, la valeur
// ***************************
unsigned int GestionPinPWM::getValue(void) {
	return pwmValue;
}


// ***************************************
// Applique le mode du PWM
// @param pMode le mode
// @return 0 si OK -1 si KO (mode inconnu)
// ***************************************
int GestionPinPWM::setMode(ModePWM pMode)
{
    int valRetour;
    switch(pMode)
    {
    case PwmModeBal:
    case PwmModeMs:
        pwmSetMode(pMode);
		mode = pMode;
        valRetour = 0;
        break;
    default:
        valRetour = -1;
    }
    return(valRetour);
}

// **********************
// Renvoie le mode actuel
// @return mode, le mode
// **********************
ModePWM GestionPinPWM::getMode(void) {
	return mode;
}

// ***********************************************
// Le diviseur de fréquence de l'horloge
// @param pDiviseur la valeur du diviseur
// @return 0 si OK -1 si diviseur hors possibilite
// ***********************************************
int GestionPinPWM::setDiviseur(unsigned int pDiviseur)
{
    if(pDiviseur < diviseurMax)
    {	diviseur = pDiviseur;
        pwmSetClock(pDiviseur);
        return(0);
    }
    else
    {
        return(-1);
    }
}

// *****************************
// Renvoie le diviseur actuel
// @return diviseur, le diviseur
// *****************************
unsigned int GestionPinPWM::getDiviseur(void) {
	return diviseur;
}

// **************************************************
// Précision du PWM
// @param pNbValeur le nombre de pas pour une periode
// @return 0 si OK -1 si nombre hors possibilite
// **************************************************
int GestionPinPWM::setPrecision(unsigned int pNbValeur)
{
    if(pNbValeur <= precisionMax)
    {
        precision = pNbValeur;
        pwmSetRange(pNbValeur);
        return(0);
    }
    else
    {
        return(-1);
    }
}

// *******************************
// Renvoie la précision actuelle
// @return precision, la precision
// *******************************
unsigned int GestionPinPWM::getPrecision(void) {
	return precision;
}

// ************************************************
// Renvoie la précision maximum possible
// @return precision, la precision maximum possible
// ************************************************
unsigned int GestionPinPWM::getPrecisionMax(void) {
	return precisionMax;
}

// *********************
// Destructeur
// Met la GPIO en entrée
// *********************
GestionPinPWM::~GestionPinPWM() {
	pinMode(pinNumber, INPUT);
}
