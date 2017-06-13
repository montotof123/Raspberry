/*
 * GestionStepper.h
 *
 *  Created on: 27 november 2016
 *      Author: totof
 * Controle un moteur pas a pas
 */

#ifndef GESTIONSTEPPER_H_
#define GESTIONSTEPPER_H_

#include "GestionPinGPIO.h"

namespace std {

enum Mode {
	ONE_ONE = 0,
	TWO_ONE = 1,
	HALF = 2
};

enum Position{
	A = 0,
	AC = 1,
	C = 2,
	CB = 3,
	B = 4,
	BD = 5,
	D = 6,
	DA = 7
};

// Classe de gestion du Stepper
class GestionStepper {
public:
	GestionStepper(PinGPIO pPinA, PinGPIO pPinB, PinGPIO pPinC, PinGPIO pPinD, Position pPosition = A, Mode pMode = ONE_ONE, bool pSynchonised = true);
	bool increment(void);
	bool decrement(void);
	bool increment(unsigned int);
	bool decrement(unsigned int);
	bool cycle(int);
	bool gotoPosition(Position);
	Position getPosition(void);
	int getTemporisation(void);
	void setTemporisation(unsigned int);
	Mode getMode(void);
	bool setMode(Mode);
	bool getHold(void);
	void setHold(bool);
	virtual ~GestionStepper();

private:
	GestionPinGPIO PinA;
	GestionPinGPIO PinB;
	GestionPinGPIO PinC;
	GestionPinGPIO PinD;
	Position position;
	void positionA(void);
	void positionB(void);
	void positionC(void);
	void positionD(void);
	void positionAC(void);
	void positionCB(void);
	void positionBD(void);
	void positionDA(void);
	void positionOff(void);
	int temporisation;
	Mode mode;
	bool hold;
};

} /* namespace std */

#endif /* GESTIONSTEPPER_H_ */
