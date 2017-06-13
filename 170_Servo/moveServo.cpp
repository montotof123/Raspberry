//============================================================================
// Name        : moveServo.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Fait bouger un servo en utilisant les classes du servo et pwm
//============================================================================

#include <iostream>	  // impression cout
#include <signal.h>   // signal de fin de programme
#include <stdlib.h>   // La librairie standard
#include <errno.h>    // Gestion des numéros d'erreur
#include <string.h>   // Gestion des String d'erreur
#include <wiringPi.h> // La wiringPi
#include "GestionServo.h"

#define ERROR -1

// Cycle Min
#define CYCLE_MIN 27
// Cycle Min
#define CYCLE_MAX 127
// Cycle Min
#define DEBATTEMENT 170
// Temporisation pour le servo
#define TEMPORISATION 20

using namespace std;

// Objets utilisés
GestionServo servo(CYCLE_MIN, CYCLE_MAX, DEBATTEMENT);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive le servo
    servo.~GestionServo();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main()
{
    cout << "Mouvement d'un servomoteur" << endl;

    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

    // Initialisation de la librairie wiringPi
    if (wiringPiSetupGpio() < 0)
    {
        cerr << "Erreur d'initialisation de wiringPi: " <<  strerror (errno) << endl;
        exit(ERROR);
    }

    servo.init();

    if(servo.isInitError())
    {
        cerr << "Erreur d'initialisation du servomoteur: " << endl;
        exit(ERROR);
    }

    cout << "Cycle minimum = " << servo.getCycleMin() << endl;
    cout << "Cycle maximum = " << servo.getCycleMax() << endl;
    cout << "Debattement   = " << servo.getAngleDebattement() << endl;

    // 4 boucles par valeur
    for(int boucle = 0; boucle < 2; boucle ++)
    {
        for(int compteur = CYCLE_MIN; compteur <= CYCLE_MAX; compteur++)
        {
            if(servo.move(compteur) == ERROR)
            {
                cerr << "Erreur move boucle 1" << endl;
                exit(ERROR);
            }
            cout << "Valeur = " << servo.getValeur() << endl;
            cout << "Angle  = " << servo.getAngle() << endl;
            delay(TEMPORISATION);
        }
        for(int compteur = CYCLE_MAX; compteur >= CYCLE_MIN; compteur--)
        {
            if(servo.move(compteur) == ERROR)
            {
                cerr << "Erreur move boucle 2" << endl;
                exit(ERROR);
            }
            cout << "Valeur = " << servo.getValeur() << endl;
            cout << "Angle  = " << servo.getAngle() << endl;
            delay(TEMPORISATION);
        }
    }

    // 4 boucles par angle
    for(int boucle = 0; boucle < 2; boucle ++)
    {
        for(int compteur = 0; compteur <= DEBATTEMENT; compteur++)
        {
            if(servo.move((float)compteur) == ERROR)
            {
                cerr << "Erreur move boucle 1" << endl;
                exit(ERROR);
            }
            cout << "Valeur = " << servo.getValeur() << endl;
            cout << "Angle  = " << servo.getAngle() << endl;
            delay(TEMPORISATION);
        }
        for(int compteur = DEBATTEMENT; compteur >= 0; compteur--)
        {
            if(servo.move((float)compteur) == ERROR)
            {
                cerr << "Erreur move boucle 2" << endl;
                exit(ERROR);
            }
            cout << "Valeur = " << servo.getValeur() << endl;
            cout << "Angle  = " << servo.getAngle() << endl;
            delay(TEMPORISATION);
        }
    }
}
