/*
 * GestionBME280.cpp
 *
 *  Created on: 26 may 2017
 *      Author: totof
 * Controle un BME280
 * Cette classe n'est pas instanciable
 * elle doit être étendue par la classe GestionBMESpi ou GestionBMEI2c
*/

#include <stdint.h>
#include <math.h>

#include <wiringPi.h>
#include "GestionBME280.h"

namespace std {

// ***********************
// Constructeur par defaut
// ***********************
GestionBME280::GestionBME280() {
}

// ***********************************************************
// Initialisation du module et mise en memoire des corrections
// ***********************************************************
void GestionBME280::init() {
	union data{
		uint16_t uSData;
		int16_t sData;
		int8_t uCData[2];
	};	
		
	data compensation;
	
	// Reinitialisation
	Reset();

	// Mise en mémoire des compensations	
	compensation.uCData[0] = read(dig_T1L);
	compensation.uCData[1] = read(dig_T1H);
	dig_T1 = compensation.uSData;
	
	compensation.uCData[0] = read(dig_T2L);
	compensation.uCData[1] = read(dig_T2H);
	dig_T2 = compensation.sData;

	compensation.uCData[0] = read(dig_T3L);
	compensation.uCData[1] = read(dig_T3H);
	dig_T3 = compensation.sData;

	compensation.uCData[0] = read(dig_P1L);
	compensation.uCData[1] = read(dig_P1H);
	dig_P1 = compensation.uSData;

	compensation.uCData[0] = read(dig_P2L);
	compensation.uCData[1] = read(dig_P2H);
	dig_P2 = compensation.sData;

	compensation.uCData[0] = read(dig_P3L);
	compensation.uCData[1] = read(dig_P3H);
	dig_P3 = compensation.sData;

	compensation.uCData[0] = read(dig_P4L);
	compensation.uCData[1] = read(dig_P4H);
	dig_P4 = compensation.sData;

	compensation.uCData[0] = read(dig_P5L);
	compensation.uCData[1] = read(dig_P5H);
	dig_P5 = compensation.sData;

	compensation.uCData[0] = read(dig_P6L);
	compensation.uCData[1] = read(dig_P6H);
	dig_P6 = compensation.sData;

	compensation.uCData[0] = read(dig_P7L);
	compensation.uCData[1] = read(dig_P7H);
	dig_P7 = compensation.sData;

	compensation.uCData[0] = read(dig_P8L);
	compensation.uCData[1] = read(dig_P8H);
	dig_P8 = compensation.sData;

	compensation.uCData[0] = read(dig_P9L);
	compensation.uCData[1] = read(dig_P9H);
	dig_P9 = compensation.sData;

	dig_H1 = read(dig_H1L);
	
	compensation.uCData[0] = read(dig_H2L);
	compensation.uCData[1] = read(dig_H2H);
	dig_H2 = compensation.sData;

	dig_H3 = read(dig_H3L);
	
	dig_H4 = (read(dig_H4L) << 4) | (read(dig_H4H) & 0x0F);

	dig_H5 = (read(dig_H5H) << 4) | (read(dig_H5L) >> 4);

	dig_H6 = read(dig_H6L);

	// Initialise des parametres par defaut
	setHumidityOversampling(Oversampling2);
	setPressureOversampling(Oversampling16);
	setTemperatureOversampling(Oversampling2);
	setMode(Normal);	
	setStandBy(Stb500ms);
	setFilter(FilterOff);
	
	// Lance une premiere mesure pour qu'elles soient valides ensuite
	getAllMesures();
}

// ***********************************
// Lecture de l'identifiant du circuit
// @return l'identifiant du circuit
// ***********************************
unsigned char GestionBME280::getId() {
	return read(ID);
}

// ****************
// Reset le circuit
// ****************
void GestionBME280::Reset() {
	write(reset, RESET);
	// Attente de fin du Power-On Reset
	delay(10);
}

// ********************************************
// Lecture du sur-echantillonnage de l'humidite
// @return le sur-echantillonnage de l'humidite
// ********************************************
Oversampling GestionBME280::getHumidityOversampling() {
	Oversampling result;
	switch(read(Ctrl_Hum)) {
		case 0: result = Skipped; break;
		case 1: result = Oversampling1; break;
		case 2: result = Oversampling2; break;
		case 3: result = Oversampling4; break;
		case 4: result = Oversampling8; break;
		case 5: result = Oversampling16; break;
	}
	return result;
}

// *********************************************
// Ecriture du sur-echantillonnage de l'humidite
// @param le sur-echantillonnage de l'humidite
// *********************************************
void GestionBME280::setHumidityOversampling(Oversampling oversampling) {
	write(Ctrl_Hum, oversampling);
}

// ***********************************************
// Indique si une conversion est en cours
// @return true si conversion en cours sinon false
// ***********************************************
bool GestionBME280::isMesuring() {
	return read(Status) & 0x08;
}

// ****************************************************************
// Indique si une copie des mesures est en cours dans les registres
// @return true si copie en cours sinon false
// ****************************************************************
bool GestionBME280::isUpdating() {
	return read(Status) & 0x01;
}

// *********************************
// Indique si la mesure est possible
// @return true si oui, false sinon
// *********************************
bool GestionBME280::isPossibleToReadMesure() {
	return !(isMesuring() | isUpdating());
}

// *********************************************
// Lecture du sur-echantillonnage de la pression
// @return le sur-echantillonnage de la pression
// *********************************************
Oversampling GestionBME280::getPressureOversampling() {
	Oversampling result;
	// Ne lit que le sur-echantillonnage de la pression tttpppmm
	switch((read(Ctrl_Meas) & 0x1C) >> 2) {
		case 0: result = Skipped; break;
		case 1: result = Oversampling1; break;
		case 2: result = Oversampling2; break;
		case 3: result = Oversampling4; break;
		case 4: result = Oversampling8; break;
		case 5: result = Oversampling16; break;
	}
	return result;
}

// **********************************************
// Ecriture du sur-echantillonnage de la pression
// @param le sur-echantillonnage de la pression
// *********************************************
void GestionBME280::setPressureOversampling(Oversampling oversampling) {
	// Ne remplace que le sur-echantillonnage de la pression tttpppmm
	write(Ctrl_Meas, (read(Ctrl_Meas) & 0xE2) | (oversampling << 2));
}

// ************************************************
// Lecture du sur-echantillonnage de la temperature
// @return le sur-echantillonnage de la temperature
// ************************************************
Oversampling GestionBME280::getTemperatureOversampling() {
	Oversampling result;
	// Ne lit que le sur-echantillonnage de la temperature tttpppmm
	switch((read(Ctrl_Meas) & 0xE0) >> 5) {
		case 0: result = Skipped; break;
		case 1: result = Oversampling1; break;
		case 2: result = Oversampling2; break;
		case 3: result = Oversampling4; break;
		case 4: result = Oversampling8; break;
		case 5: result = Oversampling16; break;
	}
	return result;
}

// *************************************************
// Ecriture du sur-echantillonnage de la temperature
// @param le sur-echantillonnage de la temperature
// *************************************************
void GestionBME280::setTemperatureOversampling(Oversampling oversampling) {
	// Ne remplace que le sur-echantillonnage de la temperature tttpppmm
	write(Ctrl_Meas, (read(Ctrl_Meas) & 0x1F) | (oversampling << 5));
}

// ***************
// Lecture du mode
// @return le mode
// ***************
Mode GestionBME280::getMode() {
	Mode result;
	// Ne lit que le mode tttpppmm
	switch((read(Ctrl_Meas) & 0x03)) {
		case 0: result = Sleep; break;
		case 1: 
		case 2: result = Forced; break;
		case 3: result = Normal; break;
	}
	return result;
}

// ****************
// Ecriture du mode
// @param le mode
// ****************
void GestionBME280::setMode(Mode mode) {
	// Ne remplace que le mode tttpppmm
	write(Ctrl_Meas, (read(Ctrl_Meas) & 0xFC) | mode);
}

// ***********************************************************
// Lecture du temps d'attente entre deux mesure en mode normal
// @return le temps d'attente entre deux mesure en mode normal
// ***********************************************************
Standby GestionBME280::getStandby() {
	Standby result;
	// Ne lit que le standby entre deux mesures en mode normal
	switch((read(Config) & 0xE0) >> 5) {
		case 0: result = Stb0p5ms; break;
		case 1: result = Stb62p5ms; break;
		case 2: result = Stb125ms; break;
		case 3: result = Stb250ms; break;
		case 4: result = Stb500ms; break;
		case 5: result = Stb1000ms; break;
		case 6: result = Stb10ms; break;
		case 7: result = Stb20ms; break;
	}
	return result;
}

// ************************************************************
// Ecriture du temps d'attente entre deux mesure en mode normal
// @param le temps d'attente entre deux mesure en mode normal
// ************************************************************
void GestionBME280::setStandBy(Standby standby) {
	// Ne remplace que le standby sssfff0s
	write(Config, (read(Config) & 0x1F) | (standby << 5));
}

// *****************************************
// Lecture du coefficient pour le filtre IIR
// @return le coefficient pour le filtre IIR
// *****************************************
Filter GestionBME280::getFilter() {
	Filter result;
	// Ne lit que le filtre IIR sssfff0s
	switch((read(Config) & 0x1C) >> 2) {
		case 0: result = FilterOff; break;
		case 1: result = Filter2; break;
		case 2: result = Filter4; break;
		case 3: result = Filter8; break;
		case 4: result = Filter16; break;
		case 5: result = Filter16; break;
		case 6: result = Filter16; break;
		case 7: result = Filter16; break;
	}
	return result;
}

// ******************************************
// Ecriture du coefficient pour le filtre IIR
// @param le coefficient pour le filtre IIR
// ******************************************
void GestionBME280::setFilter(Filter filter) {
	// Ne remplace que le filtre IIR sssfff0s
	write(Config, (read(Config) & 0xE2) | (filter << 2));
}

// ************************************************************************
// Lit toutes les mesures en même temps afin d'avoir des données cohérentes
// Doit être appelé avant getTemperature, getPressure ou getHumidity
// ************************************************************************
void GestionBME280::getAllMesures() {
	// Conversion des mesures
	union data{
		uint32_t iData;
		uint8_t uCData[4];
	};
	data convMesure;
	
	// Stockage des mesures quand c'est possible
	uint8_t mesurePressMsb;
	uint8_t mesurePressLsb;
	uint8_t mesurePressXLsb;
	uint8_t mesureTempMsb;
	uint8_t mesureTempLsb;
	uint8_t mesureTempXLsb;
	uint8_t mesureHumMsb;
	uint8_t mesureHumLsb;
	bool mesureOk = false;
	
	// Il faut que les huit registres aient été lus à la suite pour que la mesure soit valide
	while(!mesureOk) {
		int nbMesureOk = 0;
		if(isPossibleToReadMesure()) {
			mesurePressMsb = read(Press_Msb);
			nbMesureOk++;
		}
		if(isPossibleToReadMesure()) {
			mesurePressLsb = read(Press_Lsb);
			nbMesureOk++;
		}
		if(isPossibleToReadMesure()) {
			mesurePressXLsb = read(Press_Xlsb);
			nbMesureOk++;
		}
		if(isPossibleToReadMesure()) {
			mesureTempMsb = read(Temp_Msb);
			nbMesureOk++;
		}
		if(isPossibleToReadMesure()) {
			mesureTempLsb = read(Temp_Lsb);
			nbMesureOk++;
		}
		if(isPossibleToReadMesure()) {
			mesureTempXLsb = read(Temp_Xlsb);
			nbMesureOk++;
		}
		if(isPossibleToReadMesure()) {
			mesureHumMsb = read(Hum_Msb);
			nbMesureOk++;
		}
		if(isPossibleToReadMesure()) {
			mesureHumLsb = read(Hum_Lsb);
			nbMesureOk++;
		}
		if(nbMesureOk == 8) {
			mesureOk = true;
		}
	}
	
	// Pression
	convMesure.uCData[3] = 0;
	convMesure.uCData[2] = mesurePressMsb;
	convMesure.uCData[1] = mesurePressLsb;
	convMesure.uCData[0] = mesurePressXLsb;
	mesurePression = convMesure.iData >> 4;
	
	// Temperature
	convMesure.uCData[3] = 0;
	convMesure.uCData[2] = mesureTempMsb;
	convMesure.uCData[1] = mesureTempLsb;
	convMesure.uCData[0] = mesureTempXLsb;
	mesureTemperature = convMesure.iData >> 4;
	
	// Humidite
	convMesure.uCData[3] = 0;
	convMesure.uCData[2] = 0;
	convMesure.uCData[1] = mesureHumMsb;
	convMesure.uCData[0] = mesureHumLsb;
	mesureHumidity = convMesure.iData;
	
	// Calcul de la correction de temperature
	double var1, var2;
	var1 = (((double)mesureTemperature) / 16384.0 - ((double)dig_T1) / 1024.0) * ((double)dig_T2);
	var2 = ((((double)mesureTemperature) / 131072.0 - ((double)dig_T1) / 8192.0) *
		(((double)mesureTemperature) / 131072.0 - ((double)dig_T1) / 8192.0)) * ((double)dig_T3);
	t_fine = var1 + var2;
}

// ************************************
// Donne la temperature en DegC
// @return temperature en Degre celcius
// ************************************
double GestionBME280::getTemperature() {
	return t_fine / 5120.0;
}

// **************************
// Donne la pression en Pa
// @return pression en Pascal
// **************************
double GestionBME280::getPressurePa() {
	double var1, var2, p;
	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
	if (var1 == 0.0) {
		return 0; // Evite une division par 0
	}
	p = 1048576.0 - (double)mesurePression;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double)dig_P7)) / 16.0;
	return p;
}

// *******************************
// Donne la pression en hPa
// @return pression en HectoPascal
// *******************************
double GestionBME280::getPressureHectoPa() {
	return getPressurePa() / 100.0;
}

// ***********************
// Donne l'Humidite en %
// @return l'Humidite en %
// ***********************
double GestionBME280::getHumidity() {
	double var_H;
	var_H = (((double)t_fine) - 76800.0);
	var_H = (mesureHumidity - (((double)dig_H4) * 64.0 + ((double)dig_H5) / 16384.0 * var_H)) *
		(((double)dig_H2) / 65536.0 * (1.0 + ((double)dig_H6) / 67108864.0 * var_H *
		(1.0 + ((double)dig_H3) / 67108864.0 * var_H)));
	var_H = var_H * (1.0 - ((double)dig_H1) * var_H / 524288.0);
	if (var_H > 100.0)
		var_H = 100.0;
	else if (var_H < 0.0)
		var_H = 0.0;
	return var_H;
}

// *********************************************************************
// Donne l'altitude en fonction de la pression
// Attention, vrai que si la pression au niveau de la mer est de 1013hPa
// @return l'altitude
// *********************************************************************
double GestionBME280::getAltitude() {
  // Equation taken from BMP180 datasheet (page 16):
  //  http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf

  // Note that using the equation from wikipedia can give bad results
  // at high altitude.  See this thread for more information:
  //  http://forums.adafruit.com/viewtopic.php?f=22&t=58064

  return 44330.0 * (1.0 - pow(getPressureHectoPa() / MEAN_SEA_LEVEL_PRESSURE, 0.190294957));
}

// ***********************************************************
// Donne la pression recalcule au niveau de la mer
// C'est cette pression qui est donnée dans les bulletin meteo
// @return la pression recalculle au niveau de la mer en Pa
// ***********************************************************
double GestionBME280::getCompensedPressurePa(double altitude) {
	double delta = pow((1.0 - 2.25577e-5 * altitude), 5.255);
	return (getPressurePa() / delta);
}
	
// ************************************************************
// Donne la pression recalcule eau niveau de la mer
// C'est cette pression qui est donnee dans les bulletins meteo
// @return la pression recalculle au niveau de la mer en hPa
// ************************************************************
double GestionBME280::getCompensedPressureHectoPa(double altitude) {
	return(getCompensedPressurePa(altitude) / 100.0);
}

// ***************************************************************
// Donne l'altitude en fonction de la pression au niveau de la mer
// @return l'altitude
// ***************************************************************
double GestionBME280::getCompensedAltitude(double seaLevelPressure) {
  return 44330.0 * (1.0 - pow(getPressureHectoPa() / seaLevelPressure, 0.190294957));
}

// ***********
// Destructeur
// ***********
GestionBME280::~GestionBME280() {
}

} /* namespace std */
