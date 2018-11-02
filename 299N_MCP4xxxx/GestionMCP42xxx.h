/*
 * GestionMCP42xxx.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP42010, MCP42050 et MCP42100
 */

#ifndef GESTIONMCP42xxx_H_
#define GESTIONMCP42xxx_H_

#include <stdint.h>
#include "GestionPinGPIO.h"
#include "GestionMCP41xxx.h"

enum Pot {
  pot0     = 0b00000001,
  pot1     = 0b00000010,
  potTwice = 0b00000011
};

// Classe de gestion des MCP42010, MCP42050 et MCP42100
class GestionMCP42xxx : public GestionMCP41xxx {
public:
	GestionMCP42xxx(void);
	GestionMCP42xxx(Channel, float);
	GestionMCP42xxx(Channel, float, PinGPIO);
	GestionMCP42xxx(Channel, float, PinGPIO, PinGPIO);
	bool init(Channel, float);
	bool init(Channel, float, PinGPIO);
	bool init(Channel, float, PinGPIO, PinGPIO);
	bool softShutdown(Pot);
	bool increment(Pot, float);
	bool decrement(Pot, float);
	bool setCurrentValue(Pot, float);
	float getCurrentValue(Pot);
	bool hardShutdownIn(void);
	bool hardShutdownOut(void);
	bool hardReset(void);
	
	virtual ~GestionMCP42xxx();
private:
	float currentPot1Value;
	GestionPinGPIO shutdown;
	GestionPinGPIO reset;
	bool isReset(void);
	bool isShutdown(void);
	bool useReset = false;
	bool useShutdown = false;;
};

#endif /* GESTIONMCP42xxx_H_ */
