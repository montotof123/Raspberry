/*
 * GESTIONADS1115Full.h
 *
 *  Created on: 19 aout 2018
 *      Author: totof
 * Gestion du circuit ADS1115
 */
 
#ifndef GESTIONADS1115FULL_H
#define GESTIONADS1115FULL_H

#include <stdint.h>

// Adresse I2C
enum Address {
	ADDR_GND = 0x48,
	ADDR_VCC = 0x49,
	ADDR_SDA = 0x4A,
	ADDR_SCL = 0x4B
};

// Registre
enum Registre {
	CONVERSION = 0x00,
	CONFIG = 0x01,
	LOW_COMPARAISON = 0x02,
	HIGH_COMPARAISON = 0x03
};

// Mask des fonctionnalite
enum Mask {
	CHANNEL_MASK = 0x7000,
	RATE_MASK= 0x00E0,
	GAIN_MASK = 0x0E00,
	MODE_MASK = 0x0100,
	CMODE_MASK = 0x0010,
	CPOL_MASK = 0x0008,
	CLAT_MASK = 0x0004,
	CQUE_MASK = 0x0003
};

// Canaux de mesure
enum Channel {
	CHANNEL_SINGLE_0 = 0x4000,
	CHANNEL_SINGLE_1 = 0x5000,
	CHANNEL_SINGLE_2 = 0x6000,
	CHANNEL_SINGLE_3 = 0x7000,
	CHANNEL_DIFF_0_1 = 0x0000, // (default)
	CHANNEL_DIFF_2_3 = 0x1000,
	CHANNEL_DIFF_0_3 = 0x2000,
	CHANNEL_DIFF_1_3 = 0x3000,
	NO_CHANNEL = 0xFFFF
};

// Vitesse de mesure
enum Rate {
	RATE_8SPS = 0x0000,
	RATE_16SPS = 0x0020,
	RATE_32SPS = 0x0040,
	RATE_64SPS = 0x0060,
	RATE_128SPS = 0x0080, // (default)
	RATE_250SPS = 0x00A0,
	RATE_475SPS = 0x00C0,
	RATE_860SPS = 0x00E0
};

// Amplificateur
enum Gain {
	GAIN_6_144 = 0x0000,
	GAIN_4_096 = 0x0200,
	GAIN_2_048 = 0x0400, // (default)
	GAIN_1_024 = 0x0600,
	GAIN_0_512 = 0x0800,
	GAIN_0_256 = 0x0A00
};

// Mode de mesure
enum Mode {
	CONTINUOUS = 0x0000, // (default)
	SINGLE_SHOT = 0x0100
};

// Mode de comparaison
enum CMod {
	CMODE_TRAD = 0x0000,	// Traditional comparator with hysteresis (default)
	CMODE_WINDOW = 0x0010	// Window comparator
};

// Polarite de la broche de comparaison ALRT
enum CPol {
	CPOL_ACTVLOW = 0x0000,	// Active low (default)
	CPOL_ACTVHI	= 0x0008	// Active high
};	

// Verouillage de la broche ALRT
enum CLat {
	CLAT_NONLAT = 0x0000,	// Non-latching comparator (default)
	CLAT_LATCH = 0x0004		// Latching comparator
};

// Comparitor queue

enum CQue {
	CQUE_1CONV = 0x0000,	// Assert after one conversions
	CQUE_2CONV = 0x0001,	// Assert after two conversions
	CQUE_4CONV = 0x0002,	// Assert after four conversions
	CQUE_NONE = 0x0003		// Disable the comparator (default)
};

// Fonctionnement
enum Fonctionnality {
	START_CONVERSION = 0x8000,
	MESUREMENT_OK = 0x8000,
	RESET = 0x8583
};

class GestionADS1115Full {
public:
    GestionADS1115Full();
    GestionADS1115Full(Address);
	bool init(Address);
	void setRate(Rate);
	void setGain(Gain);
	void setComparator(CMod, CPol, CLat, CQue);
	void setHighValueComparator(int16_t);
	void setLowValueComparator(int16_t);	
	void setHighValueComparator(float);
	void setLowValueComparator(float);	
	void setContinuousMode(Channel);
	float getContinuousValue(void);
	void setSingleMode(void);
    float getSingleValue(Channel);
	Channel getChannelByNumber(uint8_t);
	~GestionADS1115Full();
	
private:
	int handle;
	float tensionMax = 2.048;
	uint16_t config = RESET;
	Channel canalCont; // Memorise le canal de mesure continu
};

#endif // GESTIONADS1115_H