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
		GestionLedRGBPCA9685(void);
		GestionLedRGBPCA9685(GestionPCA9685::Register_Led, GestionPCA9685::Register_Led, GestionPCA9685::Register_Led, GestionLedRGB::LedType, GestionPCA9685*);
		void init(GestionPCA9685::Register_Led, GestionPCA9685::Register_Led, GestionPCA9685::Register_Led, GestionLedRGB::LedType, GestionPCA9685*);

		void setPercentRGB(float, float, float);
		void setColorRGB(uint8_t, uint8_t, uint8_t);
		void setColorRGB(ColorRGB);
		void setTypeLed(GestionLedRGB::LedType);
		uint8_t getMaxValue(void);
		GestionPCA9685::Register_Led getLedRed(void);
		GestionPCA9685::Register_Led getLedGreen(void);
		GestionPCA9685::Register_Led getLedBlue(void);

		virtual ~GestionLedRGBPCA9685();
	
	private:
		GestionPCA9685 *pca9685;
		GestionLedRGB ledRGB;
		GestionPCA9685::Register_Led ledRed;
		GestionPCA9685::Register_Led ledGreen;
		GestionPCA9685::Register_Led ledBlue;
};

#endif