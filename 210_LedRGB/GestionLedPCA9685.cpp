/*
 * GestionLedPCA9685.cpp
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */

#include "GestionLedPCA9685.h"

// ******************************
// Constructeur
// ******************************
GestionLedPCA9685::GestionLedPCA9685(Register_Led pValue, Address address) {
	pca9685.init(address);
	ledValue = pValue;
}

// ****************************************
// Initialise la valeur avec un pourcentage
// @Param value (entre 0 et 100)
// ****************************************
void GestionLedPCA9685::setPercent(float pPValue) {
	setValue(static_cast<uint8_t>(MAX_VALUE * pPValue / 100.0));
}

// *****************************
// Initialise la valeur
// @Param value (entre 0 et 255)
// *****************************
void GestionLedPCA9685::setValue(uint8_t pValue) {
	led.setValue(pValue);
	switch(pValue) {
		case 0: pca9685.setFullOff(ledValue); break;
		case 255 : pca9685.setFullOn(ledValue); break;
		default: pca9685.setPWM (ledValue, static_cast<uint16_t>((pValue * pca9685.getPWMScale()) / getMaxValue()));
	}
}

// ******************
// Donne la MAX_VALUE
// @return MAX_VALUE
// ******************
uint8_t GestionLedPCA9685::getMaxValue(void) {
	return led.getMaxValue();
}

// ************************
// Destructeur
// ************************
GestionLedPCA9685::~GestionLedPCA9685() {
}
