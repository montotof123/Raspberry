/*
 * GestionHP50827300.cpp
 *
 *  Created on: 16 juillet 2017
 *      Author: totof
 * Controle de l'afficheur HP 5082-7300
*/
 
#include <stdint.h>
#include "GestionHP50827300.h"

namespace std {

// *******************************************************
// Constructeur vide
// *******************************************************
GestionHP50827300::GestionHP50827300() {
}

// *******************************************************
// Constructeur
// @param input1 entree input1 de l'afficheur
// @param input2 entree input2 de l'afficheur
// @param input4 entree input4 de l'afficheur
// @param input8 entree input8 de l'afficheur
// @param decimalPoint entree point decimal de l'afficheur
// @param latchEnable entree verouillage de l'afficheur
// *******************************************************
GestionHP50827300::GestionHP50827300(PinGPIO input1, PinGPIO input2, PinGPIO input4, PinGPIO input8, PinGPIO decimalPoint, PinGPIO latchEnable) {
	init(input1, input2, input4, input8, decimalPoint, latchEnable);
}

// *******************************************************
// Init si constructeur vide
// @param input1 entree input1 de l'afficheur
// @param input2 entree input2 de l'afficheur
// @param input4 entree input4 de l'afficheur
// @param input8 entree input8 de l'afficheur
// @param decimalPoint entree point decimal de l'afficheur
// @param latchEnable entree verouillage de l'afficheur
// *******************************************************
void GestionHP50827300::init(PinGPIO input1, PinGPIO input2, PinGPIO input4, PinGPIO input8, PinGPIO decimalPoint, PinGPIO latchEnable) {
	PinInput1.init(input1);
	PinInput2.init(input2);
	PinInput4.init(input4);
	PinInput8.init(input8);
	PinDecimalPoint.init(decimalPoint);
	PinLatchEnable.init(latchEnable);
	
	PinLatchEnable.out();
	PinLatchEnable.on();
	PinInput1.out();
	PinInput2.out();
	PinInput4.out();
	PinInput8.out();
	PinDecimalPoint.out();
	
	setBlank();
	
	valeur = NOT_A_NUMBER;
	point = false;
}

// ***********************************************
// Incremente la valeur de l'afficheur
// @return true si OK, false si valeur trop grande
// ***********************************************
bool GestionHP50827300::increment() {
	bool result = true;
	if(valeur < 9 && valeur != NOT_A_NUMBER) {
		valeur++;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// ***********************************************
// Decremente la valeur de l'afficheur
// @return true si OK, false si valeur trop petite
// ***********************************************
bool GestionHP50827300::decrement() {
	bool result = true;
	if(valeur > 0 && valeur != NOT_A_NUMBER) {
		valeur--;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// **************************************************
// Incremente la valeur de l'afficheur plusieurs fois
// @param pNombre le nombre d'incrementation
// @return true si OK, false si valeur trop grande
// **************************************************
bool GestionHP50827300::increment(uint8_t pNombre) {
	bool result = true;
	if(pNombre < 1) {
		return false;
	}
	if(valeur + pNombre <= 9 && valeur != NOT_A_NUMBER) {
		valeur += pNombre;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// **************************************************
// Decremente la valeur de l'afficheur plusieurs fois
// @param pNombre le nombre de decrementation
// @return true si OK, false si valeur trop petite
// **************************************************
bool GestionHP50827300::decrement(uint8_t pNombre) {
	bool result = true;
	if(pNombre < 1) {
		return false;
	}
	if(valeur - pNombre >= 0 && valeur != NOT_A_NUMBER) {
		valeur -= pNombre;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// ************************************************
// Affiche une valeur entre 0 et 9 sans la virgule
// @return true si OK, false si valeur hors echelle
// ************************************************
bool GestionHP50827300::setValueWithoutPoint(uint8_t pValeur) {
	bool result = true;
	switch(pValeur) {
		case 0: setValue(ZERO); break;
		case 1: setValue(UN); break;
		case 2: setValue(DEUX); break;
		case 3: setValue(TROIS); break;
		case 4: setValue(QUATRE); break;
		case 5: setValue(CINQ); break;
		case 6: setValue(SIX); break;
		case 7: setValue(SEPT); break;
		case 8: setValue(HUIT); break;
		case 9: setValue(NEUF); break;
		default: result = false;
	}
	if(result) {
		valeur = pValeur;
		point = false;
	}
	return result;
}

// ************************************************
// Affiche une valeur entre 0 et 9 avec la virgule
// @return true si OK, false si valeur hors echelle
// ************************************************
bool GestionHP50827300::setValueWithPoint(uint8_t pValeur) {
	bool result = true;
	switch(pValeur) {
		case 0: setValue(ZERO_POINT); break;
		case 1: setValue(UN_POINT); break;
		case 2: setValue(DEUX_POINT); break;
		case 3: setValue(TROIS_POINT); break;
		case 4: setValue(QUATRE_POINT); break;
		case 5: setValue(CINQ_POINT); break;
		case 6: setValue(SIX_POINT); break;
		case 7: setValue(SEPT_POINT); break;
		case 8: setValue(HUIT_POINT); break;
		case 9: setValue(NEUF_POINT); break;
		default: result = false;
	}
	if(result) {
		valeur = pValeur;
		point = true;
	}
	return result;
}

// ************************
// Allume tous les segments
// ************************	
void GestionHP50827300::setTest(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(TEST);
}

// ************************
// Eteint tous les segments
// ************************	
void GestionHP50827300::setBlank(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(BLANK);
}

// ****************
// Affiche un moins
// ****************	
void GestionHP50827300::setMinus(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(MINUS);
}

// ****************
// Affiche un moins
// ****************	
void GestionHP50827300::setMinusWithPoint(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(MINUS_POINT);
}

// ********************************************
// Affiche une valeur
// @return true si OK, false si valeur inconnue
// ********************************************	
bool GestionHP50827300::setValue(Values pValeur) {
	bool result = true;
	// Attention point decimal actif sur off
	switch(pValeur) {
		case ZERO        : PinInput8.off(); PinInput4.off(); PinInput2.off(); PinInput1.off(); PinDecimalPoint.on (); break;
		case UN          : PinInput8.off(); PinInput4.off(); PinInput2.off(); PinInput1.on (); PinDecimalPoint.on (); break;
		case DEUX        : PinInput8.off(); PinInput4.off(); PinInput2.on (); PinInput1.off(); PinDecimalPoint.on (); break;
		case TROIS       : PinInput8.off(); PinInput4.off(); PinInput2.on (); PinInput1.on (); PinDecimalPoint.on (); break;
		case QUATRE      : PinInput8.off(); PinInput4.on (); PinInput2.off(); PinInput1.off(); PinDecimalPoint.on (); break;
		case CINQ        : PinInput8.off(); PinInput4.on (); PinInput2.off(); PinInput1.on (); PinDecimalPoint.on (); break;
		case SIX         : PinInput8.off(); PinInput4.on (); PinInput2.on (); PinInput1.off(); PinDecimalPoint.on (); break;
		case SEPT        : PinInput8.off(); PinInput4.on (); PinInput2.on (); PinInput1.on (); PinDecimalPoint.on (); break;
		case HUIT        : PinInput8.on (); PinInput4.off(); PinInput2.off(); PinInput1.off(); PinDecimalPoint.on (); break;
		case NEUF        : PinInput8.on (); PinInput4.off(); PinInput2.off(); PinInput1.on (); PinDecimalPoint.on (); break;
		case ZERO_POINT  : PinInput8.off(); PinInput4.off(); PinInput2.off(); PinInput1.off(); PinDecimalPoint.off(); break;
		case UN_POINT    : PinInput8.off(); PinInput4.off(); PinInput2.off(); PinInput1.on (); PinDecimalPoint.off(); break;
		case DEUX_POINT  : PinInput8.off(); PinInput4.off(); PinInput2.on (); PinInput1.off(); PinDecimalPoint.off(); break;
		case TROIS_POINT : PinInput8.off(); PinInput4.off(); PinInput2.on (); PinInput1.on (); PinDecimalPoint.off(); break;
		case QUATRE_POINT: PinInput8.off(); PinInput4.on (); PinInput2.off(); PinInput1.off(); PinDecimalPoint.off(); break;
		case CINQ_POINT  : PinInput8.off(); PinInput4.on (); PinInput2.off(); PinInput1.on (); PinDecimalPoint.off(); break;
		case SIX_POINT   : PinInput8.off(); PinInput4.on (); PinInput2.on (); PinInput1.off(); PinDecimalPoint.off(); break;
		case SEPT_POINT  : PinInput8.off(); PinInput4.on (); PinInput2.on (); PinInput1.on (); PinDecimalPoint.off(); break;
		case HUIT_POINT  : PinInput8.on (); PinInput4.off(); PinInput2.off(); PinInput1.off(); PinDecimalPoint.off(); break;
		case NEUF_POINT  : PinInput8.on (); PinInput4.off(); PinInput2.off(); PinInput1.on (); PinDecimalPoint.off(); break;
		case TEST        : PinInput8.on (); PinInput4.off(); PinInput2.on (); PinInput1.off(); PinDecimalPoint.off(); break;
		case BLANK       : PinInput8.on (); PinInput4.on (); PinInput2.on (); PinInput1.off(); PinDecimalPoint.on (); break;
		case MINUS       : PinInput8.on (); PinInput4.on (); PinInput2.off(); PinInput1.on (); PinDecimalPoint.on (); break;
		case MINUS_POINT : PinInput8.on (); PinInput4.on (); PinInput2.off(); PinInput1.on (); PinDecimalPoint.off (); break;
		default          : result = false;
	}
	if(result) {
		PinLatchEnable.invertState();
		PinLatchEnable.invertState();
	}
	return result;
}
	
// ******************
// Destructeur
// Désactive les GPIO
// ******************
GestionHP50827300::~GestionHP50827300() {
	PinInput1.~GestionPinGPIO();
	PinInput2.~GestionPinGPIO();
	PinInput4.~GestionPinGPIO();
	PinInput8.~GestionPinGPIO();
	PinDecimalPoint.~GestionPinGPIO();
	PinLatchEnable.~GestionPinGPIO();
}

} /* namespace std */
