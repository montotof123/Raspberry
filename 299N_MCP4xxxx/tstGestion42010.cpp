#include <iostream>
#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>	  // Fin

#include "GestionMCP42010.h"

using namespace std;

GestionMCP42010 potentiometre(channel_0);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive le potentiometre
    potentiometre.~GestionMCP42010();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	// Initialisation des pot a 0
	cout << "Initialisation" << endl;
	cout << potentiometre.setCurrentValue(potTwice, 0) << endl;
	cout << potentiometre.getPotValue() << endl;
	
	delay(20000);
	
	cout << "Incrementation du pot0" << endl;
	for(;potentiometre.getCurrentValue(pot0) != potentiometre.getPotValue();) {
		delay(1000);
		cout << potentiometre.increment(pot0, 200) << endl;
		cout << potentiometre.getCurrentValue(pot0) << endl;
	}
	delay(8000);
	cout << "decremente le pot0" << endl;
	for(;potentiometre.getCurrentValue(pot0) != 0;) {
		delay(1000);
		cout << potentiometre.decrement(pot0, 200) << endl;
		cout << potentiometre.getCurrentValue(pot0) << endl;
	}
	cout << "positionne le pot0 a 3000" << endl;
	cout << potentiometre.setCurrentValue(pot0, 3000) << endl;
	delay(3000);
	cout << "Shutdown du pot0" << endl;
	cout << potentiometre.softShutdown(pot0) << endl;
	delay(10000);
	
	cout << "Incrementation du pot1" << endl;
	for(;potentiometre.getCurrentValue(pot1) != potentiometre.getPotValue();) {
		delay(1000);
		cout << potentiometre.increment(pot1, 200) << endl;
		cout << potentiometre.getCurrentValue(pot1) << endl;
	}
	delay(8000);
	cout << "decremente le pot1" << endl;
	for(;potentiometre.getCurrentValue(pot1) != 0;) {
		delay(1000);
		cout << potentiometre.decrement(pot1, 200) << endl;
		cout << potentiometre.getCurrentValue(pot1) << endl;
	}
	cout << "positionne le pot1 a 3000" << endl;
	cout << potentiometre.setCurrentValue(pot1, 3000) << endl;
	delay(3000);
	cout << "Shutdown du pot1" << endl;
	cout << potentiometre.softShutdown(pot1) << endl;
	delay(10000);
	
	cout << "Fin" << endl;
}
