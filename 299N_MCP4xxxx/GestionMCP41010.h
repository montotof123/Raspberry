/*
 * GestionMCP41010.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP41010
 */

#ifndef GESTIONMCP41010_H_
#define GESTIONMCP41010_H_

#include "GestionMCP41xxx.h"

// Classe de gestion du MCP41010
class GestionMCP41010 : public GestionMCP41xxx {
public:
	GestionMCP41010(void);
	GestionMCP41010(Channel);
	bool init(Channel);
	
	virtual ~GestionMCP41010();
};

#endif /* GESTIONMCP41010_H_ */
