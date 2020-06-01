/*
 * GestionPinGPIO.cpp
 *
 *     Created on: 31/05/2020
 *         Author: totof
 * version 2 pour librairie PIGPIO
 */

#include "GestionPinGPIO.h"
#include "Logger.h"

// ***********************
// Constructeur
// Constructeur par defaut
// ***********************
GestionPinGPIO::GestionPinGPIO() {
}

// *********************************
// Constructeur
// Mémorise le numéro de pin utilisé
// @param numéro de pin
// *********************************
GestionPinGPIO::GestionPinGPIO(PinGPIO pPinNumber) {
	Logger::log("DEBUG", "--> GestionPinGPIO::GestionPinGPIO(PinGPIO pPinNumber)");
	Logger::log("DEBUG", " pPinNumber = ", false);
	Logger::log("DEBUG", pPinNumber);	
	init(pPinNumber);
	Logger::log("DEBUG", "<-- GestionPinGPIO::GestionPinGPIO(PinGPIO pPinNumber)");
}

// ******************************************************
// Méthode init en cas d'appel au constructeur par défaut
// @param numéro de pin
// ******************************************************
void GestionPinGPIO::init(PinGPIO pPinNumber) {
	Logger::log("DEBUG", "--> GestionPinGPIO::init(PinGPIO pPinNumber)");
	Logger::log("DEBUG", " pPinNumber = ", false);
	Logger::log("DEBUG", pPinNumber);	
	pinNumber = pPinNumber;	
	Logger::log("DEBUG", "<-- GestionPinGPIO::init(PinGPIO pPinNumber)");
}

// *************************************
// Applique la direction sur une GPIO
// @param pDirection la direction
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::pinModePI(PinDirection pDirection) {
	Logger::log("DEBUG", "--> GestionPinGPIO::pinModePI(PinDirection pDirection))");
	Logger::log("DEBUG", " pDirection = ", false);
	Logger::log("DEBUG", pDirection);	
	Logger::log("DEBUG", "--> GestionPinGPIO::pinModePI(PinDirection pDirection))");
	return set_mode(GestionPin::getReturnInit(), pinNumber, pDirection);
}

// *************************************
// GPIO en entrée
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::in() {
	Logger::log("DEBUG", "--> GestionPinGPIO::in())");
	Logger::log("DEBUG", "<-- GestionPinGPIO::in())");
	return pinModePI(In);
}

// *************************************
// GPIO en sortie
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::out() {
	Logger::log("DEBUG", "--> GestionPinGPIO::out())");
	Logger::log("DEBUG", "<-- GestionPinGPIO::out())");
	return pinModePI(Out);
}

// ***********************************************
// Active/désactive les résistance de pull down/up
// @param le type de résistance
// @return 0 si ok sinon voir doc pigpio
// ***********************************************
int GestionPinGPIO::pullUpDnControlPI(Pud pNiveau) {
	Logger::log("DEBUG", "--> GestionPinGPIO::pullUpDnControlPI(Pud pNiveau))");
	Logger::log("DEBUG", " pNiveau = ", false);
	Logger::log("DEBUG", pNiveau);	
	Logger::log("DEBUG", "<-- GestionPinGPIO::pullUpDnControlPI(Pud pNiveau))");
	return set_pull_up_down(GestionPin::getReturnInit(), pinNumber, pNiveau);
}

// *************************************
// Active la résistance de pull up
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::pullUp() {
	Logger::log("DEBUG", "--> GestionPinGPIO::pullUp())");
	return pullUpDnControlPI(Up);
	Logger::log("DEBUG", "<-- GestionPinGPIO::pullUp())");
}

// *************************************
// Active la résistance de pull down
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::pullDn() {
	Logger::log("DEBUG", "--> GestionPinGPIO::pullDn())");
	Logger::log("DEBUG", "<-- GestionPinGPIO::pullDn())");
	return pullUpDnControlPI(Down);
}


// ***************************************
// Désactive la résistance de pull up/down
// @return 0 si ok sinon voir doc pigpio
// ***************************************
int GestionPinGPIO::pullOff() {
	Logger::log("DEBUG", "--> GestionPinGPIO::pullOff())");
	Logger::log("DEBUG", "<-- GestionPinGPIO::pullOff())");
	return pullUpDnControlPI(Off);
}


// *************************************
// Applique un niveau à la GPIO 
// @param le niveau
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::write(Level pValue) {
	Logger::log("DEBUG", "--> GestionPinGPIO::write(Level pValue))");
	Logger::log("DEBUG", " pValue = ", false);
	Logger::log("DEBUG", pValue);	
	Logger::log("DEBUG", "<-- GestionPinGPIO::write(Level pValue))");
	int result;
	switch(pValue) {
		case Low: result = off(); break;
		case High: result = on(); break;
	}
	return result;
}

// *************************************
// Applique un niveau bas à la GPIO 
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::off() {
	Logger::log("DEBUG", "--> GestionPinGPIO::off())");
	Logger::log("DEBUG", "<-- GestionPinGPIO::off())");
	return gpio_write(GestionPin::getReturnInit(), pinNumber, Low);
}

// *************************************
// Applique un niveau haut à la GPIO 
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::on() {
	Logger::log("DEBUG", "--> GestionPinGPIO::on())");
	Logger::log("DEBUG", "<-- GestionPinGPIO::on())");
	return gpio_write(GestionPin::getReturnInit(), pinNumber, High);
}

// *************************************
// inverse le niveau de la GPIO
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::invertState() {
	Logger::log("DEBUG", "--> GestionPinGPIO::invertState())");
	if(isOn()) {
		Logger::log("DEBUG", "<-- GestionPinGPIO::invertState())");
		return off();
	} else {
		Logger::log("DEBUG", "<-- GestionPinGPIO::invertState())");
		return on();		
	}
}

// ****************************
// Lecture du niveau de la GPIO
// @return le niveau
// ****************************
Level GestionPinGPIO::read() {
	Logger::log("DEBUG", "--> GestionPinGPIO::read())");
	if(gpio_read(GestionPin::getReturnInit(), pinNumber)) {
		Logger::log("DEBUG", "<-- GestionPinGPIO::read())");
		return High;
	} else {
		Logger::log("DEBUG", "<-- GestionPinGPIO::read())");
}		return Low;		
	}


// *************************************
// Demande si la GPIO est au niveau haut
// @return true si oui sinon false
// *************************************
bool GestionPinGPIO::isOn() {
	Logger::log("DEBUG", "--> GestionPinGPIO::isOn())");
	Level high = High;
	if(gpio_read(GestionPin::getReturnInit(), pinNumber) == high){
		Logger::log("DEBUG", "<-- GestionPinGPIO::isOn())");
		return true;
	}
	Logger::log("DEBUG", "<-- GestionPinGPIO::isOn())");
	return false;
}

// ************************************
// Demande si la GPIO est au niveau bas
// @return true si oui sinon false
// ************************************
bool GestionPinGPIO::isOff() {
	Logger::log("DEBUG", "--> GestionPinGPIO::isOff())");
	Level low = Low;
	if(gpio_read(GestionPin::getReturnInit(), pinNumber) == low){
		Logger::log("DEBUG", "<-- GestionPinGPIO::isOff())");
		return true;
	}
	Logger::log("DEBUG", "<-- GestionPinGPIO::isOff())");
	return false;
}

// ***********************************************
// Active une fonction d'interruption sur un front
// @param le front
// @param un pointeur sur la fonction
// @return 0 si ok sinon voir doc pigpio
// ***********************************************
int GestionPinGPIO::fctInterrupt(CBFunc_t intr) {
	Logger::log("DEBUG", "--> GestionPinGPIO::fctInterrupt(gpioAlertFunc_t intr))");
	Logger::log("DEBUG", " intr = ", false);
	Logger::log("DEBUG", intr);	
	Logger::log("DEBUG", "<-- GestionPinGPIO::fctInterrupt(gpioAlertFunc_t intr))");
	return callback(GestionPin::getReturnInit(), pinNumber, EITHER_EDGE, intr);
}

// *************************************
// Positionne la frequence du PWM
// @param la frequence
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::setPWMFrequency(int pFrequency) {
	Logger::log("DEBUG", "--> GestionPinGPIO::setPWMFrequency(int pFrequency))");
	Logger::log("DEBUG", " pFrequency = ", false);
	Logger::log("DEBUG", pFrequency);	
	Logger::log("DEBUG", "<-- GestionPinGPIO::setPWMFrequency(int pFrequency))");
	return set_PWM_frequency(GestionPin::getReturnInit(), pinNumber, pFrequency);
}

// *************************************
// Positionne l'echelle du PWM
// @param l'echelle
// @return 0 si ok sinon voir doc pigpio
// *************************************
int GestionPinGPIO::setPWMRange(int pRange) {
	Logger::log("DEBUG", "--> GestionPinGPIO::setPWMRange(int pRange))");
	Logger::log("DEBUG", " pRange = ", false);
	Logger::log("DEBUG", pRange);	
	Logger::log("DEBUG", "<-- GestionPinGPIO::setPWMRange(int pRange))");
	return set_PWM_range(GestionPin::getReturnInit(), pinNumber, pRange);
}

// ***************************************
// Positionne le PWM
// @param valeur du PWM (entre 0 et range)
// @return 0 si ok sinon voir doc pigpio
// ***************************************
int GestionPinGPIO::PWMOn(int pValueInRange) {
	Logger::log("DEBUG", "--> GestionPinGPIO::PWMOn(int pValueInRange))");
	Logger::log("DEBUG", " pValueInRange = ", false);
	Logger::log("DEBUG", pValueInRange);	
	Logger::log("DEBUG", "<-- GestionPinGPIO::PWMOn(int pValueInRange))");
	return set_PWM_dutycycle(GestionPin::getReturnInit(), pinNumber, pValueInRange);
	
}

// ***********************************
// Positionne le PWM à fond
// @return 0 si ok sinon voir doc pigpio
// ************************************
int GestionPinGPIO::PWMOn(void) {
	Logger::log("DEBUG", "--> GestionPinGPIO::PWMOn(void))");
	Logger::log("DEBUG", "<-- GestionPinGPIO::PWMOn(void))");
	return PWMOn(get_PWM_range(GestionPin::getReturnInit(), pinNumber));
}

// ***********************************************
// Arrete le PWM
// @return 0 si ok sinon voir doc pigpio
// ***********************************************
int GestionPinGPIO::PWMOff(void) {
	Logger::log("DEBUG", "--> GestionPinGPIO::PWMOff(void))");
	return PWMOn(0);
	Logger::log("DEBUG", "<-- GestionPinGPIO::PWMOff(void))");
}


// ******************************************
// Demande si le destructeur sera appliqué
// return destroyFlag, le flag de destructeur
// ******************************************
bool GestionPinGPIO::isToDesactivate(void) {
	Logger::log("DEBUG", "--> GestionPinGPIO::isToDesactivate(void))");
	Logger::log("DEBUG", "<-- GestionPinGPIO::isToDesactivate(void))");
	return desactivateFlag;
}

// ****************************************
// Indique que le destructeur sera appliqué
// ****************************************
void GestionPinGPIO::toDesactivate(void) {
	Logger::log("DEBUG", "--> GestionPinGPIO::toDesactivate(void))");
	setToDesactivate(true);
	Logger::log("DEBUG", "<-- GestionPinGPIO::toDesactivate(void))");
}

// ***********************************************
// Indique que le destructeur ne sera pas appliqué
// ***********************************************
void GestionPinGPIO::noDesactivate(void) {
	Logger::log("DEBUG", "--> GestionPinGPIO::noDesactivate(void))");
	setToDesactivate(false);
	Logger::log("DEBUG", "<-- GestionPinGPIO::noDesactivate(void))");
}

// ************************************
// Positionne le flag de destructeur
// @param pValue le flag de destructeur
// ************************************
void GestionPinGPIO::setToDesactivate(bool pValue) {
	Logger::log("DEBUG", "--> GestionPinGPIO::setToDesactivate(bool pValue))");
	Logger::log("DEBUG", " pValue = ", false);
	Logger::log("DEBUG", pValue);	
	desactivateFlag = pValue;
	Logger::log("DEBUG", "<-- GestionPinGPIO::setToDesactivate(bool pValue))");
}

// **********************************************************
// Destructeur
// Si le flag de destroy est activé,
// met la GPIO en entrée et désactive la résistance de rappel
// sinon, la GPIO reste en état même à la sortie du programme
// **********************************************************
GestionPinGPIO::~GestionPinGPIO() {
	Logger::log("DEBUG", "--> GestionPinGPIO::~GestionPinGPIO())");
	if(isToDesactivate()) {
		// Il faut réactiver la librairie car la fin du programme ou un CTRL-CTRL-C
		// désactive la librairie avant l'appel du destructeur
		// int returnInit = pigpio_start("192.168.1.28");
		Pud pudOff = Off;
		PinDirection in = In;
		pullUpDnControlPI(pudOff);
		pinModePI(in);
		// pigpio_stop(GestionPin::getReturnInit());
	}
	Logger::log("DEBUG", "<-- GestionPinGPIO::~GestionPinGPIO())");
}
