/*
 * GestionAD9833.cpp
 *
 *  Created on: 12 mai 2018
 *      Author: totof
 * Controle un AD9833 en SPI avec la librairie wiringPi sur Raspberry Pi
 */
 
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "GestionAD9833.h"
#include <iostream>	  // impression cout
namespace std {

// **************************
// Constructeur
// @param pChannel le channel
// **************************
GestionAD9833::GestionAD9833(Channel pChannel) {
	init(pChannel, speed_33);
}

// ******************************
// Constructeur
// @param pChannel le channel
// @param pFrequence la frequence
// ******************************
GestionAD9833::GestionAD9833(Channel pChannel, Frequence pFrequence) {
	init(pChannel, pFrequence);
}

// **************************************
// Initialisation
// @param pChannel le channel
// @param pFrequence la frequence
// Mémorise le canal et initialise le SPI
// **************************************
void GestionAD9833::init(Channel pChannel, Frequence pFrequence) {
	channel = pChannel;
	initError = wiringPiSPISetupMode(channel, pFrequence, 2);
}

// ***************************************************
// reset le module
// @Return le resultat de l'écriture dans le canal SPI
// ***************************************************
int GestionAD9833::reset(void) {
	return write(RESET);
}

// ***************************************************************************
// Memorise une frequence dans un registre
// @Warning ne fait que memoriser, pour emettre utiliser la methode emit
// @Param le registre
// @Param la frequence en Hz
// @return le résultat du dernier write si ok, sinon une erreur d'un des write
// ***************************************************************************
int GestionAD9833::setFrequency(RegFreq pRegFreq, uint32_t pFrequency) {
	union freqData{
		uint32_t u32Data;
		uint16_t u16Data[2];
	};	
	freqData freqWord;
	if ( pFrequency > maxFrequency ) {		
		return(errorFreqTooHigh); // Erreur
	}
	freqWord.u32Data = ((double)pFrequency * (double)pow2_28) / refFrequency;
	int result = write(WRITE); 
	if(result < 0) {
		return result; // Erreur
	}
	cout << hex << "1-freqWord.u32Data = " << freqWord.u32Data << endl;
	switch(pRegFreq) {
		case RegFreq0: cout << "freqWord.u16Data[0] | FREQ0=" << ((freqWord.u16Data[0] & MASK_FREQ) | FREQ0) << endl;
						result = write((freqWord.u16Data[0] & MASK_FREQ) | FREQ0); 
			           if(result < 0) {
		                   return result; // Erreur
	                   }
					   freqWord.u32Data <<= 2; // Decale de 2 car les blocs sont de 14 bits
						cout << "2-freqWord.u32Data = " << freqWord.u32Data << endl;
						cout << "freqWord.u16Data[1] | FREQ0=" << ((freqWord.u16Data[1] & MASK_FREQ) | FREQ0) << endl;
					   result = write((freqWord.u16Data[1] & MASK_FREQ) | FREQ0); 
			           if(result < 0) {
		                   return result; // Erreur
	                   }
					   break;
		case RegFreq1: cout << "freqWord.u16Data[0] | FREQ1=" << ((freqWord.u16Data[0] & MASK_FREQ) | FREQ1) << endl;
						result = write((freqWord.u16Data[0] & MASK_FREQ) | FREQ1); 
			           if(result < 0) {
		                   return result; // Erreur
	                   }
					   freqWord.u32Data <<= 2; // Decale de 2 car les blocs sont de 14 bits
						cout << "3-freqWord.u32Data = " << freqWord.u32Data << endl;
						cout << "freqWord.u16Data[1] | FREQ1=" << ((freqWord.u16Data[1] & MASK_FREQ) | FREQ1) << dec << endl;
					   result = write((freqWord.u16Data[1] & MASK_FREQ) | FREQ1); 
			           if(result < 0) {
		                   return result; // Erreur
	                   }
					   break;
		default: return errorFreqReg;
	}
	freq[pRegFreq] = pFrequency;
	return result;
}

// ***************************************************************************
// Memorise une phase dans un registre
// @Warning ne fait que memoriser, pour emettre utiliser la methode emit
// @Param le registre
// @Param la phase en degrée
// @return le résultat du dernier write si ok, sinon une erreur d'un des write
// ***************************************************************************
int GestionAD9833::setPhase(RegPhase pRegPhase, uint16_t pPhase) {
	// Phase entre 0 et 360
	pPhase %= 360;
	uint16_t phaseVal = (uint16_t)(BITS_PER_DEG * pPhase) & 0x0FFF;
	int result = write(WRITE); 
	if(result < 0) {
		return result;  // Erreur
	}
	switch(pRegPhase) {
		case RegPhase0: result = write(phaseVal | PHASE0); 
						if(result < 0) {
							return result; // Erreur
						}
		                break;
		case RegPhase1: result = write(phaseVal | PHASE1); 
						if(result < 0) {
							return result; // Erreur
						}
		                break;
		default: return errorPhaseReg;
	}
	phase[pRegPhase] = pPhase;
	return result;
}

// ***************************************************************************
// Emet une frequence avec un phase et un type de signal
// Le registre frequence a emettre
// Le registre phase a emettre
// Le type de signal a emettre
// @return le résultat du dernier write si ok, sinon une erreur d'un des write
// ***************************************************************************
int GestionAD9833::emit(RegFreq pRegFreq, RegPhase pRegPhase, Signal pSignal) {
	uint16_t control = RUN;
	switch(pRegFreq) {
		case RegFreq0: break; // Freq0 = 0
		case RegFreq1: control |= EMIT_FREQ1; break;
	}
	switch(pRegPhase) {
		case RegPhase0: break; // Phase0 = 0
		case RegPhase1: control |= EMIT_PHASE1; break;
	}
	switch(pSignal) {
		case Sine:       break; // Sine = 0
		case Square:     control |= Square; break;
		case HalfSquare: control |= HalfSquare; break;
		case Triangle:   control |= Triangle; break;
	}
	int result = write(control);
	if(result < 0) {
		return result; // Erreur
	}
	emitRegFreq = pRegFreq;
	emitRegPhase = pRegPhase;
	emitSignal = pSignal;
	return result;
}

// *******************************************
// Donne la frequence stockee dans un registre
// @Param le registre frequence
// @Return la frequence
// *******************************************
uint32_t GestionAD9833::getFrequency(RegFreq pRegFreq) {
	return freq[pRegFreq];
}

// ***************************************
// Donne la phase stockee dans un registre
// @Param le registre phase
// @Return la phase
// ***************************************
uint16_t GestionAD9833::getPhase(RegPhase pRegPhase) {
	return phase[pRegPhase];
}

// *****************************************
// Donne le registre de la frequence emise
// @Return le registre de la frequence emise
// *****************************************
RegFreq GestionAD9833::getEmitRegFreq(void) {
	return emitRegFreq;
}

// *************************************
// Donne le registre de la phase emise
// @Return le registre de la phase emise
// *************************************
RegPhase GestionAD9833::getEmitRegPhase(void){
	return emitRegPhase;
}

// ******************************
// Donne le type de signal emit
// @Return le type de signal emit
// ******************************
Signal GestionAD9833::getEmitSignal(void){
	return emitSignal;
}

// ***************************************
// Donne le résultat de l'initialisation
// @Return Le resultat de l'initialisation
// ***************************************
int GestionAD9833::getInitError(void) {
	return initError;
}

// *********************************************
// Ecrit une valeur de 16 bits dans le canal SPI
// @param la valeur a ecrire
// *********************************************
int GestionAD9833::write(uint16_t pValeur) {
	spiData data;
	data.uSData = pValeur;
	swap(data);
	wiringPiSPIDataRW (channel, data.uCData, 2);
}

// *********************************************
// swap les deux octets d'un spiData
// @param un pointeur sur la structure à swapper
// *********************************************
void GestionAD9833::swap(spiData &data) {
	unsigned char temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}

// ***********************************************
// Destructeur
// ***********************************************
GestionAD9833::~GestionAD9833() {
}

} /* namespace std */
