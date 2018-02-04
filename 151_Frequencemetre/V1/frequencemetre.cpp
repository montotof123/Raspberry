//================================================
// Name        : fréquencemètre.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Mesurer une fréquence sur un GPIO
//================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin
#include <chrono>     // Chronometre
#include "GestionPinGPIO.h"

using namespace std;
using namespace std::chrono;

// Objets utilisés
GestionPinGPIO mesure(GPIO26);

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
    mesure.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterrupt(void) {
	float frequence; 
	
	// Calcul de la vitesse de rotation
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
	if(time_span.count() != 0) {
		frequence = 1 / time_span.count();
	}
	
	// Affichage et mémorisation
	cout << "Fréquence: " << frequence << " Hz" << endl;
	svgHorloge = horloge;
}


// ******************
// Fonction pricipale
// ******************
int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	// Programmation de la reception
	mesure.in();
	mesure.pullUp();
	mesure.fctInterrupt(Falling, &fctInterrupt);
	
	for(;;) {
		delay(500);
	}
}
