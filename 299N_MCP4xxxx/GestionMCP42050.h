/*
 * GestionMCP42050.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP42050
 */

#ifndef GESTIONMCP42050_H_
#define GESTIONMCP42050_H_

#include "GestionMCP42xxx.h"

// Classe de gestion du MCP42050
class GestionMCP42050 : public GestionMCP42xxx {
public:
	GestionMCP42050(void);
	GestionMCP42050(Channel);
	GestionMCP42050(Channel, PinGPIO);
	GestionMCP42050(Channel, PinGPIO, PinGPIO);
	bool init(Channel);
	bool init(Channel, PinGPIO);
	bool init(Channel, PinGPIO, PinGPIO);
	
	virtual ~GestionMCP42050();
};

#endif /* GESTIONMCP42050_H_ */
