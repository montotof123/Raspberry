/*
 * GestionSPI.h
 *
 *  Created on: 15 octobre 2016
 *      Author: totof
 * Controle un SPI avec la librairie wiringPi sur Raspberry Pi
 */

#ifndef GESTIONSPI_H_
#define GESTIONSPI_H_

enum Channel
{
	channel_0 = 0,
	channel_1 = 1
};

// Frequence SPI
enum Frequence
{
	speed_27  = 1000000,
	speed_33  = 1250000,
	speed_50  = 2000000,
	speed_max = 6000000
};

#endif /* GESTIONSPI_H_ */
