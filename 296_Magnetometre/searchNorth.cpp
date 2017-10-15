#include <iostream>
#include <wiringPi.h>
#include <signal.h>

#include "GestionHMC5883.h"
#include "GestionStepper.h"

using namespace std;

GestionHMC5883 hmc5883;
GestionStepper stepper(GPIO25, GPIO12, GPIO16, GPIO20, A, HALF);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive le servo
    stepper.~GestionStepper();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	hmc5883.init(hmc5883.AddressBase);
	
	cout << hmc5883.getId() << endl;
	cout << hmc5883.isMagnetometre() << endl;
	
	cout << hmc5883.Config(hmc5883._2, hmc5883._3, hmc5883.Normal, hmc5883._1090, hmc5883.SingleMesureament) << endl;
	for(int compteur = 0; ; compteur++) {
		while(!hmc5883.isReady());
		
		cout << dec << "X=" << hmc5883.getRawAxeX();
		cout << " Y=" << hmc5883.getRawAxeY();
		cout << " Z=" << hmc5883.getRawAxeZ() << endl;
		
		float cap = hmc5883.getCap();
		cout << "cap=" << cap << endl << endl;
		
		if(cap < 180.0) {
			stepper.decrement();
		} else {
			stepper.increment();
		}
		
		hmc5883.setModeSelect(hmc5883.SingleMesureament);
		delay(10);
	}
}
