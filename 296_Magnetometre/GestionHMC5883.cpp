/*
 * GestionHMC5883.cpp
 *
 *  Created on: 25 september 2017
 *      Author: totof
 * Controle un module HMC5883
 */
#include <math.h>
#include <list>
#include "GestionHMC5883.h"
 
// *****************
// Constructeur vide
// *****************
GestionHMC5883::GestionHMC5883() {
}

// ******************************
// Constructeur
// @Param l'adresse I2C du module
// ******************************
GestionHMC5883::GestionHMC5883(Address address) {
	init(address);
}

// ******************************
// Initialisation
// @Param l'adresse I2C du module
// ******************************
bool GestionHMC5883::init(Address address) {
	GestionI2C::init(address);
}

// ************************************************
// Positionne le nombre d'echantillonage par mesure 
// true si commande ok, sinon false
// ************************************************	
bool GestionHMC5883::setNombreMesure(NombreMesure nombreMesure) {
	return !write8(ConfigurationA, (read8(ConfigurationA) & !NombreMesureMask) | nombreMesure);
}

// **********************************************
// Donne le nombre d'echantillonage par mesures 
// @Return le nombre d'echantillonage par mesures
// **********************************************		
GestionHMC5883::NombreMesure GestionHMC5883::getNombreMesure(void) {
	switch(read8(ConfigurationA) & NombreMesureMask) {
		case _1: return _1; break;
		case _2: return _2; break;
		case _4: return _4; break;
		case _8: return _8; break;
	}
}

// ******************************************
// Positionne le nombre de mesure par seconde
// true si commande ok, sinon false
// ******************************************		
bool GestionHMC5883::setFrequence(Frequence frequence) {
	return !write8((read8(ConfigurationA) & !FrequenceMask) | frequence);
}

// ***************************************
// Donne le nombre de mesure par seconde
// @Return le nombre de mesure par seconde
// ***************************************		
GestionHMC5883::Frequence GestionHMC5883::getFrequence(void) {
	switch(read8(ConfigurationA) & FrequenceMask) {
		case _0_75: return _0_75; break;
		case _1_5: return _1_5; break;
		case _3: return _3; break;
		case _7_5: return _7_5; break;
		case _15: return _15; break;
		case _30: return _30; break;
		case _75: return _75; break;
	}
}

// ********************************
// Positionne le mode de mesure
// true si commande ok, sinon false
// ********************************		
bool GestionHMC5883::setMesurementMode(MeasurementMode measurementMode) {
	return !write8(ConfigurationA, (read8(ConfigurationA) & !MeasurementModeMask) | measurementMode);
}

// *************************
// Donne le mode de mesure
// @Return le mode de mesure
// *************************	
GestionHMC5883::MeasurementMode GestionHMC5883::getMesurementMode(void) {
	switch(read8(ConfigurationA) & MeasurementModeMask) {
		case Normal: return Normal; break;
		case PositiveBias: return PositiveBias; break;
		case NegativeBias: return NegativeBias; break;
	}
}

// ********************************
// Positionne le gain
// true si commande ok, sinon false
// ********************************		
bool GestionHMC5883::setGain(Gain gain) {
	return !write8(ConfigurationB, (read8(ConfigurationB) & !GainMask) | gain);
}

// ***************
// Donne le gain
// @Return le gain
// ***************
GestionHMC5883::Gain GestionHMC5883::getGain(void) {
	switch(read8(ConfigurationB) & GainMask) {
		case _1370: return _1370; break;
		case _1090: return _1090; break;
		case _820: return _820; break;
		case _660: return _660; break;
		case _440: return _440; break;
		case _390: return _390; break;
		case _330: return _330; break;
		case _230: return _230; break;
	}
}
		
// ********************************
// Positionne le mode d'operation
// true si commande ok, sinon false
// ********************************	
bool GestionHMC5883::setModeSelect(ModeSelect modeSelect) {
	return !write8(Mode, (read8(Mode) & !ModeMask) | modeSelect);
}

// ***************************
// Donne le mode d'operation
// @Return le mode d'operation
// ***************************
GestionHMC5883::ModeSelect GestionHMC5883::getModeSelect(void) {
	switch(read8(Mode) & ModeMask) {
		case Continu: return Continu; break;
		case SingleMesureament: return SingleMesureament; break;
		case Idle: return Idle; break;
	}
}

// *******************************
// Configuration du module
// @PAram NombreMesure
// @Param Frequence
// @Param MeasurementMode
// @Param Gain
// @Param Mode
// @Return true si ok, false sinon
// *******************************
bool GestionHMC5883::Config(NombreMesure nombreMesure, Frequence frequence, MeasurementMode measurementMode, Gain gain, ModeSelect modeSelect) {
	bool result1 = !write8(ConfigurationA, nombreMesure | frequence | measurementMode);
	bool result2 = !write8(ConfigurationB, gain);
	bool result3 = !write8(Mode, modeSelect);
	return result1 & result2 & result3;
}

// ****************
// Getter Raw Axe X
// @Return axe X
// ****************
int16_t GestionHMC5883::getRawAxeX(void) {
	i2cData data;
	data.uCData[0] = read8(DataXLSB);
	data.uCData[1] = read8(DataXMSB);
	return data.uSData;
}

// ****************
// Getter Raw Axe Y
// @Return axe Y
// ****************	
int16_t GestionHMC5883::getRawAxeY(void) {
	i2cData data;
	data.uCData[0] = read8(DataYLSB);
	data.uCData[1] = read8(DataYMSB);
	return data.uSData;
}

// ****************
// Getter Raw Axe Z
// @Return axe Z
// ****************	
int16_t GestionHMC5883::getRawAxeZ(void) {
	i2cData data;
	data.uCData[0] = read8(DataZLSB);
	data.uCData[1] = read8(DataZMSB);
	return data.uSData;
}

// ******************************
// Getter Raw Axe X from all axex
// @Return axe X
// ******************************
int16_t GestionHMC5883::getRawFromAllAxeX(void) {
	return(rawAllAxeX.uSData);
}

// ******************************
// Getter Raw Axe Y from all axex
// @Return axe Y
// ******************************	
int16_t GestionHMC5883::getRawFromAllAxeY(void) {
	return(rawAllAxeY.uSData);
}

// ******************************
// Getter Raw Axe Z from all axex
// @Return axe Z
// ******************************
int16_t GestionHMC5883::getRawFromAllAxeZ(void) {
	return(rawAllAxeZ.uSData);
}

// *********************************************
// Getter mesure sur tous les axes en même temps
// @Return liste des mesures sur tous les axes
// *********************************************
std::list<int8_t> GestionHMC5883::getRawAllAxes(void) {
    std::list<int8_t> liste = readList(DataXMSB, 6);
    
    int compteur = 0;
    for(std::list<int8_t>::iterator it = liste.begin(); it!=liste.end(); ++it)
    {
		switch(compteur) {
			case 0: rawAllAxeX.uCData[1] = *it; break;
			case 1: rawAllAxeX.uCData[0] = *it; break;
			case 2: rawAllAxeZ.uCData[1] = *it; break;
			case 3: rawAllAxeZ.uCData[0] = *it; break;
			case 4: rawAllAxeY.uCData[1] = *it; break;
			case 5: rawAllAxeY.uCData[0] = *it; break;
		}
		compteur++;
    }
	return(liste);
}
// *************************
// Donne la valeur du gain
// @Return la valeur du gain
// *************************
uint16_t GestionHMC5883::getValGain(void){
	switch(getGain()) {
		case _1370: return 1370; break;
		case _1090: return 1090; break;
		case _820 : return 820; break;
		case _660 : return 660; break;
		case _440 : return 440; break;
		case _390 : return 390; break;
		case _330 : return 330; break;
		case _230 : return 230; break;
	}
}

// **********************
// Getter Axe X in Gauss
// @Return axe X in Gauss
// **********************
float GestionHMC5883::getGaussAxeX(void) {
	return((float)getRawAxeX() / (float)getValGain());
}

// **********************
// Getter Axe Y in Gauss
// @Return axe Y in Gauss
// **********************
float GestionHMC5883::getGaussAxeY(void) {
	return((float)getRawAxeY() / (float)getValGain());
}

// **********************
// Getter Axe X in Gauss
// @Return axe X in Gauss
// **********************
float GestionHMC5883::getGaussAxeZ(void) {
	return((float)getRawAxeZ() / (float)getValGain());
}

// *********************
// Donne le cap en degre
// @Return le cap
// *********************
float GestionHMC5883::getMagneticCap(void) {	
	// calculate the heading values for all the three sensors
	// range is 0xF800 to 0x07FF or -2048 to 2047
	int16_t HX = getRawAxeX();
	int16_t HZ = getRawAxeZ();
	int16_t HY = getRawAxeY();

	// convert the numbers to fit the 
	if (HX > 0x07FF) HX = 0xFFFF - HX;
	if (HZ > 0x07FF) HZ = 0xFFFF - HZ;
	if (HY > 0x07FF) HY = 0xFFFF - HY;
  
	// declare the heading variable we'll be returning
	float H = 0;

	if (HY == 0 && HX > 0) H = 180.0;
	if (HY == 0 && HX <= 0) H = 0.0;
	if (HY > 0) H = 90.0 - atan((float)HX / (float)HY) * 180.0 / M_PI;
	if (HY < 0) H = 270.0 - atan((float)HX / (float)HY) * 180.0 / M_PI;
  
	return H;
}

// ********************************************************
// Donne le cap corrigé par la declinaison magnetic du lieu
// @Return magnetic cap
// ********************************************************
float GestionHMC5883::getCap(void) {
	float valeur = getMagneticCap() + MagneticDeclinaison;
	if(valeur < 0) {
		valeur += 360.0;
	}
	if(valeur >= 360.0) {
		valeur -= 360.0;
	}
	return valeur;
}

// *********
// Getter ID
// Return ID
// *********
std::string GestionHMC5883::getId(void) {
	std::string data;
	
	data = (char)read8(IdentificationA);
	data += (char)read8(IdentificationB);
	data += (char)read8(IdentificationC);
	return data;
}

// *****************************
// Test si c'est bien un HMC5883
// true si oui, sinon false
// *****************************
bool GestionHMC5883::isMagnetometre(void) {
	if((char)read8(IdentificationA) != 'H') return false;
	if((char)read8(IdentificationB) != '4') return false;
	if((char)read8(IdentificationC) != '3') return false;
	return true;
}

// ********************************
// Donnees verouillees
// @Return true si oui, sinon false
// ********************************
bool GestionHMC5883::isLock(void) {
	return read8(Status) & Lock;
}

// ********************************
// Donnees prete pour lecture
// @Return true si oui, sinon false
// ********************************
bool GestionHMC5883::isReady(void) {
	return read8(Status) & Ready;
}
