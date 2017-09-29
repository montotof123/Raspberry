/*
 * GestionServoPCA9685.cpp
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */

#include "GestionServoPCA9685.h"

// *****************
// Constructeur vide
// *****************
GestionServoPCA9685::GestionServoPCA9685() {
}

// *******************************
// Constructeur
// @Param Le port du PCA9685
// @Param L'adresse du PCA9685
// @Param la valeur minimum du PWM
// @Param la valeur maximum du PWM
// @Param le debattement
// *******************************
GestionServoPCA9685::GestionServoPCA9685(Register_Led pValue, Address address, uint16_t cycleMin, uint16_t cycleMax, float debattement) {
	init(pValue, address, cycleMin, cycleMax, debattement);
}

// ***************************
// Constructeur
// @Param Le port du PCA9685
// @Param L'adresse du PCA9685
// @Param Servo
// ***************************
GestionServoPCA9685::GestionServoPCA9685(Register_Led pValue, Address address, Servo servo) {
	init(pValue, address, servo);
}

// *******************************
// Constructeur
// @Param Le port du PCA9685
// @Param L'adresse du PCA9685
// @Param la valeur minimum du PWM
// @Param la valeur maximum du PWM
// @Param le debattement
// *******************************
void GestionServoPCA9685::init(Register_Led pValue, Address address, Servo servo) {
	init(pValue, address, servo.cycleMin, servo.cycleMax, servo.angleDebattement);
}

// *******************************
// Constructeur
// @Param Le port du PCA9685
// @Param L'adresse du PCA9685
// @Param la valeur minimum du PWM
// @Param la valeur maximum du PWM
// @Param le debattement
// *******************************
void GestionServoPCA9685::init(Register_Led pValue, Address address, uint16_t cycleMin, uint16_t cycleMax, float debattement) {
	GestionServo::init(cycleMin, cycleMax, debattement);
	pca9685.init(address);
	pca9685.setPWMFreq(_50HZ);
	ledValue = pValue;
	initialisation(pca9685.getPWMScale());
}

// ***********************************
// Valide l'initialisation
// @Param l'echelle totale du pwm
// @return true si init ok sinon false 
// ***********************************
bool GestionServoPCA9685::initialisation(uint16_t scale) {
	fullInit = true;
	if(cycleMin < 0) {
		fullInit = false;
	}
	if(cycleMax > scale) {
		fullInit = false;
	}

	return fullInit;
}

// ***************************************
// Ecrit une valeur pour parametrer le pwm
// @Return true si ok, false sinon
// ***************************************
bool GestionServoPCA9685::write(float angle) {
	move(angle);
	return pca9685.setPWM(ledValue, GestionServo::getValeur());
}

// ***************************************
// Ecrit une valeur pour parametrer le pwm
// @Return true si ok, false sinon
// ***************************************
bool GestionServoPCA9685::write(uint16_t value) {
	move(value);
	return pca9685.setPWM(ledValue, GestionServo::getValeur());
}

// ************************
// Destructeur
// ************************
GestionServoPCA9685::~GestionServoPCA9685() {
}
