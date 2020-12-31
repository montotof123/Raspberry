/***************************************************************
 *   \file    GestionSPI.h
 *   \brief   Entete de la classe de gestion de l'interface SPI
 *   \note    Version utilisant la librairie pigpio
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    22/08/2020
 ***************************************************************/
 
#ifndef GESTIONSPI_H_
#define GESTIONSPI_H_

#include <stdint.h>

class GestionSpi {
	public:
		/*! Liste des canaux du Raspberry */
		enum Channel 
		{
			channel_0 = 0, /*!< Canal 0 broche 24 */	
			channel_1 = 1  /*!< Canal 1 broche 26 */	
		};
		
		/*! Liste de fréquence standard */
		enum Frequence 
		{
			speed_low = 50000,    /*!< 50kHz */	
			speed_27  = 1000000,  /*!< 1MHz pour tension d'alimentation 2.7V (datasheet)*/	
			speed_33  = 1250000,  /*!< 1.25MHz pour tension d'alimentation 3.3V (datasheet)*/	
			speed_50  = 2000000,  /*!< 2MHz pour tension d'alimentation 5.0V (datasheet)*/	
			speed_max = 6000000   /*!< 6MHz maximum testé avec un fonctionnement correct */	
		};
		
		GestionSpi(void);
		GestionSpi(Channel);
		GestionSpi(Channel, Frequence);
		bool initSpi(Channel, Frequence);
		
		bool isInitialize(void);
 
		uint16_t read(char[], uint16_t);
		uint16_t write(char[], uint16_t);
  
		virtual ~GestionSpi();
		
	private:
		int handle;
		bool initialize = false;
};


#endif 