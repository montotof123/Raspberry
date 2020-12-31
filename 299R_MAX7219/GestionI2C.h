/***************************************************************
 *   \file    GestionI2C.h
 *   \brief   Entete de la classe de gestion de l'interface I2C
 *   \note    Version utilisant la librairie pigpio
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    23/11/2020
 ***************************************************************/
 
#ifndef GESTIONI2C_H_
#define GESTIONI2C_H_

#include <stdint.h>

#define ERROR -42

class GestionI2C {
	protected:
		GestionI2C();
		GestionI2C(uint16_t);
		void initI2CPeripheric(uint16_t);
		
		bool isInitialize(void);
 
		int8_t read8(void);
		bool write8(uint8_t);
		
 		int8_t readBlock(uint8_t);
		char* getBlock(void);
 
		int8_t read8(uint8_t);
		bool write8(uint8_t, uint8_t);
  
		int16_t read16(uint8_t);
		bool write16(uint8_t, uint16_t);
		
		int16_t read16Swapped(uint8_t);
		bool write16Swapped(uint8_t, uint16_t);
		
		virtual ~GestionI2C();
		
	private:
		int handle;
		bool initialize = false;
		
		char block[32];

		union i2cUData{
			uint16_t uSData;
			uint8_t uCData[2];
		};	
		union i2cData{
			int16_t uSData;
			int8_t uCData[2];
		};	

		void swapU(i2cUData &);
		void swap(i2cData &);
};

#endif