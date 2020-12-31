/*!
 *   \file    GestionMatrix.cpp
 *   \brief   Classe de gestion des matrices à base de MAX7219.
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    28/12/2020
 */

#include <pigpio.h>

#include "Logger.h"
#include "Chiffres.h"
#include "GestionMatrix.h"
#include "GestionMAX7219Reg.h"
 
/**
 * \brief   Constructeur. 
 *
 * \details Constructeur standard.
 *
 * \note    Appel automatiquement la méthode d'initialisation de la matrice et des MAX7219.
 *
 * \param   pTest Un flag qui active ou non le test des matrices à LED.
 */
GestionMatrix::GestionMatrix(bool pTest)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", " test = ", false);
	Logger::log("DEBUG", pTest);	

	initMAX7219C0();
	initMatrix(pTest);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

/**
 * \brief   Initialisation des matrices à LED. 
 *
 * \details Initialisation pour assurer le bon fonctionnement des matrices à LED.
 *
 * \note    Est appelé directement par le constructeur.
 *
 * \param   pTest Un flag qui active ou non le test des matrices à LED..
 */
void GestionMatrix::initMatrix(bool pTest) 
{
	// Allume toutes les LED des matrices au maximum pendant 2s
	if(pTest) {
		write8(MAX7219_DISPLAY_TEST, 0x01);
		write8(MAX7219_DISPLAY_TEST, 0x01);
		write8(MAX7219_DISPLAY_TEST, 0x01);
		write8(MAX7219_DISPLAY_TEST, 0x01);
		// 2s.
		gpioDelay(2000000);
	}
	
	// Annule le test des LED si il est lancé
	write8(MAX7219_DISPLAY_TEST, 0x00);
	write8(MAX7219_DISPLAY_TEST, 0x00);
	write8(MAX7219_DISPLAY_TEST, 0x00);
	write8(MAX7219_DISPLAY_TEST, 0x00);
	
	// Pas de décodage (utile seulement pour les afficheurs 7 segments)
	write8(MAX7219_DECODE_MODE, 0x00);
	
	// Réglage de l'intensité d'allumage des LED
	write8(MAX7219_INTENSITY, 0x03);
	
	// Utilisation de toutes les LED
	write8(MAX7219_SCAN_LIMIT, 0x07);
	
	// Eteint tous les afficheurs
	write8(MAX7219_DIGIT0, 0x00);
	write8(MAX7219_DIGIT1, 0x00);
	write8(MAX7219_DIGIT2, 0x00);
	write8(MAX7219_DIGIT3, 0x00);
	write8(MAX7219_DIGIT4, 0x00);
	write8(MAX7219_DIGIT5, 0x00);
	write8(MAX7219_DIGIT6, 0x00);
	write8(MAX7219_DIGIT7, 0x00);

	// Active tous les afficheurs
	write8(MAX7219_SHUTDOWN, 0x01);
	write8(MAX7219_NO_OP, 0x00);
	write8(MAX7219_NO_OP, 0x00);
	write8(MAX7219_NO_OP, 0x00);	
}

/**
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre
 *
 * \param pValeur le chiffre à afficher
 * \param pLigne la ligne du chiffre  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrix::segment(uint8_t pValeur, uint8_t pLigne)
{
	uint8_t result = -1;
	switch(pValeur) {
		case 0: result = zero[pLigne]; break;
		case 1: result = un[pLigne]; break;
		case 2: result = deux[pLigne]; break;
		case 3: result = trois[pLigne]; break;
		case 4: result = quatre[pLigne]; break;
		case 5: result = cinq[pLigne]; break;
		case 6: result = six[pLigne]; break;
		case 7: result = sept[pLigne]; break;
		case 8: result = huit[pLigne]; break;
		case 9: result = neuf[pLigne]; break;
	}
	return result;
}

/**
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre avec deux points
 *
 * \param pValeur le chiffre à afficher
 * \param pLigne la ligne du chiffre  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrix::segmentDp(uint8_t pValeur, uint8_t pLigne)
{
	uint8_t result = -1;
	switch(pValeur) {
		case 0: result = zeroDp[pLigne]; break;
		case 1: result = unDp[pLigne]; break;
		case 2: result = deuxDp[pLigne]; break;
		case 3: result = troisDp[pLigne]; break;
		case 4: result = quatreDp[pLigne]; break;
		case 5: result = cinqDp[pLigne]; break;
		case 6: result = sixDp[pLigne]; break;
		case 7: result = septDp[pLigne]; break;
		case 8: result = huitDp[pLigne]; break;
		case 9: result = neufDp[pLigne]; break;
	}
	return result;
}

/**
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre avec un décalage d'un rang
 *
 * \param pValeur le chiffre à afficher
 * \param pLigne la ligne du chiffre  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrix::segmentDm(uint8_t pValeur, uint8_t pLigne)
{
	uint8_t result = -1;
	switch(pValeur) {
		case 0: result = zeroDm[pLigne]; break;
		case 1: result = unDm[pLigne]; break;
		case 2: result = deuxDm[pLigne]; break;
		case 3: result = troisDm[pLigne]; break;
		case 4: result = quatreDm[pLigne]; break;
		case 5: result = cinqDm[pLigne]; break;
		case 6: result = sixDm[pLigne]; break;
		case 7: result = septDm[pLigne]; break;
		case 8: result = huitDm[pLigne]; break;
		case 9: result = neufDm[pLigne]; break;
	}
	return result;
}

/**
 * \brief   Affichage de l'heure. 
 *
 * \details Affichage des chiffres sur les 8 segments des 4 matrices
 *
 * \param   nbDizaineHeure Les dizaines d'heures (entre 0 et 2)
 * \param   nbHeure Les heures (entre 0 et 9 ou entre 0 et 3 si les dizaines d'heures sont à 2)
 * \param   nbDizaineMinute Les dizaines de minute (entre 0 et 5)
 * \param   nbMinute Les minutes (entre 0 et 9)
 */
void GestionMatrix::horloge(uint8_t nbDizaineHeure, uint8_t nbHeure, uint8_t nbDizaineMinute, uint8_t nbMinute) 
{
	for(uint8_t compteur = 0; compteur != 8 ; compteur++) {
		switch(compteur) {
		case 0:
			setDigit0(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		case 1:
			setDigit1(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		case 2:
			setDigit2(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		case 3:
			setDigit3(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		case 4:
			setDigit4(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		case 5:
			setDigit5(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		case 6:
			setDigit6(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		case 7:
			setDigit7(segment(nbMinute, compteur), segmentDm(nbDizaineMinute, compteur), segmentDp(nbHeure, compteur), segment(nbDizaineHeure, compteur));
			break;
		}
	}
}


/**
 * \brief   Destructeur. 
 *
 * \note    Appelé automatiquement à la fin du programme
 */
GestionMatrix::~GestionMatrix()
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
};

/*! \class GestionMatrix 
 *  \brief Class pour l'affichage sur les matrices à base de MAX7219.
 *
 */