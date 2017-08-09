/*
 * GestionSlave1Wire.cpp
 *
 *  Created on: 18 march 2017
 *      Author: totof
 * Controle des esclaves 1-wire
 */

#include <string>
#include <list>
#include <fstream>

#include "GestionSlave1Wire.h"

namespace std {

// ************************************
// Constructeur
// Vide
// ************************************
GestionSlave1Wire::GestionSlave1Wire() {
}

// *****************************************************
// Constructeur
// Initialise le nom et les identifiants du peripherique
// @param le chemin du peripherique
// *****************************************************
GestionSlave1Wire::GestionSlave1Wire(string pAdresse) {
	// Récupération du nom
	ifstream fichierName(pAdresse + "/name", ios::in);
	if(fichierName) {
		getline(fichierName, nom);
		fichierName.close();
	}
	// Récupération FID et slaveID
	ifstream fichierID(pAdresse + "/uevent", ios::in);
	string tempo;
	if(fichierID) {
		getline(fichierID, tempo);
		getline(fichierID, tempo);
		tempo = tempo.substr(7, 2);
		FID = stoi(tempo);
		getline(fichierID, slaveID);
		slaveID = slaveID.substr(13);
		fichierID.close();
	}
}

// **************
// Getter du nom
// @return le nom
// **************
string GestionSlave1Wire::getNom() const {
	return(nom);
}

// **************
// Getter du FID
// @return le FID
// **************
unsigned short GestionSlave1Wire::getFID() const {
	return(FID);
}

// *******************
// Getter du slaveFID
// @return le slaveFID
// *******************
string GestionSlave1Wire::getSlaveID() const {
	return(slaveID);
}

// ***********
// Destructeur
// ***********
GestionSlave1Wire::~GestionSlave1Wire() {
}

}

