/*********************************************************************
 *   \file    tstMatrix.cpp
 *   \brief   Programme affichant une heure aléatoire sur les matrices
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    30/12/2020
 ********************************************************************/
 
#include <iostream>
#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>

#include "GestionMatrix.h"

using namespace std;

/**
 * \brief   Fonction de fin déclenchée par CTRL-C. 
 *
 * \details Force à sortir proprement du programme.
*
 * \param   sig Le signal d'interruption ayant déclenché la fonction (ici sigint).
 */
void fin(int sig) 
{
	cout << "Fin" << endl;
	exit(0);
}

GestionMatrix matrix(true);

/**
 * \brief   Affiche toutes les 1/2 seconde une heure aléatoire sur la matrice, fin par CTRL-C. 
 */
int main(void) 
{
	signal(SIGINT, fin);

	// Initialise la fonction random.
	srand (time(NULL));

	// Environ 300s soit 5mn.
	for(int compteur = 0; compteur != 600; compteur++) { 
		srand (time(NULL));
		// Dizaine d'heures de 0 à 2.
		uint8_t nbDizaineHeure = rand()% 3;
		// Heures de 0 à 9 ou de 0 à 3 si les dizaines d'heures sont à 2.
		uint8_t nbHeure;
		if(nbDizaineHeure == 2) {
			nbHeure = rand() % 4;
		} else {
			nbHeure = rand() % 10;
		}
		//Dizaine de minutes de 0 à 6.
		uint8_t nbDizaineMinute = rand() % 6;
		// Minutes de 0 à 9.
		uint8_t nbMinute = rand() % 10;
		cout << (int)nbDizaineHeure << " " << (int)nbHeure << " " << (int)nbDizaineMinute << " " << (int)nbMinute << " " << endl;
		matrix.horloge(nbDizaineHeure, nbHeure, nbDizaineMinute, nbMinute);
		
		//500ms.
		gpioDelay(500000); 

	}
}