/*
 * GESTIONMCP6S26.h
 *
 *  Created on: 10 may 2018
 *      Author: totof
 */

#ifndef GESTIONMCP6S26_H_
#define GESTIONMCP6S26_H_

#include "GestionMCP6S21.h"

namespace std {
	
// Classe de gestion du MCP6S2x
class GestionMCP6S26 : public GestionMCP6S21 {
public:

	enum In {
		In_0 = 0b00000000,
		In_1 = 0b00000001,
		In_2 = 0b00000010,
		In_3 = 0b00000011,
		In_4 = 0b00000100,
		In_5 = 0b00000101
	};

	GestionMCP6S26(Channel);
	GestionMCP6S26(Channel, Frequence);
	void setCanal(In);
};

} /* namespace std */

#endif /* GESTIONMCP6S26_H_ */
