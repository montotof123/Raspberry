/*
 * GestionLedRGB.cpp
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */

#include "GestionLedRGB.h"

// ************
// Constructeur
// ************
GestionLedRGB::GestionLedRGB() {
}

// **************
// Constructeur
// @Param ledType
// **************
GestionLedRGB::GestionLedRGB(LedType pLedType) {
	ledType = pLedType;
}

// **************
// Setter ledType
// @Param ledType
// **************
void GestionLedRGB::setType(LedType pLedType) {
	ledType = pLedType;
}

// ***************
// Getter ledType
// @return ledType
// ***************
LedType GestionLedRGB::getType(void) {
	return ledType;
}

// *******************************************
// Initialise la couleur avec des pourcentages
// @Param rouge (entre 0 et 100)
// @Param vert (entre 0 et 100)
// @Param bleu (entre 0 et 100)
// *******************************************
void GestionLedRGB::setPercentRGB(float pPRed, float pPGreen, float pPBlue) {
	setColorRGB(static_cast<uint8_t>(MAX_VALUE * pPRed / 100.0), static_cast<uint8_t>(MAX_VALUE * pPGreen / 100.0), static_cast<uint8_t>(MAX_VALUE * pPBlue / 100.0));
}

// *********************************************
// Initialise la couleur avec les composante RGB
// @Param rouge (entre 0 et 255)
// @Param vert (entre 0 et 255)
// @Param bleu (entre 0 et 255)
// *********************************************
void GestionLedRGB::setColorRGB(uint8_t pRed, uint8_t pGreen, uint8_t pBlue) {
	red = pRed;
	green = pGreen;
	blue = pBlue;
}

// *************************************************
// Initialise la couleur avec une structure ColorRGB
// @Param la structure ColorRGB
// *************************************************
void GestionLedRGB::setColorRGB(ColorRGB couleur) {
	setColorRGB(couleur.red, couleur.green, couleur.blue);
}

// ************************
// Getter du rouge
// @return composante rouge
// ************************
uint8_t GestionLedRGB::getRed(void) {
	return red;
}

// ************************
// Getter du vert
// @return composante verte
// ************************
uint8_t GestionLedRGB::getGreen(void) {
	return green;
}

// ***********************
// Getter du bleu
// @return composante bleu
// ***********************
uint8_t GestionLedRGB::getBlue(void) {
	return blue;
}

// ******************
// Donne la MAX_VALUE
// @return MAX_VALUE
// ******************
uint8_t GestionLedRGB::getMaxValue(void) {
	return MAX_VALUE;
}

// ************************
// Destructeur
// ************************
GestionLedRGB::~GestionLedRGB() {
}
