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
#include <fstream>
#include "GestionMCP3208.h"
#include "GestionMCP4251.h"
#include "GestionSPI.h"

#define NOMBRE_MESURE 300000

int compteur = 0;
float mesures[NOMBRE_MESURE];
clock_t temps[NOMBRE_MESURE];

using namespace std;

// Objets utilisés
GestionMCP3208 mcp3208(CHANNEL_1, SPI_SPEED_50);
Channel channel = channel_0;
GestionMCP4251 mcp4251(channel);

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

	Pot pot0 = pot_0;

	cout << "reset = " << mcp4251.reset() << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 180) << endl;

	float tension;
	cout << "DEBUT mesure: " << clock() << endl;
	
	// On boucle
	while (compteur != NOMBRE_MESURE) {
		// Lecture entrée 7
		mesures[compteur] = mcp3208.readTension(VOIE_7, ALIM_33);
		temps[compteur] = clock();
		compteur++;
	}
	fin();
}
