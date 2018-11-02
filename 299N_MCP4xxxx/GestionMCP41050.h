/*
 * GestionMCP41050.h
 *
 *  Created on: 07 octobre 2018
 *      Author: totof
 * Controle des MCP41050
 */

#ifndef GESTIONMCP41050_H_
#define GESTIONMCP41050_H_

#include "GestionMCP41xxx.h"

// Classe de gestion du MCP41050
class GestionMCP41050 : public GestionMCP41xxx {
public:
	GestionMCP41050(void);
	GestionMCP41050(Channel);
	bool init(Channel);
	
	virtual ~GestionMCP41050();
};

#endif /* GESTIONMCP41050_H_ */
