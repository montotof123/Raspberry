//=================================================================
// Name        : mesure.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Mesure du convertisseur AD7822 pour l'oscilloscope
//==================================================================
#include <stdlib.h>   // La librairie standard
#include <chrono>     // Chronometre
#include <iostream>	  // impression cout
#include <fstream>

#include "GestionPinGPIO.h"

// Nombre de mesures
#define nbMesures 500000

using namespace std;
using namespace std::chrono;

// GPIO utilisés
GestionPinGPIO eoc(GPIO06);
GestionPinGPIO convst(GPIO05);
GestionPinGPIO db0(GPIO26);
GestionPinGPIO db1(GPIO19);
GestionPinGPIO db2(GPIO13);
GestionPinGPIO db3(GPIO07);
GestionPinGPIO db4(GPIO12);
GestionPinGPIO db5(GPIO16);
GestionPinGPIO db6(GPIO20);
GestionPinGPIO db7(GPIO21);
GestionPinGPIO cs(GPIO23);
GestionPinGPIO rd(GPIO24);

// Horloge
high_resolution_clock::time_point horloge;
high_resolution_clock::time_point initHorloge;
duration<double> time_span;

// Gestion des interruptions
bool mesureRun = true;
volatile int compteur = 0;

// tableau des mesures
float mesures[nbMesures];
unsigned int temps[nbMesures];

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterrupt(void) {
	// Calcul du temps
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - initHorloge);

	// Signaux RD et CS (fonctionne également sans eux)
	cs.off();
	rd.off();
	
	// Stockage des mesures
	mesures[compteur] = (float)(db7.isOn() * 128 + db6.isOn() * 64 + db5.isOn() * 32 + db4.isOn() * 16 + db3.isOn() * 8 + db2.isOn() * 4 + db1.isOn() * 2 + + db0.isOn() * 1);
	temps[compteur] = time_span.count() * 1000000;
	
	rd.on();
	cs.on();
	
	// Incrémentation du compteur de mesure
	compteur++;
	
	//Demande mesure
	if(compteur != nbMesures) {
		convst.pulseOnOff();
	} else {
		mesureRun = false;
	}
}


// ******************
// Fonction pricipale
// ******************
int main() {
	// Initialisation des GPIO
	convst.out();	
	convst.on();

	cs.out();	
	cs.on();

	rd.out();	
	rd.on();

	db0.in();
	db0.pullUp();

	db1.in();
	db1.pullUp();

	db2.in();
	db2.pullUp();

	db3.in();
	db3.pullUp();

	db4.in();
	db4.pullUp();

	db5.in();
	db5.pullUp();

	db6.in();
	db6.pullUp();

	db7.in();
	db7.pullUp();

	eoc.in();
	eoc.pullUp();
	eoc.fctInterrupt(Falling, &fctInterrupt);
	
	// Initialisation du temps 0 de l'horloge
	initHorloge = high_resolution_clock::now();
	
	//Demande première mesure
	convst.pulseOnOff();
	
	// Boucler tant qu'il y a des mesures a faire
	while (mesureRun) {
		cout << compteur << endl;
		delay(50);
	}
	
	// Affichage du temps de mesure
	horloge = high_resolution_clock::now();
	time_span = duration_cast<chrono::duration<double>>(horloge - initHorloge);
	cout << time_span.count() << endl;
	
	// nom du fichier
	string nomFichier = "mesures.csv";
	
	// Ecriture du fichier
	ofstream fichier(nomFichier.c_str(), ios::out | ios::trunc);
	for(int index = 0; index != nbMesures; index++) {
		fichier << temps[index]	<< ";" << (mesures[index] / 255.0 * 2) << endl;
	}
	fichier.close();
}
