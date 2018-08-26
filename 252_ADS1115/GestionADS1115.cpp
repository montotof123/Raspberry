#include "GestionADS1115.h"

#include <ads1115.h>
#include <stdint.h>
#include <wiringPi.h>

// Le driver wiringPi ne permet pas de modifier les bits
// COMP_MODE (mode de comparaison)
// COMP_POL (polarite du bit d'alerte)
// COMP_LAT (latche du bit d'alerte)
// COMP_QUE (activation du comparateur)

static const int base = 100;

// **************
// Constructeur
// @Param Adresse
// **************
GestionADS1115::GestionADS1115(Address address) {
    ads1115Setup (base, address);
}

// *****************
// Valeur d'un canal
// @Param le canal
// @Return la valeur
// *****************
float GestionADS1115::getValue(Channel channel) {
	float value = (uint16_t) analogRead (base + channel);
    return (float) value * tensionMax / 32768.0;
}

// **********************************************
// Positionne le nombre d'echantillon par seconde
// @Param le nombre d'echantillon
// @Remarque la valeur est reellement 
//           change a la demande de lecture
// **********************************************
void GestionADS1115::setRate(Rate rate) {
	digitalWrite(101, rate);
}

// *************************
// Positionne le gain du PGA
// @Param le gain
// @Remarque la valeur est reellement 
//           change a la demande de lecture
// *************************
void GestionADS1115::setGain(Gain gain) {
	digitalWrite(100, gain);
	switch(gain) {
		case GAIN_6_144: tensionMax = 6.144; break;
		case GAIN_4_096: tensionMax = 4.096; break;
		case GAIN_2_048: tensionMax = 2.048; break;
		case GAIN_1_024: tensionMax = 1.024; break;
		case GAIN_0_512: tensionMax = 0.512; break;
		case GAIN_0_256: tensionMax = 0.256; break;
	}
}