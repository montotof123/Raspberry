
#include <iostream>   // Include pour affichage et clavier
#include <signal.h>   // signal de fin de programme
#include <string.h>   // Gestion des String d'erreur
#include <errno.h>    // Gestion des numéros d'erreur
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> // La wiringPi

using namespace std;

const int gpio20 = 20; // Regular LED - Broadcom pin 20, P1 pin 38

// Le compteur d'appui sur le bouton
volatile int eventCounter = 0;

// Fonction de fin déclenchée par CTRL-C
void fin(int sig)
{
	// Désactive les résistances
	pullUpDnControl(gpio20, PUD_OFF);
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

// ----
// main
// ----
int main(void) {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);
	
	// Setup wiringPi library
	if (wiringPiSetupGpio () < 0) {
		cerr << "Erreur d'initialisation de wiringPi: " <<  strerror (errno) << endl;
		exit(1);
	}

	pinMode(gpio20, INPUT);
	pullUpDnControl(gpio20, PUD_UP);

	// Programmation de l'interruption si la GPIO20 passe de 1 à 0
	if ( wiringPiISR (gpio20, INT_EDGE_FALLING, &myInterrupt) < 0 ) {
		cerr << "Erreur d'initialisation de l'interruption: " <<  strerror (errno) << endl;
		exit(2);
	}

	// On boucle, mais on pourrait faire plein d'autres choses...
	while ( 1 ) {
	}
}