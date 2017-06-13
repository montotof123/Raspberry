/*
 * GestionPinPWM.h
 *
 *  Created on: 23 décembre 2016
 *      Author: totof
 */

#ifndef GESTIONPINPWM_H_
#define GESTIONPINPWM_H_

#include <wiringPi.h>
#include "GestionPin.h"

// Liste des pin
enum PinPWM {
  PWM_GPIO18 = 18
};

// Liste des mode
enum ModePWM {
    PwmModeBal = PWM_MODE_BAL,
    PwmModeMs = PWM_MODE_MS
};

// Classe de gestion des GPIO
class GestionPinPWM : public GestionPin{
public:
	GestionPinPWM();
	GestionPinPWM(PinPWM);
	void init(PinPWM);
    int setMode(ModePWM);
	ModePWM getMode(void);
    int setDiviseur(unsigned int);
	unsigned int getDiviseur(void);
    int setPrecision(unsigned int);
	unsigned int getPrecision(void);
	unsigned int getPrecisionMax(void);
	int setValue(unsigned int);
	unsigned int getValue(void);
	virtual ~GestionPinPWM();

private:
	int pwmValue;
	int pinNumber;
    int precision;
	int diviseur;
	ModePWM mode;
};

#endif /* GESTIONPINPWM_H_ */
