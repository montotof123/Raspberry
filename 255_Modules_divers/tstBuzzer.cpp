#include "GestionPinGPIO.h"

#include <iostream>	  // impression cout
#include <signal.h>	  // Fin

using namespace std;

GestionPinGPIO bip(GPIO17);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive les circuits
	bip.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
	// Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	for(;;) {
		bip.out();
		bip.on();
		delay(1000);
		bip.out();
		bip.off();
		delay(1000);
	}
}
