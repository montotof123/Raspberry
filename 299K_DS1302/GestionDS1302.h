/*
 * GestionDS1302.h
 *
 *  Created on: 08 juillet 2016
 *      Author: totof
 * Controle un circuit DS1302
 */

#ifndef _GESTION_DS1302_H_
#define _GESTION_DS1302_H_

#include "GestionPinGPIO.h"

class GestionDS1302 {
	public:
		GestionDS1302();
		GestionDS1302(PinGPIO, PinGPIO, PinGPIO);
		void init(PinGPIO, PinGPIO, PinGPIO);
		void getClock(void);
		unsigned int getSecondes(void);
		unsigned int getMinutes(void);
		unsigned int getHeures(void);
		unsigned int getJourMois(void);
		unsigned int getMois(void);
		unsigned int getAnnee(void);
		unsigned int getJourSemaine(void);
		unsigned int getInitSecondes(void);
		unsigned int getInitMinutes(void);
		unsigned int getInitHeures(void);
		unsigned int getInitJourMois(void);
		unsigned int getInitMois(void);
		unsigned int getInitAnnee(void);
		unsigned int getInitJourSemaine(void);
		unsigned int getDeltaSecondes(void);
		
	private:
		int initClock[8];
		int clock[8];
		unsigned int masks[7] = {0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x07, 0xFF};
		int bcdToD(unsigned int, unsigned int);
		long Datation (long, long, long);
};

#endif