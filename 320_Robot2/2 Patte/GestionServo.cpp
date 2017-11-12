/*
 * GestionServo.cpp
 *
 *  Created on: 1 août 2016
 *  Modified on: 20 septembre 2017
 *      Author: totof
 */

#include "GestionServo.h"

// *****************
// Constructeur vide
// *****************
GestionServo::GestionServo() {
}
// ************************************************
// Constructeur
// Initialise les valeurs min et max du servo
// Positionne le debattement a la valeur par defaut
// @param pCycleMin le cycle Min
// @param pCycleMax le cycle Max
// ************************************************
GestionServo::GestionServo(uint16_t pCycleMin, uint16_t pCycleMax) {
    init(pCycleMin, pCycleMax, DEBATTEMENT_DEFAUT);
}

// ******************************************************************
// Constructeur
// Initialise les valeurs min, max du servo et l'angle de debattement
// @param pCycleMin le cycle Min
// @param pCycleMax le cycle Max
// @param pAngleDebattement l'angle de debattement
// ******************************************************************
GestionServo::GestionServo(uint16_t pCycleMin, uint16_t pCycleMax, float pAngleDebattement) {
    init(pCycleMin, pCycleMax, pAngleDebattement);
}

// ******************************************************************
// Constructeur
// Initialise les valeurs min, max du servo et l'angle de debattement
// @Param Servo
// ******************************************************************
GestionServo::GestionServo(Servo servo) {
    init(servo);
}

// **************************************************************
// Initialisation des cycles min et max et l'angle de debattement
// @Param Servo
// **************************************************************
void GestionServo::init(Servo servo) {
	init(servo.cycleMin, servo.cycleMax, servo.angleDebattement);
}

// ***********************************************
// Initialisation des cycles min et max
// @param pCycleMin le cycle Min
// @param pCycleMax le cycle Max
// @Param pAngleDebattement l'angle de debattement
// ***********************************************
void GestionServo::init(uint16_t pCycleMin, uint16_t pCycleMax, float pAngleDebattement) {
    cycleMin = pCycleMin;
    cycleMax = pCycleMax;
	setAngleDebattement(pAngleDebattement);
}

// ********************
// Getter du cycle min
// @return le cycle min
// ********************
uint16_t GestionServo::getCycleMin(void) {
    return(cycleMin);
}

// ********************
// Getter du cycle max
// @return le cycle max
// ********************
uint16_t GestionServo::getCycleMax(void) {
    return(cycleMax);
}

// ********************************
// Getter de l'angle de debattement
// @return l'angle de debattement
// ********************************
float GestionServo::getAngleDebattement(void) {
    return(angleDebattement);
}

// ********************************
// Setter de l'angle de debattement
// @Param l'angle de debattement
// @remark verifier le flag error
// ********************************
void GestionServo::setAngleDebattement(float pAngleDebattement) {
	error = false;
	if(pAngleDebattement < 0) {
		error = true;
	}
	if(pAngleDebattement > DEGRES_PAR_TOUR) {
		error = true;
	}
    angleDebattement = pAngleDebattement;
}

// ************************************
// Fait bouger le servo vers une valeur
// @param pValeur la valeur à atteindre
// @remark verifier le flag error
// ************************************
void GestionServo::move(uint16_t pValeur) {
	error = false;
	if(fullInit) {
		if(pValeur > cycleMax || pValeur < cycleMin) {
			error = true;
		} else {
			valeur = pValeur;
			angle = valeur * (float)angleDebattement / (float)(cycleMax - cycleMin) - (float)(cycleMin * angleDebattement / (float)(cycleMax - cycleMin));
		}
	} else {
		error = true;
	}
}

// **********************************
// Fait bouger le servo vers un angle
// @param pAngle l'angle à atteindre
// **********************************
void GestionServo::move(float pAngle) {
    uint16_t valeur = (float)(cycleMax - cycleMin) / (float)angleDebattement * pAngle + cycleMin;
    move(valeur);
}

// *******************
// Getter de la valeur
// @return la valeur
// *******************
uint16_t GestionServo::getValeur() {
    return(valeur);
}

// *****************
// Getter de l'angle
// @return l'angle
// *****************
float GestionServo::getAngle() {
    return(angle);
}

// ************************************
// Getter de l'erreur de traitement
// @return true si erreur de traitement
// ************************************
bool GestionServo::isError() {
    return(error);
}

// ***********************************
// Getter de l'initialisation
// @return true si l'init est complete
// ***********************************
bool GestionServo::isFullInit() {
    return(fullInit);
}

// ***********
// Destructeur
// ***********
GestionServo::~GestionServo() {
}
