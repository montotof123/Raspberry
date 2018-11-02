/*
 * GestionMCP41xxx.cpp
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP41010, MCP41050 et MCP41100
 */

#include "GestionMCP41xxx.h"

#define pot0 0b00000001


// *****************
// Constructeur vide
// *****************
GestionMCP41xxx::GestionMCP41xxx(void) {
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// Mémorise le canal et initialise le SPI
// **************************************
GestionMCP41xxx::GestionMCP41xxx(Channel pChannel, float pPotValue) {
	init(pChannel, pPotValue);
}

// **************************************
// Constructeur
// @Param le canal
// @Param la valeur du potentiometre
// @return true si init ok, sinon false
// Mémorise le canal et initialise le SPI
// **************************************
bool GestionMCP41xxx::init(Channel pChannel, float pPotValue) {
	if(pPotValue <= 0) {
		return false;
	}
	channel = pChannel;	
	potValue = pPotValue;
	currentPot0Value = potValue / 2.0;
	return GestionSPI16::init(channel);
}

// *******************************
// Shutdown du potentiometre 0
// @Return true si ok, false sinon
// *******************************
bool GestionMCP41xxx::softShutdown(void){
	if(write((shutdownCmd | pot0) << 8) > 0) {
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
// @Param la valeur à ajouter
// @Return true si ok, false sinon
// ************************************
bool GestionMCP41xxx::increment(float pValue){
	if(pValue <= 0) {
		return false;
	}
	currentPot0Value += pValue;
	if(currentPot0Value > potValue) {
		currentPot0Value = potValue;
	}
	return setCurrentValue(currentPot0Value);
}

// ************************************
// Decrement la valeur du potentiometre
// Si la valeur finale est inférieure 
//  a la valeur du potentiometre, la 
//  valeur sera à 0
// @Param la valeur à enlever
// @Return true si ok, false sinon
// ************************************
bool GestionMCP41xxx::decrement(float pValue){
	if(pValue <= 0) {
		return false;
	}
	currentPot0Value -= pValue;
	if(currentPot0Value < 0) {
		currentPot0Value = 0;
	}
	return setCurrentValue(currentPot0Value);	
}

// *************************************
// positionne la valeur du potentiometre
// Si la valeur est superieure a la 
//  valeur du potentiometre, la valeur 
//  sera à la valeur du potentiometre
// @Param la valeur
// @Return true si ok, false sinon
// ************************************
bool GestionMCP41xxx::setCurrentValue(float pValue){
	bool result;
	if(pValue < 0) {
		return false;
	}
	currentPot0Value = pValue;
	if(currentPot0Value > potValue) {
		currentPot0Value = potValue;
	}
	if(write(((writeDataCmd | pot0) << 8 ) | ((uint8_t)(255.4 * currentPot0Value / potValue))) > 0) {
		result = true;
	} else {
		result = false;
	}
	return result;
}

// **********************************
// Donne la valeur du potentiometre
// @Return la valeur du potentiometre
// **********************************
float GestionMCP41xxx::getPotValue(void){
	return potValue;
}

// *********************************************
// Donne la position courante du potentiometre
// @Return la position courante du potentiometre
// *********************************************
float GestionMCP41xxx::getCurrentValue(void){
	return currentPot0Value;
}

// ***********
// Destructeur
// ***********
GestionMCP41xxx::~GestionMCP41xxx() {
}

