/*
 * GestionDS1307.cpp
 *
 * Created on 09/02/2020
 * Author Totof
 *
 */

#include "GestionDS1307.h"
#include "Logger.h"

#define ADRESSE 0x68

// *****************
// Constructeur vide
// *****************
GestionDS1307::GestionDS1307(void) {
	Logger::log("DEBUG", "--> GestionDS1307::GestionDS1307(void)");
	
	time_t rawtime;
	time(&rawtime);
	timeinfo = localtime (&rawtime);

	initI2C();
	setDateTime(timeinfo);
	
	Logger::log("DEBUG", "<-- GestionDS1307::GestionDS1307(void)");	
}

// *************************
// Constructeur
// @Param la date et l'heure
// *************************
GestionDS1307::GestionDS1307(struct tm * pTimeinfo) {
	Logger::log("DEBUG", "--> GestionDS1307::GestionDS1307(struct tm * pTimeinfo)");

	initI2C();
	setDateTime(pTimeinfo);
	
	Logger::log("DEBUG", "<-- GestionDS1307::GestionDS1307(struct tm * pTimeinfo)");	
}

// ***********************
// Initialisation de l'I2C
// ***********************
void GestionDS1307::initI2C(void) {
	Logger::log("DEBUG", "--> void GestionDS1307::initI2C(void)");

	initI2CPeripheric(ADRESSE);
	
	Logger::log("DEBUG", "<-- void GestionDS1307::initI2C(void)");	
}

// **********************************
// Donne la date et l'heure du module
// @Return une structure tm
// **********************************
struct tm * GestionDS1307::getDateTime(void) {
	Logger::log("DEBUG", "--> struct tm * GestionDS1307::getDateTime(void)");

	Logger::log("DEBUG", " timeinfo->tm_mday = ", false);
	Logger::log("DEBUG", timeinfo->tm_mday);	
	timeinfo->tm_mday = bcdToDec(read8(DATE));	
	Logger::log("DEBUG", " timeinfo->tm_mon = ", false);
	Logger::log("DEBUG", timeinfo->tm_mon);	
	timeinfo->tm_mon = bcdToDec(read8(MONTH));
	Logger::log("DEBUG", " timeinfo->tm_year = ", false);
	Logger::log("DEBUG", timeinfo->tm_year);	
	timeinfo->tm_year = bcdToDec(read8(YEAR)) + 100;
	Logger::log("DEBUG", " timeinfo->tm_sec = ", false);
	Logger::log("DEBUG", timeinfo->tm_sec);	
	timeinfo->tm_sec = bcdToDec(read8(SECOND));	
	Logger::log("DEBUG", " timeinfo->tm_min = ", false);
	Logger::log("DEBUG", timeinfo->tm_min);	
	timeinfo->tm_min = bcdToDec(read8(MINUTE));
	Logger::log("DEBUG", " timeinfo->tm_hour = ", false);
	Logger::log("DEBUG", timeinfo->tm_hour);	
	timeinfo->tm_hour = bcdToDec(read8(HOUR));
	
	// Positionne wday et yday
	mktime(timeinfo);

	Logger::log("DEBUG", "<-- struct tm * GestionDS1307::getDateTime(void)");	
	
	return timeinfo;
}

// ***************************************
// Positionne la date et l'heure du module
// ***************************************
void GestionDS1307::setDateTime(struct tm * pTimeinfo) {
	Logger::log("DEBUG", "--> void GestionDS1307::setDateTime(struct tm * pTimeinfo)");

	Logger::log("DEBUG", " timeinfo->tm_sec = ", false);
	Logger::log("DEBUG", timeinfo->tm_sec);	
	write8(SECOND, decToBcd(timeinfo->tm_sec));
	Logger::log("DEBUG", " timeinfo->tm_min = ", false);
	Logger::log("DEBUG", timeinfo->tm_min);	
	write8(MINUTE, decToBcd(timeinfo->tm_min));
	Logger::log("DEBUG", " timeinfo->tm_hour = ", false);
	Logger::log("DEBUG", timeinfo->tm_hour);	
	write8(HOUR, decToBcd(timeinfo->tm_hour));
	Logger::log("DEBUG", " timeinfo->tm_mday = ", false);
	Logger::log("DEBUG", timeinfo->tm_mday);	
	write8(DATE, decToBcd(timeinfo->tm_mday));
	Logger::log("DEBUG", " timeinfo->tm_mon = ", false);
	Logger::log("DEBUG", timeinfo->tm_mon);	
	write8(MONTH, decToBcd(timeinfo->tm_mon));
	Logger::log("DEBUG", " timeinfo->tm_year = ", false);
	Logger::log("DEBUG", timeinfo->tm_year);	
	write8(YEAR, decToBcd(timeinfo->tm_year - 100));
	
	Logger::log("DEBUG", "<-- void GestionDS1307::setDateTime(struct tm * pTimeinfo)");	
}

// ****************************
// Convertit décimal en BCD
// @Param la valeur a convertir
// @Return la valeur convertie
// ****************************
uint8_t GestionDS1307::decToBcd(uint8_t data) {
	Logger::log("DEBUG", "--> uint8_t GestionDS1307::decToBcd(uint8_t data)");
	Logger::log("DEBUG", "  data = ", false);
	Logger::logHex("DEBUG", data);	
	Logger::log("DEBUG", "  result = ", false);
	Logger::logHex("DEBUG", (uint8_t)(((data / 10) << 4) | (data % 10)));	
	Logger::log("DEBUG", "<-- uint8_t GestionDS1307::decToBcd(uint8_t data)");	

	return ((data / 10) << 4) | (data % 10);
}

// ****************************
// Convertit BCD en décimal
// @Param la valeur a convertir
// @Return la valeur convertie
// ****************************
uint8_t GestionDS1307::bcdToDec(uint8_t data) {
	Logger::log("DEBUG", "--> uint8_t GestionDS1307::bcdToDec(uint8_t data)");
	Logger::log("DEBUG", "  data = ", false);
	Logger::logHex("DEBUG", data);	
	Logger::log("DEBUG", "  result = ", false);
	Logger::logHex("DEBUG", (uint8_t)((((data & 0x70) >> 4) * 10) + (data & 0x0F)));	
	Logger::log("DEBUG", "<-- uint8_t GestionDS1307::bcdToDec(uint8_t data)");	

	return (((data & 0x70) >> 4) * 10) + (data & 0x0F);
}

// **********************************
// Programmation de la sortie SQW/OUT
// @Param paramètre de sortie
// **********************************
void GestionDS1307::setOutput(Output pOutput) {
	Logger::log("DEBUG", "--> void GestionDS1307::setOutput(Output pOutput)");
	Logger::log("DEBUG", "  pOutput = ", false);
	Logger::log("DEBUG", pOutput);	

	write8(CONTROL, pOutput);
	
	Logger::log("DEBUG", "<-- void GestionDS1307::setOutput(Output pOutput)");	
}

// ********************************
// Stockage d'une valeur en mémoire
// @Param adresse
// @Param data
// ********************************
void GestionDS1307::setData(uint8_t adresse, uint8_t data) {
	Logger::log("DEBUG", "--> void GestionDS1307::setData(uint8_t adresse, uint8_t data)");
	Logger::log("DEBUG", "  adresse = ", false);
	Logger::log("DEBUG", adresse);	
	Logger::log("DEBUG", "  data = ", false);
	Logger::log("DEBUG", data);	

	write8(adresse, data);
	
	Logger::log("DEBUG", "<-- void GestionDS1307::setData(uint8_t adresse, uint8_t data)");	
}

// *******************************
// Lecture d'une valeur en mémoire
// @Param adresse
// @Return data
// *******************************
uint8_t GestionDS1307::getData(uint8_t adresse) {
	Logger::log("DEBUG", "--> uint8_t GestionDS1307::getData(uint8_t adresse)");
	Logger::log("DEBUG", "  adresse = ", false);
	Logger::log("DEBUG", adresse);	
	Logger::log("DEBUG", "<-- uint8_t GestionDS1307::getData(uint8_t adresse)");	
	
	return read8(adresse);
}

// ***********
// destructeur
// ***********
GestionDS1307::~GestionDS1307(void) {
	Logger::log("DEBUG", "--> virtual GestionDS1307::~GestionDS1307(void)");
	Logger::log("DEBUG", "<-- virtual GestionDS1307::~GestionDS1307(void)");
}


