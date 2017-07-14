/*
 * GESTIONBME280Spi.h
 *
 *  Created on: 26 mai 2017
 *      Author: totof
 */

#ifndef GESTIONBME280SPI_H_
#define GESTIONBME280SPI_H_

#include "GestionSPI.h"
#include "GestionBME280.h"

namespace std {

// Classe de gestion du BME280 en SPI
class GestionBME280Spi : public GestionBME280 {
public:
	GestionBME280Spi(Channel);
	GestionBME280Spi(Channel, Frequence);

	virtual ~GestionBME280Spi();
	
private:
	Channel channel;
	uint8_t read(Register);
	void write(Register, uint8_t);
};

} /* namespace std */

#endif /* GESTIONBME280SPI_H_ */
