/*
 * GestionPinGPIO.h
 *
 *     Created on: 31/05/2020
 *         Author: totof
 * version 2 pour librairie PIGPIO
 */

#ifndef GESTIONPINGPIO_H_
#define GESTIONPINGPIO_H_

#include "GestionPin.h"

// Liste des pin
enum PinGPIO {
  GPIO02 = 2,
  GPIO03 = 3,
  GPIO04 = 4,
  GPIO17 = 17,
  GPIO27 = 27,
  GPIO22 = 22,
  GPIO10 = 10,
  GPIO09 = 9,
  GPIO11 = 11,
  GPIO05 = 5,
  GPIO06 = 6,
  GPIO13 = 13,
  GPIO19 = 19,
  GPIO26 = 26,
  GPIO14 = 14,
  GPIO15 = 15,
  GPIO18 = 18,
  GPIO23 = 23,
  GPIO24 = 24,
  GPIO25 = 25,
  GPIO08 = 8,
  GPIO07 = 7,
  GPIO12 = 12,
  GPIO16 = 16,
  GPIO20 = 20,
  GPIO21 = 21
};

// Liste des directions
enum PinDirection {
	In = PI_INPUT,
	Out = PI_OUTPUT
};

// Liste des résistances de rappel
enum Pud {
	Off = PI_PUD_OFF,
	Down = PI_PUD_DOWN,
	Up = PI_PUD_UP
};

// Liste des niveaux
enum Level {
	Low = 0,
	High = 1
};

// Classe de gestion des GPIO
class GestionPinGPIO : public GestionPin {
public:
	GestionPinGPIO();
	GestionPinGPIO(PinGPIO);
	void init(PinGPIO);
	int in(void);
	int out(void);
	int pullUp(void);
	int pullDn(void);
	int pullOff(void);
	int write(Level);
	int off(void);
	int on(void);
	int invertState(void);
	Level read(void);
	bool isOn(void);
	bool isOff(void);
	int fctInterrupt(CBFunc_t);
	int setPWMFrequency(int);
	int setPWMRange(int);
	int PWMOn(int);
	int PWMOn(void);
	int PWMOff(void);
	bool isToDesactivate(void);
	void toDesactivate(void);
	void noDesactivate(void);
	virtual ~GestionPinGPIO();

private:
	int pinNumber;
	int pinModePI(PinDirection);
	int pullUpDnControlPI(Pud);
	void setToDesactivate(bool);
	bool desactivateFlag = true;
};

#endif /* GESTIONPINGPIO_H_ */
