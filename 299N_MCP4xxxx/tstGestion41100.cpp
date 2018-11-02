#include <iostream>
#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>	  // Fin

#include "GestionMCP41100.h"

using namespace std;

GestionMCP41100 potentiometre(channel_0);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive le potentiometre
    potentiometre.~GestionMCP41100();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	cout << "Initialisation"<< endl;
	cout << potentiometre.setCurrentValue(0) << endl;
	cout << potentiometre.getPotValue() << endl;
	
	delay(20000);
	
	// Incremente le pot
	cout << "incremente"<< endl;
	for(;potentiometre.getCurrentValue() != potentiometre.getPotValue();) {
		delay(1000);
		cout << potentiometre.increment(5000) << endl;
		cout << potentiometre.getCurrentValue() << endl;
	}
	delay(8000);
	
	cout << "Decremente"<< endl;
	// Decremente le pot
	for(;potentiometre.getCurrentValue() != 0;) {
		delay(1000);
		cout << potentiometre.decrement(5000) << endl;
		cout << potentiometre.getCurrentValue() << endl;
	}
	// Positionne le pot
	cout << "Pot 75000"<< endl;
	cout << potentiometre.setCurrentValue(75000) << endl;
	delay(10000);
	// shutdown du pot
	cout << "Shutdown"<< endl;
	cout << potentiometre.softShutdown() << endl;
	delay(10000);

	cout << "Fin" << endl;
}
