//==========================================================
// Name        : tstCompteTours.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Fait tourner un moteur à une vitesse donnée
//==========================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin
#include <chrono>     // Chronometre
#include "GestionPinGPIO.h"
#include "GestionPinPWM.h"

using namespace std;
using namespace std::chrono;

// Objets utilisés
GestionPinPWM pwm(PWM_GPIO18);
GestionPinGPIO moteur1(GPIO05);
GestionPinGPIO moteur2(GPIO06);
GestionPinGPIO laser(GPIO20);
GestionPinGPIO passage(GPIO21);

// Le compteur de passage
volatile int passageCounter = 0;

// Horloge
high_resolution_clock::time_point horloge;
high_resolution_clock::time_point svgHorloge;
duration<double> time_span;

// Nombre de tour cible
int nbTourCible;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive les GPIO
    pwm.~GestionPinPWM();
    moteur1.~GestionPinGPIO();
    moteur2.~GestionPinGPIO();
    laser.~GestionPinGPIO();
    passage.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterrupt(void) {
	float nbTour; 
	
	// Calcul de la vitesse de rotation
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
	if(time_span.count() != 0) {
		nbTour = (1 / time_span.count() * 60) / 2;
	}
	
	// Regulateur
	if(nbTour > nbTourCible) {
		pwm.setValue(pwm.getValue() - 1);
	} else {
		pwm.setValue(pwm.getValue() + 1);		
	}
	
	// Affichage et mémorisation
	cout << "Passage numéro: " << passageCounter << " temps: " << time_span.count() << " nombre tours/mn = " << nbTour << endl;
	passageCounter++;
	svgHorloge = horloge;
}


// ******************
// Fonction pricipale
// ******************
int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	// Initialisation PWM
	pwm.setMode(PwmModeMs);
	pwm.setDiviseur(30);
	pwm.setPrecision(1024);
	pwm.setValue(0);
	
	// Initialisation moteur
	moteur1.out();
	moteur1.off();
	moteur2.out();
	moteur2.off();
	
	// Initialisation laser
	laser.out();
	laser.on(); // Attention laser actif état bas
	
	// Programmation de la reception
	passage.in();
	passage.pullUp();
	passage.fctInterrupt(Falling, &fctInterrupt);
	
	// Allumage laser
	laser.off();
	
	// Demarrage moteur
	moteur1.on();
	
	for(;;) {	
		cout << "Nombre de tour/mn cible: ";
		cin >> nbTourCible;
		pwm.setValue(pwm.getPrecisionMax() / 2);
	}
}
