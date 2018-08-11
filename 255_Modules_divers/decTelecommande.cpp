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
#include <string>
#include <math.h>       /* pow */
#include "GestionPinGPIO.h"

using namespace std;
using namespace std::chrono;

// Objets utilisés
GestionPinGPIO passage(GPIO17);

// Le compteur de passage
volatile int passageCounter = 0;

// tableau des temps d'interruption
float valeurInt[36];
string touche;
int valTouche;


// Horloge
high_resolution_clock::time_point horloge;
high_resolution_clock::time_point svgHorloge;
duration<double> time_span;

// *******************
// Valeur de la touche
// *******************
int getValTouche(void) {
	valTouche = 0;
	for(int compteur = 2; compteur < 34; compteur++) {
		if(valeurInt[compteur] > 0.0018) {
			valTouche += pow(2.0, 33 - compteur);
		}
	}
	return valTouche;
}

// *****************
// Code de la touche
// *****************
string getTouche(void) {
	switch(valTouche) {
		case 0xFFA25D: touche = "CH-"; break;
		case 0xFF629D: touche = "CH"; break;
		case 0xFFE21D: touche = "CH+"; break;
		case 0xFF22DD: touche = "PREV"; break;
		case 0xFF02FD: touche = "NEXT"; break;
		case 0xFFC23D: touche = "PLAY/PAUSE"; break;
		case 0xFFE01F: touche = "VOL-"; break;
		case 0xFFA857: touche = "VOL+"; break;
		case 0xFF906F: touche = "EQ"; break;
		case 0xFF6897: touche = "0"; break;
		case 0xFF9867: touche = "100+"; break;
		case 0xFFB04F: touche = "200+"; break;
		case 0xFF30CF: touche = "1"; break;
		case 0xFF18E7: touche = "2"; break;
		case 0xFF7A85: touche = "3"; break;
		case 0xFF10EF: touche = "4"; break;
		case 0xFF38C7: touche = "5"; break;
		case 0xFF5AA5: touche = "6"; break;
		case 0xFF42BD: touche = "7"; break;
		case 0xFF4AB5: touche = "8"; break;
		case 0xFF52AD: touche = "9"; break;
		default: touche = "Inconnu";
	}
	return touche;
}

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
	
	// Nouvelle touche
	if(time_span.count() > 0.2) {
		// Nouvelle touche
		passageCounter = 0;
	}
	
	// Stockage des valeurs d'interruption
	if(passageCounter < 35) {
		valeurInt[passageCounter] = time_span.count();
	}
	
	// Touche complète
	if(passageCounter == 35) {
		valTouche = getValTouche();
		touche = getTouche();
		cout << " Valeur: " << hex << valTouche << " Touche: " << touche << endl;
	}
	// Répétition
	if(passageCounter > 35 && time_span.count() > 0.08) {
		cout << " Valeur: " << hex << valTouche << " Touche: " << touche << " Répétition" << endl;
	}
	
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
