//============================================================================
// Name        : pile.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <signal.h>   // signal de fin de programme
#include <stdlib.h>   // La librairie standard
#include <time.h>     // l'horloge
#include <errno.h>    // Gestion des numéros d'erreur
#include <string.h>   // Gestion des String d'erreur
#include <wiringPi.h> // La wiringPi
#include "GestionPinGPIO.h"

using namespace std;

// Le compteur d'appui sur le bouton
volatile int eventCounter = 0;

GestionPinGPIO gpio20(20);

// Fonction de fin déclenchée par CTRL-C
void fin(int sig)
{
	// Désactive les résistances
	gpio20.~GestionPinGPIO();
	cout << "FIN signal: " << sig << endl;
	exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void myInterrupt(void) {
	eventCounter++;
	cout << "Nb: " << eventCounter << " temps: " << clock() << endl;
}

int main() {
	cout << "Gestion interruption en vrai C++ " << endl; // prints testeur de pile Raspberry

	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	// Setup wiringPi library
	if (wiringPiSetupGpio() < 0) {
		cerr << "Erreur d'initialisation de wiringPi: " <<  strerror (errno) << endl;
		exit(1);
	}

	gpio20.pinModePI(INPUT);
	gpio20.pullUpDnControlPI(PUD_UP);
	gpio20.wiringPiISRPI(INT_EDGE_FALLING, &myInterrupt);

	// On boucle, mais on pourrait faire plein d'autres choses...
	while ( 1 ) {
	}
}
