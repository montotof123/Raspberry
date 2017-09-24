/*
 * GestionLedRGBPCA9685.cpp
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */

#include "GestionLedRGBPCA9685.h"

// ************
// Constructeur
// ************
GestionLedRGBPCA9685::GestionLedRGBPCA9685(Register_Led pRed, Register_Led pGreen, Register_Led pBlue, LedType ledType, Address address) {
	pca9685.init(address);
	ledRGB.setType(ledType);
	ledRed = pRed;
	ledGreen = pGreen;
	ledBlue = pBlue;
}

// *******************************************
// Initialise la couleur avec des pourcentages
// @Param rouge (entre 0 et 100)
// @Param vert (entre 0 et 100)
// @Param bleu (entre 0 et 100)
// *******************************************
void GestionLedRGBPCA9685::setPercentRGB(float pPRed, float pPGreen, float pPBlue) {
	ledRGB.setColorRGB(static_cast<uint8_t>(MAX_VALUE * pPRed / 100.0), static_cast<uint8_t>(MAX_VALUE * pPGreen / 100.0), static_cast<uint8_t>(MAX_VALUE * pPBlue / 100.0));
	setColorRGB(static_cast<uint8_t>(MAX_VALUE * pPRed / 100.0), static_cast<uint8_t>(MAX_VALUE * pPGreen / 100.0), static_cast<uint8_t>(MAX_VALUE * pPBlue / 100.0));
}

// *********************************************
// Initialise la couleur avec les composante RGB
// @Param rouge (entre 0 et 255)
// @Param vert (entre 0 et 255)
// @Param bleu (entre 0 et 255)
// *********************************************
void GestionLedRGBPCA9685::setColorRGB(uint8_t pRed, uint8_t pGreen, uint8_t pBlue) {
	ledRGB.setColorRGB(pRed, pGreen, pBlue);
	// Si la led est une anode commune, elle est commandée par des 0 (active niveau bas)
	if(ledRGB.getType() == CommonAnode) {
		pRed = 255 - pRed;
		pGreen = 255 - pGreen;
		pBlue = 255 - pBlue;		
	}
	
	switch(pRed) {
		case 0: pca9685.setFullOff(ledRed); break;
		case 255 : pca9685.setFullOn(ledRed); break;
		default: pca9685.setPWM (ledRed, static_cast<uint16_t>((pRed * pca9685.getPWMScale()) / getMaxValue()));
	}
	
	switch(pGreen) {
		case 0: pca9685.setFullOff(ledGreen); break;
		case 255 : pca9685.setFullOn(ledGreen); break;
		default: 	pca9685.setPWM (ledGreen, static_cast<uint16_t>((pGreen * pca9685.getPWMScale()) / getMaxValue()));
	}
	
	switch(pBlue) {
		case 0: pca9685.setFullOff(ledBlue); break;
		case 255 : pca9685.setFullOn(ledBlue); break;
		default: 	pca9685.setPWM (ledBlue, static_cast<uint16_t>((pBlue * pca9685.getPWMScale()) / getMaxValue()));
	}
}

// *************************************************
// Initialise la couleur avec une structure ColorRGB
// @Param la structure ColorRGB
// *************************************************
void GestionLedRGBPCA9685::setColorRGB(ColorRGB couleur) {
	ledRGB.setColorRGB(couleur.red, couleur.green, couleur.blue);
	setColorRGB(couleur.red, couleur.green, couleur.blue);
}

// *****************************
// Positionne le type de led RGB
// @Param le type de LED
// *****************************
void GestionLedRGBPCA9685::setTypeLed(LedType ledType) {
	ledRGB.setType(ledType);
}

// ******************
// Donne la MAX_VALUE
// @return MAX_VALUE
// ******************
uint8_t GestionLedRGBPCA9685::getMaxValue(void) {
	return MAX_VALUE;
}

// ************************
// Destructeur
// ************************
GestionLedRGBPCA9685::~GestionLedRGBPCA9685() {
}
