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
// @Param pointeur sur PCA9685
// @Param la valeur minimum du PWM
// @Param la valeur maximum du PWM
// @Param le debattement
// *******************************
GestionServoPCA9685::GestionServoPCA9685(GestionPCA9685::Register_Led pValue, GestionPCA9685 *pPca9685, uint16_t cycleMin, uint16_t cycleMax, float debattement) {
	init(pValue, pPca9685, cycleMin, cycleMax, debattement);
}

// ***************************
// Constructeur
// @Param Le port du PCA9685
// @Param pointeur sur PCA9685
// @Param Servo
// ***************************
GestionServoPCA9685::GestionServoPCA9685(GestionPCA9685::Register_Led pValue, GestionPCA9685 *pPca9685, Servo servo) {
	init(pValue, pPca9685, servo);
}

// ***************************
// Constructeur
// @Param Le port du PCA9685
// @Param pointeur sur PCA9685
// @Param le servo
// ***************************
void GestionServoPCA9685::init(GestionPCA9685::Register_Led pValue, GestionPCA9685 *pPca9685, Servo servo) {
	init(pValue, pPca9685, servo.cycleMin, servo.cycleMax, servo.angleDebattement);
}

// *******************************
// Constructeur
// @Param Le port du PCA9685
// @Param pointeur sur PCA9685
// @Param la valeur minimum du PWM
// @Param la valeur maximum du PWM
// @Param le debattement
// *******************************
void GestionServoPCA9685::init(GestionPCA9685::Register_Led pValue, GestionPCA9685 *pPca9685, uint16_t cycleMin, uint16_t cycleMax, float debattement) {
	GestionServo::init(cycleMin, cycleMax, debattement);
	pca9685 = pPca9685;
	ledValue = pValue;
	initialisation(pca9685->getPWMScale());
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
	return pca9685->setPWM(ledValue, GestionServo::getValeur());
}

// ***************************************
// Ecrit une valeur pour parametrer le pwm
// @Return true si ok, false sinon
// ***************************************
bool GestionServoPCA9685::write(uint16_t value) {
	move(value);
	return pca9685->setPWM(ledValue, GestionServo::getValeur());
}

// ************************
// Destructeur
// ************************
GestionServoPCA9685::~GestionServoPCA9685() {
}
