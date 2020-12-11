#include <iostream>
#include <pigpio.h>
#include <signal.h>

#include "GestionCAP1203.h"

using namespace std;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
	cout << "Fin" << endl;
	exit(0);
}

GestionCAP1203 cap1203;

int main(void) {
	cap1203.reset();
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	cout << "Product ID = " << hex << (int)cap1203.getProductID() << endl;
	cout << "Vendor ID  = " << hex << (int)cap1203.getVendorID() << endl;
	cout << "Revision   = " << dec << (int)cap1203.getRevision() << endl;
	cout << "CAP1203    = " << dec << cap1203.isCAP1203() << endl << endl;
	
	if(!cap1203.standbyInit()) {
		exit(0);
	}
	for(;;) {
		cout << "CS3 = " << hex << cap1203.isCs3();
		cout << " CS2 = " << hex << cap1203.isCs2();
		cout << " CS1 = " << hex << cap1203.isCs1() << endl;
	}
}