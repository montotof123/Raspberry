// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright Drew Noakes 2013-2016

#include "joystick.h"
#include <unistd.h>
#include <signal.h>	  // Fin
#include <iostream>	  // impression cout

#define NB_MAX_BOUTON 30
#define NB_MAX_AXE 30

using namespace std;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

int main(int argc, char** argv)
{
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	// Create an instance of Joystick
	Joystick joystick("/dev/input/js0");
	
	// Nombre de bouton et d'axe
	int nbBouton = 0;
	int nbAxe = 0;
	// Changer la valeur NB_MAX_BOUTON si le joystick a plus de 30 boutons
	int boutons[NB_MAX_BOUTON];
	// Changer la valeur NB_MAX_AXE si le joystick a plus de 30 axes
	int axes[NB_MAX_AXE];
	
	// Ensure that it was found and that we can use it
	if (!joystick.isFound()) {
		cout << "open failed." << endl;
		exit(-1);
	}

	while (true){
		// Restrict rate
		usleep(5000);

		// Attempt to sample an event from the joystick
		JoystickEvent event;
		if (joystick.sample(&event)) {
			// Initialisation
			if(event.isInitialState()){
				// Initialisation, permet de compter le nombre de boutons et d'axes
				if (event.isButton()){
					if(nbBouton < event.number) {
						nbBouton = event.number;
					}
					if(nbBouton > NB_MAX_BOUTON) {
						exit(-2);
					}
					boutons[event.number] = event.value;
				}
				if (event.isAxis()) {
					if(nbAxe < event.number) {
						nbAxe = event.number;
					}
					if(nbAxe > NB_MAX_AXE) {
						exit(-3);
					}
					axes[event.number] = event.value;
				}
			// Si c'est un bouton
			} else if (event.isButton()){
				boutons[event.number] = event.value;
			// Si c'est un axe
			} else if (event.isAxis()) {
				axes[event.number] = event.value;
			}
		}
		// Efface l'ecran
		system("clear");
		// Affiche les boutons
		for(int compteur = 0; compteur <= nbBouton; compteur++) {
			cout << "Bouton n°" << compteur << " = " << (boutons[compteur] == 0 ? "up" : "down") << endl;
		}
		// Affiche les axes
		for(int compteur = 0; compteur <= nbAxe; compteur++) {
			cout << "Axe n°" << compteur << " = " << axes[compteur] << endl;
		}
	}
}
