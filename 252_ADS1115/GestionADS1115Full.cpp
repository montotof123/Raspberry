/*
 * GESTIONADS1115Full.cpp
 *
 *  Created on: 19 aout 2018
 *      Author: totof
 * Gestion du circuit ADS1115
 * Full version issu de la librairie wiringPi
 */

#include <byteswap.h>
#include <stdio.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "GestionADS1115Full.h"

// *****************
// Constructeur vide
// *****************
GestionADS1115Full::GestionADS1115Full() {
}

// **************
// Constructeur
// @Param Adresse
// **************
GestionADS1115Full::GestionADS1115Full(Address address) {
    init(address);
}

// **************
// Initialisation
// @Param Adresse
// **************
bool GestionADS1115Full::init(Address address) {
	if ((handle = wiringPiI2CSetup (address)) < 0) {
		return FALSE;
	} else {
		return TRUE;
	}
}

// **********************************************
// Positionne le nombre d'echantillon par seconde
// Toujours faire avant la selection du mode
// @Param le nombre d'echantillon
// **********************************************
void GestionADS1115Full::setRate(Rate rate) {
	config &= ~RATE_MASK;
	config |= rate;
}

// *************************
// Positionne le gain du PGA
// Toujours faire avant la selection du mode
// @Param le gain
// *************************
void GestionADS1115Full::setGain(Gain gain) {
	config &= ~GAIN_MASK;
	config |= gain;
	switch(gain) {
		case GAIN_6_144: tensionMax = 6.144; break;
		case GAIN_4_096: tensionMax = 4.096; break;
		case GAIN_2_048: tensionMax = 2.048; break;
		case GAIN_1_024: tensionMax = 1.024; break;
		case GAIN_0_512: tensionMax = 0.512; break;
		case GAIN_0_256: tensionMax = 0.256; break;
	}
}

// ******************************************************
// Parametrage du comparateur
// Toujours faire avant la selection du mode
// @Param le nombre d'echantillon
// @Param le mode de comparaison
// @Param la polarite de la broche ALRT
// @Param le verouillage de la comparaison
// @Param le nombre de mesure pour activer la broche ALRT
// ******************************************************
void GestionADS1115Full::setComparator(CMod cMod, CPol cPol, CLat cLat, CQue cQue) {
	config &= ~CMODE_MASK;
	config &= ~CPOL_MASK;
	config &= ~CLAT_MASK;
	config &= ~CQUE_MASK;
	config |= cMod;
	config |= cPol;
	config |= cLat;
	config |= cQue;
}

// ******************************************
// Positionne la tension haute de comparaison
// @Param la valeur
// ******************************************
void GestionADS1115Full::setHighValueComparator(float tension) {
	setHighValueComparator((int16_t)((tension * 32768) / tensionMax));
}

// ******************************************
// Positionne la tension basse de comparaison
// @Param la valeur
// ******************************************
void GestionADS1115Full::setLowValueComparator(float tension) {
	setLowValueComparator((int16_t)((tension * 32768) / tensionMax));
}

// *****************************************
// Positionne la valeur haute de comparaison
// @Param la valeur
// *****************************************
void GestionADS1115Full::setHighValueComparator(int16_t data) {
	wiringPiI2CWriteReg16 (handle, HIGH_COMPARAISON, __bswap_16 (data)) ;
}

// *****************************************
// Positionne la valeur basse de comparaison
// @Param la valeur
// *****************************************
void GestionADS1115Full::setLowValueComparator(int16_t data) {
	wiringPiI2CWriteReg16 (handle, LOW_COMPARAISON, __bswap_16 (data)) ;
}

// ******************************************************************
// Positionne le canal de mesure et active le mode de mesure continue
// @Param le canal
// ******************************************************************
void GestionADS1115Full::setContinuousMode(Channel channel) {
	config &= ~CHANNEL_MASK;
	config |= channel;
	config &= ~MODE_MASK;
	config |= CONTINUOUS;
	wiringPiI2CWriteReg16 (handle, CONFIG, __bswap_16 (config));
}

// *********************************************************
// Valeur du canal positionne pour le mode de mesure continu
// @Return la valeur
// *********************************************************
float GestionADS1115Full::getContinuousValue(void) {
	int16_t result = wiringPiI2CReadReg16 (handle, CONVERSION);
	result = __bswap_16 (result) ;

	// Sometimes with a 0v input on a single-ended channel the internal 0v reference
	//	can be higher than the input, so you get a negative result...
	if(result < 0) {
		switch(canalCont) {
			case CHANNEL_SINGLE_0:
			case CHANNEL_SINGLE_1:
			case CHANNEL_SINGLE_2:
			case CHANNEL_SINGLE_3: result = 0;
		}
	}

    return (float) result * tensionMax / 32768.0;
}

// *******************************
// Active le mode de mesure single
// *******************************
void GestionADS1115Full::setSingleMode(void) {
	config &= ~MODE_MASK;
	config |= SINGLE_SHOT;
}

// ***************************************
// Valeur d'un canal en mode mesure simple
// @Param le canal
// @Return la valeur
// ***************************************
float GestionADS1115Full::getSingleValue(Channel channel) {
	// Positionne le canal et demande une mesure
	config &= ~CHANNEL_MASK;
	config |= channel;
	config |= START_CONVERSION;
	wiringPiI2CWriteReg16 (handle, CONFIG, __bswap_16 (config)) ;
	
	int16_t flagMeasurementConfig;
	for (;;) {
		flagMeasurementConfig =  wiringPiI2CReadReg16 (handle, CONFIG) ;
		flagMeasurementConfig = __bswap_16 (flagMeasurementConfig) ;
		if ((flagMeasurementConfig & MESUREMENT_OK) != 0) {
			break ;
		}
		delayMicroseconds (101) ; // Attention aux performances, voir http://wiringpi.com/reference/timing/
	}

	int16_t result = wiringPiI2CReadReg16 (handle, CONVERSION);
	result = __bswap_16 (result) ;

	// Sometimes with a 0v input on a single-ended channel the internal 0v reference
	//	can be higher than the input, so you get a negative result...
	if(result < 0) {
		switch(channel) {
			case CHANNEL_SINGLE_0:
			case CHANNEL_SINGLE_1:
			case CHANNEL_SINGLE_2:
			case CHANNEL_SINGLE_3: result = 0;
		}
	}

    return (float) result * tensionMax / 32768.0;
}

// ********************************************************
// Donne le canal en fonction d'un numero d'ordre predefini
// Permet de balayer plus facilement les canaux
// @Param le numero d'ordre du canal (voir code)
// @Return le canal
// ********************************************************
Channel GestionADS1115Full::getChannelByNumber(uint8_t number) {
	switch(number) {
		case 0: return(CHANNEL_SINGLE_0);
		case 1: return(CHANNEL_SINGLE_1);
		case 2: return(CHANNEL_SINGLE_2);
		case 3: return(CHANNEL_SINGLE_3);
		case 4: return(CHANNEL_DIFF_0_1);
		case 5: return(CHANNEL_DIFF_2_3);
		case 6: return(CHANNEL_DIFF_0_3);
		case 7: return(CHANNEL_DIFF_1_3);
		default: return(NO_CHANNEL);
	}
}

// *******************************
// Destructeur
// Remet le module en état de base
// *******************************
GestionADS1115Full::~GestionADS1115Full(void) {
	wiringPiI2CWriteReg16 (handle, CONFIG, __bswap_16(RESET));
}
