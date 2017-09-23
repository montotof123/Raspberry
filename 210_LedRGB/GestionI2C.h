/*
 * GestionI2C.h
 *
 * Created on 09/09/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONI2C_H_
#define GESTIONI2C_H_

#include <stdint.h>

class GestionI2C {
	public:
		GestionI2C();
		GestionI2C(uint16_t);
		void init(uint16_t);
		
		bool isInitialize(void);
 
		int8_t read8(void);
		bool write8(uint8_t);
  
		int8_t read8(uint8_t);
		bool write8(uint8_t, uint8_t);
  
		int16_t read16(uint8_t);
		bool write16(uint8_t, uint16_t);
		
		virtual ~GestionI2C();
		
	private:
		int handle;
		bool initialize = false;
};

#endif