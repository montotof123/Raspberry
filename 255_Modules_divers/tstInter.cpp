#include "GestionPinGPIO.h"

#include <iostream>	  // impression cout
#include <signal.h>	  // Fin

using namespace std;

GestionPinGPIO alerte(GPIO17);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive les circuits
	alerte.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterrupt(void) {
	// Affichage et mémorisation
	cout << "*************** ACTIF ***************" <<  endl;
}


int main() {
	// Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	// Programmation de la l'alerte
	alerte.pullUp();
	alerte.in();
	alerte.fctInterrupt(Falling, &fctInterrupt);
	
	for(;;) {
		delay(500);
	}
}
