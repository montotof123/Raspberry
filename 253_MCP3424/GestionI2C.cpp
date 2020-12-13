/*
 * GestionI2C.cpp
 * Version pigpio
 *
 * Created on 23/11/2020
 * Author Totof
 *
 */

#include <pigpio.h>
#include <unistd.h>

#include "GestionI2C.h"
#include "Logger.h"

// *****************
// Constructeur vide
// *****************
GestionI2C::GestionI2C() {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

// *************************
// Constructeur
// @param adresse du circuit 
// *************************
GestionI2C::GestionI2C(uint16_t pAddress) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pAddress = ", false);
	Logger::log("DEBUG", pAddress);	

	initI2CPeripheric(pAddress);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

// ******************************************
// Initialisation si constructeur vide appele
// @param adresse du circuit 
// ******************************************
void GestionI2C::initI2CPeripheric(uint16_t pAddress) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pAddress = ", false);
	Logger::log("DEBUG", pAddress);	

	gpioInitialise();
	handle = i2cOpen(1, pAddress, 0);
	initialize = true;
	if(handle < 0) {
		initialize = false;
	}

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

// ********************************
// L'I2C est t'il initialise
// @return true si oui false si non
// ********************************
bool GestionI2C::isInitialize(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " initialize = ", false);
	Logger::log("DEBUG", initialize);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return initialize;
}
// **************************************************
// Lecture d'une valeur dans un circuit sans registre
// @return valeur lue si positif, erreur si negatif
// **************************************************
int8_t GestionI2C::read8(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	int8_t value = i2cReadByte (handle);
	Logger::log("DEBUG", " value = ", false);
	Logger::log("DEBUG", value);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return value;
}

// **************************************************************
// Lecture d'une série de valeur dans un circuit sans registre
// @Param le nombre de valeurs à lire (entre 1 et 32)
// @return le nombre de valeurs lue si positif, erreur si negatif
// **************************************************************
int8_t GestionI2C::readBlock(uint8_t pNbValues) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pNbValues = ", false);
	Logger::log("DEBUG", pNbValues);

	// Erreur de paramètre
	if(pNbValues > 32) {
		return(ERROR);
	}

	int8_t value = i2cReadDevice (handle, block, pNbValues);
	Logger::log("DEBUG", " value = ", false);
	Logger::log("DEBUG", value);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return value;
}

// *************************
// Getter du block d'octets
// @Return le block d'octets
// *************************
char* GestionI2C::getBlock(void) {
	return block;
}

// ***************************************************
// Ecriture d'une valeur dans un circuit sans registre
// @param la valeur a ecrire
// @return true si ok, false si erreur
// ***************************************************
bool GestionI2C::write8(uint8_t pData) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pData = ", false);
	Logger::log("DEBUG", pData);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	if(i2cWriteByte (handle, pData) == 0) {
		return true;
	} else {
		return false;
	}
}

// ***************************************************
// Lecture d'une valeur dans un circuit avec registres
// @param le registre
// @return valeur lue si positif, erreur si negatif
// ***************************************************
int8_t GestionI2C::read8(uint8_t pReg) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pReg = ", false);
	Logger::log("DEBUG", pReg);	

	int8_t value = i2cReadByteData (handle, pReg); 

	Logger::log("DEBUG", " value = ", false);
	Logger::log("DEBUG", value);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return value;
}

// ****************************************************
// Ecriture d'une valeur dans un circuit avec registres
// @param le registre
// @param la valeur a ecrire
// @return true si ok, false si erreur
// ****************************************************
bool GestionI2C::write8(uint8_t pReg, uint8_t pData) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pReg = ", false);
	Logger::log("DEBUG", pReg);	

	Logger::log("DEBUG", " pData = ", false);
	Logger::log("DEBUG", pData);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	if(i2cWriteByteData (handle, pReg, pData) == 0) {
		return true;
	} else {
		return false;
	}
}

// ***************************************************
// Lecture d'une valeur dans un circuit avec registres
// @param le registre
// @return valeur lue si positif, erreur si negatif
// ***************************************************
int16_t GestionI2C::read16(uint8_t pReg) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pReg = ", false);
	Logger::log("DEBUG", pReg);	
	
	int16_t value = i2cReadWordData (handle, pReg);

	Logger::log("DEBUG", " value = ", false);
	Logger::log("DEBUG", value);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return value;
}

// ****************************************************
// Ecriture d'une valeur dans un circuit avec registres
// @param le registre
// @param la valeur a ecrire
// @return true si ok, false si erreur
// ****************************************************
bool GestionI2C::write16(uint8_t pReg, uint16_t pData) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pReg = ", false);
	Logger::log("DEBUG", pReg);	

	Logger::log("DEBUG", " pData = ", false);
	Logger::log("DEBUG", pData);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	if(i2cWriteWordData (handle, pReg, pData) == 0) {
		return true;
	} else {
		return false;
	}
}
	
// ***************************************************
// Lecture d'une valeur dans un circuit avec registres
// Les deux octets sont swappe apres lecture
// @param le registre
// @return valeur lue si positif, erreur si negatif
// ***************************************************
int16_t GestionI2C::read16Swapped(uint8_t pReg) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pReg = ", false);
	Logger::log("DEBUG", pReg);	

	i2cData data;
	data.uSData = i2cReadWordData (handle, pReg);
	swap(data);

	Logger::log("DEBUG", " data.uSData = ", false);
	Logger::log("DEBUG", data.uSData);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return data.uSData;
}

// ****************************************************
// Ecriture d'une valeur dans un circuit avec registres
// Les deux octets sont swappe avant l'ecriture
// @param le registre
// @param la valeur a ecrire
// @return true si ok, false si erreur
// ****************************************************
bool GestionI2C::write16Swapped(uint8_t pReg, uint16_t pVal) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pReg = ", false);
	Logger::log("DEBUG", pReg);	

	Logger::log("DEBUG", " pVal = ", false);
	Logger::log("DEBUG", pVal);	

	i2cUData data;
	data.uSData = pVal;
	swapU(data);

	Logger::log("DEBUG", " data.uSData = ", false);
	Logger::log("DEBUG", data.uSData);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	if(i2cWriteWordData (handle, pReg, data.uSData) == 0) {
		return true;
	} else {
		return false;
	}
}

	
// *********************************
// swap les deux octets d'un i2cData
// *********************************
void GestionI2C::swap(i2cData &data) {
	int8_t temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}
	
// **********************************
// swap les deux octets d'un i2cUData
// **********************************
void GestionI2C::swapU(i2cUData &data) {
	uint8_t temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}
	
// ***********
// Destructeur
// ***********
GestionI2C::~GestionI2C() {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	gpioTerminate();
	i2cClose(handle);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}


