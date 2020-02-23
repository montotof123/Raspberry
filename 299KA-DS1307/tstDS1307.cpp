#include <iostream>
#include <signal.h>
#include <wiringPi.h>

#include "GestionDS1307.h"
#include "GestionPinGPIO.h"

using namespace std;

// Initialise la date et l'heure à celle du moment
GestionDS1307 ds1307;
struct tm * timeinfo;

GestionPinGPIO dataIn(GPIO17);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	cout << "Fin" << endl;
	ds1307.setOutput(ds1307.Output::_0);
	exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void myInterrupt(void) {
	char buffer[256]; 
	timeinfo = ds1307.getDateTime();
	strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
	cout << buffer << endl;

}

// *****************
// Boucle principale
// *****************
int main() {
	// Ecoute du CTRL-C avec fonction de fin
	signal(SIGINT, fin);
	
	char buffer[256]; 
	// Boucle principale
	// Affiche la date et l'heure 20 fois
	for(int compteur = 0; compteur != 20; compteur++) {
		timeinfo = ds1307.getDateTime();
		cout << "Jour de l'année   : " << timeinfo->tm_yday << endl;
		cout << "Jour de la semaine: " << timeinfo->tm_wday << endl;
		cout << "Jour du mois      : " << timeinfo->tm_mday << endl;
		cout << "Mois              : " << timeinfo->tm_mon << endl;
		cout << "Année             : " << timeinfo->tm_year << endl;
		cout << "Heure             : " << timeinfo->tm_hour << endl;
		cout << "Minute            : " << timeinfo->tm_min << endl;
		cout << "Seconde           : " << timeinfo->tm_sec << endl;

		// *******************************************************
		// format la date et l'heure sous un format
		// @Param le format
		// @Return la date formatté
		// %a	Nom du jour en abrégé
		// %A	Nom du jour complet
		// %b	Nom du mois en abrégé
		// %B	Nom du mois complet
		// %c	MM/JJ/AA HH:MM:SS
		// %d	Numéro du jour dans le mois (01 à 31)
		// %H	Heure sur 24 heures (00 à 23)
		// %I	Heure sur 12 heures (01 à 12)
		// %m	Numéro du mois dans l'année (01 à 12)
		// %M	La minute (0 à 59)
		// %p	AM ou PM suivant la partie de la journée
		// %S	La seconde (0 à 59)
		// %u	Numéro du jour de la semaine (1 (lun.) à 7 (dim.))
		// %w	Numéro du jour de la semaine (0 (dim.) à 6 (sam.))
		// %x	MM/JJ/AA
		// %X	HH:MM:SS
		// %y	Année sur deux chiffres
		// %Y	Année sur quatre chiffres
		// %Z	Nom du fuseau horaire
		// %%	Le caractère %
		// *******************************************************
		strftime(buffer, sizeof(buffer), "%A %w %d %B %Y %H:%M:%S %j", timeinfo);
		cout << buffer << endl;
		
		delay(600);
	}
	
	// utilisation de la mémoire
	for(int compteur = 0x08; compteur != 0x40; compteur++) {
		ds1307.setData(compteur, compteur - 0x03);
	}
	delay(500);
	for(int compteur = 0x08; compteur != 0x40; compteur++) {
		cout << "Adresse: " << compteur << " Valeur: " << (int)ds1307.getData(compteur) << endl;
	}
	
	// Programmation de la GPIO d'interruption
	dataIn.in();
	dataIn.pullUp();
	dataIn.fctInterrupt(Falling, &myInterrupt);
	ds1307.setOutput(ds1307.Output::_1Hz);
	for(;;) {
		delay(1);
	}
}
