//==============================================
// Name        : tst24c256.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : Ecriture dans des eeprom 24c256
//==============================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>	  // Fin
#include <string.h>
#include "Gestion24cXXX.h"

using namespace std;

// Objets utilisés
Gestion24cXXX eeprom0(ADDR0, GPIO04);
Gestion24cXXX eeprom1(ADDR1, GPIO05);

// ******************
// Fonction pricipale
// ******************
int main() {
	// ***********************************************
	// Ecriture de l'alphabet en minuscule sur eeprom0
	// ***********************************************
	char valeur0[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	// Ecriture
	if(!eeprom0.write(150, valeur0)) {
		cout << eeprom0.getErrorMessage() << endl;
	}	
	// Lecture
	char* result0;
	result0 = eeprom0.read(150, 26);
	if(eeprom0.getErrorFlag()) {
		cout << eeprom0.getErrorMessage() << endl;		
	}
	cout << "Lecture eeprom0 : " << result0 << endl;
	// Conseillé pour éviter une fuite mémoire du au malloc
	free(result0);
	
	// ***********************************************
	// Ecriture de l'alphabet en majuscule sur eeprom1
	// ***********************************************
	char valeur1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	// Ecriture
	if(!eeprom1.write(10, valeur1)) {
		cout << eeprom1.getErrorMessage() << endl;
	}	
	// Lecture
	char* result1;
	result1 = eeprom1.read(10, 26);
	if(eeprom1.getErrorFlag()) {
		cout << eeprom1.getErrorMessage() << endl;		
	}
	cout << "Lecture eeprom1 : " << result1 << endl;
	// Conseillé pour éviter une fuite mémoire du au malloc
	free(result1);

	// ***************************************
	// Ecriture sur eeprom protégé en ecriture
	// ***************************************
	eeprom1.writeProtect(true);
	cout << "eeprom1 protect = " << eeprom1.isWriteProtect() << endl;
	char valeur2[] = {'P', 'R', 'O', 'T', 'E', 'C', 'T', 'E', 'D'};
	// Ecriture
	if(!eeprom1.write(50, valeur2)) {
		cout << eeprom1.getErrorMessage() << endl;
	}	
	// Lecture
	char* result2;
	result2 = eeprom1.read(50, 9);
	if(eeprom1.getErrorFlag()) {
		cout << eeprom1.getErrorMessage() << endl;		
	}
	cout << "Lecture eeprom1 : " << result2 << endl;
	// Conseillé pour éviter une fuite mémoire du au malloc
	free(result2);
	eeprom1.writeProtect(false);
	
	// ***********************************
	// Ecriture d'un caractère sur eeprom0
	// ***********************************
	// Ecriture
	if(!eeprom0.write(50, '*')) {
		cout << eeprom0.getErrorMessage() << endl;
	}	
	// Lecture
	char* result3;
	result3 = eeprom0.read(50, 1);
	if(eeprom0.getErrorFlag()) {
		cout << eeprom0.getErrorMessage() << endl;		
	}
	cout << "Lecture eeprom0 : " << result3 << endl;
	// Conseillé pour éviter une fuite mémoire du au malloc
	free(result3);
	
	// ***********************************
	// Ecriture de 32768 octet sur eeprom0
	// ***********************************
	char valeur4[32750];
	int compteur;
	for(compteur = 0; compteur != 32750; compteur++) {
		valeur4[compteur] = (char)(compteur % 26 + 97);
	}

	// Ecriture
	if(!eeprom0.write(0, valeur4)) {
		cout << eeprom0.getErrorMessage() << endl;
	}	
	// Lecture
	char* result4;
	result4 = eeprom0.read(0, strlen(valeur4));
	if(eeprom0.getErrorFlag()) {
		cout << eeprom0.getErrorMessage() << endl;		
	}
	cout << "Lecture eeprom0 : " << result4 << endl;
	// Conseillé pour éviter une fuite mémoire du au malloc
	free(result4);
	
	
}
