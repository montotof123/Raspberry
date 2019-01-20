//======================================================
// Name        : tstTimeSigCommutateur.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Fonctionnement d'un commutateur rotatif
//======================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin
#include <chrono>     // Chronometre
#include "GestionPinGPIO.h"

using namespace std;
using namespace std::chrono;

// Objets utilisés
GestionPinGPIO clk(GPIO13);
GestionPinGPIO dt(GPIO19);
GestionPinGPIO sw(GPIO26);

// Le compteur de passage
volatile int passageCounter = 0;

// Horloge
high_resolution_clock::time_point horloge;
high_resolution_clock::time_point svgHorloge;
duration<double> time_span;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive les GPIO
    clk.~GestionPinGPIO();
    dt.~GestionPinGPIO();
    sw.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterruptClk(void) {
	
	// Calcul de la vitesse des interruptions
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
	
	// Affichage et mémorisation
	if(time_span.count() > 0.1) {
		cout << "Clk Passage numéro: " << passageCounter << " temps: " << time_span.count() <<  endl;
		passageCounter++;
	}
	svgHorloge = horloge;
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterruptDt(void) {
	
	// Calcul de la vitesse des interruptions
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
	
	// Affichage et mémorisation
	if(time_span.count() > 0.1) {
		cout << "Dt  Passage numéro: " << passageCounter << " temps: " << time_span.count() <<  endl;
		passageCounter++;
	}
	svgHorloge = horloge;
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterruptSw(void) {
	
	// Calcul de la vitesse des interruptions
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
	
	// Affichage et mémorisation
	cout << "Sw  Passage numéro: " << passageCounter << " temps: " << time_span.count() <<  endl;
	passageCounter++;
	svgHorloge = horloge;
}


// *******************
// Fonction principale
// *******************
int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	// Programmation de la reception
	clk.in();
	clk.pullUp();
	clk.fctInterrupt(Falling, &fctInterruptClk);
	dt.in();
	dt.pullUp();
	dt.fctInterrupt(Falling, &fctInterruptDt);
	sw.in();
	sw.pullUp();
	sw.fctInterrupt(Falling, &fctInterruptSw);
	
	
	for(;;) {	
		delay(200);
	}
}
