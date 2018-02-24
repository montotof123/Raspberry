//============================================================================
// Name        : oscMesure.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Mesure du convertisseur MCP3208 pour l'oscilloscope
//============================================================================

#include <iostream>	  // impression cout
#include <signal.h>   // signal de fin de programme
#include <stdlib.h>   // La librairie standard
#include <errno.h>    // Gestion des numéros d'erreur
#include <string.h>   // Gestion des String d'erreur
#include <wiringPi.h> // La wiringPi
#include <chrono>     // Chronometre
#include <fstream>
#include "GestionMCP3208.h"

#define NOMBRE_MESURE 300000

int compteur = 0;
float mesures[NOMBRE_MESURE];
unsigned int temps[NOMBRE_MESURE];

using namespace std;
using namespace std::chrono;

// Objets utilisés
GestionMCP3208 mcp3208(CHANNEL_0, SPI_SPEED_50);
high_resolution_clock::time_point horloge;
high_resolution_clock::time_point initHorloge;
duration<double> time_span;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin()
{
	// Désactive les résistances
	cout << "NOMBRE mesure: " << compteur << endl;
	cout << "FIN mesure: " << clock() << endl;
	
	// nom du fichier
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,sizeof(buffer),"%Y%m%d%I%M%S",timeinfo);
	string str(buffer);
	string nomFichier = "mesure" + str + ".csv";
	
	// Ecriture du fichier
	ofstream fichier(nomFichier.c_str(), ios::out | ios::trunc);
	fichier << "temps;valeur" << endl;
	for(int index = 0; index != NOMBRE_MESURE; index++) {
		fichier << temps[index]	<< ";" << mesures[index] << endl;
	}
	fichier.close();
	exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Mesure du convertisseur MCP3208" << endl;

	// Ecoute du CTRL-C avec fonction à lancer
	// signal(SIGINT, fin);

	// Initialisation de la librairie wiringPi
	if (wiringPiSetupGpio() < 0) {
		cerr << "Erreur d'initialisation de wiringPi: " <<  strerror (errno) << endl;
		exit(1);
	}

	float tension;
	cout << "DEBUT mesure: " << clock() << endl;
	initHorloge = high_resolution_clock::now();
	
	// On boucle
	while (compteur != NOMBRE_MESURE) {
		// Lecture entrée 7
		horloge = high_resolution_clock::now();
		time_span = duration_cast<chrono::duration<double>>(horloge - initHorloge);
		mesures[compteur] = mcp3208.readTension(VOIE_7, ALIM_33);
		temps[compteur] = time_span.count() * 1000000;
		compteur++;
	}
	fin();
}
