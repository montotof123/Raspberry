/*
 * GestionMCP42010.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP42010
 */

#ifndef GESTIONMCP42010_H_
#define GESTIONMCP42010_H_

#include "GestionMCP42xxx.h"

// Classe de gestion du MCP42010
class GestionMCP42010 : public GestionMCP42xxx {
public:
	GestionMCP42010(void);
	GestionMCP42010(Channel);
	GestionMCP42010(Channel, PinGPIO);
	GestionMCP42010(Channel, PinGPIO, PinGPIO);
	bool init(Channel);
	bool init(Channel, PinGPIO);
	bool init(Channel, PinGPIO, PinGPIO);
	
	virtual ~GestionMCP42010();
};

#endif /* GESTIONMCP42010_H_ */
