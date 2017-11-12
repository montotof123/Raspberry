/*
 * GestionServoPCA9685.h
 *
 * Created on 14/09/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONSERVOPCA9685_H_
#define GESTIONSERVOPCA9685_H_

#include "GestionServo.h"
#include "GestionPCA9685.h"

class GestionServoPCA9685 : public GestionServo {
	public:
		GestionServoPCA9685(void);
		GestionServoPCA9685(GestionPCA9685::Register_Led, GestionPCA9685*, uint16_t, uint16_t, float);
		GestionServoPCA9685(GestionPCA9685::Register_Led, GestionPCA9685*, Servo);
		void init(GestionPCA9685::Register_Led, GestionPCA9685*, uint16_t, uint16_t, float);
		void init(GestionPCA9685::Register_Led, GestionPCA9685*, Servo);
		bool write(uint16_t);
		bool write(float);

		virtual ~GestionServoPCA9685();
		
	protected:
		bool initialisation(uint16_t);
	
	private:
		GestionPCA9685 *pca9685;
		GestionPCA9685::Register_Led ledValue;
};

#endif