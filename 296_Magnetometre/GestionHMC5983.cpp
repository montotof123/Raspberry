/*
 * GestionHMC5983.cpp
 *
 *  Created on: 25 september 2017
 *      Author: totof
 * Controle un module HMC5983
 */
 #include <math.h>
 #include "GestionHMC5983.h"
 
// *****************
// Constructeur vide
// *****************
GestionHMC5983::GestionHMC5983() {
}

// ******************************
// Constructeur
// @Param l'adresse I2C du module
// ******************************
GestionHMC5983::GestionHMC5983(Address address) {
	init(address);
}

// ******************************
// Initialisation
// @Param l'adresse I2C du module
// ******************************
bool GestionHMC5983::init(Address address) {
	GestionHMC5883::init(address);
}

// ********************************
// Active le senseur de temperature
// true si commande ok, sinon false
// ********************************
bool GestionHMC5983::sensorTemperatureOn(void) {
	return !write8(ConfigurationA, read8(ConfigurationA) | SensorOn);
}

// **********************************************
// Demande si le senseur de temperature est actif
// true si oui, sinon false
// **********************************************
bool GestionHMC5983::isSensorTemperatureOn(void) {
	return read8(ConfigurationA) & SensorOn;
}

// **********************************
// Deactive le senseur de temperature
// true si commande ok, sinon false
// **********************************
bool GestionHMC5983::sensorTemperatureOff(void) {
	return !write8(ConfigurationA, read8(ConfigurationA) & !SensorOn);
}

// *************************************************
// Demande si le senseur de temperature est deactive
// true si oui, sinon false
// *************************************************
bool GestionHMC5983::isSensorTemperatureOff(void) {
	return !read8(ConfigurationA) & SensorOn;
}

// ********************************
// Passe l'I2C en high speed mode
// true si commande ok, sinon false
// ********************************		
bool GestionHMC5983::setHighSpeedI2COn(void) {
	return !write8(Mode, read8(Mode) | HighSpeedI2C);
}

// ***************************************
// Indique si l'I2C est en high speed mode
// true si oui, false sinon
// ***************************************
bool GestionHMC5983::isHighSpeedI2COn(void) {
	return read8(Mode) & HighSpeedI2C;
}
	
// ********************************
// Passe l'I2C en low speed mode
// true si commande ok, sinon false
// ********************************		
bool GestionHMC5983::setHighSpeedI2COff(void) {
	return !write8(Mode, read8(Mode) & !HighSpeedI2C);
}

// ***************************************
// Indique si l'I2C est en low speed mode
// true si oui, false sinon
// ***************************************
bool GestionHMC5983::isHighSpeedI2COff(void) {
	return !read8(Mode) & HighSpeedI2C;
}
	
// **********************************
// Passe le module en puissance basse
// true si commande ok, sinon false
// **********************************	
bool GestionHMC5983::setPowerLowOn(void) {
	return !write8(Mode, read8(Mode) | PowerLow);}

// ***************************************
// Indique si le module en puissance basse
// true si oui, false sinon
// ***************************************
bool GestionHMC5983::isPowerLowOn(void) {
	return read8(Mode) & PowerLow;
}
		
// ***********************************
// Passe le module en puissance normal
// true si commande ok, sinon false
// ***********************************	
bool GestionHMC5983::setPowerLowOff(void) {
	return !write8(Mode, read8(Mode) & !PowerLow);
}

// ****************************************
// Indique si le module en puissance normal
// true si oui, false sinon
// ****************************************
bool GestionHMC5983::isPowerLowOff(void) {
	return !read8(Mode) & PowerLow;
}
		
// *******************************
// Configuration du module
// @Param Temperature
// @PAram NombreMesure
// @Param Frequence
// @Param MeasurementMode
// @Param Gain
// @Param Mode
// @Return true si ok, false sinon
// *******************************
bool GestionHMC5983::Config(Temperature temperature, NombreMesure nombreMesure, Frequence frequence, MeasurementMode measurementMode, Gain gain, ModeSelect modeSelect) {
	bool result1 = !write8(ConfigurationA, temperature | nombreMesure | frequence | measurementMode);
	bool result2 = !write8(ConfigurationB, gain);
	bool result3 = !write8(Mode, modeSelect);
	return result1 & result2 & result3;
}

// ************************************
// Getter de la temperature
// @Return temperature en degre celcius
// ************************************
float GestionHMC5983::getTemperature(void) {
	i2cData data;
	data.uCData[0] = read8(TemperatureLSB);
	data.uCData[1] = read8(TemperatureMSB);
	return (float)data.uSData / 128.0 + 25.0;
}

// ********************************
// Donnees ecrasees
// @Return true si oui, sinon false
// ********************************
bool GestionHMC5983::isOverWritten(void) {
	return read8(Status) & OverWritten;
}
