/*
 * GESTIONAD9833.h
 *
 *  Created on: 12 mai 2018
 *      Author: totof
 */

#ifndef GESTIONAD9833_H_
#define GESTIONAD9833_H_

#include "GestionSPI.h"
#include <stdint.h>

#define RESET       0b0000000100000000
#define WRITE       0b0010000100000000	
#define RUN         0b0010000000000000	
#define FREQ0       0b0100000000000000
#define FREQ1       0b1000000000000000
#define MASK_FREQ   0b0011111111111111
#define PHASE0      0b1100000000000000
#define PHASE1      0b1110000000000000
#define EMIT_FREQ1  0b0000100000000000
#define EMIT_PHASE1 0b0000010000000000

#define maxFrequency 12.5e6
#define pow2_28	     268435456L	// 2^28 used in frequency word calculation
#define refFrequency 25000000UL
#define BITS_PER_DEG 11.3777777777778	// 4096 / 360

namespace std {
enum LstError {
	errorFreqTooHigh = -20,
	errorFreqReg = -30,
	errorPhaseReg = -40
};

enum RegFreq {
	RegFreq0,
	RegFreq1
};

enum RegPhase {
	RegPhase0,
	RegPhase1
};

enum Signal {
	Square     = 0b0000000000101000,
	HalfSquare = 0b0000000000100000,
	Sine       = 0b0000000000000000,
	Triangle   = 0b0000000000000010
};

// Classe de gestion de l'AD9833
class GestionAD9833 {
public:
	GestionAD9833(Channel);
	GestionAD9833(Channel, Frequence);
	
	void init(Channel, Frequence);
	
	int reset(void);
	int setFrequency(RegFreq, uint32_t);
	int setPhase(RegPhase, uint16_t);
	int emit(RegFreq, RegPhase, Signal);
	uint32_t getFrequency(RegFreq);
	uint16_t getPhase(RegPhase);
	RegFreq getEmitRegFreq(void);
	RegPhase getEmitRegPhase(void);
	Signal getEmitSignal(void);
	int getInitError(void);

	virtual ~GestionAD9833();
	
private:
	Channel channel;
	
	uint32_t freq[2];
	uint16_t phase[2];
	RegFreq emitRegFreq;
	RegPhase emitRegPhase;
	Signal emitSignal;;
	int initError;
	
	int write(uint16_t);
	
	union spiData{
		uint16_t uSData;
		uint8_t uCData[2];
	};	

	void swap(spiData &);
};

} /* namespace std */

#endif /* GESTIONAD9833_H_ */
