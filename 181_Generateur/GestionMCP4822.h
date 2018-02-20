/*
 * GestionMCP4822.h
 *
 *  Created on: 19 octobre 2016
 *      Author: totof
 * Controle un MCP4822 avec la librairie wiringPi sur Raspberry Pi
 */

#ifndef GESTIONMCP4822_H_
#define GESTIONMCP4822_H_

#include <stdint.h>
#include "GestionSPI.h"

enum Dac
{
  A = 0x0000,
  B = 0x8000
};

enum Gain
{
  FOIS_1 = 0x2000,
  FOIS_2 = 0x0000
};

enum SHDN
{
  YES = 0x0000,
  NO = 0x1000
};

// Classe de gestion du MCP4822
class GestionMCP4822 {
public:
	GestionMCP4822(Channel);
	GestionMCP4822(Channel, Frequence);
	bool output(Dac, float);
	float getMaxValue(void);
	float getHighImpedance(void);
	virtual ~GestionMCP4822();

private:
	union spiData{
		unsigned short uSData;
		unsigned char uCData[2];
	};	
	
	Channel channel;
	bool write(Dac, unsigned short, Gain, SHDN);
	void swap(spiData &);
	
	const unsigned short MAX_VALUE = 4096;
	const float MID_VALUE = 2.048;
	const float HIGH_IMPEDANCE = 1000000;
};

#endif /* GESTIONMCP4822_H_ */
