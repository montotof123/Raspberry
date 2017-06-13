/*
 * GestionPWM.cpp
 *
 *  Created on: 1 août 2016
 *      Author: totof
 */

#include <wiringPi.h>
#include "GestionPWM.h"

#define diviseurMax 4096
#define precisionMax 1024
#define pwmPin 18 // PWM LED - Broadcom pin 18, P1 pin 12

// ***************************
// Constructeur
// Initialise le PWM en sortie
// ***************************
GestionPWM::GestionPWM()
{
}

// *********************
// Initialisation du pwm
// *********************
void GestionPWM::init()
{
    pinMode(pwmPin, PWM_OUTPUT);
}
// ***************************************
// Applique le mode du PWM
// @param pMode le mode
// @return 0 si OK -1 si KO (mode inconnu)
// ***************************************
int GestionPWM::mode(int pMode)
{
    int valRetour;
    switch(pMode)
    {
    case PWM_MODE_BAL:
    case PWM_MODE_MS:
        pwmSetMode(pMode);
        valRetour = 0;
        break;
    default:
        valRetour = -1;
    }
    return(valRetour);
}

// ***********************************************
// Le diviseur de fréquence de l'horloge
// @param pDiviseur la valeur du diviseur
// @return 0 si OK -1 si diviseur hors possibilite
// ***********************************************
int GestionPWM::diviseur(int pDiviseur)
{
    if(pDiviseur < diviseurMax)
    {
        pwmSetClock(pDiviseur);
        return(0);
    }
    else
    {
        return(-1);
    }
}

// **************************************************
// Précision du PWM
// @param pNbValeur le nombre de pas pour une periode
// @return 0 si OK -1 si nombre hors possibilite
// **************************************************
int GestionPWM::precision(int pNbValeur)
{
    if(pNbValeur <= precisionMax)
    {
        range = pNbValeur;
        pwmSetRange(pNbValeur);
        return(0);
    }
    else
    {
        return(-1);
    }
}

// ***************************************************
// Nombre de pas à l'état haut du PWM pour une période
// @param nombre de pas
// @return 0 si OK -1 si valeur hors possibilite
// ***************************************************
int GestionPWM::write(int pValeur)
{
    if(pValeur <= range)
    {
        pwmWrite(pwmPin, pValeur);
        return(0);
    }
    else
    {
        return(-1);
    }
}

// ****************
// Désactive le pwm
// ****************
GestionPWM::~GestionPWM()
{
    pinMode(pwmPin, INPUT);
}
