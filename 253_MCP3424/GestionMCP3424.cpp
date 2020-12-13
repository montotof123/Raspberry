/*
 * GestionMCP3424.cpp
 *
 * Created on 12/12/2020
 * Author Totof
 *
 */
 
#ifndef __GestionMCP3424_CPP__
#define __GestionMCP3424_CPP__

#include <stdint.h>
#include "GestionMCP3424.h"

#include "Logger.h"

// *****************
// Constructeur vide
// *****************
GestionMCP3424::GestionMCP3424(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// **********************
// Constructeur 
// @Param adresse I2C
// @Param channel
// @Param Conversion mode
// @Param sample rate
// @Param gain
// **********************
GestionMCP3424::GestionMCP3424(Adresse pAdresse, Channel pChannel, ConversionMode pConversionMode, SampleRate pSampleRate, PgaGain pPgaGain) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pAdresse = ", false);
	Logger::logHex("DEBUG", (uint8_t)pAdresse);	
	Logger::log("DEBUG", " pChannel = ", false);
	Logger::logHex("DEBUG", (uint8_t)pChannel);	
	Logger::log("DEBUG", " pConversionMode = ", false);
	Logger::logHex("DEBUG", (uint8_t)pConversionMode);	
	Logger::log("DEBUG", " pSampleRate = ", false);
	Logger::logHex("DEBUG", (uint8_t)pSampleRate);	
	Logger::log("DEBUG", " pPgaGain = ", false);
	Logger::logHex("DEBUG", (uint8_t)pPgaGain);	

	InitMCP3424(pAdresse, pChannel, pConversionMode, pSampleRate, pPgaGain);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// **********************
// Initialisation
// @Param adresse I2C
// @Param channel
// @Param Conversion mode
// @Param sample rate
// @Param gain
// **********************
bool GestionMCP3424::InitMCP3424(Adresse pAdresse, Channel pChannel, ConversionMode pConversionMode, SampleRate pSampleRate, PgaGain pPgaGain) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	channel = pChannel;
	conversionMode = pConversionMode;
	sampleRate = pSampleRate;
	pgaGain = pPgaGain;
	
	initI2CPeripheric(pAdresse);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return isInitialize();
}

//****************
// Getter channel
// @Return channel
// ***************
GestionMCP3424::Channel GestionMCP3424::getChannel(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " channel = ", false);
	Logger::logHex("DEBUG", (uint8_t)channel);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	return channel;
}

// **************
// Setter channel
// @Param channel
// **************
void GestionMCP3424::setChannel(GestionMCP3424::Channel pChannel) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pChannel = ", false);
	Logger::logHex("DEBUG", (uint8_t)pChannel);	
	
	channel = pChannel;
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

//***********************
// Getter ConvertionMode
// @Return ConvertionMode
// **********************
GestionMCP3424::ConversionMode GestionMCP3424::getConversionMode(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " converstionMode = ", false);
	Logger::logHex("DEBUG", (uint8_t)conversionMode);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	return conversionMode;
}

// *********************
// Setter ConvertionMode
// @Param ConvertionMode
// *********************
void GestionMCP3424::setConversionMode(GestionMCP3424::ConversionMode pConversionMode) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pConvertionMode = ", false);
	Logger::logHex("DEBUG", (uint8_t)pConversionMode);	
	
	conversionMode = pConversionMode;
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

//*******************
// Getter sampleRate
// @Return sampleRate
// ******************
GestionMCP3424::SampleRate GestionMCP3424::getSampleRate(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " sampleRate = ", false);
	Logger::logHex("DEBUG", (uint8_t)sampleRate);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	return sampleRate;
}

// *****************
// Setter sampleRate
// @Param sampleRate
// *****************
void GestionMCP3424::setSampleRate(GestionMCP3424::SampleRate pSampleRate) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pSampleRate = ", false);
	Logger::logHex("DEBUG", (uint8_t)pSampleRate);	
	
	sampleRate = pSampleRate;
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

//****************
// Getter pgaGain
// @Return pgaGain
// ***************
GestionMCP3424::PgaGain GestionMCP3424::getPgaGain(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pgaGain = ", false);
	Logger::logHex("DEBUG", (uint8_t)pgaGain);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	return pgaGain;
}

// **************
// Setter pgaGain
// @Param pgaGain
// **************
void GestionMCP3424::setPgaGain(GestionMCP3424::PgaGain pPgaGain) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pPgaGain = ", false);
	Logger::logHex("DEBUG", (uint8_t)pPgaGain);
	
	pgaGain = pPgaGain;
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// *****************
// Demande de mesure
// @Return la mesure
// *****************
float GestionMCP3424::getMesure(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	double value = -9999.999F;
	double gain;
	bool negatif = false;
	uint32_t binaryValue;
	
	if(isInitialize()) {
		write8(NEW_CONVERSION | channel | conversionMode | sampleRate | pgaGain);
		switch(pgaGain) {
			case GestionMCP3424::PGA_GAIN_X1: gain = 0.5F; break;
			case GestionMCP3424::PGA_GAIN_X2: gain = 1.0F; break;
			case GestionMCP3424::PGA_GAIN_X4: gain = 2.0F; break;
			case GestionMCP3424::PGA_GAIN_X8: gain = 4.0F; break;
		}
		// 18 bits
		if(sampleRate == GestionMCP3424::SAMPLE_RATE_375_SPS) {
			if(readBlock(3) == 3) {
				binaryValue = ((getBlock()[0] & 0x03) << 16) | (getBlock()[1] << 8) | getBlock()[2];
				if ((binaryValue >> 17) & 1) {
					binaryValue &= ~(1 << 17);
					negatif = true;
				}
				value = ((double)binaryValue * (LSB_18 / gain)); 
				if(negatif) {
					value = -value;
				}
			}
		} else {
			if(readBlock(2) == 2) {
				switch(sampleRate) {
					// 16 bits
					case GestionMCP3424::SAMPLE_RATE_15_SPS:  
						binaryValue = (getBlock()[0] << 8) | getBlock()[1];
						if ((binaryValue >> 15) & 1) {
							binaryValue &= ~(1 << 15);
							negatif = true;
						}
						value = ((double)binaryValue * (LSB_16 / gain)); 
						if(negatif) {
							value = -value;
						}
						break;
					// 14 bits
					case GestionMCP3424::SAMPLE_RATE_60_SPS: 
						binaryValue = ((getBlock()[0] & 0b00111111) << 8) | getBlock()[1];
						if ((binaryValue >> 13) & 1) {
							binaryValue &= ~(1 << 13);
							negatif = true;
						}
						value = ((double)binaryValue * (LSB_14 / gain)); 
						if(negatif) {
							value = -value;
						}
						break;
					// 12 bits
					case GestionMCP3424::SAMPLE_RATE_240_SPS: 
						binaryValue = ((getBlock()[0] & 0b00001111) << 8) | getBlock()[1];
						if ((binaryValue >> 11) & 1) {
							binaryValue &= ~(1 << 11);
							negatif = true;
						}
						value = ((double)binaryValue * (LSB_12 / gain)); 
						if(negatif) {
							value = -value;
						}
						break;
				}
			}
		}
	}

	Logger::log("DEBUG", " value = ", false);
	Logger::log("DEBUG", (float)value);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	return(value);
}
		

// ***********
// Destructeur
// ***********
GestionMCP3424::~GestionMCP3424(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

#endif
