/*!
 *   \file    GestionDS1307.h
 *   \brief   Entete de la classe de gestion de l'horloge DS1307.
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    22/01/2020
 */
 
#ifndef GESTIONDS1307_H_
#define GESTIONDS1307_H_

#include "GestionI2C.h"
#include <time.h> 
#include <stdint.h>

class GestionDS1307 : GestionI2C {
public:
	/*! Liste des registres du circuit */
	enum Registers 
	{
		SECOND  = 0x00,	/*!< Les secondes */	
		MINUTE  = 0x01,	/*!< Les minutes */	
		HOUR    = 0x02,	/*!< Les heures */
		DAY     = 0x03,	/*!< Le jour de la semaine */
		DATE    = 0x04,	/*!< Le jour du mois */	
		MONTH   = 0x05,	/*!< Le mois */	
		YEAR    = 0x06,	/*!< L'année */	
		CONTROL = 0x07  /*!< Control */
	};
		
	/*! Liste des fréquences et niveaux sur la sortie SQW/OUT */
	enum Output 
	{
		_1Hz     = 0b00010000, /*!< 1 Hz */
		_4O96Hz  = 0b00010001, /*!< 4096 Hz */
		_8192Hz  = 0b00010010, /*!< 8192 Hz */
		_32768Hz = 0b00010011, /*!< 32768 Hz */
		_0       = 0b00000000, /*!< Toujours à 0 */
		_1       = 0b10000000  /*!< Toujours à 1 */
	};

	GestionDS1307(void);
	GestionDS1307(struct tm *);
	
	void setOutput(Output);
	
	void setDateTime(struct tm *);
	
	struct tm * getDateTime(void);

	uint8_t getData(uint8_t);
	
	void setData(uint8_t, uint8_t);
	
	virtual ~GestionDS1307();

private:
	uint8_t decToBcd(uint8_t);
	uint8_t bcdToDec(uint8_t);
	struct tm * timeinfo;
};

#endif 
