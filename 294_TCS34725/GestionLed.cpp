/*
 * GestionLed.cpp
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */

#include "GestionLed.h"

// ******************************
// Constructeur
// ******************************
GestionLed::GestionLed() {
}

// ****************************************
// Initialise la valeur avec un pourcentage
// @Param value
// ****************************************
void GestionLed::setPercent(float pPValue) {
	setValue(static_cast<uint8_t>(MAX_VALUE * pPValue));
}

// ********************
// Initialise la valeur
// @Param value
// ********************
void GestionLed::setValue(uint8_t pValue) {
	value = pValue;
}

// ***********************
// Getter du bleu
// @return composante bleu
// ***********************
uint8_t GestionLed::getValue(void) {
	return value;
}

// ******************
// Donne la MAX_VALUE
// @return MAX_VALUE
// ******************
uint8_t GestionLed::getMaxValue(void) {
	return MAX_VALUE;
}

// ************************
// Destructeur
// ************************
GestionLed::~GestionLed() {
}
