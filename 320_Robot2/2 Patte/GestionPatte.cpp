/*
 * GestionPatte.cpp
 *
 * Created on 21/09/2017
 * Author Totof
 *
 */

#include <wiringPi.h>
 
#include "GestionPatte.h"

// *****************
// Constructeur vide
// *****************
GestionPatte::GestionPatte(){
}
// **************************************
// Constructeur
// @Param adresse du PCA9685
// @Param sortie du bassin
// @Param parametre du servo du bassin
// @Param sortie du femur
// @Param parametre du servo du femur
// @Param sortie de la rotule
// @Param parametre du servo de la rotule
// **************************************
GestionPatte::GestionPatte(GestionPCA9685 *pPca9685, 
		GestionPCA9685::Register_Led ledBassin, Servo servoBassin, 
		GestionPCA9685::Register_Led ledFemur, Servo servoFemur, 
		GestionPCA9685::Register_Led ledRotule, Servo servoRotule) {
	bassin.init(ledBassin, pPca9685, servoBassin);
	femur.init(ledFemur, pPca9685, servoFemur);
	rotule.init(ledRotule, pPca9685, servoRotule);
}
// **************************************
// initialisation si constructeur vide
// @Param adresse du PCA9685
// @Param sortie du bassin
// @Param parametre du servo du bassin
// @Param sortie du femur
// @Param parametre du servo du femur
// @Param sortie de la rotule
// @Param parametre du servo de la rotule
// **************************************
void GestionPatte::init(GestionPCA9685 *pPca9685, 
		GestionPCA9685::Register_Led ledBassin, Servo servoBassin, 
		GestionPCA9685::Register_Led ledFemur, Servo servoFemur, 
		GestionPCA9685::Register_Led ledRotule, Servo servoRotule) {
	bassin.init(ledBassin, pPca9685, servoBassin);
	femur.init(ledFemur, pPca9685, servoFemur);
	rotule.init(ledRotule, pPca9685, servoRotule);
}

// *******************************************************************
// Mouvement d'un element de la patte
// @Param l'element a bouger
// @Param valeur
// @Param delay en micro seconde entre deux changement de pwm du servo
// *******************************************************************
void GestionPatte::mouvement(GestionServoPCA9685& element, uint16_t valeur, uint32_t tempo) {
	if(tempo == 0) {
		element.write(valeur);
	} else {
		if(element.getValeur() < valeur) {
			for(uint16_t compteur = element.getValeur(); compteur != valeur; compteur++) {
				element.write(compteur);
				delayMicroseconds(tempo);
			}
		} else {
			for(uint16_t compteur = valeur; compteur != element.getValeur(); compteur--) {
				element.write(compteur);
				delayMicroseconds(tempo);
			}
		}
	}
}

// ******************
// Rotation du bassin
// @Param valeur
// ******************
void GestionPatte::rotation(uint16_t valeur) {
	mouvement(bassin, valeur, 0);
}

// ***************
// Hausse du femur
// @Param valeur
// ***************
void GestionPatte::hausse(uint16_t valeur) {
	mouvement(femur, valeur, 0);
}

// ************************
// Translation de la rotule
// @Param valeur
// ************************
void GestionPatte::translation(uint16_t valeur) {
	mouvement(rotule, valeur, 0);
}

// ************************************************************************************
// Rotation du bassin
// @Param valeur
// @Param delay en micro seconde entre deux changement de pwm pour la rotation du servo
// ************************************************************************************
void GestionPatte::rotation(uint16_t valeur, uint32_t tempo) {
	mouvement(bassin, valeur, tempo);
}

// ************************************************************************************
// Hausse du femur
// @Param valeur
// @Param delay en micro seconde entre deux changement de pwm pour la rotation du servo
// ************************************************************************************
void GestionPatte::hausse(uint16_t valeur, uint32_t tempo) {
	mouvement(femur, valeur, tempo);
}

// ************************************************************************************
// Translation de la rotule
// @Param valeur
// @Param delay en micro seconde entre deux changement de pwm pour la rotation du servo
// ************************************************************************************
void GestionPatte::translation(uint16_t valeur, uint32_t tempo) {
	mouvement(rotule, valeur, tempo);
}

// ****************
// Getter du bassin
// @Return bassin
// ****************
GestionServoPCA9685& GestionPatte::getBassin(void) {
	return bassin;
}

// ***************
// Getter du femur
// @Return femur
// ***************
GestionServoPCA9685& GestionPatte::getFemur(void) {
	return femur;
}

// ****************
// Getter du rotule
// @Return rotule
// ****************
GestionServoPCA9685& GestionPatte::getRotule(void) {
	return rotule;
}

// ***********
// Destructeur
// ***********
GestionPatte::~GestionPatte() {
}
