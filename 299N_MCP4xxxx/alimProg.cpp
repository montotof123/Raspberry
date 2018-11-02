#include <iostream>
#include <stdlib.h>
#include <string>
#include <signal.h>	  // Fin

#include "GestionMCP41010.h"

using namespace std;

GestionMCP41010 potentiometre(channel_0);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive le potentiometre
    potentiometre.~GestionMCP41010();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	string enter;

	cout << "Initialisation";
	getline (cin, enter);

	for(int compteur = 0; compteur <=10000; compteur += 40) {
		potentiometre.setCurrentValue(compteur);
		cout << potentiometre.getCurrentValue();
		getline (cin, enter);
	}

	cout << "Fin" << endl;
}
