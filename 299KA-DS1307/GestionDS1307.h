/*
 * GestionDS1307.h
 *
 *  Created on: 22 janvier 2020
 *      Author: totof
 */

#ifndef GESTIONDS1307_H_
#define GESTIONDS1307_H_

#include "GestionI2C.h"
#include <time.h> 
#include <stdint.h>

// Classe de gestion du DS1307
class GestionDS1307 : GestionI2C {
public:
	enum Registers {
		SECOND  = 0x00,		
		MINUTE  = 0x01,		
		HOUR    = 0x02,		
		DAY     = 0x03,
		DATE    = 0x04,		
		MONTH   = 0x05,		
		YEAR    = 0x06,		
		CONTROL = 0x07
	};
		
	// Liste des formats
	enum Output {
		_1Hz     = 0b00010000,
		_4O96Hz  = 0b00010001,
		_8192Hz  = 0b00010010,
		_32768Hz = 0b00010011, 
		_0       = 0b00000000, 
		_1       = 0b10000000
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
	void initI2C(void);
	uint8_t decToBcd(uint8_t);
	uint8_t bcdToDec(uint8_t);
	struct tm * timeinfo;
};

#endif /* GESTIONDS1307_H_ */
