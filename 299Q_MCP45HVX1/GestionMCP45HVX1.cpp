/*
 * GestionMCP45HVX1.cpp
 *
 * Created on 14/12/2020
 * Author Totof
 *
 */
 
#ifndef __GestionMCP45HVX1_CPP__
#define __GestionMCP45HVX1_CPP__

#include <stdint.h>
#include "GestionMCP45HVX1.h"

#include "Logger.h"

// *****************
// Constructeur vide
// *****************
GestionMCP45HVX1::GestionMCP45HVX1(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// **********************
// Constructeur 
// @Param adresse I2C
// @Param valeur
// **********************
GestionMCP45HVX1::GestionMCP45HVX1(Adresse pAdresse, Value pValue) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", (uint8_t)pValue);	

	InitMCP45HVX1(pAdresse, pValue);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// **********************
// Initialisation
// @Param adresse I2C
// @Param valeur
// **********************
bool GestionMCP45HVX1::InitMCP45HVX1(Adresse pAdresse, Value pValue) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", (uint8_t)pValue);	

	potValue = pValue;
	
	initI2CPeripheric(pAdresse);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return isInitialize();
}

//***********************************
// Donne la valeur du potentiometre
// @Return la valeur du potentiometre
// **********************************
uint16_t GestionMCP45HVX1::getValue(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	write8(GestionMCP45HVX1::WIPER | GestionMCP45HVX1::READ);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	// 2 octets dont le premier sera toujours à 0
	readBlock(2);
	return (getBlock()[1] * potValue) / MAX_INT_VALUE;
}

// *****************************************
// Positionne la valeur du potentiometre
// @Param la valeur du potentiometre en ohm)
// @Return true si ok, false si erreur
// *****************************************
bool GestionMCP45HVX1::setValue(uint16_t pValue) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", pValue);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return(write8(GestionMCP45HVX1::WIPER | GestionMCP45HVX1::WRITE, (pValue * MAX_INT_VALUE) / potValue));
}

//***********************************
// Increment le potentiometre
// @Return la valeur du potentiometre
// **********************************
uint16_t GestionMCP45HVX1::increment(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	write8(GestionMCP45HVX1::WIPER | GestionMCP45HVX1::INCREMENT);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	return getValue();
}

//***********************************
// Decrement le potentiometre
// @Return la valeur du potentiometre
// **********************************
uint16_t GestionMCP45HVX1::decrement(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	write8(GestionMCP45HVX1::WIPER | GestionMCP45HVX1::DECREMENT);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	return getValue();
}

// ***********************************
// Connect le potentiometre
// @Return true si ok, false si erreur
// ***********************************
bool GestionMCP45HVX1::connect(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return(write8(GestionMCP45HVX1::TCON | GestionMCP45HVX1::WRITE, CONNECT));
}

// ***********************************
// Déconnecte le potentiometre
// @Return true si ok, false si erreur
// ***********************************
bool GestionMCP45HVX1::disconnect(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return(write8(GestionMCP45HVX1::TCON | GestionMCP45HVX1::WRITE, DISCONNECT));
}

// ************************************
// Connect le potentiometre en rhéostat
// @Return true si ok, false si erreur
// ************************************
bool GestionMCP45HVX1::rheostat(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return(write8(GestionMCP45HVX1::TCON | GestionMCP45HVX1::WRITE, RHEOSTAT));
}

//***********************************
// Donne la valeur du registre TCON
// @Return la valeur du registre TCON
// **********************************
uint8_t GestionMCP45HVX1::readTCON(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	write8(GestionMCP45HVX1::TCON | GestionMCP45HVX1::READ);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	// 2 octets dont le premier sera toujours à 0
	readBlock(2);
	return (getBlock()[1]);
}

// ***********
// Destructeur
// ***********
GestionMCP45HVX1::~GestionMCP45HVX1(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

#endif
