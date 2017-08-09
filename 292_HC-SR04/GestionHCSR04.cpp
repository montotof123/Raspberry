/*
 * GestionHCSR04.cpp
 *
 *  Created on: 1 août 2016
 *      Author: totof
 */

#include <wiringPi.h>
#include <chrono>     // Chronometre
#include "GestionHCSR04.h"

namespace std {
using namespace std::chrono;

// *************************************
// Constructeur
// Mémorise le numéro des pins utilisées
// @param numéro de pin du trigger
// @param numéro de pin de l'echo
// *************************************
GestionHCSR04::GestionHCSR04(PinGPIO pinTrigger, PinGPIO pinEcho) {
	trigger.init(pinTrigger);
	echo.init(pinEcho);
	echo.in();
	trigger.out();
	trigger.off();
}

// ******************************************************
// Recuperation de la pin echo pour dispatch interruption
// ******************************************************
GestionPinGPIO GestionHCSR04::getEcho(void) {
	return echo;
}

// ********************************
// Envoie le signal pour une mesure
// ********************************
void GestionHCSR04::startMesure(void) {
	high_resolution_clock::time_point debutTimeOut;
	high_resolution_clock::time_point finTimeOut;
	duration<double> dureeTimeOut;
	double timeOut = 0.5;
	
	// flag de mesure
	mesureOk = false;
	
	// Trigger au niveau bas pour pouvoir commencer une mesure
	trigger.off();
	delayMicroseconds(50);
	
	// Nouvelle mesure
	trigger.on();
	delayMicroseconds(10); 
	trigger.off();
}

// **********************************************************
// Positionne la temperature pour calcul de la vitesse du son
// **********************************************************
void GestionHCSR04::setTemperature(double pTemperature) {
	temperature = pTemperature;
}

// *******************************
// Indique si la mesure est valide
// *******************************
bool GestionHCSR04::isMesureOk(void) {
	return mesureOk;
}

// ***************************
// Renvoie la distance mesurée
// ***************************
double GestionHCSR04::getDistance(void) {
	return distance;
}

// *********************
// Mesure de la distance
// *********************
void GestionHCSR04::fctInterruptDebut(void) {
	// Debut du signal echo
	debutMesure = high_resolution_clock::now();
	
	// Attend que le signal repasse a 0
	while(echo.isOn());
	
	// Calcul du temps à 1
	finMesure = high_resolution_clock::now();
	dureeMesure = duration_cast<chrono::duration<double>>(finMesure - debutMesure);
	
	// Calcul de la distance
	double vitesse = 0.62 * temperature + 331.6;
	distance = vitesse * dureeMesure.count() / 2.0;
	
	mesureOk = true;
}

// **********************************************************
// Destructeur
// **********************************************************
GestionHCSR04::~GestionHCSR04() {
}
}