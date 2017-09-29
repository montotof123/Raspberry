/*
 * ListServo.h
 *
 * Created on 21/09/2017
 * Author Totof
 *
 */
 
#ifndef LISTSERVO_H_
#define LISTSERVO_H_

#include "GestionServo.h"

// Patte avant gauche
Servo Sg90_PatteFG_Bassin_PCA9685 = {105, 535, 204.0};
Servo Sg90_PatteFG_Femur_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteFG_Rotule_PCA9685 = {100, 1000, 190.0};

// Patte milieu gauche
Servo Sg90_PatteMG_Bassin_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteMG_Femur_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteMG_Rotule_PCA9685 = {100, 1000, 190.0};

// Patte arriere gauche
Servo Sg90_PatteRG_Bassin_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteRG_Femur_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteRG_Rotule_PCA9685 = {100, 1000, 190.0};

// Patte avant droite
Servo Sg90_PatteFD_Bassin_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteFD_Femur_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteFD_Rotule_PCA9685 = {100, 1000, 190.0};

// Patte milieu droite
Servo Sg90_PatteMD_Bassin_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteMD_Femur_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteMD_Rotule_PCA9685 = {100, 1000, 190.0};

// Patte arriere droite
Servo Sg90_PatteRD_Bassin_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteRD_Femur_PCA9685 = {100, 1000, 190.0};
Servo Sg90_PatteRD_Rotule_PCA9685 = {100, 1000, 190.0};

#endif