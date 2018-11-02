/*
 * GestionSPI16.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle du bus SPI avec mot de 16 bits
 */

#ifndef GESTIONSPI16_H_
#define GESTIONSPI16_H_

#include <stdint.h>
#include "GestionSPI.h"

// Classe de gestion du SPI avec mot de 16 bits
class GestionSPI16 {
public:
	GestionSPI16(void);
	GestionSPI16(Channel);
	GestionSPI16(Channel, Frequence);
	bool init(Channel);
	bool init(Channel, Frequence);
	virtual ~GestionSPI16();

protected:
	union spiData{
		uint16_t uSData;
		uint8_t uCData[2];
	};	
	
	Channel channel;
	bool write(uint16_t);
	void swap(spiData &);
};

#endif /* GESTIONSPI16_H_ */