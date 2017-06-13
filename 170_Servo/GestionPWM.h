/*
 * GestionPwm.h
 *
 *  Created on: 14 août 2016
 *      Author: totof
 */

#ifndef GESTIONPWM_H_
#define GESTIONPWM_H_

// Classe de gestion du PWM
class GestionPWM
{
public:
    GestionPWM();
    void init();
    int mode(int mode);
    int diviseur(int diviseur);
    int precision(int nbValeur);
    int write(int valeur);
    virtual ~GestionPWM();

private:
    int range = 1024;
};

#endif /* GESTIONPWM_H_ */
