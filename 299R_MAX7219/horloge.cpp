/*!
 *   \file    horloge.cpp
 *   \brief   Programme affichant l'heure d'un DS1307 sur les matrices
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    30/12/2020
 */
 
#include <iostream>
#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>

#include "GestionDS1307.h"
#include "GestionMatrix.h"

using namespace std;

/**
 *   \brief   Initialise la date et l'heure du DS1307 à la date et l'heure courante.
 */
GestionDS1307 ds1307;
struct tm * timeinfo;

/**
 *   \brief  Gestion des matrice avec affichage d'un test au début.
 */
GestionMatrix matrix(true);

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

/**
 * \brief   Lit l'horloge DS1307 toutes les 1/2 seconde et affiche les heures et les minutes, fin par CTRL-C. 
 */
int main(void) 
{
	signal(SIGINT, fin);

	// Initialise la fonction random.
	srand (time(NULL));

	for(;;) { 
		timeinfo = ds1307.getDateTime();
		cout << "Jour de l'année   : " << timeinfo->tm_yday << endl;
		cout << "Jour de la semaine: " << timeinfo->tm_wday << endl;
		cout << "Jour du mois      : " << timeinfo->tm_mday << endl;
		cout << "Mois              : " << timeinfo->tm_mon << endl;
		cout << "Année             : " << timeinfo->tm_year << endl;
		cout << "Heure             : " << timeinfo->tm_hour << endl;
		cout << "Minute            : " << timeinfo->tm_min << endl;
		cout << "Seconde           : " << timeinfo->tm_sec << endl;

		// Dizaine d'heures.
		uint8_t nbDizaineHeure = timeinfo->tm_hour / 10;
		// Heures.
		uint8_t nbHeure = timeinfo->tm_hour %10;
		// Dizaine de minutes.
		uint8_t nbDizaineMinute = timeinfo->tm_min / 10;
		// Minutes.
		uint8_t nbMinute = timeinfo->tm_min % 10;
		cout << (int)nbDizaineHeure << " " << (int)nbHeure << " " << (int)nbDizaineMinute << " " << (int)nbMinute << " " << endl;
		matrix.horloge(nbDizaineHeure, nbHeure, nbDizaineMinute, nbMinute);
		
		// 500ms.
		gpioDelay(500000); 
	}
}