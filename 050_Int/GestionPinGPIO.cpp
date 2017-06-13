/*
 * GestionPinGPIO.cpp
 *
 *  Created on: 1 août 2016
 *      Author: totof
 */

#include "GestionPinGPIO.h"
#include "wiringPi.h"

GestionPinGPIO::GestionPinGPIO(int pPinNumber) {
	pinNumber = pPinNumber;
}

void GestionPinGPIO::pinModePI(int pDirection) {
	pinMode(pinNumber, pDirection);
}

void GestionPinGPIO::pullUpDnControlPI(int pNiveau) {
	pullUpDnControl(pinNumber, pNiveau);
}

int GestionPinGPIO::wiringPiISRPI(int pFront, interrupt intr) {
	return wiringPiISR(pinNumber, pFront, *intr);
}

GestionPinGPIO::~GestionPinGPIO() {
	pullUpDnControlPI(PUD_OFF);
	pinModePI(INPUT);
}
