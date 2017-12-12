/*
 * GestionINA3221.cpp
 *
 *  Created on: 02 decembre 2017
 *      Author: totof
 * Controle un module INA3221
 */
 
#include "GestionINA3221.h"

// *****************
// Constructeur vide
// *****************
GestionINA3221::GestionINA3221() {
}

// ******************************
// Constructeur
// @Param l'adresse I2C du module
// ******************************
GestionINA3221::GestionINA3221(Address address) {
	init(address);
}

// *******************************
// Initialisation
// @Param l'adresse I2C du module
// @Return true si ok, false sinon
// *******************************
bool GestionINA3221::init(Address address) {
	GestionI2C::init(address);
	return GestionI2C::isInitialize();
}

// *****************************************************
// Configuration du circuit
// @Param channel1 actif
// @Param channel2 actif
// @Param channel3 actif
// @Param nombre de mesures pour moyennage
// @Param Temps de convertion de mesure du Bus Voltage
// @Param Temps de convertion de mesure du Shunt Voltage
// @Param Mode de mesure
// *****************************************************
bool GestionINA3221::setConfiguration(Channel1 channel1, Channel2 channel2, Channel3 channel3, Average average, 
				BusVoltageConversionTime busVoltageConversionTime, ShuntVoltageConversionTime shuntVoltageConversionTime, Mode mode) {
	return !write16Swapped(Config, channel1 | channel2 | channel3 | average | busVoltageConversionTime | shuntVoltageConversionTime | mode);
}

// *********************************
// Le channel 1 est t'il actif ?
// @Return true si oui, false si non
// *********************************
bool GestionINA3221::isChannel1(void) {
	return read16Swapped(Config) & Channel1On;	
}

// *********************************
// Le channel 2 est t'il actif ?
// @Return true si oui, false si non
// *********************************
bool GestionINA3221::isChannel2(void) {
	return read16Swapped(Config) & Channel2On;	
}
		
// *********************************
// Le channel 3 est t'il actif ?
// @Return true si oui, false si non
// *********************************
bool GestionINA3221::isChannel3(void) {
	return read16Swapped(Config) & Channel3On;		
}

// *******************************************
// Donne le nombre de mesures pour moyennage
// @Return le nombre de mesures pour moyennage
// *******************************************
Average GestionINA3221::getAverage(void) {
	switch(read16Swapped(Config) & Avg_1024) {
		case Avg_1: return Avg_1;
		case Avg_4: return Avg_4;
		case Avg_16: return Avg_16;
		case Avg_64: return Avg_64;
		case Avg_128: return Avg_128;
		case Avg_256: return Avg_256;
		case Avg_512: return Avg_512;
		case Avg_1024: return Avg_1024;
	}
}

// *********************************************
// Donne le temps de convertion du Bus Voltage
// @Return le temps de convertion du Bus Voltage
// *********************************************
BusVoltageConversionTime GestionINA3221::getBusVoltageConversionTime(void) {
	switch(read16Swapped(Config) & VBUS_8244US) {
		case VBUS_140US: return VBUS_140US;
		case VBUS_204US: return VBUS_204US;
		case VBUS_332US: return VBUS_332US;
		case VBUS_588US: return VBUS_588US;
		case VBUS_1100US: return VBUS_1100US;
		case VBUS_2116US: return VBUS_2116US;
		case VBUS_4156US: return VBUS_4156US;
		case VBUS_8244US: return VBUS_8244US;
	}
}

// ***********************************************
// Donne le temps de convertion du Shunt Voltage
// @Return le temps de convertion du Shunt Voltage
// ***********************************************
ShuntVoltageConversionTime GestionINA3221::getShuntVoltageConversionTime(void) {
	switch(read16Swapped(Config) & SBUS_8244US) {
		case SBUS_140US: return SBUS_140US;
		case SBUS_204US: return SBUS_204US;
		case SBUS_332US: return SBUS_332US;
		case SBUS_588US: return SBUS_588US;
		case SBUS_1100US: return SBUS_1100US;
		case SBUS_2116US: return SBUS_2116US;
		case SBUS_4156US: return SBUS_4156US;
		case SBUS_8244US: return SBUS_8244US;
	}
}

// *************************
// Donne le mode de mesure
// @Return le mode de mesure
// *************************
Mode GestionINA3221::getMode(void) {
	switch(read16Swapped(Config) & ShuntAndBusVoltageContinuous) {
		case PowerDown: return PowerDown;
		case ShuntVoltageTriggered: return ShuntVoltageTriggered;
		case BusVoltageTrigerred: return BusVoltageTrigerred;
		case ShuntAndBusVoltageTriggered: return ShuntAndBusVoltageTriggered;
		case ShuntVoltageContinuous: return ShuntVoltageContinuous;
		case BusVoltageContinuous: return BusVoltageContinuous;
		case ShuntAndBusVoltageContinuous: return ShuntAndBusVoltageContinuous;
	}
}

// ***************
// Reset du module
// ***************
bool GestionINA3221::reset(void) {
	return !write16Swapped(Config, RESET);
}

// *********************************************
// Donne la tension du Bus en Volt pour un canal
// @Param le canal
// @Return la tension en volt
// *********************************************
float GestionINA3221::getBusVoltage_V(Channel channel) {
	while(!isConversionOk());
	switch(channel) {
		case Channel_1: return ((read16Swapped(Channel1BusVoltage) >> 3)) * _8MILLIVOLT;
		case Channel_2: return ((read16Swapped(Channel2BusVoltage) >> 3)) * _8MILLIVOLT;
		case Channel_3: return ((read16Swapped(Channel3BusVoltage) >> 3)) * _8MILLIVOLT;
	}
}

// **************************************************
// Donne la tension du Bus en milliVolt pour un canal
// @Param le canal
// @Return la tension en milliVolt
// **************************************************
float GestionINA3221::getShuntVoltage_mV(Channel channel) {
	while(!isConversionOk());
	switch(channel) {
		case Channel_1: return ((read16Swapped(Channel1ShuntVoltage) >> 3)) * _40MICROVOLT;
		case Channel_2: return ((read16Swapped(Channel2ShuntVoltage) >> 3)) * _40MICROVOLT;
		case Channel_3: return ((read16Swapped(Channel3ShuntVoltage) >> 3)) * _40MICROVOLT;
	}
}

// ************************************
// Donne le courant en mA pour un canal
// @Param le canal
// @Return le courant en mA
// ************************************
float GestionINA3221::getCurrent_mA(Channel channel) {
	return getShuntVoltage_mV(channel) / ResistanceShunt;
}

// *************************************
// Donne la puissance en W pour un canal
// @Param le canal
// @Return la puissance en W
// *************************************
float GestionINA3221::getPower_W(Channel channel) {
	return getBusVoltage_V(channel) * getCurrent_mA(channel) / 1000.0;
}

// **********************************************
// Positionne la valeur shunt limite sur un canal
// @Param le canal
// @Param la valeur en mV
// **********************************************
bool GestionINA3221::setCriticalShuntAlertLimit(Channel channel, float valeur) {
	switch(channel) {
		case Channel_1: return !write16Swapped(Channel1CriticalAlertLimit, (uint16_t)(valeur / _40MICROVOLT) << 3);
		case Channel_2: return !write16Swapped(Channel2CriticalAlertLimit, (uint16_t)(valeur / _40MICROVOLT) << 3);
		case Channel_3: return !write16Swapped(Channel3CriticalAlertLimit, (uint16_t)(valeur / _40MICROVOLT) << 3);
	}
}

// **********************************************
// Positionne la valeur shunt alarme sur un canal
// @Param le canal
// @Param la valeur en mV
// **********************************************
bool GestionINA3221::setWarningShuntAlertLimit(Channel channel, float valeur) {
	switch(channel) {
		case Channel_1: return !write16Swapped(Channel1WarningAlertLimit, (uint16_t)(valeur / _40MICROVOLT) << 3);
		case Channel_2: return !write16Swapped(Channel2WarningAlertLimit, (uint16_t)(valeur / _40MICROVOLT) << 3);
		case Channel_3: return !write16Swapped(Channel3WarningAlertLimit, (uint16_t)(valeur / _40MICROVOLT) << 3);
	}	
}

// *****************************************
// Donne la valeur shunt limite sur un canal
// @Param le canal
// @Return la valeur en mV
// *****************************************
float GestionINA3221::getCriticalShuntAlertLimit(Channel channel) {
	switch(channel) {
		case Channel_1: return ((read16Swapped(Channel1CriticalAlertLimit) >> 3)) * _40MICROVOLT;
		case Channel_2: return ((read16Swapped(Channel2CriticalAlertLimit) >> 3)) * _40MICROVOLT;
		case Channel_3: return ((read16Swapped(Channel3CriticalAlertLimit) >> 3)) * _40MICROVOLT;
	}
}

// *****************************************
// Donne la valeur shunt alarme sur un canal
// @Param le canal
// @Return la valeur en mV
// *****************************************
float GestionINA3221::getWarningShuntAlertLimit(Channel channel) {
	switch(channel) {
		case Channel_1: return ((read16Swapped(Channel1WarningAlertLimit) >> 3)) * _40MICROVOLT;
		case Channel_2: return ((read16Swapped(Channel2WarningAlertLimit) >> 3)) * _40MICROVOLT;
		case Channel_3: return ((read16Swapped(Channel3WarningAlertLimit) >> 3)) * _40MICROVOLT;
	}
}

// ******************************************
// Donne la somme des tensions sur les shunts
// @Return la somme des tensions en mV
// ******************************************
float GestionINA3221::getShuntVoltageSum_mV(void) {
	while(!isConversionOk());
	return ((read16Swapped(ShuntVoltageSum) >> 1)) * _40MICROVOLT;
}

// *********************************************************
// Positionne la valeur limite de tension sur tous les shunt
// @Param valeur en mV
// *********************************************************
bool GestionINA3221::setShuntVoltageSumLimit(float valeur) {
	return !write16Swapped(ShuntVoltageSumLimit, (uint16_t)(valeur / 0.04) << 1);
}

// ****************************************************
// Donne la valeur limite de tension sur tous les shunt
// @Return valeur en mV
// ****************************************************
float GestionINA3221::getShuntVoltageSumLimit(void) {
	return ((read16Swapped(ShuntVoltageSumLimit) >> 1)) * _40MICROVOLT;
}

// ******************************************
// Donne la somme des courants sur les shunts
// @Return La somme des courants en mA
// ******************************************
float GestionINA3221::getCurrentSum_mA(void) {
	return getShuntVoltageSum_mV() / ResistanceShunt;
}

// ***************************************************************
// Positionne les mask
// @Param Active le canal1 pour la sommation des tensions de shunt
// @Param Active le canal2 pour la sommation des tensions de shunt
// @Param Active le canal3 pour la sommation des tensions de shunt
// @Param Active la Pin de warning
// @Param Active la pin d'alerte critique
// ***************************************************************
bool GestionINA3221::setMaskEnable(SummationChannelControl1 summationChannelControl1, SummationChannelControl2 summationChannelControl2, 
			SummationChannelControl3 summationChannelControl3, WarningAlertLatchEnable warningAlertLatchEnable, 
			CriticalAlertLatchEnable criticalAlertLatchEnable) {
	return !write16Swapped(MaskEnable, summationChannelControl1 | summationChannelControl2 | summationChannelControl3 | warningAlertLatchEnable | criticalAlertLatchEnable);
}

// *************************************************************
// Le canal1 participe t'il à la sommation des tensions de shunt
// @Return true si oui, false si non
// *************************************************************
bool GestionINA3221::isSummationChannelControl1(void) {
	return read16Swapped(MaskEnable) & SummationChannelControl1On;	
}

// *************************************************************
// Le canal2 participe t'il à la sommation des tensions de shunt
// @Return true si oui, false si non
// *************************************************************
bool GestionINA3221::isSummationChannelControl2(void) {
	return read16Swapped(MaskEnable) & SummationChannelControl2On;		
}

// *************************************************************
// Le canal3 participe t'il à la sommation des tensions de shunt
// @Return true si oui, false si non
// *************************************************************
bool GestionINA3221::isSummationChannelControl3(void) {
	return read16Swapped(MaskEnable) & SummationChannelControl3On;	
}

// ******************************************
// Le WarningAlertLatchEnable est t'il actif
// @Return true si oui, false si non
// ******************************************
bool GestionINA3221::isWarningAlertLatchEnable(void) {
	return read16Swapped(MaskEnable) & WarningAlertLatchEnableOn;	
}

// ******************************************
// Le CriticalAlertLatchEnable est t'il actif
// @Return true si oui, false si non
// ******************************************
bool GestionINA3221::isCriticalAlertLatchEnable(void) {
	return read16Swapped(MaskEnable) & CriticalAlertLatchEnableOn;	
}

// ********************************************
// Le canal1 a t'il active le CriticalAlertFlag
// @Return true si oui, false si non
// ********************************************
bool GestionINA3221::isCriticalAlertFlagIndicator1(void) {
	return read16Swapped(MaskEnable) & CriticalAlertFlagIndicator1On;	
}

// ********************************************
// Le canal2 a t'il active le CriticalAlertFlag
// @Return true si oui, false si non
// ********************************************
bool GestionINA3221::isCriticalAlertFlagIndicator2(void) {
	return read16Swapped(MaskEnable) & CriticalAlertFlagIndicator2On;	
}

// ********************************************
// Le canal3 a t'il active le CriticalAlertFlag
// @Return true si oui, false si non
// ********************************************
bool GestionINA3221::isCriticalAlertFlagIndicator3(void) {
	return read16Swapped(MaskEnable) & CriticalAlertFlagIndicator3On;	
}

// ************************************
// Le SummationAlertFlag est t'il actif
// @Return true si oui, false si non
// ************************************
bool GestionINA3221::isSummationAlertFlag(void) {
	return read16Swapped(MaskEnable) & SummationAlertFlagOn;	
}

// *******************************************
// Le canal1 a t'il active le WarningAlertFlag
// @Return true si oui, false si non
// *******************************************
bool GestionINA3221::isWarningAlertFlagIndicator1(void) {
	return read16Swapped(MaskEnable) & WarningAlertFlagIndicator1On;	
}

// *******************************************
// Le canal2 a t'il active le WarningAlertFlag
// @Return true si oui, false si non
// *******************************************
bool GestionINA3221::isWarningAlertFlagIndicator2(void) {
	return read16Swapped(MaskEnable) & WarningAlertFlagIndicator2On;	
}

// *******************************************
// Le canal3 a t'il active le WarningAlertFlag
// @Return true si oui, false si non
// *******************************************
bool GestionINA3221::isWarningAlertFlagIndicator3(void) {
	return read16Swapped(MaskEnable) & WarningAlertFlagIndicator3On;	
}

// ************************************************************************************
// Lit le PowerValidAlertFlag
// @Return true si toutes les tensions de bus sont au dessus de la powerValidUpperLimit
//         false si une des tensions de bus est au dessous de la powerValidLowerLimit
// ************************************************************************************
bool GestionINA3221::isPowerValidAlertFlag(void) {
	return read16Swapped(MaskEnable) & PowerValidAlertFlagOn;	
}

// ****************************************
// Le TimingControlAlertFlag est t'il actif
// @Return false si ok, true si non
// ****************************************
bool GestionINA3221::isTimingControlAlertFlag(void) {
	return !(read16Swapped(MaskEnable) & TimingControlAlertFlagOn);	
}

// ******************************************
// La premiere conversion est t'elle en cours
// @Return true si oui, false si non
// ******************************************
bool GestionINA3221::isConversionOk(void) {
	return read16Swapped(MaskEnable) & ConversionWriting;	
}

// *************************************************************************************************
// Positionne la valeur de comparaison haute des tensions de bus pour activer le PowerValidAlertFlag
// @Param valeur de comparaison haute des tensions de bus
// *************************************************************************************************
bool GestionINA3221::setPowerValidUpperLimit(float valeur) {
	return !write16Swapped(PowerValidUpperLimit, (uint16_t)(valeur / _8MILLIVOLT) << 3);
}

// ******************************************************************************************************
// Positionne la valeur de comparaison basse de chaque tension de bus pour activer le PowerValidAlertFlag
// @Param valeur de comparaison basse des tensions de bus
// ******************************************************************************************************
bool GestionINA3221::setPowerValidLowerLimit(float valeur) {
	return !write16Swapped(PowerValidLowerLimit, (uint16_t)(valeur / _8MILLIVOLT) << 3);
}

// ************************************************************
// Donne la valeur de comparaison haute des tensions de bus
// @Return valeur de comparaison haute des tensions de bus en V
// ************************************************************
float GestionINA3221::getPowerValidUpperLimit(void) {
	return ((read16Swapped(PowerValidUpperLimit) >> 3)) * _8MILLIVOLT;
}

// ************************************************************
// Donne la valeur de comparaison basse des tensions de bus
// @Return valeur de comparaison basse des tensions de bus en V
// ************************************************************
float GestionINA3221::getPowerValidLowerLimit(void) {
	return ((read16Swapped(PowerValidLowerLimit) >> 3)) * _8MILLIVOLT;
}

// **********************************************************
// Donne le Manufacturer ID (TI pour Texas Instrument 0x5449)
// @Return le manufacturer ID
// **********************************************************
uint16_t GestionINA3221::getManufacturerID(void) {
	return read16Swapped(ManufacturerID);
}

// ***************************************
// Le Manufacturer ID est t'il TI (0x5449)
// @Return true si oui, false si non
// ***************************************
bool GestionINA3221::isManufacturerID(void) {
	return !(getManufacturerID() & ~TI);
}

// *********************************
// Donne l'ID de l'appareil (0x3220)
// @Return l'ID de l'appareil
// *********************************
uint16_t GestionINA3221::getDieID(void) {
	return read16Swapped(DieID);
}

// **********************************
// L'ID de l'appareil est t'il 0x3220
// @Return true si oui, false si non
// **********************************
bool GestionINA3221::isDieID(void) {
	return !(getDieID() & ~INA3221);
}

