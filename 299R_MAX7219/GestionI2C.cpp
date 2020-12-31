/*!
 *   \file    GestionI2C.cpp
 *   \brief   Classe de gestion de l'interface I2C
 *   \note    Version utilisant la librairie pigpio
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    09/02/2020
 */
 
#include <pigpio.h>
#include <unistd.h>

#include "GestionI2C.h"
#include "Logger.h"

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur vide.
 *
 * \note    La méthode initI2CPeripheric devra être appelé explicitement pour initialiser l'interface I2C.
 */
GestionI2C::GestionI2C() 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur standard.
 *
 * \note    Appel automatiquement la méthode d'initialisation de l'interface I2C.
 *
 * \param   pAddress L'adresse du circuit.
 */
GestionI2C::GestionI2C(uint16_t pAddress) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pAddress = ", false);
	Logger::log("DEBUG", pAddress);	

	initI2CPeripheric(pAddress);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

/**
 * \brief   Initialisation si constructeur vide appelé. 
 *
 * \details Initialise la librairie pigpio et l'I2C.
 *
 * \note    Appelé automatiquement avec le constructeur standard, doit être appelé explicitement avec le constructeur vide.
 *
 * \param   pAddress L'adresse du circuit.
 */
void GestionI2C::initI2CPeripheric(uint16_t pAddress) 
{
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

/**
 * \brief   L'I2C est t'il initialise. 
 *
 * \details Renseigné dans la méthode initI2CPeripheric.
 *
 * \return  true si oui false si non.
 */
bool GestionI2C::isInitialize(void) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " initialize = ", false);
	Logger::log("DEBUG", initialize);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return initialize;
}

/**
 * \brief   Lecture d'une valeur 8 bits dans un circuit sans registre. 
 *
 * \return  Valeur true si positif, erreur si negatif   L'adresse du circuit.
 */
int8_t GestionI2C::read8(void) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	int8_t value = i2cReadByte (handle);
	Logger::log("DEBUG", " value = ", false);
	Logger::log("DEBUG", value);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return value;
}

/**
 * \brief   Lecture d'une série de valeur 8 bits dans un circuit sans registre. 
 *
 * \note    Les valeurs sont stockées dans le tableau block qui peut être lu par la méthode getBlock
 *
 * \param   pNbValues Le nombre de valeurs à lire (entre 1 et 32).
 *
 * \return  Le nombre de valeurs true si positif, erreur si negatif.
 *
 * \attention Paramètre entre 1 et 32
 */
int8_t GestionI2C::readBlock(uint8_t pNbValues) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pNbValues = ", false);
	Logger::log("DEBUG", pNbValues);

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

/**
 * \brief   Getter du bloc d'octets. 
 *
 * \note    Bloc d'octets lus dans la méthode readBlock.
 *
 * \return  Un pointeur sur le bloc d'octet.
 */
char* GestionI2C::getBlock(void) 
{
	return block;
}

/**
 * \brief   Ecriture d'une valeur 8 bits dans un circuit sans registre. 
 *
 * \param   pData La valeur a ecrire.
 * \return  true si ok, false si erreur
 */
bool GestionI2C::write8(uint8_t pData) 
{
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

/**
 * \brief   Lecture d'une valeur 8 bits dans un circuit avec registres. 
 *
 * \param   pReg Le registre.
 * \return  La valeur true si positif, erreur si negatif
 */
int8_t GestionI2C::read8(uint8_t pReg) 
{
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

/**
 * \brief   Ecriture d'une valeur 8 bits dans un circuit avec registres. 
 *
 * \param   pReg Le registre.
 * \param   pData La valeur a écrire.
 * \return  true si ok, false si erreur.
 */
bool GestionI2C::write8(uint8_t pReg, uint8_t pData) 
{
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

/**
 * \brief   Lecture d'une valeur 16 bits dans un circuit avec registres. 
 *
 * \param   pReg Le registre.
 * \return  Valeur true si positif, erreur si negatif
 */
int16_t GestionI2C::read16(uint8_t pReg) 
{
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

/**
 * \brief   Ecriture d'une valeur 16 bits dans un circuit avec registres. 
 *
 * \param   pReg Le registre.
 * \param   pData La valeur a écrire.
 * \return  true si ok, false si erreur.
 */
bool GestionI2C::write16(uint8_t pReg, uint16_t pData) 
{
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
	
/**
 * \brief   Lecture d'une valeur 16 bits dans un circuit avec registres. 
 *
 * \note    Les deux octets sont swappés après lecture.
 *
 * \param   pReg Le registre.
 * \return  Valeur true si positif, erreur si negatif.
 */
int16_t GestionI2C::read16Swapped(uint8_t pReg) 
{
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

/**
 * \brief   Ecriture d'une valeur 16 bits dans un circuit avec registres. 
 *
 * \note    Les deux octets sont swappés après lecture.
 *
 * \param   pReg Le registre.
 * \param   pVal La valeur a ecrire.
 * \return  true si ok, false si erreur.
 */
bool GestionI2C::write16Swapped(uint8_t pReg, uint16_t pVal) 
{
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
	
/**
 * \brief   swap les deux octets d'un tableau. 
 *
 * \param   data L'adresse du tableau.
 */
void GestionI2C::swap(i2cData &data) 
{
	int8_t temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}
	
/**
 * \brief   swap les deux octets non signés d'un tableau. 
 *
 * \param   data L'adresse du tableau.
 */
void GestionI2C::swapU(i2cUData &data) 
{
	uint8_t temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}
	
/**
 * \brief   Destructeur. 
 *
 * \note    Appelé automatiquement à la fin du programme
 */
GestionI2C::~GestionI2C() 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	gpioTerminate();
	i2cClose(handle);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

/*! \class GestionI2C "GestionI2C.h"
 *  \brief Class de gestion de l'interface I2C.
 *
 */


