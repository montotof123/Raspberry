/*
 * GestionBH1750.cpp
 *
 *  Created on: 5 may 2017
 *      Author: totof
 * Controle un module BH1750
 */

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "GestionBH1750.h"

namespace std {

// *************************
// Constructeur
// @param adresse du circuit 
// *************************
GestionBH1750::GestionBH1750(Adresse pAddress) {
	fd = wiringPiI2CSetup(pAddress);
	setState(BH1750_POWER_ON);
	setState(BH1750_RESET);
}

// ********************
// Activation d'un état
// @param l'état
// ********************
void GestionBH1750::setState(ModeState mode) {
    wiringPiI2CWrite(fd, mode); 
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readMinResolutionLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité max (0001_1111)
    wiringPiI2CWrite(fd, 0x40); // 01000_000
    wiringPiI2CWrite(fd, 0x7F); // 011_11111
    wiringPiI2CWrite(fd, mode);
	
	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(70); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(8); break;
	}
	
	// Mesure
	data.uSData = wiringPiI2CReadReg16(fd, 0x00);
	
	// Mise en forme
	swap(data);
	
	// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 1.08; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 0.54; break;
	}
	return valeur;
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité standard (0100_0101)
    wiringPiI2CWrite(fd, 0x42); // 01000_010
    wiringPiI2CWrite(fd, 0x65); // 011_00101
    wiringPiI2CWrite(fd, mode); 
	
	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(150); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(20); break;
	}
	
	// Mesure
	data.uSData = wiringPiI2CReadReg16(fd, 0x00);
	
	// Mise en forme
	swap(data);
	
	// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 2.4; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 1.2; break;
	}
	return valeur;
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readDoubleResolutionLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité double (1000_1010)
    wiringPiI2CWrite(fd, 0x44); // 01000_100
    wiringPiI2CWrite(fd, 0x6A); // 011_01010
    wiringPiI2CWrite(fd, mode);
	
	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(300); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(40); break;
	}
	
	// Mesure
	data.uSData = wiringPiI2CReadReg16(fd, 0x00);
	
	// Mise en forme
	swap(data);
	
	// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 4.8; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 2.4; break;
	}
	return valeur;
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readMaxResolutionLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité max (1111_1110)
    wiringPiI2CWrite(fd, 0x47); // 01000_111
    wiringPiI2CWrite(fd, 0x7E); // 011_11110
    wiringPiI2CWrite(fd, mode);
	
	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(570); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(76); break;
	}
	
	// Mesure
	data.uSData = wiringPiI2CReadReg16(fd, 0x00);
	
	// Mise en forme
	swap(data);
	
	// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 9.12; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 4.56; break;
	}
	return valeur;
}

// *********************************
// swap les deux octets d'un i2cData
// *********************************
void GestionBH1750::swap(i2cData &data) {
	unsigned char temp = data.uCData[0];
	data.uCData[0] = data.uCData[1];
	data.uCData[1] = temp;
}

// *************************
// Destructeur
// *************************
GestionBH1750::~GestionBH1750() {
	setState(BH1750_RESET);
	setState(BH1750_POWER_DOWN);
}

}

