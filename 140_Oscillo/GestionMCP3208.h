/*
 * GestionMCP3208.h
 *
 *  Created on: 2 août 2016
 *      Author: totof
 * Controle un MCP3208 avec la librairie wiringPi sur Raspberry Pi
 */

#ifndef GESTIONMCP3208_H_
#define GESTIONMCP3208_H_

#include <stdint.h>

#define VOIE_0	0
#define VOIE_1	1
#define VOIE_2	2
#define VOIE_3	3
#define VOIE_4	4
#define VOIE_5	5
#define VOIE_6	6
#define VOIE_7	7

#define	CHANNEL_0	0
#define	CHANNEL_1	1

#define	SPI_SPEED_27 1000000
#define	SPI_SPEED_33 1250000
#define	SPI_SPEED_50 2000000

#define NOMBRE_VALEUR 4096

#define ALIM_33 3.3
#define ALIM_5 5.0

namespace std {

// Classe de gestion du MCP3208
class GestionMCP3208 {
public:
	GestionMCP3208(int pChannel, int pSpeed);
	int readValue(uint8_t pVoie);
	float readTension(uint8_t pVoie, float pAlim);
	virtual ~GestionMCP3208();

private:
	int channel;
};

} /* namespace std */

#endif /* GESTIONMCP3208_H_ */
