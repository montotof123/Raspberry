/*
 * GestionPCA9685.h
 *
 * Created on 13/09/2017
 * Author Totof
 *
 */

#ifndef GESTIONPCA9685_H
#define GESTIONPCA9685_H

#include <stdint.h>

#include "GestionI2C.h"

#define CLOCK_FREQ 25000000.0 //25MHz default osc clock
#define MIN_PWM_FREQ 24
#define MAX_PWM_FREQ 1526
#define PWM_SCALE 4095

class GestionPCA9685 : GestionI2C {
	public:
		enum Address {
			ADDR_40 = 0x40,
			ADDR_41 = 0x41,
			ADDR_42 = 0x42,
			ADDR_43 = 0x43,
			ADDR_44 = 0x44,
			ADDR_45 = 0x45,
			ADDR_46 = 0x46,
			ADDR_47 = 0x47,
			ADDR_48 = 0x48,
			ADDR_49 = 0x49,
			ADDR_4A = 0x4A,
			ADDR_4B = 0x4B,
			ADDR_4C = 0x4C,
			ADDR_4D = 0x4D,
			ADDR_4E = 0x4E,
			ADDR_4F = 0x4F,
			ADDR_50 = 0x50,
			ADDR_51 = 0x51,
			ADDR_52 = 0x52,
			ADDR_53 = 0x53,
			ADDR_54 = 0x54,
			ADDR_55 = 0x55,
			ADDR_56 = 0x56,
			ADDR_57 = 0x57,
			ADDR_58 = 0x58,
			ADDR_59 = 0x59,
			ADDR_5A = 0x5A,
			ADDR_5B = 0x5B,
			ADDR_5C = 0x5C,
			ADDR_5D = 0x5D,
			ADDR_5E = 0x5E,
			ADDR_5F = 0x5F,
			ADDR_60 = 0x60,
			ADDR_61 = 0x61,
			ADDR_62 = 0x62,
			ADDR_63 = 0x63,
			ADDR_64 = 0x64,
			ADDR_65 = 0x65,
			ADDR_66 = 0x66,
			ADDR_67 = 0x67,
			ADDR_68 = 0x68,
			ADDR_69 = 0x69,
			ADDR_6A = 0x6A,
			ADDR_6B = 0x6B,
			ADDR_6C = 0x6C,
			ADDR_6D = 0x6D,
			ADDR_6E = 0x6E,
			ADDR_6F = 0x6F,
			ADDR_71 = 0x71,
			ADDR_72 = 0x72,
			ADDR_73 = 0x73,
			ADDR_74 = 0x74,
			ADDR_75 = 0x75,
			ADDR_76 = 0x76,
			ADDR_77 = 0x77,
			ADDR_78 = 0x78,
			ADDR_79 = 0x79,
			ADDR_7A = 0x7A,
			ADDR_7B = 0x7B,
			ADDR_7C = 0x7C,
			ADDR_7D = 0x7D,
			ADDR_7E = 0x7E,
			ADDR_7F = 0x7F
		};

		enum Register_Mode {
			MODE1 = 0x00,
			MODE2 = 0x01
		};

		enum Register_I2C {
			SUBADR1 =    0x02,		
			SUBADR2 =    0x03,		
			SUBADR3 =    0x04,		
			ALLCALLADR = 0x05
		};

		enum Register_Led {
			LED_0  = 0x06,
			LED_1  = 0x0A,
			LED_2  = 0x0E,
			LED_3  = 0x12,
			LED_4  = 0x16,
			LED_5  = 0x1A,
			LED_6  = 0x1E,
			LED_7  = 0x22,
			LED_8  = 0x26,
			LED_9  = 0x2A,
			LED_10 = 0x2E,
			LED_11 = 0x32,
			LED_12 = 0x36,
			LED_13 = 0x3A,
			LED_14 = 0x3E,
			LED_15 = 0x42
		};

		enum Register_All {
			ALL_LED = 0xFA
		};

		enum Register_Pre_Scale {
			PRE_SCALE = 0xFE
		};

		enum Led_Control {	
			ON_L  = 0x00,	
			ON_H  = 0x01,
			OFF_L = 0x02,
			OFF_H = 0x03	
		};

		GestionPCA9685();
		GestionPCA9685(Address);

		void init(Address);
		bool setPWMFreq (uint16_t);
		bool setPWM (Register_Led, uint16_t, uint16_t);
		bool setPWM (Register_Led, uint16_t);
		bool setPWM (Register_Led, float);
		void setFullOn (Register_Led);
		void setFullOff (Register_Led);
		uint16_t getPWM (Register_Led);
		uint16_t getPWMOff(Register_Led);
		bool setAllPWM (uint16_t, uint16_t);
		bool setAllPWM (uint16_t);
		bool setAllPWM (float);
		void setFullAllOn (void);
		void setFullAllOff (void);
		uint16_t getPWMScale(void);
		void sleep(void);
		void unSleep(void);

		virtual ~GestionPCA9685();

	private:
		void reset(void);
};
#endif