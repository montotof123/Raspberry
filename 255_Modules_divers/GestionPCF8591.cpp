/*
 * GestionPCF8591.cpp
 *
 * Created on 23/07/2018
 * Author Totof
 *
 */

#include "GestionPCF8591.h"

#define PCF       120
#define ADDRESS   0x48

// ***************************************************************************
// Constructeur
// @Param un flag indiquant si le setup de la librairie doit etre fait
//        utile si la classe est utilise avec la librairie de gestion des GPIO
// ***************************************************************************
GestionPCF8591::GestionPCF8591(bool setup) {
	if(setup) {
		wiringPiSetup();
	}
	pcf8591Setup(PCF, ADDRESS);
}

// ***********************
// lit un convertisseur AD
// @Param le canal
// @return la valeur lue
// ***********************
uint8_t GestionPCF8591::read(Canal canal) {
	return (uint8_t)analogRead(PCF + canal);
}

// ******************************
// Positionne le convertisseur DA
// @Param la valeur
// ******************************
void GestionPCF8591::write(uint8_t valeur) {
	analogWrite(PCF, (int)valeur);
}

// ***********
// Destructeur
// ***********
GestionPCF8591::~GestionPCF8591() {
}
