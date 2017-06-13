/*
 * GestionDS18B20.cpp
 *
 *  Created on: 18 march 2017
 *      Author: totof
 * Controle des thermometre 1-wire DALLAS DS18B20
 */

#include <string>
#include <list>
#include <fstream>
#include "GestionSlave1Wire.h"
#include "GestionDS18B20.h"

namespace std {

// **********************************
// Constructeur
// Memorise le chemin du peripherique
// @param le chemin du peripherique
// **********************************
GestionDS18B20::GestionDS18B20(string pAdresse) :GestionSlave1Wire(pAdresse), adresse(pAdresse){
}

// *******************
// Getter d'une mesure
// @return la mesure
// *******************
MesureDS18B20 GestionDS18B20::getMesure() {
	MesureDS18B20 mesure(getData());
	return(mesure);
}

// **************************
// Getter des donnees brutes
// @return les donnees brutes
// **************************
list<string> GestionDS18B20::getData() {
	string status;
	string valeur;
	
	ifstream fichierData(adresse + "/w1_slave", ios::in);
	if(fichierData) {
		getline(fichierData, status);
		getline(fichierData, valeur);
		fichierData.close();
	}
	list<string> data;
	data.push_back(status);
	data.push_back(valeur);
	
	return data;
}

// ***********
// Destructeur
// ***********
GestionDS18B20::~GestionDS18B20() {
}

}

