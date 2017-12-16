#include <iostream>
#include <wiringPi.h>

#include "Gestion74HCT595.h"
#include "GestionPinGPIO.h"
#include "GestionMatriceLedRed8x8.h"

using namespace std;

Gestion74HCT595 circuitData(GPIO14, GPIO15, GPIO18, true);
Gestion74HCT595 circuitAdresse(GPIO16, GPIO20, GPIO21, true);

// ************************************
// Affiche un caractere sur l'afficheur
// @Param le caractere
// @Param le temps d'affichage en ms
// ************************************
void affiche(uint8_t caractere[], uint16_t tempsMs) {
	for(int temps = 0; temps != tempsMs / 8; temps++) {
		for(int compteur = 0; compteur != 8; compteur++) {
			circuitData.write(caractere[compteur]);
			circuitAdresse.low(compteur); 
			delay(1);
		}
	}
	
}

int main() {
	// Toutes les lignes
	for(int ligne = 0; ligne != 256; ligne++) {
		circuitData.write((uint8_t)ligne);
		circuitAdresse.write((uint8_t)0);
		delay(100);
	}
	// Tous les points
	for(int ligne = 0; ligne != 8; ligne++) {
		for(int colonne = 0; colonne != 8; colonne++) {
			circuitData.hight(ligne);
			circuitAdresse.low(colonne);
			delay(100);
		}
	}
	// Caractere
	affiche(Carre1, 1000);
	affiche(Carre2, 1000);
	affiche(Carre3, 1000);
	affiche(Carre4, 1000);
	
	affiche(B, 1000);
	affiche(O, 1000);
	affiche(N, 1000);
	affiche(J, 1000);
	affiche(O, 1000);
	affiche(U, 1000);
	affiche(R, 1000);
	affiche(FULL, 1000);
	affiche(BLANK, 1000);
}
