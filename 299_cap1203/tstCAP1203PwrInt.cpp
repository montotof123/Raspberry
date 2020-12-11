#include <iostream>
#include <pigpio.h>
#include <signal.h>

#include "GestionCAP1203.h"
#include "GestionPinGPIO.h"

using namespace std;

GestionCAP1203 cap1203;
GestionPinGPIO int1(GPIO21);
int compteur = 0;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
	cout << "Fin" << endl;
	exit(0);
}

void intInt1(int gpio, int level, uint32_t tick) {
	cout << "CS1 = " << hex << cap1203.isCs1();
	cout << " CS2 = " << hex << cap1203.isCs2();
	cout << " CS3 = " << hex << cap1203.isCs3();
	cap1203.validInterrupt();
	cout << " Int: " << dec << level << " compteur: " << compteur << endl;
	cout << " Pwr: " << dec << cap1203.isPwr() << endl;
	cout << "Statut=" << (int)cap1203.getGeneralStatut() << endl;
	compteur++;
}

int main(void) {
	cap1203.reset();
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	// Interruption a chaque appui sur le bouton
	int1.in();
	int1.pullUp();
	int1.fctInterrupt(intInt1);

	cout << "Product ID = " << hex << (int)cap1203.getProductID() << endl;
	cout << "Vendor ID  = " << hex << (int)cap1203.getVendorID() << endl;
	cout << "Revision   = " << dec << (int)cap1203.getRevision() << endl;
	cout << "CAP1203    = " << dec << cap1203.isCAP1203() << endl << endl;
	
	if(!cap1203.pwrInit()) {
		exit(0);
	}
	for(;;) {
		gpioDelay(100000); // 100ms
	}
}