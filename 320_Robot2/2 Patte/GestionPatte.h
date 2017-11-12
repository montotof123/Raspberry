/*
 * GestionPatte.h
 *
 * Created on 21/09/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONPATTE_H_
#define GESTIONPATTE_H_

#include "GestionServoPCA9685.h"

class GestionPatte {
	public:
		GestionPatte(void);
		GestionPatte(GestionPCA9685*, GestionPCA9685::Register_Led, Servo, GestionPCA9685::Register_Led, Servo, GestionPCA9685::Register_Led, Servo);
		void init(GestionPCA9685*, GestionPCA9685::Register_Led, Servo, GestionPCA9685::Register_Led, Servo, GestionPCA9685::Register_Led, Servo);
		
		void rotation(uint16_t);
		void hausse(uint16_t);
		void translation(uint16_t);
		void rotation(uint16_t, uint32_t);
		void hausse(uint16_t, uint32_t);
		void translation(uint16_t, uint32_t);
		
		GestionServoPCA9685& getBassin(void);
		GestionServoPCA9685& getFemur(void);
		GestionServoPCA9685& getRotule(void);

		virtual ~GestionPatte();
	
	private:
		GestionServoPCA9685 bassin;
		GestionServoPCA9685 femur;
		GestionServoPCA9685 rotule;

		void mouvement(GestionServoPCA9685&, uint16_t, uint32_t);
};

#endif