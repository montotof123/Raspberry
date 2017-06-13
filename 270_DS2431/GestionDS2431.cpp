/*
 * GestionDS2431.cpp
 *
 *  Created on: 02 april 2017
 *      Author: totof
 * Controle des eeprom 1-wire DALLAS DS2431
 */

#include <string>
#include <list>
#include <fstream>
#include "GestionSlave1Wire.h"
#include "GestionDS2431.h"

namespace std {

// **********************************
// Constructeur
// Memorise le chemin du peripherique
// @param le chemin du peripherique
// **********************************
GestionDS2431::GestionDS2431(string pAdresse) :GestionSlave1Wire(pAdresse), adresse(pAdresse){
}

// *******************
// Getter d'un message
// @return le message
// *******************
string GestionDS2431::getMessage() {
	return(getData().back());
}

// ******************************
// Setter d'un message
// @param message
// @return true si ok sinon false
// ******************************
bool GestionDS2431::setMessage(string valeur) {
	bool result = false;
	ofstream fichierData(adresse + "/eeprom", ios::out);
	if(fichierData) {
		fichierData << valeur << endl;
		fichierData.close();
		result = true;
	}
	return(result);
}

// **************************
// Getter des donnees brutes
// @return les donnees brutes
// **************************
list<string> GestionDS2431::getData() {
	string valeur;
	
	ifstream fichierData(adresse + "/eeprom", ios::in);
	if(fichierData) {
		getline(fichierData, valeur);
		fichierData.close();
	}
	list<string> data;
	data.push_back(valeur);
	
	return data;
}

// ***********
// Destructeur
// ***********
GestionDS2431::~GestionDS2431() {
}

}

