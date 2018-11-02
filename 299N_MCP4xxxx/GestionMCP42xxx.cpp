/*
 * GestionMCP42xxx.cpp
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP42010, MCP42050 et MCP42100
 */

#include "GestionMCP42xxx.h"
#include <wiringPi.h> // La wiringPi

// *****************
// Constructeur vide
// *****************
GestionMCP42xxx::GestionMCP42xxx(void) {
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP42xxx::GestionMCP42xxx(Channel pChannel, float pPotValue) {
	init(pChannel, pPotValue);
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// @Param la pin Reset
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP42xxx::GestionMCP42xxx(Channel pChannel, float pPotValue, PinGPIO pReset) {
	init(pChannel, pPotValue, pReset);
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// @Param la pin Reset
// @Param la pin Shutdown
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP42xxx::GestionMCP42xxx(Channel pChannel, float pPotValue, PinGPIO pReset, PinGPIO pShutdown) {
	init(pChannel, pPotValue, pReset, pShutdown);
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// @return true si init ok, sinon false
// Mémorise le canal et initialise le SPI
// **************************************
bool GestionMCP42xxx::init(Channel pChannel, float pValue) {
	if(pValue <= 0) {
		return false;
	}
	channel = pChannel;	
	potValue = pValue;
	currentPot0Value = pValue / 2.0;
	currentPot1Value = pValue / 2.0;
	return GestionMCP41xxx::init(channel, potValue);
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// @Param pinReset
// @return true si init ok, sinon false
// Mémorise le canal et initialise le SPI
// **************************************
bool GestionMCP42xxx::init(Channel pChannel, float pValue, PinGPIO pinReset) {
	reset.init(pinReset);
	reset.out();
	reset.on();
	useReset = true;
	return init(pChannel, pValue);
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// @Param pinReset
// @Param pinShutdown
// @return true si init ok, sinon false
// Mémorise le canal et initialise le SPI
// **************************************
bool GestionMCP42xxx::init(Channel pChannel, float pValue, PinGPIO pinReset, PinGPIO pinShutdown) {
	shutdown.init(pinShutdown);
	shutdown.out();
	shutdown.on();
	useShutdown = true;
	return init(pChannel, pValue, pinReset);
}

// *******************************
// Shutdown du potentiometre
// @Param le potentiometre
// @Return true si ok, false sinon
// *******************************
bool GestionMCP42xxx::softShutdown(Pot pPot){
	if(write((shutdownCmd | pPot) << 8) > 0) {
		return true;
	} else {
		return false;
	}
}

// ************************************
// Increment la valeur du potentiometre
// Si la valeur finale est superieure 
//  a la valeur du potentiometre, la 
//  valeur sera à la valeur du 
//  potentiometre
// @Param le potentiometre
// @Param la valeur à ajouter
// @Return true si ok, false sinon
// ************************************
bool GestionMCP42xxx::increment(Pot pPot, float pValue){
	bool result = true;
	if(pValue <= 0) {
		return false;
	}
	switch(pPot) {
		case pot0: currentPot0Value += pValue; break;
		case pot1: currentPot1Value += pValue; break;
		case potTwice: currentPot0Value += pValue; currentPot1Value += pValue; break;
		default: return false;
	}
	if(currentPot0Value > potValue) {
		currentPot0Value = potValue;
	}
	if(currentPot1Value > potValue) {
		currentPot1Value = potValue;
	}
	switch(pPot) {
		case pot0: result &= setCurrentValue(pot0, currentPot0Value); break;
		case pot1: result &= setCurrentValue(pot1, currentPot1Value); break;
		case potTwice: result &= setCurrentValue(pot0, currentPot0Value); result |= setCurrentValue(pot1, currentPot1Value); break;
		default: return false;
	}
	return result;
}

// ************************************
// Decrement la valeur du potentiometre
// Si la valeur finale est inférieure 
//  a la valeur du potentiometre, la 
//  valeur sera à 0
// @Param le potentiometre
// @Param la valeur à enlever
// @Return true si ok, false sinon
// ************************************
bool GestionMCP42xxx::decrement(Pot pPot, float pValue){
	bool result = true;
	if(pValue <= 0) {
		return false;
	}
	switch(pPot) {
		case pot0: currentPot0Value -= pValue; break;
		case pot1: currentPot1Value -= pValue; break;
		case potTwice: currentPot0Value -= pValue; currentPot1Value -= pValue; break;
		default: return false;
	}
	if(currentPot0Value < 0) {
		currentPot0Value = 0;
	}
	if(currentPot1Value < 0) {
		currentPot1Value = 0;
	}
	switch(pPot) {
		case pot0: result &= setCurrentValue(pot0, currentPot0Value); break;
		case pot1: result &= setCurrentValue(pot1, currentPot1Value); break;
		case potTwice: result &= setCurrentValue(pot0, currentPot0Value); result |= setCurrentValue(pot1, currentPot1Value); break;
		default: return false;
	}
	return result;	
}

// *************************************
// positionne la valeur du potentiometre
// Si la valeur est superieure a la 
//  valeur du potentiometre, la valeur 
//  sera à la valeur du potentiometre
// @Param le potentiometre
// @Param la valeur
// @Return true si ok, false sinon
// ************************************
bool GestionMCP42xxx::setCurrentValue(Pot pPot, float pValue){
	bool result = true;
	if(pValue < 0) {
		return false;
	}
	switch(pPot) {
		case pot0: currentPot0Value = pValue; break;
		case pot1: currentPot1Value = pValue; break;
		case potTwice: currentPot0Value = pValue; currentPot1Value = pValue; break;
		default: return false;
	}
	if(currentPot0Value > potValue) {
		currentPot0Value = potValue;
	}
	if(currentPot1Value > potValue) {
		currentPot1Value = potValue;
	}
	if(currentPot0Value < 0) {
		currentPot0Value = 0;
	}
	if(currentPot1Value < 0) {
		currentPot1Value = 0;
	}
	switch(pPot) {
		case pot0: result &= write(((writeDataCmd | pot0) << 8 ) | ((uint8_t)(255.4 * currentPot0Value / potValue))); break;
		case pot1: result &= write(((writeDataCmd | pot1) << 8 ) | ((uint8_t)(255.4 * currentPot1Value / potValue))); break;
		case potTwice: result &= write(((writeDataCmd | pot0) << 8 ) | ((uint8_t)(255.4 * currentPot0Value / potValue)));
		               result &= write(((writeDataCmd | pot1) << 8 ) | ((uint8_t)(255.4 * currentPot1Value / potValue))); break;
	}
	return result;
}

// *********************************************
// Donne la position courante du potentiometre
// @Return la position courante du potentiometre
// *********************************************
float GestionMCP42xxx::getCurrentValue(Pot pPot){
	switch(pPot) {
		case pot0: return currentPot0Value;
		case pot1: return currentPot1Value;
		case potTwice: return -1.0;
	}
}

// *************************************************
// Place le circuit en mode consommation minimale
// @return true si c'est possible et ok, false sinon
// *************************************************
bool GestionMCP42xxx::hardShutdownIn(void) {
	if(isShutdown()) {
		shutdown.off();
		return true;
	}
	return false;
}

// *************************************************
// Sort le circuit du mode consommation minimale
// @return true si c'est possible et ok, false sinon
// *************************************************
bool GestionMCP42xxx::hardShutdownOut(void) {
	if(isShutdown()) {
		shutdown.on();
		return true;
	}
	return false;
}

// *************************************************
// Reset le circuit
// @return true si c'est possible et ok, false sinon
// *************************************************
bool GestionMCP42xxx::hardReset(void) {
	if(isReset()) {
		reset.off();
		currentPot0Value = potValue / 2.0;
		currentPot1Value = potValue / 2.0;
		delayMicroseconds(1); // normalement 150ns
		reset.on();
		return true;
	}
	return false;
}

// **************************************
// Indique si la broche Reset est utilisé
// @Return true si oui, false sinon
// **************************************	
bool GestionMCP42xxx::isReset(void){
	return useReset;
}

// ******************************************
// Indique si la broche Shutdown est utilisée
// @Return true si oui, false sinon
// ******************************************	
bool GestionMCP42xxx::isShutdown(void){
	return useShutdown;
}

// ***********
// Destructeur
// ***********
GestionMCP42xxx::~GestionMCP42xxx() {
}

