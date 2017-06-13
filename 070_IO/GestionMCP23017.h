/*
 * GESTIONMCP23017.h
 *
 *  Created on: 14 novembre 2016
 *      Author: totof
 */

#ifndef GESTIONMCP23017_H_
#define GESTIONMCP23017_H_

#include "GestionSPI.h"
#include "GestionMCP23x17.h"

namespace std {

// Classe de gestion du MCP23017
class GestionMCP23017 : public GestionMCP23x17 {
public:
	GestionMCP23017(int);

	virtual ~GestionMCP23017();
	
private:
	int fd;
	unsigned char read(Registre);
	void write(Registre, unsigned char);
};

} /* namespace std */

#endif /* GESTIONMCP23017_H_ */
