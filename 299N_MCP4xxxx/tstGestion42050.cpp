#include <iostream>
#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>	  // Fin

#include "GestionMCP42050.h"

using namespace std;

GestionMCP42050 potentiometre(channel_0);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive le potentiometre
    potentiometre.~GestionMCP42050();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	// Initialisation des pot a 0
	cout << "Initialisation"<< endl;
	cout << potentiometre.setCurrentValue(potTwice, 0) << endl;
	cout << potentiometre.getPotValue() << endl;
	
	delay(20000);
	
	// Incrementation du pot0
	for(;potentiometre.getCurrentValue(pot0) != potentiometre.getPotValue();) {
		delay(1000);
		cout << potentiometre.increment(pot0, 2500) << endl;
		cout << potentiometre.getCurrentValue(pot0) << endl;
	}
	delay(8000);
	// decremente le pot0
	for(;potentiometre.getCurrentValue(pot0) != 0;) {
		delay(1000);
		cout << potentiometre.decrement(pot0, 2500) << endl;
		cout << potentiometre.getCurrentValue(pot0) << endl;
	}
	// position le pot0
	cout << potentiometre.setCurrentValue(pot0, 25000) << endl;
	delay(3000);
	// Shutdown du pot0
	cout << potentiometre.softShutdown(pot0) << endl;
	delay(10000);
	
	// Incrementation du pot1
	for(;potentiometre.getCurrentValue(pot1) != potentiometre.getPotValue();) {
		delay(1000);
		cout << potentiometre.increment(pot1, 2500) << endl;
		cout << potentiometre.getCurrentValue(pot1) << endl;
	}
	delay(8000);
	// decremente le pot1
	for(;potentiometre.getCurrentValue(pot1) != 0;) {
		delay(1000);
		cout << potentiometre.decrement(pot1, 2500) << endl;
		cout << potentiometre.getCurrentValue(pot1) << endl;
	}
	// position le pot1
	cout << potentiometre.setCurrentValue(pot1, 25000) << endl;
	delay(3000);
	// Shutdown du pot1
	cout << potentiometre.softShutdown(pot1) << endl;
	delay(10000);
	
	cout << "Fin" << endl;
}
