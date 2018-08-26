/*
 * GESTIONADS1115.h
 *
 *  Created on: 18 aout 2018
 *      Author: totof
 */
 
#ifndef GESTIONADS1115_H
#define GESTIONADS1115_H

#include <ads1115.h>

enum Address {
	ADDR_GND = 0x48,
	ADDR_VCC = 0x49,
	ADDR_SDA = 0x4A,
	ADDR_SCL = 0x4B
};

enum Channel {
	CHANNEL_0 = 0,
	CHANNEL_1 = 1,
	CHANNEL_2 = 2,
	CHANNEL_3 = 3,
	CHANNEL_0_1 = 4,
	CHANNEL_2_3 = 5,
	CHANNEL_0_3 = 6,
	CHANNEL_1_3 = 7
};

// Attention le rate 250 n'est pas implemente dans la lib wiringPi
enum Rate {
	RATE_8SPS = 0,
	RATE_16SPS = 1,
	RATE_32SPS = 2,
	RATE_64SPS = 3,
	RATE_128SPS = 4,
	RATE_475SPS = 5,
	RATE_860SPS = 6
};

enum Gain {
	GAIN_6_144 = 0,
	GAIN_4_096 = 1,
	GAIN_2_048 = 2,
	GAIN_1_024 = 3,
	GAIN_0_512 = 4,
	GAIN_0_256 = 5
};


class GestionADS1115 {
public:
    GestionADS1115 (Address);
    float getValue (Channel);
	void setRate(Rate);
	void setGain(Gain);
	
private:
	float tensionMax = 4.096;
};

#endif // GESTIONADS1115_H