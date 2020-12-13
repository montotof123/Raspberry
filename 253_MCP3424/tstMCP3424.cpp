#include <iostream>
#include <signal.h>

#include "GestionMCP3424.h"
#include <pigpio.h>

using namespace std;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
	cout << "Fin" << endl;
	exit(0);
}

GestionMCP3424 mcp3424;

int main(void) {
	if(!mcp3424.InitMCP3424(mcp3424.ADRESSE_0x6E, mcp3424.CHANNEL_1, mcp3424.Continuous, mcp3424.SAMPLE_RATE_375_SPS, mcp3424.PGA_GAIN_X1)) {
		exit(0);
	}
	
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	int compteur = 0;
	for(;;) {
		cout << "Val = " <<  mcp3424.getMesure() << " compteur = " << dec << compteur << endl;
		compteur++;
		gpioDelay(100000); // 100ms
	}
}