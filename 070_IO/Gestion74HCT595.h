/*
 * Gestion74HCT595.h
 *
 *  Created on: 15 december 2017
 *      Author: totof
 * Controle un circuit 74HCT595
 */

#ifndef _GESTION_74HCT595_H_
#define _GESTION_74HCT595_H_

#include <stdint.h>
#include "GestionPinGPIO.h"

enum Pin {
	Pin0 = 0,
	Pin1 = 1,
	Pin2 = 2,
	Pin3 = 3,
	Pin4 = 4,
	Pin5 = 5,
	Pin6 = 6,
	Pin7 = 7
};

enum PinHight {
	PinHight0 = 0b10000000,
	PinHight1 = 0b01000000,
	PinHight2 = 0b00100000,
	PinHight3 = 0b00010000,
	PinHight4 = 0b00001000,
	PinHight5 = 0b00000100,
	PinHight6 = 0b00000010,
	PinHight7 = 0b00000001
};

enum PinLow {
	PinLow0 = 0b01111111,
	PinLow1 = 0b10111111,
	PinLow2 = 0b11011111,
	PinLow3 = 0b11101111,
	PinLow4 = 0b11110111,
	PinLow5 = 0b11111011,
	PinLow6 = 0b11111101,
	PinLow7 = 0b11111110
};

class Gestion74HCT595 {
	public:
		Gestion74HCT595();
		Gestion74HCT595(PinGPIO, PinGPIO, PinGPIO, bool);
		void init(PinGPIO, PinGPIO, PinGPIO, bool);
		void write(bool);
		void scroll(void);
		void latch(void);
		void write(uint8_t);
		void write(char);
		void hight(PinHight);
		void hight(uint8_t);
		void low(PinLow);
		void low(uint8_t);
		
	private:
		GestionPinGPIO gpioData;
		GestionPinGPIO gpioClock;
		GestionPinGPIO gpioLatch;
};

#endif