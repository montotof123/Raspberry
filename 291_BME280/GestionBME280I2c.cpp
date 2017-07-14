/*
 * GestionBME280Spi.cpp
 *
 *  Created on: 27 may 2017
 *      Author: totof
 * Controle un BME280 en SPI avec la librairie wiringPi sur Raspberry Pi
 */
 
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "GestionBME280I2c.h"
#include <stdlib.h>

namespace std {

// ***********************************************
// Constructeur
// @param pChannel le channel
// Mémorise le canal et initialise le SPI
// ***********************************************
GestionBME280I2c::GestionBME280I2c(Adresse pAdresse) {
	fd = wiringPiI2CSetup (pAdresse);
	init();
}

// ****************************
// Lit la valeur d'un registre
// @param pRegistre le registre
// @return la valeur lue
// ****************************
uint8_t GestionBME280I2c::read(Register pRegistre) {
	return (uint8_t)wiringPiI2CReadReg8 (fd, pRegistre) ;
}

// *********************************
// Ecrit une valeur dans un registre
// @param pRegistre le registre
// @param la valeur a ecrire
// *********************************
void GestionBME280I2c::write(Register pRegistre, uint8_t pValeur) {
	wiringPiI2CWriteReg8 (fd, pRegistre, pValeur);
}

// ***********************************************
// Destructeur
// Met les deux ports en entree pour les securiser
// ***********************************************
GestionBME280I2c::~GestionBME280I2c() {
}

} /* namespace std */
