/*
 * GestionINA3221.h
 *
 *  Created on: 30 november 2017
 *      Author: totof
 * Controle un module INA3221
 */

#ifndef _GESTION_INA3221_H_
#define _GESTION_INA3221_H_

#include <stdint.h>
#include "GestionI2C.h"

#define ResistanceShunt 0.1
#define RESET 0b1000000000000000
#define TI 0x5449
#define INA3221 0x3220
#define _40MICROVOLT 0.04
#define _8MILLIVOLT 0.008

enum Address {
	ADDR_40 = 0x40,
	ADDR_41 = 0x41,
	ADDR_42 = 0x42,
	ADDR_43 = 0x43
};

enum Channel {
	Channel_1 = 1,
	Channel_2 = 2,
	Channel_3 = 3
};

enum Register {
	Config = 0x00,
	Channel1ShuntVoltage = 0x01,
	Channel1BusVoltage = 0x02,
	Channel2ShuntVoltage = 0x03,
	Channel2BusVoltage = 0x04,
	Channel3ShuntVoltage = 0x05,
	Channel3BusVoltage = 0x06,
	Channel1CriticalAlertLimit = 0x07,
	Channel1WarningAlertLimit = 0x08,
	Channel2CriticalAlertLimit = 0x09,
	Channel2WarningAlertLimit = 0x0A,
	Channel3CriticalAlertLimit = 0x0B,
	Channel3WarningAlertLimit = 0x0C,
	ShuntVoltageSum = 0x0D,
	ShuntVoltageSumLimit = 0x0E,
	MaskEnable = 0x0F,
	PowerValidUpperLimit = 0x10,
	PowerValidLowerLimit = 0x11,
	ManufacturerID = 0xFE,
	DieID = 0xFF
};

enum Channel1 {
	Channel1On  = 0b0100000000000000,
	Channel1Off = 0b0000000000000000
};
	
enum Channel2 {
	Channel2On  = 0b0010000000000000,
	Channel2Off = 0b0000000000000000
};

enum Channel3 {
	Channel3On  = 0b0001000000000000,
	Channel3Off = 0b0000000000000000
};

enum Average {
	Avg_1    = 0b0000000000000000,
	Avg_4    = 0b0000001000000000,
	Avg_16   = 0b0000010000000000,
	Avg_64   = 0b0000011000000000,
	Avg_128  = 0b0000100000000000,
	Avg_256  = 0b0000101000000000,
	Avg_512  = 0b0000110000000000,
	Avg_1024 = 0b0000111000000000
};

enum BusVoltageConversionTime {	
    VBUS_140US  = 0b0000000000000000,
    VBUS_204US  = 0b0000000001000000,
    VBUS_332US  = 0b0000000010000000,
    VBUS_588US  = 0b0000000011000000,
    VBUS_1100US = 0b0000000100000000,
    VBUS_2116US = 0b0000000101000000,
    VBUS_4156US = 0b0000000110000000,
    VBUS_8244US = 0b0000000111000000
};

enum ShuntVoltageConversionTime {	
    SBUS_140US  = 0b0000000000000000,
    SBUS_204US  = 0b0000000000001000,
    SBUS_332US  = 0b0000000000010000,
    SBUS_588US  = 0b0000000000011000,
    SBUS_1100US = 0b0000000000100000,
    SBUS_2116US = 0b0000000000101000,
    SBUS_4156US = 0b0000000000110000,
    SBUS_8244US = 0b0000000000111000
};

enum Mode {
    PowerDown                    = 0b0000000000000000,
    ShuntVoltageTriggered        = 0b0000000000000001,
    BusVoltageTrigerred          = 0b0000000000000010,
    ShuntAndBusVoltageTriggered  = 0b0000000000000011,
    ShuntVoltageContinuous       = 0b0000000000000101,
    BusVoltageContinuous         = 0b0000000000000110,
    ShuntAndBusVoltageContinuous = 0b0000000000000111
};

enum SummationChannelControl1 {
	SummationChannelControl1On  = 0b0100000000000000,
	SummationChannelControl1Off = 0b0000000000000000
};

enum SummationChannelControl2 {
	SummationChannelControl2On  = 0b0010000000000000,
	SummationChannelControl2Off = 0b0000000000000000
};

enum SummationChannelControl3 {
	SummationChannelControl3On  = 0b0001000000000000,
	SummationChannelControl3Off = 0b0000000000000000
};

enum WarningAlertLatchEnable {
	WarningAlertLatchEnableOn  = 0b0000100000000000,
	WarningAlertLatchEnableOff = 0b0000000000000000
};

enum CriticalAlertLatchEnable {
	CriticalAlertLatchEnableOn  = 0b0000010000000000,
	CriticalAlertLatchEnableOff = 0b0000000000000000
};

enum CriticalAlertFlagIndicator1 {
	CriticalAlertFlagIndicator1On  = 0b0000001000000000,
	CriticalAlertFlagIndicator1Off = 0b0000000000000000
};

enum CriticalAlertFlagIndicator2 {
	CriticalAlertFlagIndicator2On  = 0b0000000100000000,
	CriticalAlertFlagIndicator2Off = 0b0000000000000000
};

enum CriticalAlertFlagIndicator3 {
	CriticalAlertFlagIndicator3On  = 0b0000000010000000,
	CriticalAlertFlagIndicator3Off = 0b0000000000000000
};

enum SummationAlertFlag {
	SummationAlertFlagOn  = 0b0000000001000000,
	SummationAlertFlagOff = 0b0000000000000000
};

enum WarningAlertFlagIndicator1 {
	WarningAlertFlagIndicator1On  = 0b0000000000100000,
	WarningAlertFlagIndicator1Off = 0b0000000000000000
};

enum WarningAlertFlagIndicator2 {
	WarningAlertFlagIndicator2On  = 0b0000000000010000,
	WarningAlertFlagIndicator2Off = 0b0000000000000000
};

enum WarningAlertFlagIndicator3 {
	WarningAlertFlagIndicator3On  = 0b0000000000001000,
	WarningAlertFlagIndicator3Off = 0b0000000000000000
};

enum PowerValidAlertFlag {
	PowerValidAlertFlagOn  = 0b0000000000000100,
	PowerValidAlertFlagOff = 0b0000000000000000
};

enum TimingControlAlertFlag {
	TimingControlAlertFlagOn  = 0b0000000000000010,
	TimingControlAlertFlagOff = 0b0000000000000000
};

enum ConversionReadyFlag {
	ConversionWriting = 0b0000000000000001,
	ConversionReady   = 0b0000000000000000
};

class GestionINA3221 : GestionI2C {
	public:
		GestionINA3221();
		GestionINA3221(Address);
		bool init(Address);
		bool setConfiguration(Channel1, Channel2, Channel3, Average, BusVoltageConversionTime, ShuntVoltageConversionTime, Mode);
		bool isChannel1(void);
		bool isChannel2(void);
		bool isChannel3(void);
		Average getAverage(void);
		BusVoltageConversionTime getBusVoltageConversionTime(void);
		ShuntVoltageConversionTime getShuntVoltageConversionTime(void);
		Mode getMode(void);
		bool reset(void);
		float getBusVoltage_V(Channel);
		float getShuntVoltage_mV(Channel);
		float getCurrent_mA(Channel);
		float getPower_W(Channel);
		bool setCriticalShuntAlertLimit(Channel, float);
		bool setWarningShuntAlertLimit(Channel, float);
		float getCriticalShuntAlertLimit(Channel);
		float getWarningShuntAlertLimit(Channel);
		float getShuntVoltageSum_mV(void);
		bool setShuntVoltageSumLimit(float);
		float getShuntVoltageSumLimit(void);
		float getCurrentSum_mA(void);
		bool setMaskEnable(SummationChannelControl1, SummationChannelControl2, SummationChannelControl3, WarningAlertLatchEnable, CriticalAlertLatchEnable);
		bool isSummationChannelControl1(void);
		bool isSummationChannelControl2(void);
		bool isSummationChannelControl3(void);
		bool isWarningAlertLatchEnable(void);
		bool isCriticalAlertLatchEnable(void);
		bool isCriticalAlertFlagIndicator1(void);
		bool isCriticalAlertFlagIndicator2(void);
		bool isCriticalAlertFlagIndicator3(void);
		bool isSummationAlertFlag(void);
		bool isWarningAlertFlagIndicator1(void);
		bool isWarningAlertFlagIndicator2(void);
		bool isWarningAlertFlagIndicator3(void);
		bool isPowerValidAlertFlag(void);
		bool isTimingControlAlertFlag(void);
		bool isConversionOk(void);
		bool setPowerValidUpperLimit(float);
		bool setPowerValidLowerLimit(float);
		float getPowerValidUpperLimit(void);
		float getPowerValidLowerLimit(void);
		uint16_t getManufacturerID(void);
		bool isManufacturerID(void);
		uint16_t getDieID(void);
		bool isDieID(void);
};

#endif