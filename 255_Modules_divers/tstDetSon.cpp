#include "GestionPCF8591.h"

#include <iostream>	  // impression cout
#include <signal.h>	  // Fin

using namespace std;

GestionPCF8591 pcf8591(true);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive les circuits
    pcf8591.~GestionPCF8591();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
	// Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	for(;;) {
		cout << "Canal 0: " << (int)pcf8591.read(Canal0) << endl;
		//delay(500);
	}
}
