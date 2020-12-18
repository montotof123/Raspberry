/*
 * GestionMCP45HVX1.h
 *
 * Created on 14/12/2020
 * Author Totof
 *
 */
 
#ifndef __GestionMCP45HVX1_H__
#define __GestionMCP45HVX1_H__

#include <stdint.h>
#include "GestionI2C.h"

class GestionMCP45HVX1 : GestionI2C {
	public:
		enum Adresse {
			ADRESSE_0x3C = 0x3C,
			ADRESSE_0x3D = 0x3D,
			ADRESSE_0x3E = 0x3E,
			ADRESSE_0x3F = 0x3F
		};
		
		enum Command {
			WRITE     = 0b00000000,
			INCREMENT = 0b00000100,
			DECREMENT = 0b00001000,
			READ      = 0b00001100
		};

		enum Register {
			WIPER = 0b00000000,
			TCON  = 0b01000000
		};
		
		enum Value {
			R5K  = 5000,
			R10K  = 10000,
			R50K  = 50000,
			R100K = 100000
		};

		#define MAX_INT_VALUE 0xFF
		#define CONNECT       0xFF
		#define DISCONNECT    0x00
		#define RHEOSTAT      0x0B
		
		// Constructeur
		GestionMCP45HVX1();
		
		// Constructeur
		GestionMCP45HVX1(Adresse, Value);
		
		// Initialisation
		bool InitMCP45HVX1(Adresse, Value);
		
		// Valeur
		uint16_t getValue(void);
		bool setValue(uint16_t);
		uint16_t increment(void);
		uint16_t decrement(void);

		// ConversionMode
		bool connect(void);
		bool disconnect(void);
		bool rheostat(void);
		
		// Tcon
		uint8_t readTCON(void);
		
		// Destructeur
		virtual ~GestionMCP45HVX1(void);
	private:
		Value potValue;
};

#endif
