/*
 * GestionHCSR04.h
 *
 *  Created on: 30/07/2017
 *      Author: totof
 */

#ifndef GESTIONHCSR04_H_
#define GESTIONHCSR04_H_

#include "GestionPinGPIO.h"
#include <chrono>     // Chronometre

namespace std {
using namespace std::chrono;

// Classe de gestion des HC-SR04
class GestionHCSR04 {
public:
	GestionHCSR04(PinGPIO, PinGPIO);
	void startMesure(void);
	void setTemperature(double);
	double getDistance(void);
	bool isMesureOk(void);
	GestionPinGPIO getEcho(void);
	void fctInterruptDebut(void);
	virtual ~GestionHCSR04();

private:
	GestionPinGPIO trigger;
	GestionPinGPIO echo;
	bool mesureOk = false;
	double temperature = 20.0;
	double distance;
	high_resolution_clock::time_point debutMesure;
	high_resolution_clock::time_point finMesure;
	duration<double> dureeMesure;
};
}
#endif /* GESTIONHCSR04_H_ */