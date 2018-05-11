/*
 * GESTIONMCP6S22.h
 *
 *  Created on: 10 may 2018
 *      Author: totof
 */

#ifndef GESTIONMCP6S22_H_
#define GESTIONMCP6S22_H_

#include "GestionMCP6S21.h"

namespace std {

// Classe de gestion du MCP6S2x
class GestionMCP6S22  : public GestionMCP6S21 {
public:
	enum In {
		In_0 = 0b00000000,
		In_1 = 0b00000001
	};

	GestionMCP6S22(Channel);
	GestionMCP6S22(Channel, Frequence);
	void setCanal(In);
};

} /* namespace std */

#endif /* GESTIONMCP6S22_H_ */
