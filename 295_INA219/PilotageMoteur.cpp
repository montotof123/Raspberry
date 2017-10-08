#include <iostream>
#include <wiringPi.h>
#include <signal.h>

#include "GestionINA219.h"
#include "GestionPinGPIO.h"

// Valeur a modifier en fonction du moteur
// C'est la consommation du moteur plus 20%
#define valeurMaxmA 25.0 
#define nombreErreur 3
#define tempsArretErreur 700 
#define tempoLancementMoteur 300

using namespace std;

GestionINA219 ina219;
GestionPinGPIO command(GPIO12);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	command.off();
	cout << "Fin" << endl;
	exit(0);
}


int main() {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	// Initialisation
	command.out();
	command.off();
	ina219.init(ADDR_45);
	ina219.reset();
	ina219.setCalibration_3_2A(_32V, B_12Bits_1S_532US, S_12Bits_1S_532US, ShuntAndBusVoltageContinuous);
	int countError = 0;
	
	// Demarrage et temporisation pour lancement moteur
	command.on();
	delay(tempoLancementMoteur);
	
	while(1) {
		// Mesure du courant
		float courant = ina219.getCurrent_mA();
		//cout << courant << endl;
		
		// Si le courant depasse la valeur limite
		if(courant > valeurMaxmA) {
			// On eteint le moteur
			command.off();
			// On compte et on affiche les erreurs
			countError++;
			cout << "Erreur n°: " << countError  << "  courant: " << courant << " mA" << endl;
			// On attend n milliseconde avant de relancer
			delay(tempsArretErreur);
			command.on();
			// Temporisation pour lancement moteur
			delay(tempoLancementMoteur);
		} else {
			// Si pas d'erreur, on reinitialise le compteur
			countError = 0;
		}
		// Au bout de n erreurs, on arrete tout
		if(countError == nombreErreur) {
			fin(0);
		}
	}
}
