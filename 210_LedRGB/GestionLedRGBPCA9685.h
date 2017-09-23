/*
 * GestionLedRGBPCA9685.h
 *
 * Created on 13/09/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONLEDRGBPCA9685_H_
#define GESTIONLEDRGBPCA9685_H_

#include "GestionLedRGB.h"
#include "GestionPCA9685.h"

class GestionLedRGBPCA9685 {
	public:
		GestionLedRGBPCA9685(Register_Led, Register_Led, Register_Led, LedType, Address);

		void setPercentRGB(float, float, float);
		void setColorRGB(uint8_t, uint8_t, uint8_t);
		void setColorRGB(ColorRGB);
		void setTypeLed(LedType);
		uint8_t getMaxValue(void);
		
		virtual ~GestionLedRGBPCA9685();
	
	private:
		GestionPCA9685 pca9685;
		GestionLedRGB ledRGB;
		Register_Led ledRed;
		Register_Led ledGreen;
		Register_Led ledBlue;
};

#endif