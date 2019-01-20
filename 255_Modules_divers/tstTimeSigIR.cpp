//===========================================================
// Name        : tstTimeSigIR.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Test du signal ingrarouge d'une telecommande
//===========================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin
#include <chrono>     // Chronometre
#include "GestionPinGPIO.h"

using namespace std;
using namespace std::chrono;

// Objets utilisés
GestionPinGPIO passage(GPIO17);

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
    passage.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterrupt(void) {
	
	// Calcul de la vitesse des interruptions
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
	
	// Affichage et mémorisation
	cout << "Passage numéro: " << passageCounter << " temps: " << time_span.count() <<  endl;
	passageCounter++;
	svgHorloge = horloge;
}


// ******************
// Fonction pricipale
// ******************
int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	// Programmation de la reception
	passage.in();
	passage.pullUp();
	passage.fctInterrupt(Falling, &fctInterrupt);
	
	
	for(;;) {	
		delay(200);
	}
}
