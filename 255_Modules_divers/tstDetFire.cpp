#include "GestionPCF8591.h"
#include "GestionPinGPIO.h"

#include <iostream>	  // impression cout
#include <signal.h>	  // Fin

using namespace std;

GestionPCF8591 pcf8591(true);
GestionPinGPIO alerte(GPIO17);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive les circuits
    pcf8591.~GestionPCF8591();
	alerte.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterrupt(void) {
	// Affichage et mémorisation
	cout << "*************** ALERTE ***************" <<  endl;
}


int main() {
	// Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	// Programmation de la l'alerte
	alerte.pullUp();
	alerte.in();
	alerte.fctInterrupt(Falling, &fctInterrupt);
	
	for(;;) {
		cout << "Canal 0: " << (int)pcf8591.read(Canal0) << endl;
		delay(500);
	}
}
