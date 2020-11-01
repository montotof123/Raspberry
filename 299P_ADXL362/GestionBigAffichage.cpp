// *****************************************************
// Permet l'affichage d'une valeur réelle en grand (5*7)
// Totof
// 26/08/2018
// Free
// *****************************************************

#include <iostream>
#include <iomanip>
#include <math.h>

#include "GestionBigAffichage.h"

using namespace std;

// *************************************************************************
// Donne la ligne a afficher de la matrice d'un chiffre
// Remplace la matrice par une string de chiffre si ils doivent être affiché
// @Param le chiffre a afficher
// @Param la ligne de matrice a appliquer
// @return la string correspondant à la matrice pour le chiffre
// *************************************************************************
string GestionBigAffichage::getLineChar(int chiffre, int pattern) {
	string result = "";
	// Parcour chaque colonne du pattern de la matrice
	for(int colonne = 0; colonne != 5; colonne++) {
		switch(colonne) {
			case 4: if(pattern & 0b00000001) {
						// Gestion du point
						if(chiffre == -1) {
							result += "*";
						} else {
							// Met le chiffre si il y a 1 dans la matrice pour cet emplacement
							result += to_string(chiffre);
						}
					} else {
						// Met un espace si il y a 0 dans la matrice pour cet emplacement
						result = result + ' ';
					} 
					break;
			case 3:if(pattern & 0b00000010) {
						// Gestion du point
						if(chiffre == -1) {
							result += "*";
						} else {
							// Met le chiffre si il y a 1 dans la matrice pour cet emplacement
							result += to_string(chiffre);
						}
					} else {
						// Met un espace si il y a 0 dans la matrice pour cet emplacement
						result = result + ' ';
					} 
					break;
			case 2:if(pattern & 0b00000100) {
						// Gestion du point
						if(chiffre == -1) {
							result += "*";
						} else {
							// Met le chiffre si il y a 1 dans la matrice pour cet emplacement
							result += to_string(chiffre);
						}
					} else {
						// Met un espace si il y a 0 dans la matrice pour cet emplacement
						result = result + ' ';
					} 
					break;
			case 1:if(pattern & 0b00001000) {
						// Gestion du point
						if(chiffre == -1) {
							result += "*";
						} else {
							// Met le chiffre si il y a 1 dans la matrice pour cet emplacement
							result += to_string(chiffre);
						}
					} else {
						// Met un espace si il y a 0 dans la matrice pour cet emplacement
						result = result + ' ';
					} 
					break;
			case 0:if(pattern & 0b00010000) {
						// Gestion du point
						if(chiffre == -1) {
							result += "*";
						} else {
							// Met le chiffre si il y a 1 dans la matrice pour cet emplacement
							result += to_string(chiffre);
						}
					} else {
						// Met un espace si il y a 0 dans la matrice pour cet emplacement
						result = result + ' ';
					} 
					break;
		}
	}
	return result;
}

// ****************************************
// Donne le chiffre d'une valeur a un index 
// index 0 millieme
// index 1 centieme
// index 2 dizieme
// index 3 unite
// index 4 dizaine
// index 5 centaine
// index 6 millier
// index 7 dixmille
// index 8 centmille
// index 9 million
// max nnnnnnn.nnn
// @Param l'index
// @Param la valeur
// @return le chiffre
// *****************************************
uint8_t GestionBigAffichage::getChiffre(int index, float valeur) {
	switch(index) {
		case 0: return ((int)valeur % 10);
		case 1: return ((int)valeur % 100) / 10;
		case 2: return ((int)valeur % 1000) / 100;
		case 3: return ((int)valeur % 10000) / 1000;
		case 4: return ((int)valeur % 100000) / 10000;
		case 5: return ((int)valeur % 1000000) / 100000;
		case 6: return ((int)valeur % 10000000) / 1000000;
		case 7: return ((int)valeur % 100000000) / 10000000;
		case 8: return ((int)valeur % 1000000000) / 100000000;
		case 9: return valeur / 10000000000;
	}
	return -1;
}

// *************************************************
// Donne une des 7 lignes a afficher pour une valeur
// @Param la ligne de 0 à 6
// @Param la valeur a afficher
// @return la ligne a afficher
// *************************************************
string GestionBigAffichage::getLineValue(uint8_t ligne, double valeur) {
	string result;
	int nbChiffre;
	
	// Traitement de la partie entière
	float partieEntiere = trunc(valeur);
	if(partieEntiere != 0) {
		nbChiffre = log10(partieEntiere);
	} else {
		nbChiffre = 0;
	}
	// Récupére la ligne de la matrice de chaque chiffre
	for(int index = nbChiffre; index >= 0 ; index--) {
		switch(getChiffre(index, partieEntiere)) {
			case 0: result += getLineChar(getChiffre(index, partieEntiere), zero[ligne]); break;
			case 1: result += getLineChar(getChiffre(index, partieEntiere), un[ligne]); break;
			case 2: result += getLineChar(getChiffre(index, partieEntiere), deux[ligne]); break;
			case 3: result += getLineChar(getChiffre(index, partieEntiere), trois[ligne]); break;
			case 4: result += getLineChar(getChiffre(index, partieEntiere), quatre[ligne]); break;
			case 5: result += getLineChar(getChiffre(index, partieEntiere), cinq[ligne]); break;
			case 6: result += getLineChar(getChiffre(index, partieEntiere), six[ligne]); break;
			case 7: result += getLineChar(getChiffre(index, partieEntiere), sept[ligne]); break;
			case 8: result += getLineChar(getChiffre(index, partieEntiere), huit[ligne]); break;
			case 9: result += getLineChar(getChiffre(index, partieEntiere), neuf[ligne]); break;
		}
		// Espace entre les chiffres
		result += "  ";
	}
	
	// Traitement de la partie décimale
	double partieDecimale = trunc(((1.0005D + (valeur - trunc(valeur))) * 1000.0D));
	int finAffDecimal = 0;
	// Nombre de chiffre après la virgule a afficher
	if((int)partieDecimale % 10 == 0) {
		finAffDecimal++;
	}
	if((int)partieDecimale % 100 == 0) {
		finAffDecimal++;
	}
	// Si la partie decimale est nulle on n'affiche rien
	if(partieDecimale != 1000) {
		// Ajout du point
		result += getLineChar(-1, point[ligne]);
		nbChiffre = log10(partieDecimale);
		// Récupére la ligne de la matrice de chaque chiffre
		for(int index = nbChiffre - 1; index >= finAffDecimal; index--) {
			switch(getChiffre(index, partieDecimale)) {
				case 0: result += getLineChar(getChiffre(index, partieDecimale), zero[ligne]); break;
				case 1: result += getLineChar(getChiffre(index, partieDecimale), un[ligne]); break;
				case 2: result += getLineChar(getChiffre(index, partieDecimale), deux[ligne]); break;
				case 3: result += getLineChar(getChiffre(index, partieDecimale), trois[ligne]); break;
				case 4: result += getLineChar(getChiffre(index, partieDecimale), quatre[ligne]); break;
				case 5: result += getLineChar(getChiffre(index, partieDecimale), cinq[ligne]); break;
				case 6: result += getLineChar(getChiffre(index, partieDecimale), six[ligne]); break;
				case 7: result += getLineChar(getChiffre(index, partieDecimale), sept[ligne]); break;
				case 8: result += getLineChar(getChiffre(index, partieDecimale), huit[ligne]); break;
				case 9: result += getLineChar(getChiffre(index, partieDecimale), neuf[ligne]); break;
			}
		// Espace entre les chiffres
			result += "  ";
		}
	}
	return result;
}

// ****************************************
// Affiche la valeur en grand (matrice 5*7)
// @Param valeur a afficher
// ****************************************
void GestionBigAffichage::affValue(double valeur) {
	// Parcourt les 7 lignes des matrices
	for(int ligne = 0; ligne != 7; ligne++) {
		cout << getLineValue(ligne, valeur) << endl;
	}
}
