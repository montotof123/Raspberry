//============================================================================
// Name        : piletst.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Mesure de piles et batteries
//============================================================================

#include <iostream>	  // impression cout
#include <signal.h>   // signal de fin de programme
#include <stdlib.h>   // La librairie standard
#include <time.h>     // l'horloge
#include <errno.h>    // Gestion des numéros d'erreur
#include <string.h>   // Gestion des String d'erreur
#include <wiringPi.h> // La wiringPi
#include "GestionPinGPIO.h"
#include "GestionMCP3208.h"

// Temporisation anti rebond
#define TEMPO 500000

using namespace std;

// Objets utilisés
GestionPinGPIO gpio27(27);
GestionPinGPIO gpio22(22);
GestionPinGPIO gpio23(23);
GestionPinGPIO gpio24(24);
GestionPinGPIO gpio25(25);
GestionMCP3208 mcp3208(CHANNEL_1, SPI_SPEED_33);

// Horloge anti rebond
clock_t svgClock = 0;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	// Désactive les résistances
	gpio27.~GestionPinGPIO();
	gpio22.~GestionPinGPIO();
	gpio23.~GestionPinGPIO();
	gpio24.~GestionPinGPIO();
	gpio25.~GestionPinGPIO();
	cout << "FIN signal: " << sig << endl;
	exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void bascPileBat(void) {
	// Inversion de la GPIO22 avec anti rebond
	cout << "Interruption" << endl;
}

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Test des piles et batteries" << endl; // prints testeur de pile Raspberry

	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	// Initialisation de la librairie wiringPi
	if (wiringPiSetupGpio() < 0) {
		cerr << "Erreur d'initialisation de wiringPi: " <<  strerror (errno) << endl;
		exit(1);
	}

	// GPIO 22, 23, 24 et 25 en sortie initialisation à 0
	gpio22.out();
	gpio22.off();
	gpio23.out();
	gpio23.off();
	gpio24.out();
	gpio24.off();
	gpio25.out();
	gpio25.off();
	
	// GPIO 27 en entrée avec résistance de pull up activé
	gpio27.in();
	gpio27.pullUp();
	
	// Fonction d'interruption de la bascule pile/batterie
	gpio27.fctInterrupt(INT_EDGE_FALLING, &bascPileBat);

	// On boucle
	while (true) {
		float tension;
		// Lecture entrée 7
		tension = mcp3208.readTension(VOIE_7, ALIM_33);
		cout << "Tension = " << tension << endl;
		gpio22.on();
		gpio23.off();
		gpio24.off();
		gpio25.off();
		delay(500);
		gpio22.off();
		gpio23.on();
		gpio24.off();
		gpio25.off();
		delay(500);
		gpio22.off();
		gpio23.off();
		gpio24.on();
		gpio25.off();
		delay(500);
		gpio22.off();
		gpio23.off();
		gpio24.off();
		gpio25.on();
		delay(500);
	}
}
