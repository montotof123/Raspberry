/*
 * GestionMPR121.h
 *
 *  Created on: 17 december 2017
 *      Author: totof
 * Controle un module MPR121
 */

#ifndef _GESTION_MPR121_H_
#define _GESTION_MPR121_H_

#include "GestionPinGPIO.h"
#include "GestionI2C.h"
#include <stdint.h>
#include <list>

#define RESET 0x63

enum AdresseMpr121 {
	ADDRESS_VDD_5A = 0x5A,
	ADDRESS_VSS_5B = 0x5B,
	ADDRESS_SDA_5C = 0x5C,
	ADDRESS_SCL_5D = 0x5D
};

enum RegistreMpr121 {
	REG_TOUCH_STATUS_LSB = 0x00,
	REG_TOUCH_STATUS_MSB = 0x01,
	REG_OOR_STATUS_LSB = 0x02,
	REG_OOR_STATUS_MSB = 0x03,
	REG_ELE0_FILTERED_DATA_LSB = 0x04,
	REG_ELE0_FILTERED_DATA_MSB = 0x05,
	REG_ELE1_FILTERED_DATA_LSB = 0x06,
	REG_ELE1_FILTERED_DATA_MSB = 0x07,
	REG_ELE2_FILTERED_DATA_LSB = 0x08,
	REG_ELE2_FILTERED_DATA_MSB = 0x09,
	REG_ELE3_FILTERED_DATA_LSB = 0x0A,
	REG_ELE3_FILTERED_DATA_MSB = 0x0B,
	REG_ELE4_FILTERED_DATA_LSB = 0x0C,
	REG_ELE4_FILTERED_DATA_MSB = 0x0D,
	REG_ELE5_FILTERED_DATA_LSB = 0x0E,
	REG_ELE5_FILTERED_DATA_MSB = 0x0F,
	REG_ELE6_FILTERED_DATA_LSB = 0x10,
	REG_ELE6_FILTERED_DATA_MSB = 0x11,
	REG_ELE7_FILTERED_DATA_LSB = 0x12,
	REG_ELE7_FILTERED_DATA_MSB = 0x13,
	REG_ELE8_FILTERED_DATA_LSB = 0x14,
	REG_ELE8_FILTERED_DATA_MSB = 0x15,
	REG_ELE9_FILTERED_DATA_LSB = 0x16,
	REG_ELE9_FILTERED_DATA_MSB = 0x17,
	REG_ELE10_FILTERED_DATA_LSB = 0x18,
	REG_ELE10_FILTERED_DATA_MSB = 0x19,
	REG_ELE11_FILTERED_DATA_LSB = 0x1A,
	REG_ELE11_FILTERED_DATA_MSB = 0x1B,
	REG_ELEPROX_FILTERED_DATA_LSB = 0x1C,
	REG_ELEPROX_FILTERED_DATA_MSB = 0x1D,
	REG_ELE0_BASELINE = 0x1E,
	REG_ELE1_BASELINE = 0x1F,
	REG_ELE2_BASELINE = 0x20,
	REG_ELE3_BASELINE = 0x21,
	REG_ELE4_BASELINE = 0x22,
	REG_ELE5_BASELINE = 0x23,
	REG_ELE6_BASELINE = 0x24,
	REG_ELE7_BASELINE = 0x25,
	REG_ELE8_BASELINE = 0x26,
	REG_ELE9_BASELINE = 0x27,
	REG_ELE10_BASELINE = 0x28,
	REG_ELE11_BASELINE = 0x29,
	REG_ELEPROX_BASELINE = 0x2A,
	REG_MHD_RISING = 0x2B,
	REG_NHD_RISING = 0x2C,
	REG_NCL_RISING = 0x2D,
	REG_FDL_RISING = 0x2E,
	REG_MHD_FALLING = 0x2F,
	REG_NHD_FALLING = 0x30,
	REG_NCL_FALLING = 0x31,
	REG_FDL_FALLING = 0x32,
	REG_NHD_TOUCHED = 0x33,
	REG_NCL_TOUCHED = 0x34,
	REG_FDL_TOUCHED = 0x35,
	REG_ELEPROX_MHD_RISING = 0x36,
	REG_ELEPROX_NHD_RISING = 0x37,
	REG_ELEPROX_NCL_RISING = 0x38,
	REG_ELEPROX_FDL_RISING = 0x39,
	REG_ELEPROX_MHD_FALLING = 0x3A,
	REG_ELEPROX_NHD_FALLING = 0x3B,
	REG_ELEPROX_NCL_FALLING = 0x3C,
	REG_ELEPROX_FDL_FALLING = 0x3D,
	REG_ELEPROX_NHD_TOUCHED = 0x3E,
	REG_ELEPROX_NCL_TOUCHED = 0x3F,
	REG_ELEPROX_FDL_TOUCHED = 0x40,
	REG_ELE0_TOUCH_THRESHOLD = 0x41,
	REG_ELE0_RELEASE_THRESHOLD = 0x42,
	REG_ELE1_TOUCH_THRESHOLD = 0x43,
	REG_ELE1_RELEASE_THRESHOLD = 0x44,
	REG_ELE2_TOUCH_THRESHOLD = 0x45,
	REG_ELE2_RELEASE_THRESHOLD = 0x46,
	REG_ELE3_TOUCH_THRESHOLD = 0x47,
	REG_ELE3_RELEASE_THRESHOLD = 0x48,
	REG_ELE4_TOUCH_THRESHOLD = 0x49,
	REG_ELE4_RELEASE_THRESHOLD = 0x4A,
	REG_ELE5_TOUCH_THRESHOLD = 0x4B,
	REG_ELE5_RELEASE_THRESHOLD = 0x4C,
	REG_ELE6_TOUCH_THRESHOLD = 0x4D,
	REG_ELE6_RELEASE_THRESHOLD = 0x4E,
	REG_ELE7_TOUCH_THRESHOLD = 0x4F,
	REG_ELE7_RELEASE_THRESHOLD = 0x50,
	REG_ELE8_TOUCH_THRESHOLD = 0x51,
	REG_ELE8_RELEASE_THRESHOLD = 0x52,
	REG_ELE9_TOUCH_THRESHOLD = 0x53,
	REG_ELE9_RELEASE_THRESHOLD = 0x54,
	REG_ELE10_TOUCH_THRESHOLD = 0x55,
	REG_ELE10_RELEASE_THRESHOLD = 0x56,
	REG_ELE11_TOUCH_THRESHOLD = 0x57,
	REG_ELE11_RELEASE_THRESHOLD = 0x58,
	REG_ELEPROX_TOUCH_THRESHOLD = 0x59,
	REG_ELEPROX_RELEASE_THRESHOLD = 0x5A,
	REG_DEBOUNCE_TOUCH_AND_RELEASE = 0x5B,
	REG_AFE_CONFIGURATION1 = 0x5C,
	REG_AFE_CONFIGURATION2 = 0x5D,
	REG_ELECTRODE_CONFIGURATION = 0x5E,
	REG_ELE0_ELECTRODE_CURRENT = 0x5F,
	REG_ELE1_ELECTRODE_CURRENT = 0x60,
	REG_ELE2_ELECTRODE_CURRENT = 0x61,
	REG_ELE3_ELECTRODE_CURRENT = 0x62,
	REG_ELE4_ELECTRODE_CURRENT = 0x63,
	REG_ELE5_ELECTRODE_CURRENT = 0x64,
	REG_ELE6_ELECTRODE_CURRENT = 0x65,
	REG_ELE7_ELECTRODE_CURRENT = 0x66,
	REG_ELE8_ELECTRODE_CURRENT = 0x67,
	REG_ELE9_ELECTRODE_CURRENT = 0x68,
	REG_ELE10_ELECTRODE_CURRENT = 0x69,
	REG_ELE11_ELECTRODE_CURRENT = 0x6A,
	REG_ELEPROX_ELECTRODE_CURRENT = 0x6B,
	REG_ELE0_ELE1_CHARGE_TIME = 0x6C,
	REG_ELE2_ELE3_CHARGE_TIME = 0x6D,
	REG_ELE4_ELE5_CHARGE_TIME = 0x6E,
	REG_ELE6_ELE7_CHARGE_TIME = 0x6F,
	REG_ELE8_ELE9_CHARGE_TIME = 0x70,
	REG_ELE10_ELE11_CHARGE_TIME = 0x71,
	REG_ELEPROX_CHARGE_TIME = 0x72,
	REG_GPIO_CONTROL_0 = 0x73,
	REG_GPIO_CONTROL_1 = 0x74,
	REG_GPIO_DATA = 0x75,
	REG_GPIO_DIRECTION_CONTROL = 0x76,
	REG_GPIO_ENABLE = 0x77,
	REG_GPIO_DATA_SET = 0x78,
	REG_GPIO_DATA_CLEAR = 0x79,
	REG_GPIO_DATA_TOGGLE = 0x7A,
	REG_AUTO_CONFIG_CONTROL0 = 0x7B,
	REG_AUTO_CONFIG_CONTROL1 = 0x7C,
	REG_AUTO_CONFIG_USL = 0x7D,
	REG_AUTO_CONFIG_LSL = 0x7E,
	REG_AUTO_CONFIG_TARGET_LEVEL = 0x7F,
	REG_SOFT_RESET_REGISTER = 0x80,
	REG_PWM0 = 0x81,
	REG_PWM1 = 0x82,
	REG_PWM2 = 0x83,
	REG_PWM3 = 0x84
};

inline
RegistreMpr121 &operator++(RegistreMpr121 &r) {
	return r = RegistreMpr121(r + 1);
}

enum Electrode {
	ELE0 = 0,
	ELE1 = 1,
	ELE2 = 2,
	ELE3 = 3,
	ELE4 = 4,
	ELE5 = 5,
	ELE6 = 6,
	ELE7 = 7,
	ELE8 = 8,
	ELE9 = 9,
	ELE10 = 10,
	ELE11 = 11,
	ELEPROX = 12
};

inline
Electrode &operator++(Electrode &e) {
	return e = Electrode(e + 1);
}

// 	REG_TOUCH_STATUS, REG_OOR_STATUS_MSB
enum Touch {
	TOUCH_0    = 0b0000000000000001,
	TOUCH_1    = 0b0000000000000010,
	TOUCH_2    = 0b0000000000000100,
	TOUCH_3    = 0b0000000000001000,
	TOUCH_4    = 0b0000000000010000,
	TOUCH_5    = 0b0000000000100000,
	TOUCH_6    = 0b0000000001000000,
	TOUCH_7    = 0b0000000010000000,
	TOUCH_8    = 0b0000000100000000,
	TOUCH_9    = 0b0000001000000000,
	TOUCH_10   = 0b0000010000000000,
	TOUCH_11   = 0b0000100000000000,
	TOUCH_PROX = 0b0001000000000000
};

#define TOUCH_MASK 0b0001111111111111
#define OVCF16 0b1000000000000000
#define OVCF8 0b10000000
#define ACFF 0b10000000
#define ARFF 0b01000000

// REG_DEBOUNCE_TOUCH_AND_RELEASE
enum Debounce {
	TOUCH_DEBOUNCE = 0b01110000,
	RELEASE_DEBOUNCE = 0b00000111
};

enum TouchDebounce {
	TOUCH_DEBOUNCE_0 = 0b00000000,
	TOUCH_DEBOUNCE_1 = 0b00010000,
	TOUCH_DEBOUNCE_2 = 0b00100000,
	TOUCH_DEBOUNCE_3 = 0b00110000,
	TOUCH_DEBOUNCE_4 = 0b01000000,
	TOUCH_DEBOUNCE_5 = 0b01010000,
	TOUCH_DEBOUNCE_6 = 0b01100000,
	TOUCH_DEBOUNCE_7 = 0b01110000
};

enum ReleaseDebounce {
	RELEASE_DEBOUNCE_0 = 0b00000000,
	RELEASE_DEBOUNCE_1 = 0b00000001,
	RELEASE_DEBOUNCE_2 = 0b00000010,
	RELEASE_DEBOUNCE_3 = 0b00000011,
	RELEASE_DEBOUNCE_4 = 0b00000100,
	RELEASE_DEBOUNCE_5 = 0b00000101,
	RELEASE_DEBOUNCE_6 = 0b00000110,
	RELEASE_DEBOUNCE_7 = 0b00000111
};

// AFE_CONFIGURATION
enum AFEConfiguration {
	FFI = 0b11000000,
	CDC = 0b00111111,
	CDT = 0b11100000,
	SFI = 0b00011000,
	ESI = 0b00000111
};

enum FirstFilterIterations {
	FFI6Samples  = 0b00000000,
	FFI10Samples = 0b01000000,
	FFI18Samples = 0b10000000,
	FFI34Samples = 0b11000000
};

enum ChargeDischargeCurrent {
	CDC0 = 0,
	CDC1 = 1,
	CDC2 = 2,
	CDC3 = 3,
	CDC4 = 4,
	CDC5 = 5,
	CDC6 = 6,
	CDC7 = 7,
	CDC8 = 8,
	CDC9 = 9,
	CDC10 = 10,
	CDC11 = 11,
	CDC12 = 12,
	CDC13 = 13,
	CDC14 = 14,
	CDC15 = 15,
	CDC16 = 16,
	CDC17 = 17,
	CDC18 = 18,
	CDC19 = 19,
	CDC20 = 20,
	CDC21 = 21,
	CDC22 = 22,
	CDC23 = 23,
	CDC24 = 24,
	CDC25 = 25,
	CDC26 = 26,
	CDC27 = 27,
	CDC28 = 28,
	CDC29 = 29,
	CDC30 = 30,
	CDC31 = 31,
	CDC32 = 32,
	CDC33 = 33,
	CDC34 = 34,
	CDC35 = 35,
	CDC36 = 36,
	CDC37 = 37,
	CDC38 = 38,
	CDC39 = 39,
	CDC40 = 40,
	CDC41 = 41,
	CDC42 = 42,
	CDC43 = 43,
	CDC44 = 44,
	CDC45 = 45,
	CDC46 = 46,
	CDC47 = 47,
	CDC48 = 48,
	CDC49 = 49,
	CDC50 = 50,
	CDC51 = 51,
	CDC52 = 52,
	CDC53 = 53,
	CDC54 = 54,
	CDC55 = 55,
	CDC56 = 56,
	CDC57 = 57,
	CDC58 = 58,
	CDC59 = 59,
	CDC60 = 60,
	CDC61 = 61,
	CDC62 = 62,
	CDC63 = 63
};

enum ChargeDischargeTime {
	CDTInvalid  = 0b00000000,
	CDT05US = 0b00100000,
	CDT1US = 0b01000000,
	CDT2US = 0b01100000,
	CDT4US = 0b10000000,
	CDT8US = 0b10100000,
	CDT16US = 0b11000000,
	CDT32US = 0b11100000
};

enum SecondFilterIterations {
	SFI4 = 0b00000000,
	SFI6 = 0b00001000,
	SFI10 = 0b00010000,
	SFI18 = 0b00011000
};

enum ElectrodeSampleInterval {
	ESI1 =   0b00000000,
	ESI2 =   0b00000001,
	ESI4 =   0b00000010,
	ESI8 =   0b00000011,
	ESI16 =  0b00000100,
	ESI32 =  0b00000101,
	ESI64 =  0b00000110,
	ESI128 = 0b00000111
};

// ELECTRODE_CONFIGURATION
enum ElectrodeConfiguration {
	CALIBRATION_LOCK_BIT = 0b11000000,
	ELEPROX_BIT          = 0b00110000,
	ELE_BIT              = 0b00001111
};

enum CalibrationLockBit {
	BASELINE_TRACKING_ENABLE = 0b00000000,
	CALIBRATION_LOCK = 0b01000000,
	BASELINE_TRACKING_AND_INITIALIZE_ENABLE1 = 0b10000000,
	BASELINE_TRACKING_AND_INITIALIZE_ENABLE2 = 0b11000000
};

enum ElectrodeEnabled {
	ELECTRODE_DISABLED = 0b00000000,
	ELECTRODE0         = 0b00000001,
	ELECTRODE0_1       = 0b00000010,
	ELECTRODE0_2       = 0b00000011,
	ELECTRODE0_3       = 0b00000100,
	ELECTRODE0_4       = 0b00000101,
	ELECTRODE0_5       = 0b00000110,
	ELECTRODE0_6       = 0b00000111,
	ELECTRODE0_7       = 0b00001000,
	ELECTRODE0_8       = 0b00001001,
	ELECTRODE0_9       = 0b00001010,
	ELECTRODE0_10      = 0b00001011,
	ELECTRODE0_11      = 0b00001100
};

enum ElectrodeProximityElectrode {
	ELEPROX_DISABLED = 0b00000000,
	ELEPROX0_1       = 0b00010000,
	ELEPROX0_3       = 0b00100000,
	ELEPROX0_11      = 0b00110000
};

// Individual Charge Time 
enum IndividualChargeTime {
	ChargeTime0_2_4_6_8_10 = 0b00000111,
	ChargeTime1_3_5_7_9_11 = 0b01110000,
	ChargeTimeEleProx = 0b00000111
};

// GPIO
enum GPIONumber {
	NO_GPIO = 0b00000000,
	D7 = 0b10000000,
	D6 = 0b01000000,
	D5 = 0b00100000,
	D4 = 0b00010000,
	D3 = 0b00001000,
	D2 = 0b00000100,
	D1 = 0b00000010,
	D0 = 0b00000001
};

enum GPIOFunction {
	GPIODisabled = 0,
	GPIOInput = 1,			// A utiliser que si l'entree est obligatoirement a un niveau, jamais en l'air
	GPIOInputPullDown = 2,  // Si entree en l'air, niveau a 0
	GPIOInputPullUp = 3,	// Si entree en l'air, niveau a 1
	GPIOOutput = 4,
	GPIOOutputHighSideMOS = 5, // Voir https://electronics.stackexchange.com/questions/188745/high-side-driver-and-low-side-driver
	GPIOOutputLowSideMOS = 6
};

// AUTO_CONFIG
enum AutoConfig {
	AFES = 0b11000000,
	RETRY = 0b00110000,
	BVA = 0b00001100,
	ARE = 0b00000010,
	ACE = 0b00000001,
	SCTS = 0b10000000,
	OORIE = 0b00000100,
	ARFIE = 0b00000010,
	ACFIE = 0b00000001
};

enum AutoConfigAFES {
	AFE6Samples  = 0b00000000,
	AFE10Samples = 0b01000000,
	AFE18Samples = 0b10000000,
	AFE34Samples = 0b11000000
};

enum AutoConfigRetry {
	NORETRY     = 0b00000000,
	RETRY2Times = 0b00010000,
	RETRY4Times = 0b00100000,
	RETRY8Times = 0b00110000	
};

enum AutoConfigBaseline {
	BaselineNoChange     = 0b00000000,
	BaselineChangeTo0    = 0b00000100,
	BaselineSetValue5MSB = 0b00001000,
	BaselineSetValue     = 0b00001100
};

enum AutoReConfigActive {
	AutoReConfigEnable  = 0b00000010,
	AutoReConfigDisable = 0b00000000
};

enum AutoConfigActive {
	AutoConfigEnable  = 0b00000001,
	AutoConfigDisable = 0b00000000
};

enum ChargeTimeSearch {
	SkipChargeTimeSearch = 0b10000000,
	DoChargeTimeSearch   = 0b00000000
};

enum AutoConfigInterrupt {
	AutoConfigInterruptFailEnable  = 0b00000001,
	AutoConfigInterruptFailDisable = 0b00000000
};

enum AutoReConfigInterrupt {
	AutoReConfigInterruptFailEnable  = 0b00000010,
	AutoReConfigInterruptFailDisable = 0b00000000
};

enum OutOfRangeInterrupt {
	OutOfRangeInterruptEnable  = 0b00000100,
	OutOfRangeInterruptDisable = 0b00000000
};

// PWM
enum PwmValues {
	PWMOff  = 0x0000, // Pas de pwm donc allume a font
	PWM1_15 = 0x0001, // allumage le plus faible
	PWM2_14 = 0x0010,
	PWM3_13 = 0x0011,
	PWM4_12 = 0x0100,
	PWM5_11 = 0x0101,
	PWM6_10 = 0x0110,
	PWM7_9  = 0x0111,
	PWM8_8  = 0x1000,
	PWM9_7  = 0x1001,
	PWM10_6 = 0x1010,
	PWM11_5 = 0x1011,
	PWM12_4 = 0x1100,
	PWM13_3 = 0x1101,
	PWM14_2 = 0x1110,
	PWM15_1 = 0x1111  // allumage le plus fort
};

class GestionMPR121 : GestionI2C {
	public:
		// Contructeur initialisation
		GestionMPR121();
		GestionMPR121(AdresseMpr121);
		GestionMPR121(AdresseMpr121, PinGPIO);
		bool init(AdresseMpr121);
		bool init(AdresseMpr121, PinGPIO);
		// 0x00 0x01
		uint16_t getAllTouchStatus(void);
		bool getTouchStatus(Electrode, bool = false); // true pour lancer une mesure, sinon lecture du résultat de getAllTouchStatus
		bool getOverCurrentFlag(bool);
		bool setOverCurrent(void);
		// 0x02 0x03
		uint16_t getOutOfRange(void);
		bool isAutoConfigFailFlagFromRegister(void);
		bool isAutoReConfigFailFlagFromRegister(void);
		bool isOutOfRangeFromRegister(Electrode);
		bool isAutoConfigFailFlagFromRead(void);
		bool isAutoReConfigFailFlagFromRead(void);
		bool isOutOfRangeFromRead(Electrode);
		// 0x04 0x1D
		std::list<int8_t> getAllElectrodeData(void);	
		uint16_t getElectrodeDataFromAllRead(Electrode);
		uint16_t getElectrodeDataFromRegister(Electrode);
		// 0x1E 0x2A
		std::list<int8_t> getAllBaselineValue(void);
		uint8_t getBaselineValueFromAllRead(Electrode);
		uint8_t getBaselineValueFromRegister(Electrode);
		bool setBaselineValue(Electrode, uint8_t);
		// 0x00 0x2A
		void getFullData(void);
		// 0x2B 0x2E
		uint8_t getElementMaximumHalfDeltaRising(void);
		bool setElementMaximumHalfDeltaRising(uint8_t);
		uint8_t getElementNoiseHalfDeltaRising(void);
		bool setElementNoiseHalfDeltaRising(uint8_t);
		uint8_t getElementNoiseCountLimitRising(void);
		bool setElementNoiseCountLimitRising(uint8_t);
		uint8_t getElementFilterDelayCountLimitRising(void);
		bool setElementFilterDelayCountLimitRising(uint8_t);
		// 0x2F 0x32
		uint8_t getElementMaximumHalfDeltaFalling(void);
		bool setElementMaximumHalfDeltaFalling(uint8_t);
		uint8_t getElementNoiseHalfDeltaFalling(void);
		bool setElementNoiseHalfDeltaFalling(uint8_t);
		uint8_t getElementNoiseCountLimitFalling(void);
		bool setElementNoiseCountLimitFalling(uint8_t);
		uint8_t getElementFilterDelayCountLimitFalling(void);
		bool setElementFilterDelayCountLimitFalling(uint8_t);
		// 0x33 0x35
		uint8_t getElementNoiseHalfDeltaTouched(void);
		bool setElementNoiseHalfDeltaTouched(uint8_t);
		uint8_t getElementNoiseCountLimitTouched(void);
		bool setElementNoiseCountLimitTouched(uint8_t);
		uint8_t getElementFilterDelayCountLimitTouched(void);
		bool setElementFilterDelayCountLimitTouched(uint8_t);
		// 0x36 0x39
		uint8_t getEleProximityMaximumHalfDeltaRising(void);
		bool setEleProximityMaximumHalfDeltaRising(uint8_t);
		uint8_t getEleProximityNoiseHalfDeltaRising(void);
		bool setEleProximityNoiseHalfDeltaRising(uint8_t);
		uint8_t getEleProximityNoiseCountLimitRising(void);
		bool setEleProximityNoiseCountLimitRising(uint8_t);
		uint8_t getEleProximityFilterDelayCountLimitRising(void);
		bool setEleProximityFilterDelayCountLimitRising(uint8_t);
		// 0x3A 0x3D
		uint8_t getEleProximityMaximumHalfDeltaFalling(void);
		bool setEleProximityMaximumHalfDeltaFalling(uint8_t);
		uint8_t getEleProximityNoiseHalfDeltaFalling(void);
		bool setEleProximityNoiseHalfDeltaFalling(uint8_t);
		uint8_t getEleProximityNoiseCountLimitFalling(void);
		bool setEleProximityNoiseCountLimitFalling(uint8_t);
		uint8_t getEleProximityFilterDelayCountLimitFalling(void);
		bool setEleProximityFilterDelayCountLimitFalling(uint8_t);
		// 0x3E 0x40
		uint8_t getEleProximityNoiseHalfDeltaTouched(void);
		bool setEleProximityNoiseHalfDeltaTouched(uint8_t);
		uint8_t getEleProximityNoiseCountLimitTouched(void);
		bool setEleProximityNoiseCountLimitTouched(uint8_t);
		uint8_t getEleProximityFilterDelayCountLimitTouched(void);
		bool setEleProximityFilterDelayCountLimitTouched(uint8_t);
		// 0x41 0x5A
		uint8_t getTouchThreshold(Electrode);
		bool setAllTouchThreshold(uint8_t);
		bool setTouchThreshold(Electrode, uint8_t);
		uint8_t getReleaseThreshold(Electrode);
		bool setAllReleaseThreshold(uint8_t);
		bool setReleaseThreshold(Electrode, uint8_t);
		// 0x5B
		uint8_t getTouchDebounce(void);
		uint8_t getReleaseDebounce(void);
		bool setTouchReleaseDebounce(TouchDebounce, ReleaseDebounce);
		// 0x5C 0x5D
		FirstFilterIterations getFirstFilterIterations(void);
		ChargeDischargeCurrent getChargeDisChargeCurrent(void);
		ChargeDischargeTime getChargeDischargeTime(void);
		SecondFilterIterations getSecondFilterIterations(void);
		ElectrodeSampleInterval getElectrodeSampleInterval(void);
		bool setAFEConfiguration(FirstFilterIterations, ChargeDischargeCurrent, ChargeDischargeTime, SecondFilterIterations, ElectrodeSampleInterval);
		// 0x5E
		CalibrationLockBit getCalibrationLockBit(void);
		ElectrodeEnabled getElectrodeEnabled(void);
		ElectrodeProximityElectrode getElectrodeProximityElectrode(void);
		bool setElectrodeConfiguration(CalibrationLockBit, ElectrodeProximityElectrode, ElectrodeEnabled);
		bool stop(void);
		bool run(ElectrodeProximityElectrode, ElectrodeEnabled);
		// 0x5F 0x6B
		ChargeDischargeCurrent getElectrodeChargeCurrent(Electrode);
		bool setElectrodeChargeCurrent(Electrode, ChargeDischargeCurrent);
		ChargeDischargeCurrent getElectrodeProximityChargeCurrent(void);
		bool setElectrodeProximityChargeCurrent(ChargeDischargeCurrent);
		// 0x6C 0x72
		ChargeDischargeTime getElectrodeChargeTime(Electrode);
		bool setElectrodeChargeTime(Electrode, ChargeDischargeTime);
		ChargeDischargeTime getElectrodeProximityChargeTime(void);
		bool setElectrodeProximityChargeTime(ChargeDischargeTime);
		// 0x73 0x7A
		GPIOFunction getGPIOFunction(GPIONumber);
		bool setGPIOFunction(GPIOFunction functionGPIO7, GPIOFunction functionGPIO6, GPIOFunction functionGPIO5, GPIOFunction functionGPIO4, GPIOFunction functionGPIO3, GPIOFunction functionGPIO2, GPIOFunction functionGPIO1, GPIOFunction functionGPIO0);
		uint8_t getGPIOData(void);
		bool setGPIOData(uint8_t);
		bool isGPIODataOn(GPIONumber);
		bool isGPIODataOff(GPIONumber);
		bool setGPIOData(GPIONumber gpioA, GPIONumber gpioB = NO_GPIO, GPIONumber gpioC = NO_GPIO, GPIONumber gpioD = NO_GPIO, GPIONumber gpioE = NO_GPIO, GPIONumber gpioF = NO_GPIO, GPIONumber gpioG = NO_GPIO, GPIONumber gpioH = NO_GPIO);
		bool clearGPIOData(GPIONumber gpioA, GPIONumber gpioB = NO_GPIO, GPIONumber gpioC = NO_GPIO, GPIONumber gpioD = NO_GPIO, GPIONumber gpioE = NO_GPIO, GPIONumber gpioF = NO_GPIO, GPIONumber gpioG = NO_GPIO, GPIONumber gpioH = NO_GPIO);
		bool toggleGPIOData(GPIONumber gpioA, GPIONumber gpioB = NO_GPIO, GPIONumber gpioC = NO_GPIO, GPIONumber gpioD = NO_GPIO, GPIONumber gpioE = NO_GPIO, GPIONumber gpioF = NO_GPIO, GPIONumber gpioG = NO_GPIO, GPIONumber gpioH = NO_GPIO);
		// 0x7B 0x7F
		AutoConfigAFES getAutoConfigAFES(void);
		AutoConfigRetry getAutoConfigRetry(void);
		AutoConfigBaseline getAutoConfigBaseline(void);
		AutoReConfigActive getAutoReConfig(void);
		AutoConfigActive getAutoConfig(void);
		ChargeTimeSearch getChargeTimeSearch(void);
		AutoConfigInterrupt getAutoConfigInterrupt(void);
		AutoReConfigInterrupt getAutoReConfigInterrupt(void);
		OutOfRangeInterrupt getOutOfRangeInterrupt(void);
		bool setAutoConfigure(AutoConfigAFES, AutoConfigRetry, AutoConfigBaseline, AutoReConfigActive, AutoConfigActive, ChargeTimeSearch, AutoConfigInterrupt, AutoReConfigInterrupt, OutOfRangeInterrupt);
		uint8_t getUpperSiteLimit(void);
		bool setUpperSiteLimit(uint8_t);
		uint8_t getLowerSiteLimit(void);
		bool setLowerSiteLimit(uint8_t);
		uint8_t getTargetLevel(void);
		bool setTargetLevel(uint8_t);
		// 0x80
		bool reset(void);
		// 0x81 0x84
		bool setPwm(GPIONumber, PwmValues);
		PwmValues getPwm(GPIONumber);
		
		// IRQ
		GestionPinGPIO getInterrupt(void);
		// Error
		bool getError(void);
		// Config
		bool config12Electrodes(void);
		bool configAllElectrodeProximity(void);
		bool configAuto12Electrodes(void);
		bool config4Electrodes8Gpio(void);
		bool configAuto8Electrodes4prox(void);
		// Debug
		uint8_t getRegister(RegistreMpr121);
		bool setRegister(RegistreMpr121, uint8_t);
		
	private:
		GestionPinGPIO interrupt;

		bool error = false;

		uint16_t touchStatut;
		bool touchRead = false;
		
		uint16_t outOfRange;
		bool outOfRangeRead = false;

		std::list<int8_t> data;
		bool dataRead = false;
		
		std::list<int8_t> baseline;
		bool baselineRead = false;
};
#endif