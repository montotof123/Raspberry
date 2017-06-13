/*
 * GestionPinGPIO.cpp
 *
 *  Created on: 1 août 2016
 *      Author: totof
 */

#include <wiringPi.h>
#include "GestionPinGPIO.h"

// *********************************
// Constructeur
// Mémorise le numéro de pin utilisé
// @param numéro de pin
// *********************************
GestionPinGPIO::GestionPinGPIO(int pPinNumber) {
	pinNumber = pPinNumber;
}

// **********************************
// Applique la direction sur une GPIO
// @param pDirection la direction
// **********************************
void GestionPinGPIO::pinModePI(int pDirection) {
	pinMode(pinNumber, pDirection);
}

// **************
// GPIO en entrée
// **************
void GestionPinGPIO::in() {
	pinMode(pinNumber, INPUT);
}

// **************
// GPIO en sortie
// **************
void GestionPinGPIO::out() {
	pinMode(pinNumber, OUTPUT);
}

// ***********************************************
// Active/désactive les résistance de pull down/up
// @param le type de résistance
// ***********************************************
void GestionPinGPIO::pullUpDnControlPI(int pNiveau) {
	pullUpDnControl(pinNumber, pNiveau);
}

// *******************************
// Active la résistance de pull up
// *******************************
void GestionPinGPIO::pullUp() {
	pullUpDnControl(pinNumber, PUD_UP);
}

// *********************************
// Active la résistance de pull down
// *********************************
void GestionPinGPIO::pullDn() {
	pullUpDnControl(pinNumber, PUD_DOWN);
}

// ***************************************
// Désactive la résistance de pull up/down
// ***************************************
void GestionPinGPIO::pullOff() {
	pullUpDnControl(pinNumber, PUD_OFF);
}

// ****************************
// Applique un niveau à la GPIO 
// @param le niveau
// ****************************
void GestionPinGPIO::write(int pValue) {
	digitalWrite(pinNumber, pValue);
}

// ********************************
// Applique un niveau bas à la GPIO 
// ********************************
void GestionPinGPIO::off() {
	digitalWrite(pinNumber, LOW);
}

// *********************************
// Applique un niveau haut à la GPIO 
// *********************************
void GestionPinGPIO::on() {
	digitalWrite(pinNumber, HIGH);
}

// ****************************
// inverse le niveau de la GPIO
// ****************************
void GestionPinGPIO::invertState() {
	if(isOn()) {
		off();
	} else {
		on();		
	}
}

// ****************************
// Lecture du niveau de la GPIO
// @return le niveau
// ****************************
int GestionPinGPIO::read() {
	return digitalRead(pinNumber);
}

// *************************************
// Demande si la GPIO est au niveau haut
// @return true si oui sinon false
// *************************************
bool GestionPinGPIO::isOn() {
	if(digitalRead(pinNumber) == 1){
		return true;
	}
	return false;
}

// ************************************
// Demande si la GPIO est au niveau bas
// @return true si oui sinon false
// ************************************
bool GestionPinGPIO::isOff() {
	if(digitalRead(pinNumber) == 0){
		return true;
	}
	return false;
}

// ***********************************************
// Active une fonction d'interruption sur un front
// @param le front
// @param un pointeur sur la fonction
// @return 0 si OK
// ***********************************************
int GestionPinGPIO::fctInterrupt(int pFront, interrupt intr) {
	return wiringPiISR(pinNumber, pFront, *intr);
}

// **********************************************************
// Destructeur
// Met la GPIO en entrée et désactive la résistance de rappel
// **********************************************************
GestionPinGPIO::~GestionPinGPIO() {
	pullUpDnControlPI(PUD_OFF);
	pinModePI(INPUT);
}
