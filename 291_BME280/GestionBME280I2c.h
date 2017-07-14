/*
 * GESTIONBME280I2c.h
 *
 *  Created on: 26 mai 2017
 *      Author: totof
 */

#ifndef GESTIONBME280I2C_H_
#define GESTIONBME280I2C_H_

#include "GestionBME280.h"

enum Adresse {
	Adr_Low = 0x76,
	Adr_High = 0x77
};

namespace std {

// Classe de gestion du BME280 en I2C
class GestionBME280I2c : public GestionBME280 {
public:
	GestionBME280I2c(Adresse);

	virtual ~GestionBME280I2c();
	
private:
	int fd;
	uint8_t read(Register);
	void write(Register, uint8_t);
};

} /* namespace std */

#endif /* GESTIONBME280I2C_H_ */
