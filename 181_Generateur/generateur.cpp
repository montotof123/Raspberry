//=============================================================
// Name        : generateur.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Generateur de signaux carre, triangle ou sinus
//=============================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin, fonction cyclique
#include <unistd.h>	  // Delais pour les alarmes
#include <string.h>	  // String
#include <wiringPi.h>
#include "GestionMCP4822.h"
#include "LibSignal.h"

#define NOSIGNAL 0
#define CARRE 1
#define TRIANGLE 2
#define SINUS 3

using namespace std;

// Objets utilisés
GestionMCP4822 mcp4822(channel_0);
int valSignal = NOSIGNAL;
float tensionMax;
int position = 0;
Dac canal;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    // Désactive le generateur
    mcp4822.~GestionMCP4822();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// ****************
// Generateur carre
// ****************
void genCarre(int sig) {
	mcp4822.output(canal, carre[position] * tensionMax);
	position = (position + 1) % 2;
}

// *******************
// Generateur triangle
// *******************
void genTriangle(int sig) {
	mcp4822.output(canal, triangle[position] * tensionMax);
	position = (position + 1) % 20;
}

// ****************
// Generateur sinus
// ****************
void genSinus(int sig) {
	mcp4822.output(canal, sinus[position] * tensionMax);
	position = (position + 1) % 40;
}

// ******************
// Fonction pricipale
// ******************
int main(int argc, char *argv[]) {
	if(argc != 5) {
		cout << "Fonctionnement:" << endl;
		cout << "  generateur canal signal tension interruption" << endl;
		cout << "    canal : {A, B}" << endl;
		cout << "    signal : {carre, triangle, sinus}" << endl;
		cout << "    tension: tension max entre 0 et 4.095" << endl; 
		cout << "    interruption: temps en microSeconde entre deux lectures de valeur" << endl;
		cout << "  pour un même temps d'interruption, la fréquence variera en fonction du signal" << endl;
		cout << "  Le carré à 2 pas" << endl;
		cout << "  Le triangle à 20 pas" << endl;
		cout << "  Le sinus à 40 pas" << endl;
	}
	
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	// Verification et stockage canal
	bool correctCanal = false;
	if(!strcmp(argv[1], "A")) {
		canal = A;
		correctCanal = true;
	}
	if(!strcmp(argv[1], "B")) {
		canal = B;
		correctCanal = true;
	}
	if(!correctCanal) {
		exit(1);
	}
	
	// Verification et stockage tension
	tensionMax = atof(argv[3]);
	if(tensionMax > 4.095) {
		exit(3);
	}
	
	// Verification et stockage type signal
	if(!strcmp(argv[2], "carre")) {
		valSignal = CARRE;
		signal(SIGALRM, genCarre);   
	}
	if(!strcmp(argv[2], "triangle")) {
		valSignal = TRIANGLE;
		signal(SIGALRM, genTriangle);   
	}
	if(!strcmp(argv[2], "sinus")) {
		valSignal = SINUS;
		signal(SIGALRM, genSinus);   
	}
	if(valSignal == NOSIGNAL) {
		exit(2);
	}
	
	// Lancement cyclique d'une mesure
    ualarm(atoi(argv[4]), atoi(argv[4]));

	// Boucle d'attente infinie
	for(;;) {
		delay(500);
	}
}