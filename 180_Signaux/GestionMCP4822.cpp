/*
 * GestionMCP4822.cpp
 *
 *  Created on:21 octobre 2016
 *      Author: totof
 * Controle un MCP4822 avec la librairie wiringPi sur Raspberry Pi
*/
 
// ****************************************************
// Attention: la commande wiringPiSPIDataRW passe les
// octets dans l'ordre 0,1,2 etc, il faut donc inverser
// les octets 0 et 1 dans toutes les commandes 16 bits
// ainsi que dans les résultats
// ****************************************************

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>
#include <linux/spi/spidev.h>

#include "GestionMCP4822.h"
#include "GestionSPI.h"

namespace std {

// *****************************************
// Constructeur
// @param pChannel le canal de communication
// Mémorise le canal et initialise le SPI
// *****************************************
GestionMCP4822::GestionMCP4822(Channel pChannel) {
	channel = pChannel;
	Frequence frequence = speed_50;
	wiringPiSPISetup (channel, frequence);
}

// ****************************************************
// Constructeur
// @param pChannel le canal de communication
// @param pFrequence la frequence
// Mémorise le canal, la frequence et initialise le SPI
// ****************************************************
GestionMCP4822::GestionMCP4822(Channel pChannel, Frequence pFrequence) {
	channel = pChannel;
	wiringPiSPISetup (channel, pFrequence);
}

// ***********************************************
// Ecrit une valeur dans les registres 
// @param pDac le DAC
// @param pValue la valeur
// @param pGain le gain
// @param pSHDN le SHDN
// @return true si OK, false si valeur trop grande
// ***********************************************
bool GestionMCP4822::write(Dac pDac, unsigned short pValue, Gain pGain = FOIS_2, SHDN pSHDN = NO) {
	// Erreur valeur trop grande
	if(pValue > MAX_VALUE) {
		return false;
	}
	
	union spiData data;
	data.uSData = pDac | pValue | pGain | pSHDN;
	swap(data);
	wiringPiSPIDataRW (channel, data.uCData, 2);
	return true;
}

// ***********************************************
// Demande une tension precise à un DAC
// @param pDac le DAC
// @param pValue la valeur
// @return true si OK, false si valeur trop grande
// ***********************************************
bool GestionMCP4822::output(Dac pDac, float pValue){
	SHDN shutdown;
	unsigned short value;
	Gain gain;
	
	// Pas de valeur negative
	if(pValue < 0) {
		return false;
	}
	
	// Entre 0 et 2,048V
	if (pValue < MID_VALUE) {
		shutdown = NO;
		gain = FOIS_1;
		value = pValue * 1000.0 * 2;
	}
	// Entre 2,048V et 4,09599...V
	if (pValue >= MID_VALUE) {
		shutdown = NO;
		gain = FOIS_2;
		value = pValue * 1000.0;
	}
	// Au dessus de 4.096V (valeur trop grande)
	if (pValue > MAX_VALUE / 1000.0) {
		shutdown = NO;
		gain = FOIS_1;
		value = 0xFFFF;
	}
	// Haute impedance
	if(pValue == HIGH_IMPEDANCE) {
		shutdown = YES;
		value = MAX_VALUE;
		gain = FOIS_1;
	}
	return write(pDac, value, gain, shutdown);
}

// *********************
// Donne la valeur max
// @return la valeur max
// *********************
float GestionMCP4822::getMaxValue(){
	return MAX_VALUE / 1000.0;
}

// ************************************
// Donne la valeur de haute impedance
// @return la valeur de haute impedance
// ************************************
float GestionMCP4822::getHighImpedance(){
	return HIGH_IMPEDANCE;
}

// *********************************************
// swap les deux octets d'un spiData
// @param un pointeur sur la structure à swapper
// *********************************************
void GestionMCP4822::swap(spiData &data) {
	unsigned char temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}

// ***********
// Destructeur
// ***********
GestionMCP4822::~GestionMCP4822() {
	output(A, HIGH_IMPEDANCE);
	output(B, HIGH_IMPEDANCE);
}

} /* namespace std */
