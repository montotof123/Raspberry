/*
 * GestionPCA9685.cpp
 *
 * Created on 13/09/2017
 * Author Totof
 *
 */

#include "GestionPCA9685.h"

// *****************
// Constructeur vide
// *****************
GestionPCA9685::GestionPCA9685() {
}

// ******************************
// Constructeur
// @Param l'adresse I2C du module
// ******************************
GestionPCA9685::GestionPCA9685(Address address) {
	init(address);
}

// ******************************
// Initialisation
// @Param l'adresse I2C du module
// ******************************
void GestionPCA9685::init(Address address) {
	GestionI2C::init(address);
	//reset();
	//setPWMFreq(1000);
}

// ***************
// Reset le module
// ***************
void GestionPCA9685::reset(void) {
	write8(MODE1, 0x00); //Normal mode
	write8(MODE2, 0x04); //totem pole
}

// ************************
// Met le module en sommeil
// ************************
void GestionPCA9685::sleep(void) {
	write8(MODE1, 0x10);
}

// ****************
// Reveil le module
// ****************
void GestionPCA9685::unSleep(void) {
	write8(MODE1, 0x00);
}

// ***************************************************
// Set la frequence du pwm
// @param la frequence du pwm
// @return true si OK, false si frequence hors echelle
// ***************************************************
bool GestionPCA9685::setPWMFreq(uint16_t freq) {
	if(freq < MIN_PWM_FREQ) {
		return false;
	}
	if(freq > MAX_PWM_FREQ) {
		return false;
	}
	uint8_t prescale_val = (CLOCK_FREQ / (PWM_SCALE + 1) / freq)  - 1;
	sleep();
	write8(PRE_SCALE, prescale_val); // multiplyer for PWM frequency
	write8(MODE1, 0x80); //restart
	write8(MODE2, 0x04); //totem pole (default)
	return true;
}

// ****************************************************
// Positionne un canal PWM dont le LED_ON demarrera a 0
// @Param la led
// @Param la valeur LED_OFF
// ****************************************************
bool GestionPCA9685::setPWM(Register_Led led, uint16_t value) {
	return setPWM(led, 0, value);
}

// *********************************************************
// Positionne un canal PWM avec un pourcentage a l'etat haut
// le LED_ON demarrera a 0
// @Param la led
// @Param le pourcentage a l'etat haut
// *********************************************************
bool GestionPCA9685::setPWM(Register_Led led, float value) {
	return(setPWM(led, 0, static_cast<int>(PWM_SCALE * value)));
}

// ************************
// Positionne un canal PWM
// @Param la led
// @Param la valeur LED_ON
// @Param la valeur LED_OFF
// ************************
bool GestionPCA9685::setPWM(Register_Led led, uint16_t onValue, uint16_t offValue) {
	if(onValue < 0) {
		return false;
	}
	if(onValue > PWM_SCALE) {
		return false;
	}
	if(offValue < 0) {
		return false;
	}
	if(offValue > PWM_SCALE) {
		return false;
	}
	if(onValue >= offValue) {
		return false;
	}
	
	write8(led + ON_L, onValue & 0xFF);
	write8(led + ON_H, onValue >> 8);
	write8(led + OFF_L, offValue & 0xFF);
	write8(led + OFF_H, offValue >> 8);
}

// *********************
// Allume a font une led
// @Param la led
// *********************
void GestionPCA9685::setFullOn(Register_Led led) {
	write8(led + OFF_H, 0x00);
	write8(led + ON_H, 0x10);
}

// ***************************
// Eteint completement une led
// @Param la led
// ***************************
void GestionPCA9685::setFullOff(Register_Led led) {
	write8(led + ON_H, 0x00);
	write8(led + OFF_H, 0x10);
}

// *************************************
// Donne la valeur du LED_OFF d'un canal
// @Param la led
// @return la valeur du LED_OFF
// *************************************
uint16_t GestionPCA9685::getPWMOff(Register_Led led){
	uint16_t ledval = 0;
	ledval = read8(led + OFF_H);
	ledval = ledval & 0xF;
	ledval <<= 8;
	ledval += read8(led + OFF_L);
	return ledval;
}

// ***********************************************************
// Positionne tous les canaux PWM dont le LED_ON demarrera a 0
// @Param la valeur LED_OFF
// ***********************************************************
bool GestionPCA9685::setAllPWM(uint16_t value) {
	return setAllPWM(0, value);
}

// ****************************************************************
// Positionne tous les canaux PWM avec un pourcentage a l'etat haut
// le LED_ON demarrera a 0
// @Param le pourcentage a l'etat haut
// ****************************************************************
bool GestionPCA9685::setAllPWM(float value) {
	return(setAllPWM(0, static_cast<int>(PWM_SCALE * value)));
}

// ******************************
// Positionne tous les canaux PWM
// @Param la valeur LED_ON
// @Param la valeur LED_OFF
// ******************************
bool GestionPCA9685::setAllPWM(uint16_t onValue, uint16_t offValue) {
	if(onValue < 0) {
		return false;
	}
	if(onValue > PWM_SCALE) {
		return false;
	}
	if(offValue < 0) {
		return false;
	}
	if(offValue > PWM_SCALE) {
		return false;
	}
	if(onValue >= offValue) {
		return false;
	}
	
	write8(ALL_LED + ON_L, onValue & 0xFF);
	write8(ALL_LED + ON_H, onValue >> 8);
	write8(ALL_LED + OFF_L, offValue & 0xFF);
	write8(ALL_LED + OFF_H, offValue >> 8);
}

// *****************************
// Allume a font toutes les leds
// *****************************
void GestionPCA9685::setFullAllOn(void) {
	write8(ALL_LED + OFF_H, 0x00);
	write8(ALL_LED + ON_H, 0x10);
}

// ***********************************
// Eteint completement toutes les leds
// ***********************************
void GestionPCA9685::setFullAllOff(void) {
	write8(ALL_LED + ON_H, 0x00);
	write8(ALL_LED + OFF_H, 0x10);
}

// ******************************
// Donne l'echelle maximum du PWM
// @return la PWM_SCALE
// ******************************
uint16_t GestionPCA9685::getPWMScale(void) {
	return PWM_SCALE;
}

// ************************
// Destructeur
// Met le module en sommeil
// ************************
GestionPCA9685::~GestionPCA9685() {
	//sleep();
}
