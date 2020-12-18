#include <iostream>
#include <signal.h>

#include "GestionMCP45HVX1.h"
#include <pigpio.h>

using namespace std;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
	cout << "Fin" << endl;
	exit(0);
}

GestionMCP45HVX1 mcp45hv51;

int main(void) {
	if(!mcp45hv51.InitMCP45HVX1(mcp45hv51.ADRESSE_0x3C, mcp45hv51.R5K)) {
		exit(0);
	}
	
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);
	cout << "TCON: " << hex << (int)mcp45hv51.readTCON()<< endl;
	mcp45hv51.connect();
	cout << "TCON: " << hex << (int)mcp45hv51.readTCON()<< endl;
	mcp45hv51.setValue(0);
	int compteurGlobal = 0;
	for(;;) {
		for(int compteur = 0; compteur != 256; compteur++) {
			cout << "Val = " <<  mcp45hv51.increment() << " compteurGlobal = " << dec << compteurGlobal << endl;
			compteurGlobal++;
			gpioDelay(100000); // 100ms
		}
		for(int compteur = 256; compteur != 0; compteur--) {
			cout << "Val = " <<  mcp45hv51.decrement() << " compteurGlobal = " << dec << compteurGlobal << endl;
			compteurGlobal++;
			gpioDelay(100000); // 100ms
		}
	}
}