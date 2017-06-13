/*
 * GestionServo.h
 *
 *  Created on: 14 août 2016
 *      Author: totof
 */

#ifndef GESTIONSERVO_H_
#define GESTIONSERVO_H_

#include "GestionPWM.h"

// Classe de gestion d'un servomoteur
class GestionServo
{
public:
    GestionServo(int pCycleMin, int pCycleMax);
    GestionServo(int pCycleMin, int pCycleMax, int pAngleDebattement);
    void init();
    int getCycleMin();
    int getCycleMax();
    int getAngleDebattement();
    int move(int pValeur);
    int move(float pAngle);
    int getValeur();
    float getAngle();
    int isInitError();
    virtual ~GestionServo();

private:
    void initCycles(int pCycleMin, int pCycleMax);
    int cycleMin;
    int cycleMax;
    int angleDebattement;
    int valeur = -1;
    float angle = -1.0;
    GestionPWM pwm;
    bool initError = false;
};

#endif /* GESTIONSERVO_H_ */
