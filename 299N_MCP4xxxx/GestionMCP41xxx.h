/*
 * GestionMCP41xxx.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP41010, MCP41050 et MCP41100
 */

#ifndef GESTIONMCP41xxx_H_
#define GESTIONMCP41xxx_H_

#include <stdint.h>
#include "GestionSPI16.h"

enum Command {
  shutdownCmd  = 0b00100000,
  writeDataCmd = 0b00010000
};

// Classe de gestion des MCP41010, MCP41050 et MCP41100
class GestionMCP41xxx : public GestionSPI16 {
public:
	GestionMCP41xxx(void);
	GestionMCP41xxx(Channel, float);
	bool init(Channel, float);
	bool softShutdown(void);
	bool increment(float);
	bool decrement(float);
	bool setCurrentValue(float);
	float getPotValue(void);
	float getCurrentValue(void);
	virtual ~GestionMCP41xxx();
protected:
	float potValue;
	float currentPot0Value;
};

#endif /* GESTIONMCP41xxx_H_ */
