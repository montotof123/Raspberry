/*
 * MesureDS18B20.cpp
 *
 *  Created on: 18 march 2017
 *      Author: totof
 * Mesure d'un DS18B20
 */

#include <string>
#include <list>
#include "MesureDS18B20.h"

namespace std {

// ************************************
// Constructeur
// Vide
// ************************************
MesureDS18B20::MesureDS18B20() {
}

// ****************************************************
// Constructeur
// Mets en forme une mesure a partir des donnees brutes
// @param les donnees de mesure brutes
// ****************************************************
MesureDS18B20::MesureDS18B20(list<string> pData) {
	string mesure = pData.back();
	mesure = mesure.substr(29, 5);
	temperature = (float)stoi(mesure) / 1000.0;
    pData.pop_back();
	string status = pData.back();
	status = status.substr(36, 3);
	if(status == "YES") {
		mesureState = true;
	} else {
		mesureState = false;
	}
}

// **********************
// Getter mesure OK
// @return mesure OK / KO
// **********************
bool MesureDS18B20::isMesureOK() const {
	return(mesureState);
}

// **********************
// Getter temperature
// @return la temperature
// **********************
float MesureDS18B20::getTemperature() const {
	return(temperature);
}

// ***********
// Destructeur
// ***********
MesureDS18B20::~MesureDS18B20() {
}

}

