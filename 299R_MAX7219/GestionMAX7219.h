/*!
 *   \file   GestionMAX7219.h
 *   \brief  Entete de la classe de gestion du MAX7219.
 *   \author Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date 28/12/2020
 */
 
#ifndef GESTIONMAX7219_H_
#define GESTIONMAX7219_H_

#include <stdint.h>
#include "GestionSPI.h"

class GestionMAX7219 : GestionSpi {
	public:
		GestionMAX7219(void);
		GestionMAX7219(Channel);
		bool initMAX7219(Channel);
		bool initMAX7219C0(void);
		bool initMAX7219C1(void);
		
		void noOp(void);
		void noOp4(void);
		void setDigit0(char);
		void setDigit0(char, char, char, char);
		void setDigit1(char);
		void setDigit1(char, char, char, char);
		void setDigit2(char);
		void setDigit2(char, char, char, char);
		void setDigit3(char);
		void setDigit3(char, char, char, char);
		void setDigit4(char);
		void setDigit4(char, char, char, char);
		void setDigit5(char);
		void setDigit5(char, char, char, char);
		void setDigit6(char);
		void setDigit6(char, char, char, char);
		void setDigit7(char);
		void setDigit7(char, char, char, char);
		void setIntensity(char);
		void setIntensity(char, char, char, char);
		void test(void);
		void noTest(void);
		void decode(void);
		void noDecode(void);
		void shutdown(void);
		void run(void);
		void scanLimit1(void);
		void scanLimit2(void);
		void scanLimit3(void);
		void scanLimit4(void);
		void scanLimit5(void);
		void scanLimit6(void);
		void scanLimit7(void);
		void scanLimit8(void);

		virtual ~GestionMAX7219();
		
	private:
		char spiData32[8]; /*!< Tableau de données des 4 matrices vers le SPI*/
		char spiData8[2];  /*!< Tableau de données d'une matrice vers le SPI*/
		
	protected:
		uint8_t write32(char, char, char, char, char);
		uint8_t write8(char, char);
};

#endif