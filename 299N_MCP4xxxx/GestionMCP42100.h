/*
 * GestionMCP42100.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP42100
 */

#ifndef GESTIONMCP42100_H_
#define GESTIONMCP42100_H_

#include "GestionMCP42xxx.h"

// Classe de gestion du MCP42100
class GestionMCP42100 : public GestionMCP42xxx {
public:
	GestionMCP42100(void);
	GestionMCP42100(Channel);
	GestionMCP42100(Channel, PinGPIO);
	GestionMCP42100(Channel, PinGPIO, PinGPIO);
	bool init(Channel);
	bool init(Channel, PinGPIO);
	bool init(Channel, PinGPIO, PinGPIO);
	
	virtual ~GestionMCP42100();
};

#endif /* GESTIONMCP42100_H_ */
