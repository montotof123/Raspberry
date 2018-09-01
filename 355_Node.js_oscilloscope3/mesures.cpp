//=================================================================
// Name        : mesure.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Mesure du convertisseur MCP3208 pour l'oscilloscope
//==================================================================
#include <stdlib.h>   // La librairie standard
#include <errno.h>    // Gestion des numéros d'erreur
#include <string.h>   // Gestion des String d'erreur
#include <wiringPi.h> // La wiringPi
#include <chrono>     // Chronometre
#include <iostream>	  // impression cout
#include <fstream>
#include "GestionMCP3208.h"

using namespace std;
using namespace std::chrono;

// ******************
// Fonction pricipale
// ******************
int main(int argc, char *argv[]) {
	// AIde si on lance le programme sans paramètre
	if(argc != 3) {
		cout << "usage:" << endl;
		cout << "   mesure canal nbMesure" << endl;
		cout << "exemple:" << endl;
		cout << "   mesure 7 20000" << endl;
		cout << "   faire 20000 mesures sur le canal 7 du MCP3208" << endl;
		exit(1);
	}
	// Récupération du nombre de mesure a faire
	int nombreMesure = atoi(argv[2]);
	int compteur = 0;
	// tableau des mesures
	float mesures[nombreMesure];
	unsigned int temps[nombreMesure];
	
	// Objets utilisés
	GestionMCP3208 mcp3208(CHANNEL_0, SPI_SPEED_MAX);
	high_resolution_clock::time_point horloge;
	high_resolution_clock::time_point initHorloge;
	duration<double> time_span;
	
	// Initialisation du temps 0 de l'horloge
	initHorloge = high_resolution_clock::now();
	
	// Boucler sur le nombre de mesures
	while (compteur != nombreMesure) {
		// Calcul du temps
		horloge = high_resolution_clock::now();
		time_span = duration_cast<chrono::duration<double>>(horloge - initHorloge);
		// Stockage des mesures
		mesures[compteur] = mcp3208.readTension(atoi(argv[1]), ALIM_5);
		temps[compteur] = time_span.count() * 1000000;
		// Incrémentation du compteur de mesure
		compteur++;
	}
	// nom du fichier
	string nomFichier = "mesures.csv";
	
	// Ecriture du fichier
	ofstream fichier(nomFichier.c_str(), ios::out | ios::trunc);
	for(int index = 0; index != nombreMesure; index++) {
		fichier << temps[index]	<< ";" << mesures[index] << endl;
	}
	fichier.close();
}
