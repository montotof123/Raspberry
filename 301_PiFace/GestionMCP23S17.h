/*
 * GESTIONMCP23S17.h
 *
 *  Created on: 13 novembre 2016
 *      Author: totof
 */

#ifndef GESTIONMCP23S17_H_
#define GESTIONMCP23S17_H_

#include "GestionSPI.h"
#include "GestionMCP23x17.h"

namespace std {

// Classe de gestion du MCP23S17
class GestionMCP23S17 : public GestionMCP23x17 {
public:
	GestionMCP23S17(Channel);
	GestionMCP23S17(Channel, Frequence);
	GestionMCP23S17(Channel, Adresse);
	GestionMCP23S17(Channel, Frequence, Adresse);

	virtual ~GestionMCP23S17();
	
private:
	Channel channel;
	Adresse adresse;
	unsigned char read(Registre);
	void write(Registre, unsigned char);
};

} /* namespace std */

#endif /* GESTIONMCP23S17_H_ */
