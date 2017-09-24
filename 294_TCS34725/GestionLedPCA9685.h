/*
 * GestionLedPCA9685.h
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONLEDPCA9685_H_
#define GESTIONLEDPCA9685_H_

#include "GestionLed.h"
#include "GestionPCA9685.h"

class GestionLedPCA9685 {
	public:
		GestionLedPCA9685(Register_Led, Address);

		void setPercent(float);
		void setValue(uint8_t);
		uint8_t getMaxValue(void);
		
		virtual ~GestionLedPCA9685();
	
	private:
		GestionPCA9685 pca9685;
		GestionLed led;
		Register_Led ledValue;
};

#endif