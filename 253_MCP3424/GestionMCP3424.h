/*
 * GestionMCP3424.h
 *
 * Created on 12/12/2020
 * Author Totof
 *
 */
 
#ifndef __GestionMCP3424_H__
#define __GestionMCP3424_H__

#include <stdint.h>
#include "GestionI2C.h"

class GestionMCP3424 : GestionI2C {
	public:
		enum Adresse {
			ADRESSE_0x68 = 0x68,
			ADRESSE_0x69 = 0x69,
			ADRESSE_0x6A = 0x6A,
			ADRESSE_0x6B = 0x6B,
			ADRESSE_0x6C = 0x6C,
			ADRESSE_0x6D = 0x6D,
			ADRESSE_0x6E = 0x6E,
			ADRESSE_0x6F = 0x6F
		};
		
		enum Channel {
			CHANNEL_1 = 0b00000000,
			CHANNEL_2 = 0b00100000,
			CHANNEL_3 = 0b01000000,
			CHANNEL_4 = 0b01100000
		};

		enum ConversionMode {
			Continuous = 0b00000000,
			OneShot    = 0b00010000
		};

		enum SampleRate {
			SAMPLE_RATE_240_SPS = 0b00000000,
			SAMPLE_RATE_60_SPS  = 0b00000100,
			SAMPLE_RATE_15_SPS  = 0b00001000,
			SAMPLE_RATE_375_SPS = 0b00001100,
		};

		enum PgaGain {
			PGA_GAIN_X1 = 0b00000000,
			PGA_GAIN_X2 = 0b00000001,
			PGA_GAIN_X4 = 0b00000010,
			PGA_GAIN_X8 = 0b00000011
		};
		
		#define NEW_CONVERSION 0b10000000
		#define CONVERSION_OK  0b00000000
		#define LSB_18 2.048F / 262144.0F
		#define LSB_16 2.048F / 65536.0F
		#define LSB_14 2.048F / 16384.0F
		#define LSB_12 2.048F / 4096.0F

		// Constructeur
		GestionMCP3424();
		
		// Constructeur
		GestionMCP3424(Adresse, Channel, ConversionMode, SampleRate, PgaGain);
		
		// Initialisation
		bool InitMCP3424(Adresse, Channel, ConversionMode, SampleRate, PgaGain);
		
		// Channel
		Channel getChannel(void);
		void setChannel(Channel);

		// ConverstionMode
		ConversionMode getConversionMode(void);
		void setConversionMode(ConversionMode);

		// SampleRate
		SampleRate getSampleRate(void);
		void setSampleRate(SampleRate);

		// PgaGain
		PgaGain getPgaGain(void);
		void setPgaGain(PgaGain);

		// Demande de mesure
		float getMesure(void);
		
		// Destructeur
		virtual ~GestionMCP3424(void);
	private:
		Channel channel;
		ConversionMode conversionMode;
		SampleRate sampleRate;
		PgaGain pgaGain;
};

#endif
