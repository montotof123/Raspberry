//===============================
// Name        : tstLEDRGB.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Test des LED RGB
//===============================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin, fonction cyclique
#include <unistd.h>	  // Delais pour les alarmes
#include "GestionPinGPIO.h"
#define CYCLE 20
 
using namespace std;

// Rouge sur GPIO 13
GestionPinGPIO red(GPIO13);
// Vert sur GPIO 19
GestionPinGPIO green(GPIO19);
// Bleu sur GPIO 26
GestionPinGPIO blue(GPIO26);

// Nb d'interruption rouge allume
int redOn = 7;

// Nb d'interruption vert allume
int greenOn = 13;

// Nb d'interruption bleu allume
int blueOn = 9;

// Compteur global et cyclique
long nbInterrupt = 0;
int valCycle = 0;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive les gpio
    red.~GestionPinGPIO();
    green.~GestionPinGPIO();
    blue.~GestionPinGPIO();
    exit(0);
}

// *************************************
// Fonction enclenche par l'interruption
// *************************************
void genPWM(int sig) {
	// Toutes les 3000 interruption, on change le rapport cyclique
	if(nbInterrupt % 3000 == 0) {
		redOn++;
		greenOn--;
		blueOn++;
		if(redOn == 17) {
			redOn = 3;
		}
		if(greenOn == 4) {
			greenOn = 18;
		}
		if(blueOn == 13) {
			blueOn = 7;
		}
	}
	if(valCycle < redOn) {
		red.on();
	} else {
		red.off();
	}
	if(valCycle < greenOn) {
		green.on();
	} else {
		green.off();
	}
	if(valCycle < blueOn) {
		blue.on();
	} else {
		blue.off();
	}
	valCycle++;
	if(valCycle == CYCLE) {
		valCycle = 0;
	}
	nbInterrupt++;
}

// *******************
// Fonction principale
// *******************
int main(int argc, char *argv[]) {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	// GPIO en sortie
	red.out();
	green.out();
	blue.out();

	// Lancement cyclique d'une mesure toute les 100µs
	signal(SIGALRM, genPWM);   
    ualarm(100, 100);

	// Boucle d'attente infinie, tout se passe dans les interruption
	for(;;) {}
}