/*
 * GestionHMC5883.h
 *
 *  Created on: 01 october 2017
 *      Author: totof
 * Controle un module HMC5883
 */

#ifndef _GESTION_HMC5883_H_
#define _GESTION_HMC5883_H_

#include <stdint.h>
#include <string>
#include <list>
#include "GestionI2C.h"

// http://www.magnetic-declination.com/
// Negatif si vers l'ouest positif si vers l'est
#define MagneticDeclinaison 1.58 

class GestionHMC5883  : public GestionI2C {
	public:
		enum Address {
			AddressBase  = 0x1E,
			AddressRead  = 0x3D,
			AddressWrite = 0x3C
		};

		enum Register {
			ConfigurationA  = 0x00,
			ConfigurationB  = 0x01,
			Mode            = 0x02,
			DataXMSB        = 0x03,
			DataXLSB        = 0x04,
			DataZMSB        = 0x05,
			DataZLSB        = 0x06,
			DataYMSB        = 0x07,
			DataYLSB        = 0x08,
			Status          = 0x09,
			IdentificationA = 0x0A,
			IdentificationB = 0x0B,
			IdentificationC = 0x0C
		};

		enum NombreMesure {
			_1               = 0b00000000,
			_2               = 0b00100000,
			_4               = 0b01000000,
			_8               = 0b01100000
		};

		enum Frequence {
			_0_75         = 0b00000000,
			_1_5          = 0b00000100,
			_3            = 0b00001000,
			_7_5          = 0b00001100,
			_15           = 0b00010000,
			_30           = 0b00010100,
			_75           = 0b00011000
		};

		enum MeasurementMode {
			Normal                = 0b00000000,
			PositiveBias          = 0b00000001,
			NegativeBias          = 0b00000010
		};
			
		enum Gain {
			_1370    = 0b00000000,
			_1090    = 0b00100000,
			_820     = 0b01000000,
			_660     = 0b01100000,
			_440     = 0b10000000,
			_390     = 0b10100000,
			_330     = 0b11000000,
			_230     = 0b11100000
		};

		enum ModeSelect {	
			Continu           = 0b00000000, 
			SingleMesureament = 0b00000001,
			Idle              = 0b00000010
		};

		enum Status {	
			Lock        = 0b00000010, 
			Ready       = 0b00000001
		};

		enum Mask {
			NombreMesureMask    = 0b01100000,
			FrequenceMask       = 0b00011100,
			MeasurementModeMask = 0b00000011,
			GainMask            = 0b11100000,
			ModeMask            = 0b00000011
		};

		GestionHMC5883();
		GestionHMC5883(Address);
		bool init(Address);
		
		bool setNombreMesure(NombreMesure);
		NombreMesure getNombreMesure(void);
		
		bool setFrequence(Frequence);
		Frequence getFrequence(void);
		
		bool setMesurementMode(MeasurementMode);
		MeasurementMode getMesurementMode(void);
		
		bool setGain(Gain);
		Gain getGain(void);
		
		bool setModeSelect(ModeSelect);
		ModeSelect getModeSelect(void);
		
		bool Config(NombreMesure, Frequence, MeasurementMode, Gain, ModeSelect);
		
		int16_t getRawAxeX(void);
		int16_t getRawAxeY(void);
		int16_t getRawAxeZ(void);
		int16_t getRawFromAllAxeX(void);
		int16_t getRawFromAllAxeY(void);
		int16_t getRawFromAllAxeZ(void);
		std::list<int8_t> getRawAllAxes(void);
		float getGaussAxeX(void);
		float getGaussAxeY(void);
		float getGaussAxeZ(void);
		float getMagneticCap(void);
		float getCap(void);
		
		std::string getId(void);
		bool isMagnetometre(void);
		
		bool isLock(void);
		bool isReady(void);
	
	protected:
		union i2cData{
			int16_t uSData;
			int8_t uCData[2];
		};
		
	private:
		uint16_t getValGain(void);
		
		i2cData rawAllAxeX;
		i2cData rawAllAxeY;
		i2cData rawAllAxeZ;	
};

#endif
