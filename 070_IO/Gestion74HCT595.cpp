/*
 * Gestion74HCT595.cpp
 *
 *  Created on: 15 decembre 2017
 *      Author: totof
 * Controle un circuit 74HCT595
 */
 
#include "Gestion74HCT595.h"

// *****************
// Constructeur vide
// *****************
Gestion74HCT595::Gestion74HCT595() {
}

// ************************************
// Constructeur
// @Param GPIO de la broche data
// @Param GPIO de la broche decalage
// @Param GPIO de la broche verouillage
// ************************************
Gestion74HCT595::Gestion74HCT595(PinGPIO pGpioData, PinGPIO pGpioClock, PinGPIO pGpioLatch, bool erase) {
	init(pGpioData, pGpioClock, pGpioLatch, erase);
}

// ************************************
// initialisation
// @Param GPIO de la broche data
// @Param GPIO de la broche decalage
// @Param GPIO de la broche verouillage
// ************************************
void Gestion74HCT595::init(PinGPIO pGpioData, PinGPIO pGpioClock, PinGPIO pGpioLatch, bool erase) {
	gpioData.init(pGpioData);
	gpioClock.init(pGpioClock);
	gpioLatch.init(pGpioLatch);
	gpioData.out();
	gpioClock.out();
	gpioLatch.out();	
	gpioData.off();
	gpioClock.off();
	gpioLatch.off();	
	if(erase) {
		write((uint8_t)0x00);
	}
}

// ***********************************
// Positionne l'etat de la broche data
// @Param l'etat
// ***********************************
void Gestion74HCT595::write(bool state) {
	if(state) {
		gpioData.on();
	} else {
		gpioData.off();
	}
}

// *****************************************
// Decale les data (actif sur front montant)
// *****************************************
void Gestion74HCT595::scroll(void) {
	gpioClock.off();
	gpioClock.on();
	gpioClock.off();
}

// *********************************************
// Verrouille les data (actif sur front montant)
// *********************************************
void Gestion74HCT595::latch(void) {
	gpioLatch.off();
	gpioLatch.on();
	gpioLatch.off();
}

// ***********************
// Ecrit un octet complet
// @Param l'octet a ecrire
// ***********************
void Gestion74HCT595::write(uint8_t valeur) {
	for(int compteur = 0; compteur != 8; compteur++) {
		write((bool)(valeur & (1 << compteur)));
		scroll();
	}
	latch();
}

// ****************************
// Ecrit un caractere
// @Param le caractere a ecrire
// ****************************
void Gestion74HCT595::write(char valeur) {
	write((uint8_t)valeur);
}

// ***********************
// Met un bit a 1
// @Param le numero du bit
// ***********************
void Gestion74HCT595::hight(PinHight numPin) {
	write((uint8_t)numPin);
}

// ***********************
// Met un bit a 1
// @Param le numero du bit
// ***********************
void Gestion74HCT595::hight(uint8_t numPin) {
	switch(numPin) {
		case 0: hight(PinHight0); break;
		case 1: hight(PinHight1); break;
		case 2: hight(PinHight2); break;
		case 3: hight(PinHight3); break;
		case 4: hight(PinHight4); break;
		case 5: hight(PinHight5); break;
		case 6: hight(PinHight6); break;
		case 7: hight(PinHight7); break;
	}
}

// ***********************
// Met un bit a 0
// @Param le numero du bit
// ***********************
void Gestion74HCT595::low(PinLow numPin) {
	write((uint8_t)numPin);
}

// ***********************
// Met un bit a 0
// @Param le numero du bit
// ***********************
void Gestion74HCT595::low(uint8_t numPin) {
	switch(numPin) {
		case 0: low(PinLow0); break;
		case 1: low(PinLow1); break;
		case 2: low(PinLow2); break;
		case 3: low(PinLow3); break;
		case 4: low(PinLow4); break;
		case 5: low(PinLow5); break;
		case 6: low(PinLow6); break;
		case 7: low(PinLow7); break;
	}
}