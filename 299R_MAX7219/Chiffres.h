/*****************************************************************
 *   \file    Chiffres.h
 *   \brief   Liste des caractères pour affichage sur les matrices
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    25/12/2020
 ****************************************************************/
 
#ifndef Chiffres_h
#define Chiffres_h

/**
 * \brief Chiffre 0
 */
uint8_t zero [] = 
{
	0b00111000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b01000100,
	0b01000100,
	0b01000100,
	0b00111000
};

/**
 * \brief Chiffre 1
 */
uint8_t un [] = 
{
	0b00010000,
	0b00110000,
	0b01010000,
	0b00010000,
	0b00010000,
	0b00010000,
	0b00010000,
	0b01111100
};

/**
 * \brief Chiffre 2
 */
uint8_t deux [] = 
{
	0b00111000,
	0b01000100,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b01111100
};

/**
 * \brief Chiffre 3
 */
uint8_t trois [] = 
{
	0b00111000,
	0b01000100,
	0b00000100,
	0b00011000,
	0b00011000,
	0b00000100,
	0b01000100,
	0b00111000
};

/**
 * \brief Chiffre 4
 */
uint8_t quatre [] = 
{
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01001000,
	0b01111100,
	0b00001000,
	0b00001000
};

/**
 * \brief Chiffre 5
 */
uint8_t cinq [] = 
{
	0b01111100,
	0b01000000,
	0b01000000,
	0b01111000,
	0b00000100,
	0b00000100,
	0b01000100,
	0b00111000
};

/**
 * \brief Chiffre 6
 */
uint8_t six [] = 
{
	0b00111000,
	0b01000100,
	0b01000000,
	0b01111000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b00111000
};

/**
 * \brief Chiffre 7
 */
uint8_t sept [] = 
{
	0b01111100,
	0b00000100,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b01000000
};

/**
 * \brief Chiffre 8
 */
uint8_t huit [] = 
{
	0b00111000,
	0b01000100,
	0b01000100,
	0b00111000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b00111000
};

/**
 * \brief Chiffre 9
 */
uint8_t neuf [] = 
{
	0b00111000,
	0b01000100,
	0b01000100,
	0b00111100,
	0b00000100,
	0b00000100,
	0b01000100,
	0b00111000
};

/**
 * \brief Chiffre 0 avec décalage d'un rang
 */
uint8_t zeroDm [] = 
{
	0b00011100,
	0b00100010,
	0b00100010,
	0b00100010,
	0b00100010,
	0b00100010,
	0b00100010,
	0b00011100
};

/**
 * \brief Chiffre 1 avec décalage d'un rang
 */
uint8_t unDm [] = 
{
	0b00001000,
	0b00011000,
	0b00101000,
	0b00001000,
	0b00001000,
	0b00001000,
	0b00001000,
	0b00111110
};

/**
 * \brief Chiffre 2 avec décalage d'un rang
 */
uint8_t deuxDm [] = 
{
	0b00011100,
	0b00100010,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b00111110
};

/**
 * \brief Chiffre 3 avec décalage d'un rang
 */
uint8_t troisDm [] = 
{
	0b00011100,
	0b00100010,
	0b00000010,
	0b00001100,
	0b00001100,
	0b00000010,
	0b00100010,
	0b00011100
};

/**
 * \brief Chiffre 4 avec décalage d'un rang
 */
uint8_t quatreDm [] = 
{
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100100,
	0b00111110,
	0b00000100,
	0b00000100
};

/**
 * \brief Chiffre 5 avec décalage d'un rang
 */
uint8_t cinqDm [] = 
{
	0b00111110,
	0b00100000,
	0b00100000,
	0b00111100,
	0b00000010,
	0b00000010,
	0b00100010,
	0b00011100
};

/**
 * \brief Chiffre 6 avec décalage d'un rang
 */
uint8_t sixDm [] = 
{
	0b00011100,
	0b00100010,
	0b00100000,
	0b00111100,
	0b00100010,
	0b00100010,
	0b00100010,
	0b00011100
};

/**
 * \brief Chiffre 7 avec décalage d'un rang
 */
uint8_t septDm [] = 
{
	0b00111110,
	0b00000010,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b00100000
};

/**
 * \brief Chiffre 8 avec décalage d'un rang
 */
uint8_t huitDm [] = 
{
	0b00011100,
	0b00100010,
	0b00100010,
	0b00011100,
	0b00100010,
	0b00100010,
	0b00100010,
	0b00011100
};

/**
 * \brief Chiffre 9 avec décalage d'un rang
 */
uint8_t neufDm [] = 
{
	0b00011100,
	0b00100010,
	0b00100010,
	0b00011110,
	0b00000010,
	0b00000010,
	0b00100010,
	0b00011100
};

/**
 * \brief Chiffre 0 avec deux points
 */
uint8_t zeroDp [] = 
{
	0b01110000,
	0b10001000,
	0b10001000,
	0b10001001,
	0b10001000,
	0b10001000,
	0b10001001,
	0b01110000
};

/**
 * \brief Chiffre 1 avec deux points
 */
uint8_t unDp [] = 
{
	0b00100000,
	0b01100000,
	0b10100000,
	0b00100001,
	0b00100000,
	0b00100000,
	0b00100001,
	0b11111000
};

/**
 * \brief Chiffre 2 avec deux points
 */
uint8_t deuxDp [] = 
{
	0b01110000,
	0b10001000,
	0b00001000,
	0b00010001,
	0b00100000,
	0b01000000,
	0b10000001,
	0b11111000
};

/**
 * \brief Chiffre 3 avec deux points
 */
uint8_t troisDp [] = 
{
	0b01110000,
	0b10001000,
	0b00001000,
	0b00110001,
	0b00110000,
	0b00001000,
	0b10001001,
	0b01110000
};

/**
 * \brief Chiffre 4 avec deux points
 */
uint8_t quatreDp [] = 
{
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000001,
	0b10010000,
	0b11111000,
	0b00010001,
	0b00010000
};

/**
 * \brief Chiffre 5 avec deux points
 */
uint8_t cinqDp [] = 
{
	0b11111000,
	0b10000000,
	0b10000000,
	0b11110001,
	0b00001000,
	0b00001000,
	0b10001001,
	0b01110000
};

/**
 * \brief Chiffre 6 avec deux points
 */
uint8_t sixDp [] = 
{
	0b01110000,
	0b10001000,
	0b10000000,
	0b11110001,
	0b10001000,
	0b10001000,
	0b10001001,
	0b01110000
};

/**
 * \brief Chiffre 7 avec deux points
 */
uint8_t septDp [] = 
{
	0b11111000,
	0b00001000,
	0b00001000,
	0b00010001,
	0b00100000,
	0b01000000,
	0b10000001,
	0b10000000
};

/**
 * \brief Chiffre 8 avec deux points
 */
uint8_t huitDp [] = 
{
	0b01110000,
	0b10001000,
	0b10001000,
	0b01110001,
	0b10001000,
	0b10001000,
	0b10001001,
	0b01110000
};

/**
 * \brief Chiffre 9 avec deux points
 */
uint8_t neufDp [] = 
{
	0b01110000,
	0b10001000,
	0b10001000,
	0b01111001,
	0b00001000,
	0b00001000,
	0b10001001,
	0b01110000
};

#endif	