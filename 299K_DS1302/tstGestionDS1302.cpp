#include <iostream>
#include <wiringPi.h>
#include <stdlib.h>

#include "GestionDS1302.h"
#include "GestionPinGPIO.h"

using namespace std;

GestionDS1302 horloge(GPIO03, GPIO04, GPIO02);

int main() {
	cout << "Initialisation"<< endl;
	cout << horloge.getJourSemaine() << " js ";
	cout << horloge.getJourMois() << " j ";
	cout << horloge.getMois() << " m ";
	cout << horloge.getAnnee() << " a" << endl;
	cout << horloge.getHeures() << "h ";
	cout << horloge.getMinutes() << " mn ";
	cout << horloge.getSecondes() << " s" << endl;
	cout << horloge.getInitJourSemaine() << " js ";
	cout << horloge.getInitJourMois() << " j ";
	cout << horloge.getInitMois() << " m ";
	cout << horloge.getInitAnnee() << " a " << endl;
	cout << horloge.getInitHeures() << " h ";
	cout << horloge.getInitMinutes() << " mn ";
	cout << horloge.getInitSecondes() << " s " << endl;
	cout << horloge.getDeltaSecondes() << " s delta" << endl;
	
	for(int compteur = 0; compteur != 20; compteur++) {
		int tempo = rand() % 20000;
		cout << endl << "tempo: " << tempo << " ms" << endl;
		delay(tempo);
		horloge.getClock();
		cout << horloge.getJourSemaine() << " js ";
		cout << horloge.getJourMois() << " j ";
		cout << horloge.getMois() << " m ";
		cout << horloge.getAnnee() << " a" << endl;
		cout << horloge.getHeures() << "h ";
		cout << horloge.getMinutes() << " mn ";
		cout << horloge.getSecondes() << " s" << endl;
		cout << horloge.getInitJourSemaine() << " js ";
		cout << horloge.getInitJourMois() << " j ";
		cout << horloge.getInitMois() << " m ";
		cout << horloge.getInitAnnee() << " a " << endl;
		cout << horloge.getInitHeures() << " h ";
		cout << horloge.getInitMinutes() << " mn ";
		cout << horloge.getInitSecondes() << " s " << endl;
		cout << horloge.getDeltaSecondes() << " s delta" << endl;
	}

}
