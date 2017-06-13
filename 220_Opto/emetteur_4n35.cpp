
#include <iostream>   // Include pour affichage et clavier
#include <wiringPi.h> // La wiringPi
#include <stdlib.h>   // La librairie standard
#include <signal.h>   // signal de fin de programme
#include <string.h>   // gestion des string

#include "GestionPinGPIO.h"

using namespace std;

GestionPinGPIO dataOut(GPIO20);
int lstBit[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

// Fonction de fin déclenchée par CTRL-C
void fin(int sig)
{
	cout << "FIN signal: " << sig << endl;
	exit(0);
}

// ----
// main
// ----
int main(int argc, char *argv[]) {

	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);	
	dataOut.out();
	dataOut.on();
	srand(time(NULL));

	// Entete, envoie un caractere à 0 en entête de message
	// Ne pas enlever car le premier bit reçu est toujours a 0
	for(int cptBit = 0; cptBit != 8; cptBit++) {
		dataOut.on();
		int valeur =  1;
		delay(valeur);
		dataOut.off();
		delay(1);
	}
	
	// Emetteur en boucle
	for(int cptLettre = 0; cptLettre != strlen(argv[1]); cptLettre++) {
		for(int cptBit = 0; cptBit != 8; cptBit++) {
			dataOut.on();
			int valeur = ((argv[1][cptLettre] & lstBit[cptBit]) == 0) ? 1 : 2;
			cout << (int)argv[1][cptLettre] << " " << lstBit[cptBit] << " " << valeur << endl;
			delay(valeur);
			dataOut.off();
			delay(0.1);
		}
	}
	dataOut.on();
	int valeur =  1;
	delay(valeur);
	dataOut.off();
}
