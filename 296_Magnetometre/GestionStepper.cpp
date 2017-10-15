/*
 * GestionStepper.cpp
 *
 *  Created on: 27 novembre 2016
 *      Author: totof
 * Controle un moteur pas a pas
*/
 
#include <stdlib.h>
#include "GestionStepper.h"

namespace std {

// *****************************************************
// Constructeur
// @param pPinA numero de la pin GPIO sur plot A
// @param pPinB numero de la pin GPIO sur plot B
// @param pPinC numero de la pin GPIO sur plot C
// @param pPinD numero de la pin GPIO sur plot D
// @param pPosition la position de depart
// @param pSynchonised synchronise la position du moteur
//        avec le point donné
// *****************************************************
GestionStepper::GestionStepper(PinGPIO pPinA, PinGPIO pPinB, PinGPIO pPinC, PinGPIO pPinD, Position pPosition, Mode pMode, bool pSynchronised) {
	PinA.init(pPinA);
	PinB.init(pPinB);
	PinC.init(pPinC);
	PinD.init(pPinD);
	PinA.out();
	PinA.off();
	PinB.out();
	PinB.off();
	PinC.out();
	PinC.off();
	PinD.out();
	PinD.off();
	position = pPosition;
	mode = pMode;
	hold = false;
	temporisation = 10;
	if(pSynchronised) {
		gotoPosition(pPosition);
	}
}

// **********************************************************************************************************
// Incremente la position du moteur
// @return true si OK, false si erreur de mode ou si la position de depart n'est pas dans le mode sélectionne
//         ou si elle n'existe pas
// **********************************************************************************************************
bool GestionStepper::increment() {
	switch(mode) {
		case ONE_ONE:
			switch(position) {
				case A: positionC(); break;
				case C: positionB(); break;
				case B: positionD(); break;
				case D: positionA(); break;
				default: return false;
			}
			break;					
		case TWO_ONE:
			switch(position) {
				case AC: positionCB(); break;
				case CB: positionBD(); break;
				case BD: positionDA(); break;
				case DA: positionAC(); break;
				default: return false;
			}
			break;					
		case HALF: 	
			switch(position) {
				case A: positionAC(); break;
				case AC: positionC(); break;
				case C: positionCB(); break;
				case CB: positionB(); break;
				case B: positionBD(); break;
				case BD: positionD(); break;
				case D: positionDA(); break;
				case DA: positionA(); break;
				default: return false;
			}
			break;	
		default: return false;
	}
	return true;
}

// **********************************************************************************************************
// Decremente la position du moteur
// @return true si OK, false si erreur de mode ou si la position de depart n'est pas dans le mode sélectionne
//         ou si elle n'existe pas
// **********************************************************************************************************
bool GestionStepper::decrement() {
	switch(mode) {
		case ONE_ONE:
			switch(position) {
				case A: positionD(); break;
				case C: positionA(); break;
				case B: positionC(); break;
				case D: positionB(); break;
				default: return false;
			}
			break;					
		case TWO_ONE:
			switch(position) {
				case AC: positionDA(); break;
				case CB: positionAC(); break;
				case BD: positionCB(); break;
				case DA: positionBD(); break;
				default: return false;
			}
			break;					
		case HALF: 	
			switch(position) {
				case A: positionDA(); break;
				case AC: positionA(); break;
				case C: positionAC(); break;
				case CB: positionC(); break;
				case B: positionCB(); break;
				case BD: positionB(); break;
				case D: positionBD(); break;
				case DA: positionD(); break;
				default: return false;
			}
			break;					
		default: return false;
	}
	return true;
}

// **********************************************************************************************************
// Incremente la position du moteur plusieurs fois
// @param pNombre le nombre d'incrementation
// @return true si OK, false si erreur de mode ou si la position de depart n'est pas dans le mode sélectionne
// **********************************************************************************************************
bool GestionStepper::increment(unsigned int pNombre) {
	for(int compteur = 0; compteur != pNombre; compteur++) {
		if(!increment()) {
			return false;
		}
	}
	return true;
}

// **********************************************************************************************************
// Decremente la position du moteur plusieurs fois
// @param pNombre le nombre de decrementation
// @return true si OK, false si erreur de mode ou si la position de depart n'est pas dans le mode sélectionne
// **********************************************************************************************************
bool GestionStepper::decrement(unsigned int pNombre) {
	for(int compteur = 0; compteur != pNombre; compteur++) {
		if(!decrement()) {
			return false;
		}
	}
	return true;
}

// **********************************************************************************************************
// Fait tourner le moteur d'un nombre de cycle
// Le nombre de cycle (positif pour incrementation, negatif pour decrementation)
// @return true si OK, false si erreur de mode ou si la position de depart n'est pas dans le mode sélectionne
// **********************************************************************************************************
bool GestionStepper::cycle(int pNbCycle) {
	if(pNbCycle > 0) {
		switch(mode) {
			case ONE_ONE:
			case TWO_ONE:
				return increment(pNbCycle * 4);
				break;					
			case HALF: 	
				return increment(pNbCycle * 8);
				break;
			default: return false;
		}
	} else {
		switch(mode) {
			case ONE_ONE:
			case TWO_ONE:
				return decrement(abs(pNbCycle) * 4);
				break;					
			case HALF: 	
				return decrement(abs(pNbCycle) * 8);
				break;					
			default: return false;
		}
	}
}

// *******************************************************************************
// Positionne le moteur sur une position
// @param pPosition, la position voulue
// @return true si OK, false si la position n'existe pas ou n'est pas dans le mode
// *******************************************************************************
bool GestionStepper::gotoPosition(Position pPosition) {
	switch(mode) {
		case ONE_ONE:
			switch(pPosition) {
				case A: positionA(); break;
				case C: positionC(); break;
				case B: positionB(); break;
				case D: positionD(); break;
				default: return false;
			}
			break;					
		case TWO_ONE:
			switch(pPosition) {
				case AC: positionAC(); break;
				case CB: positionCB(); break;
				case BD: positionBD(); break;
				case DA: positionDA(); break;
				default: return false;
			}
			break;					
		case HALF: 	
			switch(pPosition) {
				case A: positionA(); break;
				case AC: positionAC(); break;
				case C: positionC(); break;
				case CB: positionCB(); break;
				case B: positionB(); break;
				case BD: positionBD(); break;
				case D: positionD(); break;
				case DA: positionDA(); break;
				default: return false;
			}
			break;					
		default: return false;
	}
	return true;
}

// *****************************************************************************
// Positionne le moteur sur la position A
// *****************************************************************************
void GestionStepper::positionA() {
	position = A;
	PinA.on();
	PinB.off();
	PinC.off();
	PinD.off();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *****************************************************************************
// Positionne le moteur sur la position B
// *****************************************************************************
void GestionStepper::positionB() {
	position = B;
	PinA.off();
	PinB.on();
	PinC.off();
	PinD.off();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *****************************************************************************
// Positionne le moteur sur la position C
// *****************************************************************************
void GestionStepper::positionC() {
	position = C;
	PinA.off();
	PinB.off();
	PinC.on();
	PinD.off();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *****************************************************************************
// Positionne le moteur sur la position D
// *****************************************************************************
void GestionStepper::positionD() {
	position = D;
	PinA.off();
	PinB.off();
	PinC.off();
	PinD.on();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *****************************************************************************
// Positionne le moteur sur la position AC
// *****************************************************************************
void GestionStepper::positionAC() {
	position = AC;
	PinA.on();
	PinB.off();
	PinC.on();
	PinD.off();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *****************************************************************************
// Positionne le moteur sur la position CB
// *****************************************************************************
void GestionStepper::positionCB() {
	position = CB;
	PinA.off();
	PinB.on();
	PinC.on();
	PinD.off();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *****************************************************************************
// Positionne le moteur sur la position BD
// *****************************************************************************
void GestionStepper::positionBD() {
	position = BD;
	PinA.off();
	PinB.on();
	PinC.off();
	PinD.on();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *****************************************************************************
// Positionne le moteur sur la position DA
// *****************************************************************************
void GestionStepper::positionDA() {
	position = DA;
	PinA.on();
	PinB.off();
	PinC.off();
	PinD.on();
	delay(temporisation);
	if(!hold) {
		positionOff();
	}
}

// *******************
// desactive le moteur
// *******************
void GestionStepper::positionOff() {
	PinA.off();
	PinB.off();
	PinC.off();
	PinD.off();
}

// *******************
// Donne la position
// @return la position
// *******************
Position GestionStepper::getPosition(void) {
	return position;
}

// ********************************************************
// Donne la temporisation de maintient de l'impulsion en ms
// @return la temporisation
// ********************************************************
int GestionStepper::getTemporisation(void) {
	return temporisation;
}

// ****************************************************************
// Change la valeur de la temporisation de maintient de l'impulsion
// @param pTemporisation la valeur de la temporisation en ms
// ****************************************************************
void GestionStepper::setTemporisation(unsigned int pTemporisation) {
	temporisation = pTemporisation;
}

// ***************************************
// Donne le mode positionne pour le moteur
// @return le mode du moteur
// ***************************************
Mode GestionStepper::getMode(void) {
	return mode;
}

// ***********************************************************************************
// Positionne le mode du moteur
// @param pMode le mode
// @return true si mode ok avec position, sinon false ou false si le mode n'existe pas
// ***********************************************************************************
bool GestionStepper::setMode(Mode pMode) {
	switch(pMode) {
	case ONE_ONE:
		switch(position) {
			case A: 
			case C:
			case B: 
			case D: mode = pMode; break;
			default: return false;
		}
		break;					
	case TWO_ONE:
		switch(position) {
			case AC: 
			case CB:
			case BD: 
			case DA: mode = pMode; break;
			default: return false;
		}
		break;					
	case HALF: 	
		switch(position) {
			case A: 
			case AC: 
			case C: 
			case CB: 
			case B: 
			case BD: 
			case D: 
			case DA: mode = pMode; break;
			default: return false;
		}
		break;					
	default: return false;
	}
	return true;
}

// ************************************
// Donne le verrouillage pour le moteur
// @return le verouillage du moteur
// ************************************
bool GestionStepper::getHold(void) {
	return hold;
}

// ************************************
// Positionne le verrouillage du moteur
// @param pHold le verouillage
// ************************************
void GestionStepper::setHold(bool pHold) {
	hold = pHold;
}
	
// ******************
// Destructeur
// Désactive les GPIO
// ******************
GestionStepper::~GestionStepper() {
	PinA.~GestionPinGPIO();
	PinB.~GestionPinGPIO();
	PinC.~GestionPinGPIO();
	PinD.~GestionPinGPIO();
}

} /* namespace std */
