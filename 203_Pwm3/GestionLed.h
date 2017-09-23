/*
 * GestionLed.h
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONLED_H_
#define GESTIONLED_H_

#define MAX_VALUE 255

#include <stdint.h>

class GestionLed {
	public:
		GestionLed();

		void setPercent(float);
		void setValue(uint8_t);
		
		uint8_t getValue(void);
		
		uint8_t getMaxValue(void);
		
		virtual ~GestionLed();
	
	private:
		uint8_t value;
};

#endif