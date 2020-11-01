// *****************************************************
// Permet l'affichage d'une valeur réelle en grand (5*7)
// Totof
// 26/08/2018
// Free
// *****************************************************

#ifndef GESTIONBIGAFFICHAGE_H_
#define GESTIONBIGAFFICHAGE_H_

#include <string>

using namespace std;

// Matrice d'affichage des chiffres
const unsigned char zero[7] =   {0b01110,
							   0b10001,
							   0b10001,
							   0b10001,
							   0b10001,
							   0b10001,
							   0b01110};

const unsigned char un[7] =     {0b00100,
							   0b01100,
							   0b10100,
							   0b00100,
							   0b00100,
							   0b00100,
							   0b11111};

const unsigned char deux[7] =   {0b01110,
							   0b10001,
							   0b00010,
							   0b00100,
							   0b01000,
							   0b10000,
							   0b11111};
						   
const unsigned char trois[7] =  {0b01110,
							   0b10001,
							   0b00001,
							   0b00010,
							   0b00001,
							   0b10001,
							   0b01110}; 
					   
const unsigned char quatre[7] = {0b00001,
							   0b00010,
							   0b00100,
							   0b01000,
							   0b10010,
							   0b11111,
							   0b00010};

const unsigned char cinq[7] =   {0b11111,
							   0b10000,
							   0b10000,
							   0b11110,
							   0b00001,
							   0b00001,
							   0b11110};
							 
const unsigned char six[7] =    {0b01110,
							   0b10001,
							   0b10000,
							   0b11110,
							   0b10001,
							   0b10001,
							   0b01110};
							
const unsigned char sept[7] =   {0b11111,
							   0b00001,
							   0b00010,
							   0b00100,
							   0b01000,
							   0b10000,
							   0b10000};
							 
const unsigned char huit[7] =   {0b01110,
							   0b10001,
							   0b10001,
							   0b01110,
							   0b10001,
							   0b10001,
							   0b01110};
													 
const unsigned char neuf[7] =   {0b01110,
							   0b10001,
							   0b10001,
							   0b01111,
							   0b00001,
							   0b10001,
							   0b01110};
							   
const unsigned char point[7] =  {0b00000,
							   0b00000,
							   0b00000,
							   0b00000,
							   0b00000,
							   0b00110,
							   0b00110};
							   
class GestionBigAffichage {
	public:	
		static void affValue(double);
		
	private:
		static string getLineChar(int, int);
		static uint8_t getChiffre(int, float);
		static string getLineValue(uint8_t, double);
};

#endif /* GESTIONPIN_H_ */
