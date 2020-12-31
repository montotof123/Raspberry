/*!
 *   \file    GestionDS1307.cpp
 *   \brief   Classe de gestion de l'horloge DS1307.
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    09/02/2020
 */
 
#include "GestionDS1307.h"
#include "Logger.h"

#define ADRESSE 0x68

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur qui initialise l'I2C ainsi que la date et l'heure courante.
 */
GestionDS1307::GestionDS1307(void) 
{
	Logger::log("DEBUG", "--> GestionDS1307::GestionDS1307(void)");
	
	time_t rawtime;
	time(&rawtime);
	timeinfo = localtime (&rawtime);

	initI2CPeripheric(ADRESSE);
	setDateTime(timeinfo);
	
	Logger::log("DEBUG", "<-- GestionDS1307::GestionDS1307(void)");	
}

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur qui initialise l'I2C ainsi que la date et l'heure courante.
 *
 * \param   pTimeinfo La date et l'heure dans une structure tm
 */
GestionDS1307::GestionDS1307(struct tm * pTimeinfo) 
{
	Logger::log("DEBUG", "--> GestionDS1307::GestionDS1307(struct tm * pTimeinfo)");

	initI2CPeripheric(ADRESSE);
	setDateTime(pTimeinfo);
	
	Logger::log("DEBUG", "<-- GestionDS1307::GestionDS1307(struct tm * pTimeinfo)");	
}

/**
 * \brief   Donne la date et l'heure dans une structure tm. 
 *
 * \return  La date et l'heure dans une structure tm
 */
struct tm * GestionDS1307::getDateTime(void) 
{
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
	
	mktime(timeinfo); // Positionne wday et yday

	Logger::log("DEBUG", "<-- struct tm * GestionDS1307::getDateTime(void)");	
	
	return timeinfo;
}

/**
 * \brief   Positionne la date et l'heure du module.
 *
 * \param   pTimeinfo La date et l'heure dans une structure tm
 */
void GestionDS1307::setDateTime(struct tm * pTimeinfo) 
{
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

/**
 * \brief   Convertit décimal en BCD.
 *
 * \param   pData la valeur a convertir
 * \return  la valeur convertie
 */
uint8_t GestionDS1307::decToBcd(uint8_t pData) 
{
	Logger::log("DEBUG", "--> uint8_t GestionDS1307::decToBcd(uint8_t pData)");
	Logger::log("DEBUG", "  pData = ", false);
	Logger::logHex("DEBUG", pData);	
	Logger::log("DEBUG", "  result = ", false);
	Logger::logHex("DEBUG", (uint8_t)(((pData / 10) << 4) | (pData % 10)));	
	Logger::log("DEBUG", "<-- uint8_t GestionDS1307::decToBcd(uint8_t pData)");	

	return ((pData / 10) << 4) | (pData % 10);
}

/**
 * \brief   Convertit BCD en décimal.
 *
 * \param   pData la valeur a convertir
 * \return  la valeur convertie
 */
uint8_t GestionDS1307::bcdToDec(uint8_t pData) 
{
	Logger::log("DEBUG", "--> uint8_t GestionDS1307::bcdToDec(uint8_t pData)");
	Logger::log("DEBUG", "  pData = ", false);
	Logger::logHex("DEBUG", pData);	
	Logger::log("DEBUG", "  result = ", false);
	Logger::logHex("DEBUG", (uint8_t)((((pData & 0x70) >> 4) * 10) + (pData & 0x0F)));	
	Logger::log("DEBUG", "<-- uint8_t GestionDS1307::bcdToDec(uint8_t pData)");	

	return (((pData & 0x70) >> 4) * 10) + (pData & 0x0F);
}

/**
 * \brief   Programmation de la sortie SQW/OUT.
 *
 * \param   pOutput paramètre de sortie
 */
void GestionDS1307::setOutput(Output pOutput) 
{
	Logger::log("DEBUG", "--> void GestionDS1307::setOutput(Output pOutput)");
	Logger::log("DEBUG", "  pOutput = ", false);
	Logger::log("DEBUG", pOutput);	

	write8(CONTROL, pOutput);
	
	Logger::log("DEBUG", "<-- void GestionDS1307::setOutput(Output pOutput)");	
}

/**
 * \brief   Stockage d'une valeur en mémoire.
 *
 * \param   pAdresse adresse
 * \param   pData data
 */
void GestionDS1307::setData(uint8_t pAdresse, uint8_t pData) 
{
	Logger::log("DEBUG", "--> void GestionDS1307::setData(uint8_t pAdresse, uint8_t pData)");
	Logger::log("DEBUG", "  pAdresse = ", false);
	Logger::log("DEBUG", pAdresse);	
	Logger::log("DEBUG", "  pData = ", false);
	Logger::log("DEBUG", pData);	

	write8(pAdresse, pData);
	
	Logger::log("DEBUG", "<-- void GestionDS1307::setData(uint8_t pAdresse, uint8_t pData)");	
}

/**
 * \brief   Lecture d'une valeur en mémoire.
 *
 * \param   pAdresse adresse
 * \return  data
 */
uint8_t GestionDS1307::getData(uint8_t pAdresse) 
{
	Logger::log("DEBUG", "--> uint8_t GestionDS1307::getData(uint8_t pAdresse)");
	Logger::log("DEBUG", "  pAdresse = ", false);
	Logger::log("DEBUG", pAdresse);	
	Logger::log("DEBUG", "<-- uint8_t GestionDS1307::getData(uint8_t pAdresse)");	
	
	return read8(pAdresse);
}

/**
 * \brief   Destructeur. 
 *
 * \note    Appelé automatiquement à la fin du programme
 */
GestionDS1307::~GestionDS1307(void) 
{
	Logger::log("DEBUG", "--> virtual GestionDS1307::~GestionDS1307(void)");
	Logger::log("DEBUG", "<-- virtual GestionDS1307::~GestionDS1307(void)");
}

/*! \class GestionDS1307
 *  \brief Class de gestion du DS1307.
 *  \note https://datasheets.maximintegrated.com/en/ds/DS1307.pdf
 *
 */

