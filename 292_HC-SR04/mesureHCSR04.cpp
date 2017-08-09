//================================================
// Name        : mesureHCSR04.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Mesure de distance avec un HCSR04
//================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin, fonction cyclique
#include <chrono>     // Chronometre
#include <unistd.h>	  // Delais pour les alarmes
#include <typeinfo>
#include "GestionHCSR04.h"
#include "Gestion1Wire.h"
#include "GestionSlave1Wire.h"
#include "GestionDS18B20.h"

using namespace std;

// Objets utilisés
GestionHCSR04 hcsr04(GPIO23, GPIO22);


void fctInterruptDebut(void) {
	hcsr04.fctInterruptDebut();
}

// *******************
// Fonction principale
// *******************
int main() {
	Gestion1Wire* oneWire = new Gestion1Wire();
	list<GestionSlave1Wire*> lstSlave = oneWire->getLstSlaves();
	float temperature;
	
	high_resolution_clock::time_point debutProgramme;
	high_resolution_clock::time_point finProgramme;
	duration<double> dureeProgramme;
	double timeout   = 0.5; // 0.5 sec ~ 171 m
	
	// Parametrage pour interruption
	GestionPinGPIO echo = hcsr04.getEcho();
	echo.fctInterrupt(Rising, &fctInterruptDebut);
	
	// Lecture temperature
	for (GestionSlave1Wire* slave : lstSlave) {
		GestionDS18B20* fullSlave = dynamic_cast<GestionDS18B20*>(slave);
		MesureDS18B20 mesure = fullSlave->getMesure();
		if(mesure.isMesureOK()) {
			temperature = mesure.getTemperature();
		}
	}

	// Nouvelle mesure
	hcsr04.setTemperature(temperature);
	hcsr04.startMesure();	

	// Debut programme pour mesure timeout
	debutProgramme = high_resolution_clock::now();
	
	// Temps execution programme
	do {
		finProgramme = high_resolution_clock::now();
		dureeProgramme = duration_cast<chrono::duration<double>>(finProgramme - debutProgramme);
		if(hcsr04.isMesureOk()) {
			cout << hcsr04.getDistance();
			exit(0);
		}
	} while(dureeProgramme.count() < timeout);
	
	// Time out
	cout << "-1";
	exit(-1);
}
