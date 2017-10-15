/*
 * GestionHMC5983.h
 *
 *  Created on: 01 october 2017
 *      Author: totof
 * Controle un module HMC5983
 */

#ifndef _GESTION_HMC5983_H_
#define _GESTION_HMC5983_H_

#include <stdint.h>
#include "GestionHMC5883.h"

class GestionHMC5983 : public GestionHMC5883 {
	public:
		enum Register {
			ConfigurationA  = 0x00,
			ConfigurationB  = 0x01,
			Mode            = 0x02,
			DataXMSB        = 0x03,
			DataXLSB        = 0x04,
			DataYMSB        = 0x05,
			DataYLSB        = 0x06,
			DataZMSB        = 0x07,
			DataZLSB        = 0x08,
			Status          = 0x09,
			IdentificationA = 0x0A,
			IdentificationB = 0x0B,
			IdentificationC = 0x0C,
			TemperatureMSB  = 0x31,
			TemperatureLSB  = 0x32
		};

		enum Temperature {
			SensorOn        = 0b10000000,
			SensorOff       = 0b00000000
		};

		enum Frequence {
			_0_75         = 0b00000000,
			_1_5          = 0b00000100,
			_3            = 0b00001000,
			_7_5          = 0b00001100,
			_15           = 0b00010000,
			_30           = 0b00010100,
			_75           = 0b00011000,
			_220          = 0b00011100
		};

		enum SpeedI2C {
			HighSpeedI2C      = 0b10000000
		};

		enum Power {
			PowerLow          = 0b00100000 
		};

		enum Status {	
			OverWritten = 0b00010000,
			Lock        = 0b00000010, 
			Ready       = 0b00000001
		};

		enum Mask {
			TemperatureMask     = 0b10000000,
			NombreMesureMask    = 0b01100000,
			FrequenceMask       = 0b00011100,
			MeasurementModeMask = 0b00000011,
			GainMask            = 0b11100000,
			ModeMask            = 0b00000011,
			HighSpeedI2CMask    = 0b10000000,
			PowerLowMask        = 0b00100000
		};

		GestionHMC5983();
		GestionHMC5983(Address);
		bool init(Address);
		
		bool sensorTemperatureOn(void);
		bool isSensorTemperatureOn(void);
		bool sensorTemperatureOff(void);
		bool isSensorTemperatureOff(void);
		
		bool setHighSpeedI2COn(void);
		bool isHighSpeedI2COn(void);
		bool setHighSpeedI2COff(void);
		bool isHighSpeedI2COff(void);
		
		bool setPowerLowOn(void);
		bool isPowerLowOn(void);
		bool setPowerLowOff(void);
		bool isPowerLowOff(void);
		
		bool Config(Temperature, NombreMesure, Frequence, MeasurementMode, Gain, ModeSelect);
		
		float getTemperature(void);
		
		bool isOverWritten(void);
};

#endif

