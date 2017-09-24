/*
 * GestionTCS34725.cpp
 *
 * Created on 09/09/2017
 * Author Totof
 *
 */

#include <stdlib.h>
#include <math.h>
#include <wiringPi.h>

#include "GestionTCS34725.h"

// **************************
// Constructeur
// @param temps d'integration
// @Param gain 
// **************************
GestionTCS34725::GestionTCS34725(IntegrationTime it, Gain gain) {
	// Initialisation de l'I2C
	init(ADDRESS);
	
	integrationTime = it;
	gain = gain;

	if (isIdentify()) {
		initialised = true;

		/* Set default integration time and gain */
		setIntegrationTime(integrationTime);
		setGain(gain);

		/* Note: by default, the device is in power down mode on bootup */
		enable();
	}
}

//***************
// Enables device
//***************
void GestionTCS34725::enable(void) {
	write8(ENABLE, PON);
	delay(3);
	write8(ENABLE, PON | AEN);  
}

//*******************************************************
// Disables device (putting it in lower power sleep mode)
//*******************************************************
void GestionTCS34725::disable(void) {
	/* Turn the device off to save power */
	uint8_t reg = 0;
	reg = read8(ENABLE);
	write8(ENABLE, reg & ~(PON | AEN));
}

// ***************************************************
// Verifie l'identite du circuit
// @return true si c'est bien un TCS34725, sinon false
// ***************************************************
bool GestionTCS34725::isIdentify(void) {
	if ((read8(ID) != IDENTIFY)) {
		return false;
	} else {
		return true;
	}
}
  
//******************************
// Sets the integration time
// @Param le temps d'integration
//******************************
void GestionTCS34725::setIntegrationTime(IntegrationTime it) {
	/* Update the timing register */
	write8(ATIME, it);

	/* Update value placeholders */
	integrationTime = it;
}

//******************************************
// Get the integration time
// @Return le temps d'integration
//******************************************
IntegrationTime GestionTCS34725::getIntegrationTime(void) {
	return integrationTime;
}

//****************************************************
// Adjusts the gain (adjusts the sensitivity to light)
// @Param le gain
//****************************************************
void GestionTCS34725::setGain(Gain pGain) {
	/* Update the timing register */
	write8(CONTROL, pGain);

	/* Update value placeholders */
	gain = pGain;
}

//****************
// Get the gain
// @Return le gain
//****************
Gain GestionTCS34725::getGain(void) {
	return gain;
}

//********************************************************
// Reads the raw red, green, blue and clear channel values
//********************************************************
void GestionTCS34725::getRawData (void) {
	clear = read16(CDATAL);
	red = read16(RDATAL);
	green = read16(GDATAL);
	blue = read16(BDATAL);
  
	// Temporise la prochaine mesure pour 
	// assurer que le temps d'integration est ecoule
	switch (integrationTime) {
    case _2_4MS:
		delay(3);
		break;
    case _24MS:
		delay(24);
		break;
    case _50MS:
		delay(50);
		break;
    case _101MS:
		delay(101);
		break;
    case _154MS:
		delay(154);
		break;
    case _700MS:
		delay(700);
		break;
	}
}

// *************
// Getter clear
// @return clear
// *************
uint16_t GestionTCS34725::getClear(void) {
	return clear;
}

// ***********
// Getter red
// @return red
// ***********
uint16_t GestionTCS34725::getRed(void) {
	return red;
}

// *************
// Getter green
// @return green
// *************
uint16_t GestionTCS34725::getGreen(void) {
	return green;
}

// ************
// Getter blue
// @return blue
// ************
uint16_t GestionTCS34725::getBlue(void) {
	return blue;
}

//*********************************************************************
// Converts the raw R/G/B values to color temperature in degrees Kelvin
// @return la temperature de couleur en degres Kelvin
//*********************************************************************
uint16_t GestionTCS34725::calculateColorTemperature(void) {
	float X, Y, Z;      /* RGB to XYZ correlation      */
	float xc, yc;       /* Chromaticity co-ordinates   */
	float n;            /* McCamy's formula            */
	float cct;

	/* 1. Map RGB values to their XYZ counterparts.    */
	/* Based on 6500K fluorescent, 3000K fluorescent   */
	/* and 60W incandescent values for a wide range.   */
	/* Note: Y = Illuminance or lux                    */
	X = (-0.14282F * red) + (1.54924F * green) + (-0.95641F * blue);
	Y = (-0.32466F * red) + (1.57837F * green) + (-0.73191F * blue);
	Z = (-0.68202F * red) + (0.77073F * green) + ( 0.56332F * blue);

	/* 2. Calculate the chromaticity co-ordinates      */
	xc = (X) / (X + Y + Z);
	yc = (Y) / (X + Y + Z);

	/* 3. Use McCamy's formula to determine the CCT    */
	n = (xc - 0.3320F) / (0.1858F - yc);

	/* Calculate the final CCT */
	cct = (449.0F * pow((double)n, 3.0)) + (3525.0F * pow((double)n, 2.0)) + (6823.3F * n) + 5520.33F;

	/* Return the results in degrees Kelvin */
	return (uint16_t)cct;
}

//*************************************
// Converts the raw R/G/B values to lux
// @Return la luminosite en lux
//*************************************
uint16_t GestionTCS34725::calculateLux(void) {
	float illuminance;

	/* This only uses RGB ... how can we integrate clear or calculate lux */
	/* based exclusively on clear since this might be more reliable?      */
	illuminance = (-0.32466F * red) + (1.57837F * green) + (-0.73191F * blue);

	return (uint16_t)illuminance;
}

// ***********************************
// Initialise la broche d'interruption
// @Param initialisation oui ou non
// ***********************************
void GestionTCS34725::setInterrupt(bool i) {
	uint8_t r = read8(ENABLE);
	if (i) {
		r |= AIEN;
	} else {
		r &= ~AIEN;
	}
	write8(ENABLE, r);
}

// ***************************************************************************
// Remet la broche INT a 0 pour aquitement et preparer l'interruption suivante
// ***************************************************************************
void GestionTCS34725::clearInterrupt(void) {
	write8(COMMAND_BIT | 0x66);
}

// ********************************************************
// Initialise les bornes de luminosite pour l'interruption
// Permet d'allumer la LED si la luminosite est trop faible
// (La broche INT doit etre connecte a la broche LED)
// @Param luminosite minimum
// @Param luminosite maximum
// ********************************************************
void GestionTCS34725::setIntLimits(uint16_t low, uint16_t high) {
   write8(AILTL, low & 0xFF);
   write8(AILTH, low >> 8);
   write8(AIHTL, high & 0xFF);
   write8(AIHTH, high >> 8);
}

// *****************************
// Destructeur, eteint le module
// *****************************
GestionTCS34725::~GestionTCS34725() {
	disable();
}
