//==================================================================
// Name        : tstStepper.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie de gestion du moteur pas a pas
//==================================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>
#include "GestionStepper.h"

using namespace std;

// Objets utilisés
GestionStepper stepper(GPIO05, GPIO06, GPIO13, GPIO19, AC, TWO_ONE);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive le servo
    stepper.~GestionStepper();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	int entre;
	int nombre;
	int position;
	for(;;) {
		system("clear");
		
		cout << "0: increment()" << endl;
		cout << "1: decrement()" << endl;
		cout << "2: increment(unsigned int)" << endl;
		cout << "3: decrement(unsigned int)" << endl;
		cout << "4: cycle(int)" << endl;
		cout << "5: gotoPosition(Position)" << endl;
		cout << "6: getPosition()" << endl;
		cout << "7: getTemporisation()" << endl;
		cout << "8: setTemporisation(unsigned int)" << endl;
		cout << "9: getMode()" << endl;
		cout << "10: setMode(Mode)" << endl;
		cout << "11: getHold()" << endl;
		cout << "12: setHold(bool)" << endl;
		cout << "CTRL-C pour arrêter le programme" << endl;
		cin >> entre;
		switch(entre){
			case 0: 
				cout << stepper.increment() << endl; 
				break;
			case 1: 
				stepper.decrement(); 
				break;
			case 2: 
				cout << "nombre d'incréments: " << endl;
				cin >> nombre;
				cout << stepper.increment(nombre) << endl;
				break;
			case 3: 				
				cout << "nombre de décréments: " << endl;
				cin >> nombre;
				cout << stepper.decrement(nombre) << endl;
				break;
			case 4: 
				cout << "nombre de cycles: " << endl;
				cin >> nombre;
				cout << stepper.cycle(nombre) << endl;
				break;
			case 5: 
				cout << "position [A -> 0, AC -> 1, C -> 2, CB -> 3, B -> 4, BD -> 5, D -> 6, DA -> 7]" << endl;
				cin >> position;
				switch(position) {
					case 0: 
						cout << stepper.gotoPosition(A) << endl;
						break;
					case 1: 
						cout << stepper.gotoPosition(AC) << endl;
						break;
					case 2: 
						cout << stepper.gotoPosition(C) << endl;
						break;
					case 3: 
						cout << stepper.gotoPosition(CB) << endl;
						break;
					case 4: 
						cout << stepper.gotoPosition(B) << endl;
						break;
					case 5: 
						cout << stepper.gotoPosition(BD) << endl;
						break;
					case 6: 
						cout << stepper.gotoPosition(D) << endl;
						break;
					case 7: 
						cout << stepper.gotoPosition(DA) << endl;
						break;
					default: cout << "Position non reconnue" << endl;
				}
				break;
			case 6: 
				cout << stepper.getPosition() << endl;
				break;
				
			case 7: 
				cout << stepper.getTemporisation() << endl;
				break;
				
			case 8: 
				cout << "temporisation (ms): " << endl;
				cin >> nombre;
				stepper.setTemporisation(nombre);			
				break;
				
			case 9: 
				cout << stepper.getMode() << endl;
				break;
				
			case 10: 
				cout << "mode (ONE_ONE -> 0, TWO_ONE -> 1, HALF -> 2): " << endl;
				cin >> nombre;
				switch(nombre) {
					case 0:
						cout << stepper.setMode(ONE_ONE) << endl;		
						break;
					case 1: 
						cout << stepper.setMode(TWO_ONE) << endl;		
						break;
					case 2: 
						cout << stepper.setMode(HALF) << endl;		
						break;
					default: cout << "Mode non reconnu" << endl;					
				}
				break;
				
			case 11: 
				cout << stepper.getHold() << endl;
				break;
				
			case 12: 
				cout << "hold (Non -> 0, Oui -> 1): " << endl;
				cin >> nombre;
				stepper.setHold(nombre);			
				break;
			default: cout << "Commande non reconnue" << endl;
		}
		delay(2000);
	}
}
