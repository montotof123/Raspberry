//============================================================
// Name        : tstLEDDualColor.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Test du module dual color en PWM
//               3 cycle de 10s
//               cycle 0: rouge de 0 à 90% PWM
//               cycle 1: vert de 0 à 90% PWM
//               cycle 2: rouge et vert melange de 0 à 90% PWM
//============================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin, fonction cyclique
#include <unistd.h>	  // Delais pour les alarmes
#include "GestionPinGPIO.h"

using namespace std;

// Rouge sur GPIO 13
GestionPinGPIO red(GPIO13);
// Vert sur GPIO 19
GestionPinGPIO green(GPIO19);

// Nb d'interruption rouge allume
int redOn = 1;
// Nb d'interruption rouge eteint
int redOff = 10;
// Nb de cycle rouge dans une oscillation PWM
int redCycle;
// Nb de cycle rouge global
int nbRedCycle = 0;
// Etat du rouge dans une oscillation PWM (true allume, false eteint)
bool stateRed = true;

// Nb d'interruption vert allume
int greenOn = 0;
// Nb d'interruption vert eteint
int greenOff = 1;
// Nb de cycle vert dans une oscillation PWM
int greenCycle;
// Nb de cycle vert global
int nbGreenCycle = 0;
// Etat du vert dans une oscillation PWM (true allume, false eteint)
bool stateGreen = true;

// Compteur d'interruption
int compteurInterrupt = -1;
// Cycle 0-->rouge 1-->vert 2-->melange
int cyclePWM = 0;


// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive les gpio
    red.~GestionPinGPIO();
    green.~GestionPinGPIO();
    exit(0);
}

// *************************************
// Fonction enclenche par l'interruption
// *************************************
void genPWM(int sig) {
	// Cycle 0: rouge 1: vert 2: melange rouge et vert
	switch(cyclePWM) {
		case 0: 
			// ********************
			// rouge de 0 a 90% PWM
			// ********************
			// pwm rouge +10% toutes les secondes
			if(compteurInterrupt % 10001 == 0) {
				cout << "Tour:" << compteurInterrupt << endl;
				redOn = compteurInterrupt % 10;
				redOff = 10;
				greenOn = 0;
				greenOff = 1;
				redCycle = redOn;
				greenCycle = greenOn;		
			}
			// changement de cycle au bout de 10s
			if(compteurInterrupt % 100010 == 0) {
				cyclePWM = 1;
			}
			break;
		case 1: 
			// *******************
			// vert de 0 a 90% PWM
			// *******************
			// pwm vert +10% toutes les secondes
			if(compteurInterrupt % 10001 == 0) {
				cout << "Tour:" << compteurInterrupt << endl;
				redOn = 0;
				redOff = 1;
				greenOn = compteurInterrupt % 10;
				greenOff = 10;
				redCycle = redOn;
				greenCycle = greenOn;		
			}
			// changement de cycle au bout de 10s
			if(compteurInterrupt % 100010 == 0) {
				cyclePWM = 2;
			}
			break;
		case 2: 
			// ************************************
			// melange rouge et vert de 0 a 90% PWM
			// ************************************
			// pwm rouge/vert +10% toutes les secondes
			if(compteurInterrupt % 10001 == 0) {
				cout << "Tour:" << compteurInterrupt << endl;
				redOn = compteurInterrupt % 10;
				redOff = 10;
				greenOn = compteurInterrupt % 10;
				greenOff = 10;
				redCycle = redOn;
				greenCycle = greenOn;		
			}
			// changement de cycle au bout de 10s
			if(compteurInterrupt % 100010 == 0) {
				cyclePWM = 0;
			}
			break;
	}

	// Gestion du PWM
	// Rouge etat haut a true
	if(stateRed) {
		// Nombre de cycle PWM etat haut
		if(redCycle > 0) {
			red.on();
			cout << "red on" << endl;
			redCycle--;
		} 
		// Passage etat haut vers bas
		if(redCycle == 0) {
			stateRed = false;
			redCycle = redOff;
		}
	// Rouge etat bas a false
	} else {
		// Nombre de cycle PWM etat bas
		if(redCycle > 0) {
			red.off();
			cout << "red off" << endl;
			redCycle--;
		} 
		// Passage etat bas vers haut
		if(redCycle == 0) {
			stateRed = true;
			redCycle = redOn;
			nbRedCycle++;
			cout << "nb Red Cycle = " << nbRedCycle << endl;
		}		
	}
	// Vert etat haut a true
	if(stateGreen) {
		// Nombre de cycle PWM etat haut
		if(greenCycle > 0) {
			green.on();
			cout << "green on" << endl;
			greenCycle--;
		} 
		// Passage etat haut vers bas
		if(greenCycle == 0) {
			stateGreen = false;
			greenCycle = greenOff;
		}
	// Vert etat bas a false
	} else {
		// Nombre de cycle PWM etat bas
		if(greenCycle > 0) {
			green.off();
			cout << "green off" << endl;
			greenCycle--;
		} 
		// Passage etat bas vers haut
		if(greenCycle == 0) {
			stateGreen = true;
			greenCycle = greenOn;
			nbGreenCycle++;
			cout << "nb Green Cycle = " << nbGreenCycle << endl;
		}		
	}
	compteurInterrupt++;
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
	
	cout << "Init:" << endl;

	// Lancement cyclique d'une mesure toute les 100µs
	signal(SIGALRM, genPWM);   
    ualarm(100, 100);

	// Initialise nb de cycles
	redCycle = redOn;
	greenCycle = greenOn;
		
	// Boucle d'attente infinie, tout se passe dans les interruption
	for(;;) {}
}