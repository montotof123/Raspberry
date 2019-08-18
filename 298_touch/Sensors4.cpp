#include <iostream>
#include <wiringPi.h>

#include "GestionPinGPIO.h"
#include <signal.h>

using namespace std;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	cout << "Fin" << endl;
	exit(0);
}

int main() {
	GestionPinGPIO noLockHigh(GPIO21);
	GestionPinGPIO noLockLow(GPIO20);
	GestionPinGPIO selfLockHigh(GPIO16);
	GestionPinGPIO selfLockLow(GPIO12);
	noLockHigh.in();
	noLockLow.in();
	selfLockHigh.in();
	selfLockLow.in();
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);
	while(1) {
		if(noLockHigh.isOn()) {
			cout << "noLockHigh AB=00 ON  ";
		} else {
			cout << "noLockHigh AB=00 OFF ";
		}
		if(noLockLow.isOn()) {
			cout << "noLockLow AB=10 ON  ";
		} else {
			cout << "noLockLow AB=10 OFF ";
		}
		if(selfLockHigh.isOn()) {
			cout << "selfLockHigh AB=01 ON  ";
		} else {
			cout << "selfLockHigh AB=01 OFF ";
		}
		if(selfLockLow.isOn()) {
			cout << "selfLockLow AB=11 ON  " << endl;
		} else {
			cout << "selfLockLow AB=11 OFF " << endl;
		}
	}
}
