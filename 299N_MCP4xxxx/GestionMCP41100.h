/*
 * GestionMCP41100.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP41100
 */

#ifndef GESTIONMCP41100_H_
#define GESTIONMCP41100_H_

#include "GestionMCP41xxx.h"

// Classe de gestion du MCP41100
class GestionMCP41100 : public GestionMCP41xxx {
public:
	GestionMCP41100(void);
	GestionMCP41100(Channel);
	bool init(Channel);
	
	virtual ~GestionMCP41100();
};

#endif /* GESTIONMCP41100_H_ */
