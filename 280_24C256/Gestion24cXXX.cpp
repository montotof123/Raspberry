/*
 * Gestion24cXXX.cpp
 *
 *  Created on: 5 may 2017
 *      Author: totof
 */

#include "Gestion24cXXX.h"
#include "Gestion24cXXXError.h"
#include "24cXX.h"
#include "GestionPinGPIO.h"		// Gestion de la broche writeProtect
#include <string.h>
#include <stdlib.h>

// *****************************************
// Constructeur
// A utiliser si la broche WP est à la masse
// Mémorise l'adresse du composant
// @param l'adresse du composant
// *****************************************
Gestion24cXXX::Gestion24cXXX(Adresse pAdresse) {
	adresse = pAdresse;
	
	useWriteProtect = false;
}

// **********************************************************
// Constructeur
// Mémorise l'adresse du composant et la GPIO du writeProtect
// @param l'adresse du composant
// @param la GPIO du writeProtect
// **********************************************************
Gestion24cXXX::Gestion24cXXX(Adresse pAdresse, PinGPIO pPinGpio) {
	adresse = pAdresse;
	
	// Ecriture possible a l'initialisation
	gpioWriteProtect.init(pPinGpio);
	gpioWriteProtect.out();
	gpioWriteProtect.off();
	
	useWriteProtect = true;
}

// ***********************************
// Protege ou non l'eeprom en ecriture
// ***********************************
void Gestion24cXXX::writeProtect(bool pProtect) {
	if(useWriteProtect) {
		if(pProtect) {
			gpioWriteProtect.on();
		} else {
			gpioWriteProtect.off();
		}
	}
}

bool Gestion24cXXX::isWriteProtect() {
	if(!useWriteProtect) {
		return false;
	}
	return gpioWriteProtect.isOn();
}

// *******************************************************
// Indique si une erreur s'est produite à l'initialisation
// @return true si une erreur s'est produite, sinon false
// *******************************************************
bool Gestion24cXXX::getErrorFlag() {
	return errorFlag;
}

// *************************************************************************
// Donne le message d'erreur si une erreur s'est produite à l'initialisation
// @return le message d'erreur ou vide si pas d'erreur
// *************************************************************************
const char* Gestion24cXXX::getErrorMessage() {
	return errorMessage;
}

// *******************************
// Ouverture du device i2c
// @return true si ok, false sinon
// *******************************
bool Gestion24cXXX::openI2Cdevice() {
	if(eeprom_open(DEVICE, adresse, EEPROM_TYPE_16BIT_ADDR, &e) < 0) {
		return false;
	}	
	return true;
}

// ***********************************
// Ecriture d'un octet a une adresse
// @param adresseData adresse des data
// @param data le caractere
// ***********************************
bool Gestion24cXXX::write(unsigned short adresseData, char data) {
	errorFlag = false;
	errorMessage = "";
	if(openI2Cdevice()) {
		if(eeprom_write_byte(&e, adresseData, data) < 0) {
			errorFlag = true;
			errorMessage = WRITE_ERROR;		
		}
		eeprom_close(&e);
	} else {
		errorFlag = true;
		errorMessage = OPEN_ERROR;		
	}
	return !errorFlag;
}

// ************************************************
// Ecriture d'une chaine de caractere a une adresse
// @param adresseData adresse des data
// @param data la chaine de caractere
// ************************************************
bool Gestion24cXXX::write(unsigned short adresseData, char* data) {
	errorFlag = false;
	errorMessage = "";
	if(openI2Cdevice()) {
		int compteur;
		for(compteur = 0; compteur != strlen(data); compteur++) {
			if(eeprom_write_byte(&e, adresseData + compteur, data[compteur]) < 0) {
				errorFlag = true;
				errorMessage = WRITE_ERROR;		
				return !errorFlag;			}
		}
		eeprom_close(&e);
	} else {
		errorFlag = true;
		errorMessage = OPEN_ERROR;		
	}
	return !errorFlag;
}

// *************************************
// Lecture de n caracteres a une adresse
// @param adresseData adresse des data
// @param int le nombre de caracteres
// *************************************	
char* Gestion24cXXX::read(unsigned short adresseData, int nombre){
	int ch;
	errorFlag = false;
	errorMessage = "";
	char* buf;
	buf = (char*)malloc(sizeof(*buf) * nombre); 	
	if(openI2Cdevice()) {
		int compteur;
		for(compteur = 0; compteur != nombre; compteur++) {
			ch = eeprom_read_byte(&e, adresseData + compteur);
			if(ch < 0) {
				errorFlag = true;
				errorMessage = READ_ERROR;	
				return buf;				
			}
			buf[compteur] = (char)ch;
		}
		eeprom_close(&e);
	} else {
		errorFlag = true;
		errorMessage = OPEN_ERROR;		
	}
	return buf;
}

// **********************************************************
// Destructeur
/// **********************************************************
Gestion24cXXX::~Gestion24cXXX() {
}

