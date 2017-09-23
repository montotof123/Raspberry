/*
 * GestionLedRGB.h
 *
 * Created on 13/09/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONLEDRGB_H_
#define GESTIONLEDRGB_H_

#include <stdint.h>
#include "GestionLed.h"

typedef struct ColorRGB ColorRGB ;

struct ColorRGB {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

enum LedType {
	CommonAnode =   0x00,		
	CommonCathode = 0x01
};


class GestionLedRGB {
	public:
		GestionLedRGB();
		GestionLedRGB(LedType);

		void setType(LedType);
		LedType getType(void);
		void setPercentRGB(float, float, float);
		void setColorRGB(uint8_t, uint8_t, uint8_t);
		void setColorRGB(ColorRGB);
		
		uint8_t getRed(void);
		uint8_t getGreen(void);
		uint8_t getBlue(void);
		
		uint8_t getMaxValue(void);
		
		virtual ~GestionLedRGB();
	
	private:
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		LedType ledType;
		
};

#endif