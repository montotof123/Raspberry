/*
 * GESTIONBME280.h
 *
 *  Created on: 25 may 2017
 *      Author: totof
 */

#ifndef GESTIONBME280_H_
#define GESTIONBME280_H_

#include <stdint.h>

#define BME280 0x60
#define RESET 0xB6
#define MEAN_SEA_LEVEL_PRESSURE 1013

enum Register {
	dig_T1L = 0x88,
	dig_T1H = 0x89,
	dig_T2L = 0x8A,
	dig_T2H = 0x8B,
	dig_T3L = 0x8C,
	dig_T3H = 0x8D,
	dig_P1L = 0x8E,
	dig_P1H = 0x8F,
	dig_P2L = 0x90,
	dig_P2H = 0x91,
	dig_P3L = 0x92,
	dig_P3H = 0x93,
	dig_P4L = 0x94,
	dig_P4H = 0x95,
	dig_P5L = 0x96,
	dig_P5H = 0x97,
	dig_P6L = 0x98,
	dig_P6H = 0x99,
	dig_P7L = 0x9A,
	dig_P7H = 0x9B,
	dig_P8L = 0x9C,
	dig_P8H = 0x9D,
	dig_P9L = 0x9E,
	dig_P9H = 0x9F,
	dig_H1L = 0xA1,
	dig_H2L = 0xE1,
	dig_H2H = 0xE2,
	dig_H3L = 0xE3,
	dig_H4L = 0xE4,
	dig_H4H = 0xE5,
	dig_H5L = 0xE5,
	dig_H5H = 0xE6,
	dig_H6L = 0xE7,
	ID = 0xD0,
	reset = 0xE0,
	Ctrl_Hum = 0xF2,
	Status = 0xF3,
	Ctrl_Meas = 0xF4,
	Config = 0xF5,
	Press_Msb = 0xF7,
	Press_Lsb = 0xF8,
	Press_Xlsb = 0xF9,
	Temp_Msb = 0xFA,
	Temp_Lsb = 0xFB,
	Temp_Xlsb = 0xFC,
	Hum_Msb = 0xFD,
	Hum_Lsb = 0xFE
};

enum Oversampling {
	Skipped = 0x00, // 000
	Oversampling1 = 0x01, // 001
	Oversampling2 = 0x02, // 010
	Oversampling4 = 0x03, // 011
	Oversampling8 = 0x04, // 100
	Oversampling16 = 0x05 // 101
};

enum Mode {
	Sleep = 0x00,
	Forced = 0x01,
	Normal = 0x03
};

enum Standby {
	Stb0p5ms = 0x00, // 000
	Stb62p5ms = 0x01, // 001
	Stb125ms = 0x02, // 010
	Stb250ms = 0x03, // 011
	Stb500ms = 0x04, // 100
	Stb1000ms = 0x05, // 101
	Stb10ms = 0x06, // 110
	Stb20ms = 0x07 // 111
};

enum Filter {
	FilterOff = 0x00, // 000
	Filter2 = 0x01, // 001
	Filter4 = 0x02, // 010
	Filter8 = 0x03, // 011
	Filter16 = 0x04 // 100
};

namespace std {

// Classe de gestion du BME280
class GestionBME280 {
public:
	GestionBME280();
	
	unsigned char getId(void);
	void Reset(void);
	Oversampling getHumidityOversampling(void);
	void setHumidityOversampling(Oversampling);
	Oversampling getPressureOversampling(void);
	void setPressureOversampling(Oversampling);
	Oversampling getTemperatureOversampling(void);
	void setTemperatureOversampling(Oversampling);
	Mode getMode(void);
	void setMode(Mode);
	Standby getStandby(void);
	void setStandBy(Standby);
	Filter getFilter(void);
	void setFilter(Filter);
	void getAllMesures(void);
	double getTemperature(void);
	double getPressurePa(void);
	double getPressureHectoPa(void);
	double getHumidity(void);
	double getAltitude(void);
	double getCompensedPressurePa(double);
	double getCompensedPressureHectoPa(double);
	double getCompensedAltitude(double);
	
	virtual ~GestionBME280();
	
protected:
	virtual unsigned char read(Register) = 0;
	virtual void write(Register, unsigned char) = 0;
	void init(void);
	
private:
	bool isMesuring(void);
	bool isUpdating(void);
	bool isPossibleToReadMesure(void);
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
	uint8_t dig_H1;
	int16_t dig_H2;
	uint8_t dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t dig_H6;
	uint32_t t_fine;
	uint32_t mesurePression;
	uint32_t mesureTemperature;
	uint32_t mesureHumidity;
};

} /* namespace std */

#endif /* GESTIONBME280_H_ */
