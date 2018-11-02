#include <iostream>
#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>	  // Fin

#include "GestionMCP42100.h"

using namespace std;

GestionMCP42100 potentiometre(channel_0, GPIO17, GPIO27);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive le potentiometre
    potentiometre.~GestionMCP42100();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	cout << "Initialisation"<< endl;
	cout << potentiometre.setCurrentValue(potTwice, 0) << endl;
	cout << potentiometre.getPotValue() << endl;
	
	delay(15000);
	
	// Incremente les deux pot
	cout << "Incremente les deux ports" << endl;
	for(;potentiometre.getCurrentValue(pot0) != potentiometre.getPotValue();) {
		delay(500);
		cout << potentiometre.increment(potTwice, 5000) << endl;
		cout << potentiometre.getCurrentValue(pot0) << endl;
	}
	delay(2000);
	// Decremente les deux pot
	cout << "Decremente les deux ports" << endl;
	for(;potentiometre.getCurrentValue(pot0) != 0;) {
		delay(500);
		cout << potentiometre.decrement(potTwice, 5000) << endl;
		cout << potentiometre.getCurrentValue(pot0) << endl;
	}
	// Positionne les deux pot
	cout << "Les deux ports a 38000" << endl;
	cout << potentiometre.setCurrentValue(potTwice, 38000) << endl;
	delay(3000);
	// Desactive les deux pot
	cout << "Les deux ports a softShutdown" << endl;
	cout << potentiometre.softShutdown(potTwice) << endl;
	delay(10000);
	
	// Positionne les deux pot
	cout << "Les deux ports a 75000" << endl;
	cout << potentiometre.setCurrentValue(potTwice, 75000) << endl;
	delay(3000);
	cout << "hardShutdown in" << endl;
	cout << potentiometre.hardShutdownIn() << endl;
	delay(3000);
	cout << "hardShutdown out" << endl;
	cout << potentiometre.hardShutdownOut() << endl;
	delay(3000);
	cout << "Les deux ports a 25000" << endl;
	cout << potentiometre.setCurrentValue(potTwice, 25000) << endl;
	delay(3000);
	cout << "hardReset" << endl;
	cout << potentiometre.hardReset() << endl;
	delay(10000);

	cout << "Fin" << endl;
}
