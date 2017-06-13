
#include <iostream>   // Include pour affichage et clavier
#include <signal.h>   // signal de fin de programme
#include <wiringPi.h> // La wiringPi
#include <stdlib.h>   // La librairie standard
#include <chrono>     // Chronometre

#include "GestionPinGPIO.h"

using namespace std;
using namespace std::chrono;

enum lstBit {
	Bit7 = 0x80,
	Bit6 = 0x40,
	Bit5 = 0x20,
	Bit4 = 0x10,
	Bit3 = 0x08,
	Bit2 = 0x04,
	Bit1 = 0x02,
	Bit0 = 0x01,
	NoBit = 0x00
};
	
GestionPinGPIO dataIn(GPIO21);

// Le compteur de bit reçu
volatile int eventCounter = 0;

// Horloge
high_resolution_clock::time_point horloge;
high_resolution_clock::time_point svgHorloge;
duration<double> time_span;
int bitCounter = 0;

// Tableau des bits en réception
int tab[8];

// caractere recu
char character;

// *************************************
// Fonction de fin déclenchee par CTRL-C
// @param sig le signal recu
// *************************************
void fin(int sig) {
	cout << endl << "FIN signal: " << sig << endl;
	exit(0);
}

// *********************************************
// Fonction de decodage de reception
// En fonction du temps entre deux
// interruption, c'est un 1 ou un 0
// @param temps le temps entre deux interruption
// @return la valeur du bit recu
// *********************************************
int val(double temps) {
	return (temps > 0.0017) ? 1 : 0;
}

// *********************************************
// Creation du caractere a partir des bits recus
// @param tabBit le tableau de bits recus
// @return le caractere recu
// *********************************************
char createCharacter(int tabBit[]) {
	return ((tabBit[7]) ? Bit7 : NoBit) | ((tabBit[6]) ? Bit6 : NoBit) 
		| ((tabBit[5]) ? Bit5 : NoBit) | ((tabBit[4]) ? Bit4 : NoBit) 
		| ((tabBit[3]) ? Bit3 : NoBit) | ((tabBit[2]) ? Bit2 : NoBit) 
		| ((tabBit[1]) ? Bit1 : NoBit) | ((tabBit[0]) ? Bit0 : NoBit);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void myInterrupt(void) {
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
	if(eventCounter > 1) {
		bitCounter = bitCounter % 8;
		tab[bitCounter] = val(time_span.count());
		if(bitCounter == 7) {
			character = createCharacter(tab);
			cout << character << endl;
		}
		// cout << "Nb: " << eventCounter << " Bit n:" << bitCounter << " val = " << val(time_span.count()) << " caractère = " << character << " temps: " << time_span.count() << endl;
		bitCounter++;
	} 
	svgHorloge = horloge;
	eventCounter++;
}

// ----
// main
// ----
int main(void) {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);	
	
	// Programmation de la GPIO de reception
	dataIn.in();
	dataIn.pullUp();
	dataIn.fctInterrupt(Falling, &myInterrupt);

	// Boucle d'attente
	while ( 1 ) {
	}
}
