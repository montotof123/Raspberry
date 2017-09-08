/*
 * GestionAD5220.h
 *
 *  Created on: 17 octobre 2016
 *      Author: totof
 * Controle un AD5220 avec la librairie wiringPi sur Raspberry Pi
 */

#ifndef GESTIONAD5220_H_
#define GESTIONAD5220_H_

#include "GestionPinGPIO.h"

namespace std {

// Classe de gestion du AD5220
class GestionAD5220 {
public:
	GestionAD5220(PinGPIO, PinGPIO, unsigned int);
	GestionAD5220(PinGPIO, PinGPIO, PinGPIO, unsigned int);
	bool increment(void);
	bool decrement(void);
	unsigned int read(void);
	bool write(unsigned int);
	unsigned int readOhm(void);
	bool writeOhm(unsigned int);
	void reInit(void);
	unsigned int getMinValue(void);
	unsigned int getMaxValue(void);
	bool isToDesactivate(void);
	void toDesactivate(void);
	void noDesactivate(void);
	virtual ~GestionAD5220();

private:
	unsigned int value;
	unsigned int valueOhm;
	GestionPinGPIO CS;
	GestionPinGPIO CLK;
	GestionPinGPIO UD;
	bool utilCS;
	void init(PinGPIO, PinGPIO);
	void activeCircuit(void);
	void deActiveCircuit(void);
	void pulseClock(void);
	void setToDesactivate(bool);
	bool desactivateFlag = true;
	
	// Valeur maximum du potentiometre
	static const unsigned int MAX_VALUE = 0x7F;
	// Valeur minimum du potentiometre
	static const unsigned int MIN_VALUE = 0x00;
	// Valeur de départ du potentiometre
	static const unsigned int START_VALUE = 0x00;
};

} /* namespace std */

#endif /* GESTIONAD5220_H_ */
