/*
 * GestionPinGPIO.h
 *
 *  Created on: 1 août 2016
 *      Author: totof
 */

#ifndef GESTIONPINGPIO_H_
#define GESTIONPINGPIO_H_

// Type fonction d'interruption
typedef void (*interrupt)(void);

// Classe de gestion des GPIO
class GestionPinGPIO {
public:
	GestionPinGPIO(int pPinNumber);
	void in();
	void out();
	void pullUp();
	void pullDn();
	void pullOff();
	void write(int pValue);
	void off();
	void on();
	void invertState();
	int read();
	bool isOn();
	bool isOff();
	int fctInterrupt(int pFront, interrupt intr);
	virtual ~GestionPinGPIO();

private:
	int pinNumber;
	void pinModePI(int pDirection);
	void pullUpDnControlPI(int pNiveau);
};

#endif /* GESTIONPINGPIO_H_ */
