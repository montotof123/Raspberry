/*
 * GestionServo.cpp
 *
 *  Created on: 1 août 2016
 *      Author: totof
 */

#include <wiringPi.h>
#include "GestionPinPWM.h"
#include "GestionServo.h"

#define DIVISEUR 375
#define RANGE 1024
#define ERROR -1
#define DEBATTEMENT_DEFAUT 180

// ******************************************
// Constructeur
// Initialise les valeurs min et max du servo
// @param pCycleMin le cycle Min
// @param pCycleMax le cycle Max
// ******************************************
GestionServo::GestionServo(int pCycleMin, int pCycleMax)
{
    initCycles(pCycleMin, pCycleMax);
    angleDebattement = DEBATTEMENT_DEFAUT;
}

// ******************************************
// Constructeur
// Initialise les valeurs min et max du servo
// @param pCycleMin le cycle Min
// @param pCycleMax le cycle Max
// ******************************************
GestionServo::GestionServo(int pCycleMin, int pCycleMax, int pAngleDebattement)
{
    initCycles(pCycleMin, pCycleMax);
    angleDebattement = pAngleDebattement;
}

// *************************
// Initialisation des cycles
// *************************
void GestionServo::initCycles(int pCycleMin, int pCycleMax)
{
    if(pCycleMin < 0)
    {
        initError = true;
    }
    if(pCycleMax > RANGE)
    {
        initError = true;
    }
    if(!initError)
    {
        cycleMin = pCycleMin;
        cycleMax = pCycleMax;
     }
}

// *********************
// Initialisation du PWM
// *********************
void GestionServo::init()
{
    if(!initError)
    {
        pwm.init(PWM_GPIO18);
        if(pwm.setMode(PwmModeMs) == ERROR)
        {
            initError = true;
        }
        if(pwm.setDiviseur(DIVISEUR) == ERROR)
        {
            initError = true;
        }
        if(pwm.setPrecision(RANGE) == ERROR)
        {
            initError = true;
        }
    }
}

// ***********************************
// Getter de l'erreur d'initialisation
// @return true si erreur d'init
// ***********************************
int GestionServo::isInitError()
{
    return(initError);
}

// ********************
// Getter du cycle min
// @return le cycle min
// ********************
int GestionServo::getCycleMin()
{
    if(!initError)
    {
        return(cycleMin);
    }
    else
    {
        return(ERROR);
    }
}

// ********************
// Getter du cycle max
// @return le cycle max
// ********************
int GestionServo::getCycleMax()
{
    if(!initError)
    {
        return(cycleMax);
    }
    else
    {
        return(ERROR);
    }
}

// ********************************
// Getter de l'angle de debattement
// @return l'angle de debattement
// ********************************
int GestionServo::getAngleDebattement()
{
    if(!initError)
    {
        return(angleDebattement);
    }
    else
    {
        return(ERROR);
    }
}

// *********************************************
// Fait bouger le servo vers une valeur
// @param pValeur la valeur à atteindre
// @return 0 si OK -1 si valeur hors possibilite
// *********************************************
int GestionServo::move(int pValeur)
{
    if(!initError)
    {
        if(pValeur > cycleMax || pValeur < cycleMin)
        {
            // Valeur depassant les cycles
            return(ERROR);
        }
        else
        {
            if(pwm.setValue(pValeur) == ERROR)
            {
                // erreur d'écriture
                return(ERROR);
            }
            valeur = pValeur;
            angle = valeur * (float)angleDebattement / (float)(cycleMax - cycleMin) - (float)(cycleMin * angleDebattement / (float)(cycleMax - cycleMin));
            return(0);
        }
    }
    else
    {
        // Erreur à l'initialisation
        return(ERROR);
    }
}

// ********************************************
// Fait bouger le servo vers un angle
// @param pAngle l'angle à atteindre
// @return 0 si OK -1 si angle hors possibilite
// ********************************************
int GestionServo::move(float pAngle)
{
    if(pAngle > angleDebattement || pAngle < 0)
    {
        return(ERROR);
    }
    int valeur = (float)(cycleMax - cycleMin) / (float)angleDebattement * pAngle + cycleMin;
    return(move(valeur));
}

// *******************
// Getter de la valeur
// @return la valeur
// *******************
int GestionServo::getValeur()
{
    if(!initError)
    {
        return(valeur);
    }
    else
    {
        return(ERROR);
    }
}

// *****************
// Getter de l'angle
// @return l'angle
// *****************
float GestionServo::getAngle()
{
    if(!initError)
    {
        return(angle);
    }
    else
    {
        return(ERROR);
    }
}

// ******************************************
// Demande si le destructeur sera appliqué
// return destroyFlag, le flag de destructeur
// ******************************************
bool GestionServo::isToDesactivate(void) {
	return desactivateFlag;
}

// ****************************************
// Indique que le destructeur sera appliqué
// ****************************************
void GestionServo::toDesactivate(void) {
	setToDesactivate(true);
}

// ***********************************************
// Indique que le destructeur ne sera pas appliqué
// ***********************************************
void GestionServo::noDesactivate(void) {
	setToDesactivate(false);
}

// ************************************
// Positionne le flag de destructeur
// @param pValue le flag de destructeur
// ************************************
void GestionServo::setToDesactivate(bool pValue) {
	desactivateFlag = pValue;
}

// ****************
// Désactive le pwm
// ****************
GestionServo::~GestionServo()
{
 	if(isToDesactivate()) {
		pwm.noDesactivate();
	}
}
