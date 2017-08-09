/*
 *  Lancement cyclique d'une mesure du HC-SR04:
 */

#include <wiringPi.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>	  // impression cout
#include <signal.h>	  // Fin, fonction cyclique
#include <unistd.h>	  // Delais pour les alarmes
#include <string>
#include "GestionAffichage.h"

using namespace std;

GestionAffichage affichage;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// *********************************
// Fonction de lancement de commande
// *********************************
string GetStdoutFromCommand(string cmd) {
	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream)) {
			if (fgets(buffer, max_buffer, stream) != NULL) {
				data.append(buffer);
			}
		}
		pclose(stream);
	}
	return data;
}

// ****************************
// Fonction lancée cycliquement
// ****************************
void alarmWakeup(int sig) {
	string distance = GetStdoutFromCommand("/home/pi/Projet/C-Cpp/HC-SR04/mesureHCSR04");
	if(atof(distance.c_str()) != -1) {
		float distAff = atof(distance.c_str()) * 100.0;
		cout << "Distance = " << distAff << " cm" << endl;
		if(distAff >= 100.0) {
			affichage.affiche(distAff, 1);
		}
		if(distAff < 100.0 && distAff >= 10.0) {
			affichage.affiche(distAff, 2);
		}
		if(distAff < 10.0) {
			affichage.affiche(distAff, 3);
		}
	} else {
		cout << "erreur" << endl;
	}
}


int main (int argc, char *argv[])
{
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	// Lancement cyclique d'une mesure
	signal(SIGALRM, alarmWakeup);   
    ualarm(100000, 500000);

	// Boucle infinie
	for(;;) {
		delay(50);
	}
}