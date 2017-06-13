/*
 * GestionPinGPIO.h
 *
 *  Created on: 1 août 2016
 *      Author: totof
 */

#ifndef GESTIONPINGPIO_H_
#define GESTIONPINGPIO_H_

typedef void (*interrupt)(void);

class GestionPinGPIO {
public:
	GestionPinGPIO(int pPinNumber);
	void pinModePI(int pDirection);
	void pullUpDnControlPI(int pNiveau);
	int wiringPiISRPI(int pFront, interrupt intr);
	virtual ~GestionPinGPIO();

private:
	int pinNumber;
};

#endif /* GESTIONPINGPIO_H_ */
