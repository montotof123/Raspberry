/*
 * GestionCAP1203.cpp
 *
 * Created on 05/12/2020
 * Author Totof
 *
 */
 
#ifndef __GestionCAP1203_CPP__
#define __GestionCAP1203_CPP__

#include <stdint.h>
#include "GestionCAP1203Reg.h"
#include "GestionCAP1203.h"

#include "Logger.h"

#define ERROR -1

// ************
// Constructeur
// ************
GestionCAP1203::GestionCAP1203(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	InitCAP1203();
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// **************
// Initialisation
// **************
bool GestionCAP1203::InitCAP1203(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	initI2CPeripheric(I2C_ADDR);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return isInitialize();
}
		
// ********************************
// Donne le registre Main Control
// @Return le registre Main Control
// ********************************
uint8_t GestionCAP1203::getMainControl(void) {
	return genericRead8(REG_MAIN_CONTROL, __PRETTY_FUNCTION__);
}

// ******************************************
// Positionne le registre Main Control
// @Param le contenu du registre Main Control
// @Return true si ok, false si erreur
// ******************************************
bool GestionCAP1203::setMainControl(uint8_t pValue) {
	return genericWrite8(REG_MAIN_CONTROL, pValue,__PRETTY_FUNCTION__);
}

// ************************************
// Demande si le circuit est en standby 
// @Return true si oui, false si non
// ************************************
bool GestionCAP1203::isMainControlStby(void) {
	return genericRead8(REG_MAIN_CONTROL, __PRETTY_FUNCTION__) & (uint8_t)MAIN_CONTROL_STBY;
}

// ***********************************
// Positionne le circuit en standby 
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setMainControlStby(void) {
	return genericWrite8(REG_MAIN_CONTROL, genericRead8(MAIN_CONTROL_STBY, __PRETTY_FUNCTION__) | MAIN_CONTROL_STBY, __PRETTY_FUNCTION__);
}

// ***********************************
// Sort le circuit du standby 
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetMainControlStby(void) {
	return genericWrite8(REG_MAIN_CONTROL, genericRead8(MAIN_CONTROL_STBY, __PRETTY_FUNCTION__) & ~MAIN_CONTROL_STBY, __PRETTY_FUNCTION__);
}

// **************************************
// Demande si le circuit est en deepsleep 
// @Return true si oui, false si non
// **************************************
bool GestionCAP1203::isMainControlDSleep(void) {
	return genericRead8(REG_MAIN_CONTROL, __PRETTY_FUNCTION__) & (uint8_t)MAIN_CONTROL_DSLEEP;
}

// ***********************************
// Positionne le circuit en deepsleep 
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setMainControlDSleep(void) {
	return genericWrite8(REG_MAIN_CONTROL, genericRead8(MAIN_CONTROL_DSLEEP, __PRETTY_FUNCTION__) | MAIN_CONTROL_DSLEEP, __PRETTY_FUNCTION__);
}

// ***********************************
// Sort le circuit du deepsleep 
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetMainControlDSleep(void) {
	return genericWrite8(REG_MAIN_CONTROL, genericRead8(MAIN_CONTROL_DSLEEP, __PRETTY_FUNCTION__) & ~MAIN_CONTROL_DSLEEP, __PRETTY_FUNCTION__);
}

// **********************************
// Demande si il y a une interruption  
// @Return true si oui, false si non
// **********************************
bool GestionCAP1203::isMainControlInt(void) {
	return genericRead8(REG_MAIN_CONTROL, __PRETTY_FUNCTION__) & (uint8_t)MAIN_CONTROL_INT;
}

// ***********************************
// Clear l'interruption 
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetMainControlInt(void) {
	return genericWrite8(REG_MAIN_CONTROL, genericRead8(MAIN_CONTROL_INT, __PRETTY_FUNCTION__) & ~MAIN_CONTROL_INT, __PRETTY_FUNCTION__);
}

// **********************************
// Donne le registre General Statut
// @Return le registre General Statut
// **********************************
uint8_t GestionCAP1203::getGeneralStatut(void) {
	return genericRead8(REG_GENERAL_STATUS, __PRETTY_FUNCTION__);
}

// ************************************************************************
// Demande si l'un des compteurs des touches est out of limit 
// Lire le registre REG_BASE_COUNT_OUT pour connaitre les touches en erreur
// @Return true si oui, false si non
// ************************************************************************
bool GestionCAP1203::isGeneralStatutBcOut(void) {
	return genericRead8(REG_GENERAL_STATUS, __PRETTY_FUNCTION__) & (uint8_t)GENERAL_STATUS_BC_OUT;
}

// *****************************************************************************************
// Demande si l'une des calibrations des touches est failed 
// Lire le registre REG_CALIBRATION_ACTIVATE_AND_STATUS pour connaitre les touches en erreur
// @Return true si oui, false si non
// *****************************************************************************************
bool GestionCAP1203::isGeneralStatutAcalFail(void) {
	return genericRead8(REG_GENERAL_STATUS, __PRETTY_FUNCTION__) & (uint8_t)GENERAL_STATUS_ACAIL_FAIL;
}

// ***************************************************
// Demande si la touche PWR a été activé 
// Touche programmée dans le registre REG_POWER_BUTTON
// @Return true si oui, false si non
// ***************************************************
bool GestionCAP1203::isGeneralStatutPwr(void) {
	return genericRead8(REG_GENERAL_STATUS, __PRETTY_FUNCTION__) & (uint8_t)GENERAL_STATUS_PWR;
}

// ************************************************************
// Demande si l'appui sur des touches multiples est détecté  
// Touche programmée dans le registre REG_MULTIPLE_TOUCH_CONFIG
// @Return true si oui, false si non
// ************************************************************
bool GestionCAP1203::isGeneralStatutMult(void) {
	return genericRead8(REG_GENERAL_STATUS, __PRETTY_FUNCTION__) & (uint8_t)GENERAL_STATUS_MULT;
}

// **********************************************************************
// Demande si le seuil pour la détection des touches multiple est dépassé 
// Seuil programmé dans le registre REG_MULTIPLE_TOUCH_PATTERN_CONFIG
// @Return true si oui, false si non
// **********************************************************************
bool GestionCAP1203::isGeneralStatutMtp(void) {
	return genericRead8(REG_GENERAL_STATUS, __PRETTY_FUNCTION__) & (uint8_t)GENERAL_STATUS_MTP;
}

// *****************************************************************
// Demande si une touche est activée 
// Lire le registre REG_SENSOR_INPUT_STATUS pour connaitre la touche 
// @Return true si oui, false si non
// *****************************************************************
bool GestionCAP1203::isGeneralStatutTouch(void) {
	return genericRead8(REG_GENERAL_STATUS, __PRETTY_FUNCTION__) & (uint8_t)GENERAL_STATUS_TOUCH;
}

// ***************************************
// Donne le registre Sensor Input Statut
// @Return le registre Sensor Input Statut
// ***************************************
uint8_t GestionCAP1203::getGeneralInputStatut(void) {
	return genericRead8(REG_SENSOR_INPUT_STATUS, __PRETTY_FUNCTION__);
}

// **********************************
// Demande si la touche 3 est activée 
// @Return true si oui, false si non
// **********************************
bool GestionCAP1203::isGeneralInputStatutCs3(void) {
	return genericRead8(REG_SENSOR_INPUT_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// **********************************
// Demande si la touche 2 est activée 
// @Return true si oui, false si non
// **********************************
bool GestionCAP1203::isGeneralInputStatutCs2(void) {
	return genericRead8(REG_SENSOR_INPUT_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// **********************************
// Demande si la touche 1 est activée 
// @Return true si oui, false si non
// **********************************
bool GestionCAP1203::isGeneralInputStatutCs1(void) {
	return genericRead8(REG_SENSOR_INPUT_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// *************************************
// Donne le registre Noise Flag Statut
// @Return le registre Noise Flag Statut
// *************************************
uint8_t GestionCAP1203::getNoiseFlagStatus(void) {
	return genericRead8(REG_NOISE_FLAG_STATUS, __PRETTY_FUNCTION__);
}

// **************************************************************
// Demande si la touche 3 est bruités et qu'elle est inutilisable
// Paramétré par les registres REG_CONFIG et REG_CONFIG2
// @Return true si oui, false si non
// ************************************************************** 
bool GestionCAP1203::isNoiseFlagStatutCs3(void) {
	return genericRead8(REG_NOISE_FLAG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// **************************************************************
// Demande si la touche 2 est bruités et qu'elle est inutilisable
// Paramétré par les registres REG_CONFIG et REG_CONFIG2
// @Return true si oui, false si non
// ************************************************************** 
bool GestionCAP1203::isNoiseFlagStatutCs2(void) {
	return genericRead8(REG_NOISE_FLAG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// **************************************************************
// Demande si la touche 1 est bruités et qu'elle est inutilisable
// Paramétré par les registres REG_CONFIG et REG_CONFIG2
// @Return true si oui, false si non
// ************************************************************** 
bool GestionCAP1203::isNoiseFlagStatutCs1(void) {
	return genericRead8(REG_NOISE_FLAG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// ***********************************************
// Donne le delta du compteur par rapport au seuil
// @Return le registre Sensor Input 1 delta count
// ***********************************************
uint8_t GestionCAP1203::getSensorInput1DeltaCount(void) {
	return genericRead8(REG_SENSOR_INPUT_1_DELTA_COUNT, __PRETTY_FUNCTION__);
}

// ***********************************************
// Donne le delta du compteur par rapport au seuil
// @Return le registre Sensor Input 2 delta count
// ***********************************************
uint8_t GestionCAP1203::getSensorInput2DeltaCount(void) {
	return genericRead8(REG_SENSOR_INPUT_2_DELTA_COUNT, __PRETTY_FUNCTION__);
}

// ***********************************************
// Donne le delta du compteur par rapport au seuil
// @Return le registre Sensor Input 3 delta count
// ***********************************************
uint8_t GestionCAP1203::getSensorInput3DeltaCount(void) {
	return genericRead8(REG_SENSOR_INPUT_3_DELTA_COUNT, __PRETTY_FUNCTION__);
}

// **********************************
// Donne la sensibilité des touches
// @Return la sensibilité des touches
// **********************************
GestionCAP1203::DeltaSense GestionCAP1203::getSensibilityControlDeltaSense(void) {
	switch(genericRead8(REG_SENSITIVITY_CONTROL, __PRETTY_FUNCTION__) & SENSITIVITY_CONTROL_DELTA_SENSE_FILTER) {
		case SENSITIVITY_CONTROL_DELTA_SENSE_128X: return SENSITIVITY_CONTROL_DELTA_SENSE_128X; break;
		case SENSITIVITY_CONTROL_DELTA_SENSE_64X:  return SENSITIVITY_CONTROL_DELTA_SENSE_64X;  break;
		case SENSITIVITY_CONTROL_DELTA_SENSE_32X:  return SENSITIVITY_CONTROL_DELTA_SENSE_32X;  break;
		case SENSITIVITY_CONTROL_DELTA_SENSE_16X:  return SENSITIVITY_CONTROL_DELTA_SENSE_16X;  break;
		case SENSITIVITY_CONTROL_DELTA_SENSE_8X:   return SENSITIVITY_CONTROL_DELTA_SENSE_8X;   break;
		case SENSITIVITY_CONTROL_DELTA_SENSE_4X:   return SENSITIVITY_CONTROL_DELTA_SENSE_4X;   break;
		case SENSITIVITY_CONTROL_DELTA_SENSE_2X:   return SENSITIVITY_CONTROL_DELTA_SENSE_2X;   break;
		case SENSITIVITY_CONTROL_DELTA_SENSE_1X:   return SENSITIVITY_CONTROL_DELTA_SENSE_1X;   break;
	}
	return SENSITIVITY_CONTROL_DELTA_SENSE_ERROR;	
}

// **************************************************
// Donne l'échelle de la présentation des compteurs
// Ne doit normalement pas être modifié
// @Return l'échelle de la présentation des compteurs
// **************************************************
GestionCAP1203::BaseShift GestionCAP1203::getSensibilityControlBaseShift(void) {
	switch(genericRead8(REG_SENSITIVITY_CONTROL, __PRETTY_FUNCTION__) & SENSITIVITY_CONTROL_BASE_SHIFT_FILTER) {
		case SENSITIVITY_CONTROL_BASE_SHIFT_1X:   return SENSITIVITY_CONTROL_BASE_SHIFT_1X;   break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_2X:   return SENSITIVITY_CONTROL_BASE_SHIFT_2X;   break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_4X:   return SENSITIVITY_CONTROL_BASE_SHIFT_4X;   break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_8X:   return SENSITIVITY_CONTROL_BASE_SHIFT_8X;   break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_16X:  return SENSITIVITY_CONTROL_BASE_SHIFT_16X;  break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_32X:  return SENSITIVITY_CONTROL_BASE_SHIFT_32X;  break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_64X:  return SENSITIVITY_CONTROL_BASE_SHIFT_64X;  break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_128X: return SENSITIVITY_CONTROL_BASE_SHIFT_128X; break;
		case SENSITIVITY_CONTROL_BASE_SHIFT_256X: return SENSITIVITY_CONTROL_BASE_SHIFT_256X; break;
	}
	return SENSITIVITY_CONTROL_BASE_SHIFT_ERROR;	
}

// *************************************************
// Positionne le registre Sensibility Control
// @Param le DeltaSense
// @Param le BaseShift
// Le BaseShift ne doit normalement pas être modifié
// @Return true si ok, false si erreur
// *************************************************
bool GestionCAP1203::setSensibilityControl(DeltaSense pDelta, BaseShift pBase) {
		return genericWrite8(REG_SENSITIVITY_CONTROL, pDelta | pBase, __PRETTY_FUNCTION__);
}

// ************************
// Donne la configuration
// @Return la configuration
// ************************
uint8_t GestionCAP1203::getConfiguration(void) {
	return genericRead8(REG_CONFIG, __PRETTY_FUNCTION__);
}

// ***********************************
// Positionne la configuration
// @Param la configuration
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setConfiguration(uint8_t pValue) {
	return genericWrite8(REG_CONFIG, pValue,__PRETTY_FUNCTION__);
}

// *************************************
// Demande si le timeout I2C est activée 
// @Return true si oui, false si non
// *************************************
bool GestionCAP1203::isConfigurationTimeOut(void) {
	return genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)CONFIG_TIMEOUT;
}

// ***********************************
// Active le timeout I2C
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setConfigurationTimeOut(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) | CONFIG_TIMEOUT, __PRETTY_FUNCTION__);
}

// ***********************************
// Désactive le timeout I2C
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetConfigurationTimeOut(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & ~CONFIG_TIMEOUT, __PRETTY_FUNCTION__);
}

// ***************************************************
// Demande si le seuil de bruit digital est activé 
// @Return true si non, false si oui (sortie inversée)
// ***************************************************
bool GestionCAP1203::isConfigurationDisDigNoise(void) {
	return genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)CONFIG_DIS_DIG_NOISE;
}

// ***************************************************
// Désactive le seuil de bruit digital (actif à 0)
// @Return true si ok, false si erreur
// ***************************************************
bool GestionCAP1203::setConfigurationDisDigNoise(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) | CONFIG_DIS_DIG_NOISE, __PRETTY_FUNCTION__);
}

// ********************************************
// Active le seuil de bruit digital (actif à 0)
// @Return true si ok, false si erreur
// ********************************************
bool GestionCAP1203::unSetConfigurationDisDigNoise(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & ~CONFIG_DIS_DIG_NOISE, __PRETTY_FUNCTION__);
}

// ***************************************************************
// Demande si le filtre de bruit analogique est activé (actif à 0) 
// @Return true si non, false si oui (sortie inversée)
// ***************************************************************
bool GestionCAP1203::isConfigurationDisAnaNoise(void) {
	return genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)CONFIG_DIS_ANA_NOISE;
}

// ***************************************************
// Désactive le filtre de bruit analogique (actif à 0)
// @Return true si ok, false si erreur
// ***************************************************
bool GestionCAP1203::setConfigurationDisAnaNoise(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) | CONFIG_DIS_ANA_NOISE, __PRETTY_FUNCTION__);
}

// ************************************************
// Active le filtre de bruit analogique (actif à 0)
// @Return true si ok, false si erreur
// ************************************************
bool GestionCAP1203::unSetConfigurationDisAnaNoise(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & ~CONFIG_DIS_ANA_NOISE, __PRETTY_FUNCTION__);
}

// *********************************************************************************************************************************
// Demande si la recalibration d'une touche est active si elle est touchée plus longtemps que défini dans le REG_SENSOR_INPUT_CONFIG
// @Return true si non, false si oui (sortie inversée)
// *********************************************************************************************************************************
bool GestionCAP1203::isConfigurationMaxDurEn(void) {
	return genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)CONFIG_MAX_DUR_EN;
}

// ******************************************************************************************************************
// Active la recalibration d'une touche si elle est touchée plus longtemps que défini dans le REG_SENSOR_INPUT_CONFIG
// @Return true si non, false si oui (sortie inversée)
// ******************************************************************************************************************
bool GestionCAP1203::setConfigurationMaxDurEn(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) | CONFIG_MAX_DUR_EN, __PRETTY_FUNCTION__);
}

// *********************************************************************************************************************
// Désactive la recalibration d'une touche si elle est touchée plus longtemps que défini dans le REG_SENSOR_INPUT_CONFIG
// @Return true si non, false si oui (sortie inversée)
// *********************************************************************************************************************
bool GestionCAP1203::unSetConfigurationMaxDurEn(void) {
	return genericWrite8(REG_CONFIG, genericRead8(REG_CONFIG, __PRETTY_FUNCTION__) & ~CONFIG_MAX_DUR_EN, __PRETTY_FUNCTION__);
}

// ***************************
// Donne les touches actives
// @Return les touches actives
// ***************************
uint8_t GestionCAP1203::getSensorInputEnable(void) {
	return genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__);
}

// ***********************************
// Positionne les touches actives
// @Param les touches actives
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputEnable(TouchCS1 pCs1, TouchCS2 pCs2, TouchCS3 pCs3) {
	return genericWrite8(REG_SENSOR_INPUT_ENABLE, pCs1 | pCs2 | pCs3,__PRETTY_FUNCTION__);
}

// *********************************
// Demande si la touche 3 est active
// @Return true si oui, false si non
// *********************************
bool GestionCAP1203::isSensorInputEnableCs3(void) {
	return genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// ***********************************
// Active la touche 3
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputEnableCs3(void) {
	return genericWrite8(REG_SENSOR_INPUT_ENABLE, genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) | CS3, __PRETTY_FUNCTION__);
}

// ***********************************
// Désactive la touche 3
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetSensorInputEnableCs3(void) {
	return genericWrite8(REG_SENSOR_INPUT_ENABLE, genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) & ~CS3, __PRETTY_FUNCTION__);
}

// *********************************
// Demande si la touche 2 est active
// @Return true si oui, false si non
// *********************************
bool GestionCAP1203::isSensorInputEnableCs2(void) {
	return genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// ***********************************
// Active la touche 2
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputEnableCs2(void) {
	return genericWrite8(REG_SENSOR_INPUT_ENABLE, genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) | CS2, __PRETTY_FUNCTION__);
}

// ***********************************
// Désactive la touche 2
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetSensorInputEnableCs2(void) {
	return genericWrite8(REG_SENSOR_INPUT_ENABLE, genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) & ~CS2, __PRETTY_FUNCTION__);
}

// *********************************
// Demande si la touche 1 est active
// @Return true si oui, false si non
// *********************************
bool GestionCAP1203::isSensorInputEnableCs1(void) {
	return genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// ***********************************
// Active la touche 1
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputEnableCs1(void) {
	return genericWrite8(REG_SENSOR_INPUT_ENABLE, genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) | CS1, __PRETTY_FUNCTION__);
}

// ***********************************
// Désactive la touche 1
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetSensorInputEnableCs1(void) {
	return genericWrite8(REG_SENSOR_INPUT_ENABLE, genericRead8(REG_SENSOR_INPUT_ENABLE, __PRETTY_FUNCTION__) & ~CS1, __PRETTY_FUNCTION__);
}

// *********************************************************************************
// Donne la durée pendant laquelle une touche peut être touché avant recalibration
// @Return la durée pendant laquelle une touche peut être touché avant recalibration
// *********************************************************************************
GestionCAP1203::MaxDur GestionCAP1203::getSensorInputConfigMaxDur(void) {
	switch(genericRead8(REG_SENSOR_INPUT_CONFIG, __PRETTY_FUNCTION__) & SENSOR_INPUT_MAX_DUR_FILTER) {
		case SENSOR_INPUT_MAX_DUR_560MS:   return SENSOR_INPUT_MAX_DUR_560MS;   break;
		case SENSOR_INPUT_MAX_DUR_840MS:   return SENSOR_INPUT_MAX_DUR_840MS;   break;
		case SENSOR_INPUT_MAX_DUR_1120MS:  return SENSOR_INPUT_MAX_DUR_1120MS;  break;
		case SENSOR_INPUT_MAX_DUR_1400MS:  return SENSOR_INPUT_MAX_DUR_1400MS;  break;
		case SENSOR_INPUT_MAX_DUR_1680MS:  return SENSOR_INPUT_MAX_DUR_1680MS;  break;
		case SENSOR_INPUT_MAX_DUR_2240MS:  return SENSOR_INPUT_MAX_DUR_2240MS;  break;
		case SENSOR_INPUT_MAX_DUR_2800MS:  return SENSOR_INPUT_MAX_DUR_2800MS;  break;
		case SENSOR_INPUT_MAX_DUR_3360MS:  return SENSOR_INPUT_MAX_DUR_3360MS;  break;
		case SENSOR_INPUT_MAX_DUR_3920MS:  return SENSOR_INPUT_MAX_DUR_3920MS;  break;
		case SENSOR_INPUT_MAX_DUR_4480MS:  return SENSOR_INPUT_MAX_DUR_4480MS;  break;
		case SENSOR_INPUT_MAX_DUR_5600MS:  return SENSOR_INPUT_MAX_DUR_5600MS;  break;
		case SENSOR_INPUT_MAX_DUR_6720MS:  return SENSOR_INPUT_MAX_DUR_6720MS;  break;
		case SENSOR_INPUT_MAX_DUR_7840MS:  return SENSOR_INPUT_MAX_DUR_7840MS;  break;
		case SENSOR_INPUT_MAX_DUR_8906MS:  return SENSOR_INPUT_MAX_DUR_8906MS;  break;
		case SENSOR_INPUT_MAX_DUR_10080MS: return SENSOR_INPUT_MAX_DUR_10080MS; break;
		case SENSOR_INPUT_MAX_DUR_11200MS: return SENSOR_INPUT_MAX_DUR_11200MS; break;
	}
	return SENSOR_INPUT_MAX_DUR_ERROR;	
}

// ***************************************************************************************
// Donne la durée de répétition de l'interruption lord de l'appui prolongé sur une touche
// @Return la durée de répétition d l'interruption lord de l'appui prolongé sur une touche
// ***************************************************************************************
GestionCAP1203::RptRate GestionCAP1203::getSensorInputConfigRptRate(void) {
	switch(genericRead8(REG_SENSOR_INPUT_CONFIG, __PRETTY_FUNCTION__) & SENSOR_INPUT_RPT_RATE_FILTER) {
		case SENSOR_INPUT_RPT_RATE_35MS:  return SENSOR_INPUT_RPT_RATE_35MS;  break;
		case SENSOR_INPUT_RPT_RATE_70MS:  return SENSOR_INPUT_RPT_RATE_70MS;  break;
		case SENSOR_INPUT_RPT_RATE_105MS: return SENSOR_INPUT_RPT_RATE_105MS; break;
		case SENSOR_INPUT_RPT_RATE_140MS: return SENSOR_INPUT_RPT_RATE_140MS; break;
		case SENSOR_INPUT_RPT_RATE_175MS: return SENSOR_INPUT_RPT_RATE_175MS; break;
		case SENSOR_INPUT_RPT_RATE_210MS: return SENSOR_INPUT_RPT_RATE_210MS; break;
		case SENSOR_INPUT_RPT_RATE_245MS: return SENSOR_INPUT_RPT_RATE_245MS; break;
		case SENSOR_INPUT_RPT_RATE_280MS: return SENSOR_INPUT_RPT_RATE_280MS; break;
		case SENSOR_INPUT_RPT_RATE_315MS: return SENSOR_INPUT_RPT_RATE_315MS; break;
		case SENSOR_INPUT_RPT_RATE_350MS: return SENSOR_INPUT_RPT_RATE_350MS; break;
		case SENSOR_INPUT_RPT_RATE_385MS: return SENSOR_INPUT_RPT_RATE_385MS; break;
		case SENSOR_INPUT_RPT_RATE_420MS: return SENSOR_INPUT_RPT_RATE_420MS; break;
		case SENSOR_INPUT_RPT_RATE_455MS: return SENSOR_INPUT_RPT_RATE_455MS; break;
		case SENSOR_INPUT_RPT_RATE_490MS: return SENSOR_INPUT_RPT_RATE_490MS; break;
		case SENSOR_INPUT_RPT_RATE_525MS: return SENSOR_INPUT_RPT_RATE_525MS; break;
		case SENSOR_INPUT_RPT_RATE_560MS: return SENSOR_INPUT_RPT_RATE_560MS; break;
	}
	return SENSOR_INPUT_RPT_RATE_ERROR;	
}

// ***************************************************************************************
// Positionne la durée pendant laquelle une touche peut être touché avant recalibration et 
//  la durée de répétition de l'interruption lord de l'appui prolongé sur une touche
// @Param durée pendant laquelle une touche peut être touché avant recalibration et 
// @Param durée de répétition d l'interruption lord de l'appui prolongé sur une touche
// @Return true si ok, false si erreur
// ***************************************************************************************
bool GestionCAP1203::setSensorInputConfig(MaxDur pMaxDur, RptRate pRptRate) {
	return genericWrite8(REG_SENSOR_INPUT_CONFIG, pMaxDur | pRptRate, __PRETTY_FUNCTION__);
}

// ********************************
// Donne la durée avant le repeat
// @Return la durée avant le repeat
// ********************************
GestionCAP1203::MPress GestionCAP1203::getSensorInputConfigMPress(void) {
	switch(genericRead8(REG_SENSOR_INPUT_CONFIG_2, __PRETTY_FUNCTION__) & SENSOR_INPUT_M_PRESS_FILTER) {
		case SENSOR_INPUT_M_PRESS_35MS:  return SENSOR_INPUT_M_PRESS_35MS;  break;
		case SENSOR_INPUT_M_PRESS_70MS:  return SENSOR_INPUT_M_PRESS_70MS;  break;
		case SENSOR_INPUT_M_PRESS_105MS: return SENSOR_INPUT_M_PRESS_105MS; break;
		case SENSOR_INPUT_M_PRESS_140MS: return SENSOR_INPUT_M_PRESS_140MS; break;
		case SENSOR_INPUT_M_PRESS_175MS: return SENSOR_INPUT_M_PRESS_175MS; break;
		case SENSOR_INPUT_M_PRESS_210MS: return SENSOR_INPUT_M_PRESS_210MS; break;
		case SENSOR_INPUT_M_PRESS_245MS: return SENSOR_INPUT_M_PRESS_245MS; break;
		case SENSOR_INPUT_M_PRESS_280MS: return SENSOR_INPUT_M_PRESS_280MS; break;
		case SENSOR_INPUT_M_PRESS_315MS: return SENSOR_INPUT_M_PRESS_315MS; break;
		case SENSOR_INPUT_M_PRESS_350MS: return SENSOR_INPUT_M_PRESS_350MS; break;
		case SENSOR_INPUT_M_PRESS_385MS: return SENSOR_INPUT_M_PRESS_385MS; break;
		case SENSOR_INPUT_M_PRESS_420MS: return SENSOR_INPUT_M_PRESS_420MS; break;
		case SENSOR_INPUT_M_PRESS_455MS: return SENSOR_INPUT_M_PRESS_455MS; break;
		case SENSOR_INPUT_M_PRESS_490MS: return SENSOR_INPUT_M_PRESS_490MS; break;
		case SENSOR_INPUT_M_PRESS_525MS: return SENSOR_INPUT_M_PRESS_525MS; break;
		case SENSOR_INPUT_M_PRESS_560MS: return SENSOR_INPUT_M_PRESS_560MS; break;
	}
	return SENSOR_INPUT_M_PRESS_ERROR;	
}

// ***********************************
// Positionne la durée avant le repeat
// @Param la durée avant le repeat
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputConfig(MPress pMpress) {
	return genericWrite8(REG_SENSOR_INPUT_CONFIG_2, pMpress, __PRETTY_FUNCTION__);
}

// *****************************************************
// Donne le nombre d'échantillon par touche par mesure
// @Return le nombre d'échantillon par touche par mesure
// *****************************************************
GestionCAP1203::Avg GestionCAP1203::getAverageAndSamplingAvg(void) {
	switch(genericRead8(REG_AVERAGING_AND_SAMPLE_CONFIG, __PRETTY_FUNCTION__) & AVG_AND_SAMPLING_AVG_FILTER) {
		case AVG_AND_SAMPLING_AVG_1:   return AVG_AND_SAMPLING_AVG_1;   break;
		case AVG_AND_SAMPLING_AVG_2:   return AVG_AND_SAMPLING_AVG_2;   break;
		case AVG_AND_SAMPLING_AVG_4:   return AVG_AND_SAMPLING_AVG_4;   break;
		case AVG_AND_SAMPLING_AVG_8:   return AVG_AND_SAMPLING_AVG_8;   break;
		case AVG_AND_SAMPLING_AVG_16:  return AVG_AND_SAMPLING_AVG_16;  break;
		case AVG_AND_SAMPLING_AVG_32:  return AVG_AND_SAMPLING_AVG_32;  break;
		case AVG_AND_SAMPLING_AVG_64:  return AVG_AND_SAMPLING_AVG_64;  break;
		case AVG_AND_SAMPLING_AVG_128: return AVG_AND_SAMPLING_AVG_128; break;
	}
	return AVG_AND_SAMPLING_AVG_ERROR;	
}

// ********************************
// Donne le temps par échantillon
// @Return le temps par échantillon
// ********************************
GestionCAP1203::SampTime GestionCAP1203::getAverageAndSamplingSampTime(void) {
	switch(genericRead8(REG_AVERAGING_AND_SAMPLE_CONFIG, __PRETTY_FUNCTION__) & AVG_AND_SAMPLING_SAMP_TIME_FILTER) {
		case AVG_AND_SAMPLING_SAMP_TIME_320US:  return AVG_AND_SAMPLING_SAMP_TIME_320US;  break;
		case AVG_AND_SAMPLING_SAMP_TIME_640US:  return AVG_AND_SAMPLING_SAMP_TIME_640US;  break;
		case AVG_AND_SAMPLING_SAMP_TIME_1280US: return AVG_AND_SAMPLING_SAMP_TIME_1280US; break;
		case AVG_AND_SAMPLING_SAMP_TIME_2560US: return AVG_AND_SAMPLING_SAMP_TIME_2560US; break;
	}
	return AVG_AND_SAMPLING_SAMP_TIME_ERROR;	
}

// ****************************************
// Donne le cycle des mesures des touches
// @Return le cycle des mesures des touches
// ****************************************
GestionCAP1203::CycleTime GestionCAP1203::getAverageAndSamplingCycleTime(void) {
	switch(genericRead8(REG_AVERAGING_AND_SAMPLE_CONFIG, __PRETTY_FUNCTION__) & AVG_AND_SAMPLING_CYCLE_TIME_FILTER) {
		case AVG_AND_SAMPLING_CYCLE_TIME_35MS:  return AVG_AND_SAMPLING_CYCLE_TIME_35MS;  break;
		case AVG_AND_SAMPLING_CYCLE_TIME_70MS:  return AVG_AND_SAMPLING_CYCLE_TIME_70MS;  break;
		case AVG_AND_SAMPLING_CYCLE_TIME_105MS: return AVG_AND_SAMPLING_CYCLE_TIME_105MS; break;
		case AVG_AND_SAMPLING_CYCLE_TIME_140MS: return AVG_AND_SAMPLING_CYCLE_TIME_140MS; break;
	}
	return AVG_AND_SAMPLING_CYCLE_TIME_ERROR;	
}

// ********************************************************
// Postionne le nombre d'échantillon par touche par mesure,
//  le temps par échantillon,
//  le cycle des mesures des touches
// @Param le nombre d'échantillon par touche par mesure
// @Param le temps par échantillon
// @Param le cycle des mesures des touches
// @Return true si ok, false si erreur
// ********************************************************

bool GestionCAP1203::setAverageAndSampling(Avg pAvg, SampTime pSampTime, CycleTime pCycleTime) {
	return genericWrite8(REG_AVERAGING_AND_SAMPLE_CONFIG, pAvg | pSampTime | pCycleTime, __PRETTY_FUNCTION__);
}

// ************************************************************************
// Donne le registre indiquant si la calibration des touches est correcte 
// (Correcte si à 0)
// @Return le registre indiquant si la calibration des touches est correcte
// ************************************************************************
uint8_t GestionCAP1203::getCalibrationActivateAndStatus(void) {
	return genericRead8(REG_CALIBRATION_ACTIVATE_AND_STATUS, __PRETTY_FUNCTION__);
}

// ******************************************************************
// Positionne les touches à recalibrer (1 pour calibrer 0 sans effet)
// @Param touche1
// @Param touche2
// @Param touche3
// @Return true si ok, false si erreur
// ******************************************************************
bool GestionCAP1203::setCalibrationActivateAndStatus(TouchCS1 pCs1, TouchCS2 pCs2, TouchCS3 pCs3) {
	return genericWrite8(REG_CALIBRATION_ACTIVATE_AND_STATUS, pCs1 | pCs2 | pCs3,__PRETTY_FUNCTION__);
}

// *****************************************************
// Demande si la calibration de la touche 3 est correcte
// 0 calibration ok
// @Return true si non, false si oui
// *****************************************************
bool GestionCAP1203::isCalibrationActivateAndStatusCs3(void) {
	return genericRead8(REG_CALIBRATION_ACTIVATE_AND_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// ***********************************
// Force la calibration de la touche 3
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setCalibrationActivateAndStatusCs3(void) {
	return genericWrite8(REG_CALIBRATION_ACTIVATE_AND_STATUS, genericRead8(REG_CALIBRATION_ACTIVATE_AND_STATUS, __PRETTY_FUNCTION__) | CS3, __PRETTY_FUNCTION__);
}

// *****************************************************
// Demande si la calibration de la touche 2 est correcte
// 0 calibration ok
// @Return true si non, false si oui
// *****************************************************
bool GestionCAP1203::isCalibrationActivateAndStatusCs2(void) {
	return genericRead8(REG_CALIBRATION_ACTIVATE_AND_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// ***********************************
// Force la calibration de la touche 2
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setCalibrationActivateAndStatusCs2(void) {
	return genericWrite8(REG_CALIBRATION_ACTIVATE_AND_STATUS, genericRead8(REG_CALIBRATION_ACTIVATE_AND_STATUS, __PRETTY_FUNCTION__) | CS2, __PRETTY_FUNCTION__);
}

// *****************************************************
// Demande si la calibration de la touche 1 est correcte
// 0 calibration ok
// @Return true si non, false si oui
// *****************************************************
bool GestionCAP1203::isCalibrationActivateAndStatusCs1(void) {
	return genericRead8(REG_CALIBRATION_ACTIVATE_AND_STATUS, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// ***********************************
// Force la calibration de la touche 1
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setCalibrationActivateAndStatusCs1(void) {
	return genericWrite8(REG_CALIBRATION_ACTIVATE_AND_STATUS, genericRead8(REG_CALIBRATION_ACTIVATE_AND_STATUS, __PRETTY_FUNCTION__) | CS1, __PRETTY_FUNCTION__);
}


// ***********************************************************************
// Donne le registre indiquant si les touches déclenchent une interruption 
// @Return le registre indiquant si les touches déclenche une interruption
// ***********************************************************************
uint8_t GestionCAP1203::getInterruptEnable(void) {
	return genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__);
}

// ****************************************************
// Positionne les touches déclenchants une interruption
// @Param touche1
// @Param touche2
// @Param touche3
// @Return true si ok, false si erreur
// ****************************************************
bool GestionCAP1203::setInterruptEnable(TouchCS1 pCs1, TouchCS2 pCs2, TouchCS3 pCs3) {
	return genericWrite8(REG_INTERRUPT_ENABLE, pCs1 | pCs2 | pCs3,__PRETTY_FUNCTION__);
}

// *************************************************
// Demande si la touche 3 déclenche une interruption
// @Return true si oui, false si non
// *************************************************
bool GestionCAP1203::isInterruptEnableCs3(void) {
	return genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// ***********************************************************
// Active le déclenchement d'une interruption avec la touche 3
// @Return true si ok, false si erreur
// ***********************************************************
bool GestionCAP1203::setInterruptEnableCs3(void) {
	return genericWrite8(REG_INTERRUPT_ENABLE, genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) | CS3, __PRETTY_FUNCTION__);
}

// **************************************************************
// Désactive le déclenchement d'une interruption avec la touche 3
// @Return true si ok, false si erreur
// **************************************************************
bool GestionCAP1203::unSetInterruptEnableCs3(void) {
	return genericWrite8(REG_INTERRUPT_ENABLE, genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) & ~CS3, __PRETTY_FUNCTION__);
}

// *************************************************
// Demande si la touche 2 déclenche une interruption
// @Return true si oui, false si non
// *************************************************
bool GestionCAP1203::isInterruptEnableCs2(void) {
	return genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// ***********************************************************
// Active le déclenchement d'une interruption avec la touche 2
// @Return true si ok, false si erreur
// ***********************************************************
bool GestionCAP1203::setInterruptEnableCs2(void) {
	return genericWrite8(REG_INTERRUPT_ENABLE, genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) | CS2, __PRETTY_FUNCTION__);
}

// **************************************************************
// Désactive le déclenchement d'une interruption avec la touche 2
// @Return true si ok, false si erreur
// **************************************************************
bool GestionCAP1203::unSetInterruptEnableCs2(void) {
	return genericWrite8(REG_INTERRUPT_ENABLE, genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) & ~CS2, __PRETTY_FUNCTION__);
}

// *************************************************
// Demande si la touche 1 déclenche une interruption
// @Return true si oui, false si non
// *************************************************
bool GestionCAP1203::isInterruptEnableCs1(void) {
	return genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// ***********************************************************
// Active le déclenchement d'une interruption avec la touche 1
// @Return true si ok, false si erreur
// ***********************************************************
bool GestionCAP1203::setInterruptEnableCs1(void) {
	return genericWrite8(REG_INTERRUPT_ENABLE, genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) | CS1, __PRETTY_FUNCTION__);
}

// **************************************************************
// Désactive le déclenchement d'une interruption avec la touche 1
// @Return true si ok, false si erreur
// **************************************************************
bool GestionCAP1203::unSetInterruptEnableCs1(void) {
	return genericWrite8(REG_INTERRUPT_ENABLE, genericRead8(REG_INTERRUPT_ENABLE, __PRETTY_FUNCTION__) & ~CS1, __PRETTY_FUNCTION__);
}

// **************************************************************************************
// Donne le registre indiquant si les touches déclenchent une répétition d'interruption 
// @Return le registre indiquant si les touches déclenchent une répétition d'interruption
// **************************************************************************************
uint8_t GestionCAP1203::getRepeatRateEnable(void) {
	return genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__);
}

// *****************************************************************
// Positionne les touches déclenchants une répétition d'interruption
// @Param touche1
// @Param touche2
// @Param touche3
// @Return true si ok, false si erreur
// *****************************************************************
bool GestionCAP1203::setRepeatRateEnable(TouchCS1 pCs1, TouchCS2 pCs2, TouchCS3 pCs3) {
	return genericWrite8(REG_REPEAT_RATE_ENABLE, pCs1 | pCs2 | pCs3,__PRETTY_FUNCTION__);
}

// **************************************************************
// Demande si la touche 3 déclenche une répétition d'interruption
// @Return true si oui, false si non
// **************************************************************
bool GestionCAP1203::isRepeatRateEnableCs3(void) {
	return genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// ****************************************************
// Active la répétition d'interruption avec la touche 1
// @Return true si ok, false si erreur
// ****************************************************
bool GestionCAP1203::setRepeatRateEnableCs3(void) {
	return genericWrite8(REG_REPEAT_RATE_ENABLE, genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) | CS3, __PRETTY_FUNCTION__);
}

// *******************************************************
// Désactive la répétition d'interruption avec la touche 1
// @Return true si ok, false si erreur
// *******************************************************
bool GestionCAP1203::unSetRepeatRateEnableCs3(void) {
	return genericWrite8(REG_REPEAT_RATE_ENABLE, genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) & ~CS3, __PRETTY_FUNCTION__);
}

// **************************************************************
// Demande si la touche 2 déclenche une répétition d'interruption
// @Return true si oui, false si non
// **************************************************************
bool GestionCAP1203::isRepeatRateEnableCs2(void) {
	return genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// ****************************************************
// Active la répétition d'interruption avec la touche 2
// @Return true si ok, false si erreur
// ****************************************************
bool GestionCAP1203::setRepeatRateEnableCs2(void) {
	return genericWrite8(REG_REPEAT_RATE_ENABLE, genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) | CS2, __PRETTY_FUNCTION__);
}

// *******************************************************
// Désactive la répétition d'interruption avec la touche 2
// @Return true si ok, false si erreur
// *******************************************************
bool GestionCAP1203::unSetRepeatRateEnableCs2(void) {
	return genericWrite8(REG_REPEAT_RATE_ENABLE, genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) & ~CS2, __PRETTY_FUNCTION__);
}

// **************************************************************
// Demande si la touche 1 déclenche une répétition d'interruption
// @Return true si oui, false si non
// **************************************************************
bool GestionCAP1203::isRepeatRateEnableCs1(void) {
	return genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// ****************************************************
// Active la répétition d'interruption avec la touche 1
// @return true si ok, false si erreur
// ****************************************************
bool GestionCAP1203::setRepeatRateEnableCs1(void) {
	return genericWrite8(REG_REPEAT_RATE_ENABLE, genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) | CS1, __PRETTY_FUNCTION__);
}

// *******************************************************
// Désactive la répétition d'interruption avec la touche 1
// @Return true si ok, false si erreur
// *******************************************************
bool GestionCAP1203::unSetRepeatRateEnableCs1(void) {
	return genericWrite8(REG_REPEAT_RATE_ENABLE, genericRead8(REG_REPEAT_RATE_ENABLE, __PRETTY_FUNCTION__) & ~CS1, __PRETTY_FUNCTION__);
}

// *****************************************************************************************
// Donne le nombre de touche possible avant blocage pour la détection de touches multiples
// @Return le nombre de touche possible avant blocage pour la détection de touches multiples
// *****************************************************************************************
GestionCAP1203::BMultT GestionCAP1203::getMultipleTouchConfigurationBMultT(void) {
	switch(genericRead8(REG_MULTIPLE_TOUCH_CONFIG, __PRETTY_FUNCTION__) & MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_FILTER) {
		case MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_1:  return MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_1;  break;
		case MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_2:  return MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_2;  break;
		case MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_3: return MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_3; break;
	}
	return MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_ERROR;	
}

// ******************************************************
// Demande si la détection de touche multiple est activée
// @Return true si oui, false si non
// ******************************************************
bool GestionCAP1203::isMultipleTouchConfigurationMultBlkEn(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)MULTIPLE_TOUCH_CONFIG_MULTI_BLK_EN;
}

// **************************************************
// Active la détection de touche multiple est activée
// @Return true si ok, false si erreur
// **************************************************
bool GestionCAP1203::setMultipleTouchConfigurationMultBlkEn(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_CONFIG, genericRead8(REG_MULTIPLE_TOUCH_CONFIG, __PRETTY_FUNCTION__) | MULTIPLE_TOUCH_CONFIG_MULTI_BLK_EN, __PRETTY_FUNCTION__);
}

// *****************************************************
// Désactive la détection de touche multiple est activée
// @Return true si ok, false si erreur
// *****************************************************
bool GestionCAP1203::unSetMultipleTouchConfigurationMultBlkEn(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_CONFIG, genericRead8(REG_MULTIPLE_TOUCH_CONFIG, __PRETTY_FUNCTION__) & ~MULTIPLE_TOUCH_CONFIG_MULTI_BLK_EN, __PRETTY_FUNCTION__);
}

// ********************************************************
// Positionne la gestion de détection des touches multiples
// @Param Activation
// @Param nombre de touches
// @Return true si ok, false si erreur
// ********************************************************
bool GestionCAP1203::setMultipleTouchConfiguration(bool pMultBlkEn, BMultT pBMultT) {
	uint8_t value;
	if(pMultBlkEn) {
		value = MULTIPLE_TOUCH_CONFIG_MULTI_BLK_EN | pBMultT;
	} else {
		value = pBMultT;
	}
	return genericWrite8(REG_MULTIPLE_TOUCH_CONFIG, value,__PRETTY_FUNCTION__);
}


// ******************************************************************************
// Donne le seuil possible avant blocage pour la détection de touches multiples
// @Return le seuil possible avant blocage pour la détection de touches multiples
// ******************************************************************************
GestionCAP1203::MtpTh GestionCAP1203::getMultipleTouchPatternConfigurationMtpTh(void) {
		switch(genericRead8(REG_MULTIPLE_TOUCH_PATTERN_CONFIG, __PRETTY_FUNCTION__) & MULTIPLE_TOUCHE_PATTERN_MTP_TH_FILTER) {
		case MULTIPLE_TOUCHE_PATTERN_MTP_TH_125P: return MULTIPLE_TOUCHE_PATTERN_MTP_TH_125P; break;
		case MULTIPLE_TOUCHE_PATTERN_MTP_TH_250P: return MULTIPLE_TOUCHE_PATTERN_MTP_TH_250P; break;
		case MULTIPLE_TOUCHE_PATTERN_MTP_TH_375P: return MULTIPLE_TOUCHE_PATTERN_MTP_TH_375P; break;
		case MULTIPLE_TOUCHE_PATTERN_MTP_TH_100P: return MULTIPLE_TOUCHE_PATTERN_MTP_TH_100P; break;
	}
	return MULTIPLE_TOUCHE_PATTERN_MTP_TH_ERROR;	
}

// ******************************************************
// Demande si la détection multiple par seuil est activée
// @Return true si oui, false si non
// ******************************************************
bool GestionCAP1203::isMultipleTouchPatternConfigurationMtpEn(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_PATTERN_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)MULTIPLE_TOUCH_PATTERN_CONFIG_MTP_EN;
}

// *******************************************************************************************
// Demande le mode de détection des touches multiples
// @Return true si la détection est par nombre de touches, false si la détection est par seuil
// *******************************************************************************************
bool GestionCAP1203::isMultipleTouchPatternConfigurationCompPtrn(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_PATTERN_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)MULTIPLE_TOUCH_PATTERN_CONFIG_COMP_PTRN;
}

// *****************************************************************
// Demande si la broche ALERT# est activé par une détection multiple
// @Return true si oui, false si non
// *****************************************************************
bool GestionCAP1203::isMultipleTouchPatternConfigurationMtpAlert(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_PATTERN_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)MULTIPLE_TOUCH_PATTERN_CONFIG_MTP_ALERT;
}

// ***************************************************
// Paramètre la détection de touche multiple par seuil
// @Return true si ok, false si erreur
// ***************************************************
bool GestionCAP1203::setMultipleTouchPatternConfiguration(bool pMtpEn, MtpTh pMtpTh, bool pCompPtrn, bool pMtpAlert) {
	uint8_t value = pMtpTh;
	if(pMtpEn) {
		value |= MULTIPLE_TOUCH_PATTERN_CONFIG_MTP_EN;
	}
	if(pCompPtrn) {
		value |= MULTIPLE_TOUCH_PATTERN_CONFIG_COMP_PTRN;
	}
	if(pMtpAlert) {
		value |= MULTIPLE_TOUCH_PATTERN_CONFIG_MTP_ALERT;
	}
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN_CONFIG, value,__PRETTY_FUNCTION__);
}
	
// ********************************************************
// Donne les touches utilisées pour la détection multiple
// @Return les touches utilisées pour la détection multiple
// ********************************************************
uint8_t GestionCAP1203::getMultipleTouchPattern(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__);
}

// ***********************************************************
// Positionne les touches utilisées pour la détection multiple
// @Param touche1
// @Param touche2
// @Param touche3
// @Return true si ok, false si erreur
// ************************************************************
bool GestionCAP1203::setMultipleTouchPattern(TouchCS1 pCs1, TouchCS2 pCs2, TouchCS3 pCs3) {
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN, pCs1 | pCs2 | pCs3,__PRETTY_FUNCTION__);
}

// ************************************************************
// Demande si la touche 3 est active par une détection multiple
// @Return true si oui, false si non
// ************************************************************
bool GestionCAP1203::isMultipleTouchPatternCs3(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// **********************************************
// Active la touche 3 pour une détection multiple
// @Return true si ok, false si erreur
// **********************************************
bool GestionCAP1203::setMultipleTouchPatternCs3(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN, genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) | CS3, __PRETTY_FUNCTION__);
}

// *************************************************
// Désactive la touche 3 pour une détection multiple
// @Return true si ok, false si erreur
// *************************************************
bool GestionCAP1203::unSetMultipleTouchPatternCs3(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN, genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) & ~CS3, __PRETTY_FUNCTION__);
}

// ************************************************************
// Demande si la touche 2 est active par une détection multiple
// @Return true si oui, false si non
// ************************************************************
bool GestionCAP1203::isMultipleTouchPatternCs2(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// **********************************************
// Active la touche 2 pour une détection multiple
// @Return true si ok, false si erreur
// **********************************************
bool GestionCAP1203::setMultipleTouchPatternCs2(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN, genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) | CS2, __PRETTY_FUNCTION__);
}

// *************************************************
// Désactive la touche 2 pour une détection multiple
// @Return true si ok, false si erreur
// *************************************************
bool GestionCAP1203::unSetMultipleTouchPatternCs2(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN, genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) & ~CS2, __PRETTY_FUNCTION__);
}

// ************************************************************
// Demande si la touche 1 est active par une détection multiple
// @Return true si oui, false si non
// ************************************************************
bool GestionCAP1203::isMultipleTouchPatternCs1(void) {
	return genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// **********************************************
// Active la touche 1 pour une détection multiple
// @Return true si ok, false si erreur
// **********************************************
bool GestionCAP1203::setMultipleTouchPatternCs1(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN, genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) | CS1, __PRETTY_FUNCTION__);
}

// *************************************************
// Désactive la touche 1 pour une détection multiple
// @Return true si ok, false si erreur
// *************************************************
bool GestionCAP1203::unSetMultipleTouchPatternCs1(void) {
	return genericWrite8(REG_MULTIPLE_TOUCH_PATTERN, genericRead8(REG_MULTIPLE_TOUCH_PATTERN, __PRETTY_FUNCTION__) & ~CS1, __PRETTY_FUNCTION__);
}

// *******************************************************************************
// Donne les touches dont le compteur a dépassée la limite et sont inutilisables
//  associé au bit BC_OUT du registre STATUT
// @Return les touches dont le compteur a dépassée la limite et sont inutilisables
// *******************************************************************************
uint8_t GestionCAP1203::getBaseCountOutOfLimit(void) {
	return genericRead8(REG_BASE_COUNT_OUT, __PRETTY_FUNCTION__);
}

// ******************************************************************************
// Demande si le compteur de la touche 3 a dépassée la limite et est inutilisable
// @Return true si oui, false si non
// ******************************************************************************
bool GestionCAP1203::isBaseCountOutOfLimitCs3(void) {
	return genericRead8(REG_BASE_COUNT_OUT, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// ******************************************************************************
// Demande si le compteur de la touche 2 a dépassée la limite et est inutilisable
// @Return true si oui, false si non
// ******************************************************************************
bool GestionCAP1203::isBaseCountOutOfLimitCs2(void) {
	return genericRead8(REG_BASE_COUNT_OUT, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// ******************************************************************************
// Demande si le compteur de la touche 1 a dépassée la limite et est inutilisable
// @Return true si oui, false si non
// ******************************************************************************
bool GestionCAP1203::isBaseCountOutOfLimitCs1(void) {
	return genericRead8(REG_BASE_COUNT_OUT, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// *****************************************************************
// Donne le nombre de compte négatif pour lancer une recalibration
// @Return le nombre de compte négatif pour lancer une recalibration
// *****************************************************************
GestionCAP1203::NegDeltaCnt GestionCAP1203::getRecalibrationConfigNegDeltaCnt(void)	{	
	switch(genericRead8(REG_RECALIBRATION_CONFIG, __PRETTY_FUNCTION__) & RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_FILTER) {
		case RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_8:        return RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_8;        break;
		case RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_16:       return RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_16;       break;
		case RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_32:       return RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_32;       break;
		case RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_DISABLED: return RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_DISABLED; break;
	}
	return RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_ERROR;	
}

// ********************************************************
// Donne le paramétrage pour la mise à jour des compteurs
// @Return le paramétrage pour la mise à jour des compteurs
// ********************************************************
GestionCAP1203::CalCfg GestionCAP1203::getRecalibrationConfigCalCfg(void) {		
	switch(genericRead8(REG_RECALIBRATION_CONFIG, __PRETTY_FUNCTION__) & RECALIBRATION_CONFIGURATION_CAL_CFG_FILTER) {
		case RECALIBRATION_CONFIGURATION_CAL_CFG_16_16:    return RECALIBRATION_CONFIGURATION_CAL_CFG_16_16;    break;
		case RECALIBRATION_CONFIGURATION_CAL_CFG_32_32:    return RECALIBRATION_CONFIGURATION_CAL_CFG_32_32;    break;
		case RECALIBRATION_CONFIGURATION_CAL_CFG_64_64:    return RECALIBRATION_CONFIGURATION_CAL_CFG_64_64;    break;
		case RECALIBRATION_CONFIGURATION_CAL_CFG_128_128:  return RECALIBRATION_CONFIGURATION_CAL_CFG_128_128;  break;
		case RECALIBRATION_CONFIGURATION_CAL_CFG_256_256:  return RECALIBRATION_CONFIGURATION_CAL_CFG_256_256;  break;
		case RECALIBRATION_CONFIGURATION_CAL_CFG_256_1024: return RECALIBRATION_CONFIGURATION_CAL_CFG_256_1024; break;
		case RECALIBRATION_CONFIGURATION_CAL_CFG_256_2048: return RECALIBRATION_CONFIGURATION_CAL_CFG_256_2048; break;
		case RECALIBRATION_CONFIGURATION_CAL_CFG_256_4096: return RECALIBRATION_CONFIGURATION_CAL_CFG_256_4096; break;
	}
	return RECALIBRATION_CONFIGURATION_CAL_CFG_ERROR;	
}

// ***************************************************************
// Demande si toutes les touches utilisent le seuil de la touche 1
// @Return true si oui, false si non
// ***************************************************************
bool GestionCAP1203::isRecalibrationConfigButLdTh(void) {
	return genericRead8(REG_RECALIBRATION_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)RECALIBRATION_CONFIG_BUT_LD_TH;
}

// ********************************************************************************
// Demande si les calculs intermédiaires précédants sont effacés à la recalibration
// @Return true si oui, false si non
// ********************************************************************************
bool GestionCAP1203::isRecalibrationConfigNoClrIntd(void) {
	return genericRead8(REG_RECALIBRATION_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)RECALIBRATION_CONFIG_NO_CLR_INTD;
}

// ***************************************************************************
// Demande si les comptage négatifs précédants sont effacés à la recalibration
// @Return true si oui, false si non
// ***************************************************************************
bool GestionCAP1203::isRecalibrationConfigNoClrNeg(void) {
	return genericRead8(REG_RECALIBRATION_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)RECALIBRATION_CONFIG_NO_CLR_NEG;
}

// ********************************************************************************
// Paramètre le registre de recalibration
// @Param toutes les touches utilisent-elles le seuil de la touche 1
// @Param les calculs intermédiaires précédants sont-ils effacés à la recalibration
// @Param les comptage négatifs précédants sont-ils effacés à la recalibration
// @Param le nombre de compte négatif pour lancer une recalibration
// @Param le paramétrage pour la mise à jour des compteurs
// @Return true si ok, false si erreur
// ********************************************************************************
bool GestionCAP1203::setRecalibrationConfig(bool pButLdTh, bool pNoClrIntd, bool pNoClrNeg, NegDeltaCnt pNegDeltaCnt, CalCfg pCalCfg) {
	uint8_t value;
	if(pButLdTh) {
		value = RECALIBRATION_CONFIG_BUT_LD_TH | pNegDeltaCnt | pCalCfg;
	} else {
		value = pNegDeltaCnt | pCalCfg;
	}
	if(pNoClrIntd) {
		value |= RECALIBRATION_CONFIG_NO_CLR_INTD;
	} 
	if(pNoClrNeg) {
		value |= RECALIBRATION_CONFIG_NO_CLR_NEG;
	} 
	return genericWrite8(REG_RECALIBRATION_CONFIG, value, __PRETTY_FUNCTION__);
}

// *******************************
// Donne le seuil de la touche 1
// @Return le seuil de la touche 1
// *******************************
uint8_t GestionCAP1203::getSensorInputThreshold1(void) {
	return genericRead8(REG_SENSOR_1_INPUT_THRESH, __PRETTY_FUNCTION__);
}

// ***********************************
// Positionne le seuil de la touche 1
// @Param le seuil de la touche 1
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputThreshold1(uint8_t pValue) {
	return genericWrite8(REG_SENSOR_1_INPUT_THRESH, pValue,__PRETTY_FUNCTION__);
}

// *******************************
// Donne le seuil de la touche 2
// @Return le seuil de la touche 2
// *******************************
uint8_t GestionCAP1203::getSensorInputThreshold2(void) {
	return genericRead8(REG_SENSOR_2_INPUT_THRESH, __PRETTY_FUNCTION__);
}

// ***********************************
// Positionne le seuil de la touche 2
// @Param le seuil de la touche 2
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputThreshold2(uint8_t pValue) {
	return genericWrite8(REG_SENSOR_2_INPUT_THRESH, pValue,__PRETTY_FUNCTION__);
}

// *******************************
// Donne le seuil de la touche 3
// @Return le seuil de la touche 3
// *******************************
uint8_t GestionCAP1203::getSensorInputThreshold3(void) {
	return genericRead8(REG_SENSOR_3_INPUT_THRESH, __PRETTY_FUNCTION__);
}

// ***********************************
// Positionne le seuil de la touche 3
// @Param le seuil de la touche 3
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputThreshold3(uint8_t pValue) {
	return genericWrite8(REG_SENSOR_3_INPUT_THRESH, pValue,__PRETTY_FUNCTION__);
}

// *************************
// Donne le seuil de bruit
// @Return le seuil de bruit
// *************************
GestionCAP1203::CsBnTh GestionCAP1203::getSensorInputNoiseThresholdCsBnTh(void)	{	
	switch(genericRead8(REG_SENSOR_INPUT_NOISE_THRESH, __PRETTY_FUNCTION__) & SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_FILTER) {
		case SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_250P: return SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_250P; break;
		case SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_375P: return SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_375P; break;
		case SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_500P: return SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_500P; break;
		case SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_625P: return SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_625P; break;
	}
	return SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_ERROR;	
}

// ***********************************
// Positionne le seuil de bruit
// @Param le seuil de bruit
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setSensorInputNoiseThresholdCsBnTh(CsBnTh pCsBnTh) {
	return genericWrite8(REG_SENSOR_INPUT_NOISE_THRESH, pCsBnTh, __PRETTY_FUNCTION__);
}

// ********************************************
// Donne la liste des touches en mode Standby
// @Return la liste des touches en mode Standby
// ********************************************
uint8_t GestionCAP1203::getStandbyChannel(void) {
	return genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__);
}

// ***********************************************
// Positionne la liste des touches en mode Standby
// @Param la liste des touches en mode Standby
// @Return true si ok, false si erreur
// ***********************************************
bool GestionCAP1203::setStandbyChannel(TouchCS1 pCs1, TouchCS2 pCs2, TouchCS3 pCs3) {
	return genericWrite8(REG_STANDBY_CHANNEL, pCs1 | pCs2 | pCs3,__PRETTY_FUNCTION__);
}

// ******************************************
// Demande si la touche 3 est en mode Standby
// @Return true si oui, false si non
// ******************************************
bool GestionCAP1203::isStandbyChannelCs3(void) {
	return genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) & (uint8_t)CS3;
}

// ***********************************
// Active la touche 3 en mode Standby
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setStandbyChannelCs3(void) {
	return genericWrite8(REG_STANDBY_CHANNEL, genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) | CS3, __PRETTY_FUNCTION__);
}

// *************************************
// Désactive la touche 3 du mode Standby
// @Return true si ok, false si erreur
// *************************************
bool GestionCAP1203::unSetStandbyChannelCs3(void) {
	return genericWrite8(REG_STANDBY_CHANNEL, genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) & ~CS3, __PRETTY_FUNCTION__);
}

// ******************************************
// Demande si la touche 2 est en mode Standby
// @Return true si oui, false si non
// ******************************************
bool GestionCAP1203::isStandbyChannelCs2(void) {
	return genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) & (uint8_t)CS2;
}

// ***********************************
// Active la touche 2 en mode Standby
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setStandbyChannelCs2(void) {
	return genericWrite8(REG_STANDBY_CHANNEL, genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) | CS2, __PRETTY_FUNCTION__);
}

// *************************************
// Désactive la touche 2 du mode Standby
// @Return true si ok, false si erreur
// *************************************
bool GestionCAP1203::unSetStandbyChannelCs2(void) {
	return genericWrite8(REG_STANDBY_CHANNEL, genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) & ~CS2, __PRETTY_FUNCTION__);
}

// ******************************************
// Demande si la touche 1 est en mode Standby
// @Return true si oui, false si non
// ******************************************
bool GestionCAP1203::isStandbyChannelCs1(void) {
	return genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) & (uint8_t)CS1;
}

// ***********************************
// Active la touche 1 en mode Standby
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setStandbyChannelCs1(void) {
	return genericWrite8(REG_STANDBY_CHANNEL, genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) | CS1, __PRETTY_FUNCTION__);
}

// *************************************
// Désactive la touche 1 du mode Standby
// @Return true si ok, false si erreur
// *************************************
bool GestionCAP1203::unSetStandbyChannelCs1(void) {
	return genericWrite8(REG_STANDBY_CHANNEL, genericRead8(REG_STANDBY_CHANNEL, __PRETTY_FUNCTION__) & ~CS1, __PRETTY_FUNCTION__);
}

// *************************************
// Donne le nombre de mesure par cycle
// @Return le nombre de mesure par cycle
// *************************************
GestionCAP1203::StbyAvg GestionCAP1203::getStandbyConfigurationStbyAvg(void) {	
	switch(genericRead8(REG_STANDBY_CONFIG, __PRETTY_FUNCTION__) & STANDBY_CONFIGURATION_STBY_AVG_FILTER) {
		case STANDBY_CONFIGURATION_STBY_AVG_1:   return STANDBY_CONFIGURATION_STBY_AVG_1;   break;
		case STANDBY_CONFIGURATION_STBY_AVG_2:   return STANDBY_CONFIGURATION_STBY_AVG_2;   break;
		case STANDBY_CONFIGURATION_STBY_AVG_4:   return STANDBY_CONFIGURATION_STBY_AVG_4;   break;
		case STANDBY_CONFIGURATION_STBY_AVG_8:   return STANDBY_CONFIGURATION_STBY_AVG_8;   break;
		case STANDBY_CONFIGURATION_STBY_AVG_16:  return STANDBY_CONFIGURATION_STBY_AVG_16;  break;
		case STANDBY_CONFIGURATION_STBY_AVG_32:  return STANDBY_CONFIGURATION_STBY_AVG_32;  break;
		case STANDBY_CONFIGURATION_STBY_AVG_64:  return STANDBY_CONFIGURATION_STBY_AVG_64;  break;
		case STANDBY_CONFIGURATION_STBY_AVG_128: return STANDBY_CONFIGURATION_STBY_AVG_128; break;
	}
	return STANDBY_CONFIGURATION_STBY_AVG_ERROR;	
}

// *****************************
// Donne le temps d'une mesure
// @Return le temps d'une mesure
// *****************************
GestionCAP1203::StbySampTime GestionCAP1203::getStandbyConfigurationStbySampTime(void) {	
	switch(genericRead8(REG_STANDBY_CONFIG, __PRETTY_FUNCTION__) & STANDBY_CONFIGURATION_STBY_SAMP_TIME_FILTER) {
		case STANDBY_CONFIGURATION_STBY_SAMP_TIME_320US: return STANDBY_CONFIGURATION_STBY_SAMP_TIME_320US; break;
		case STANDBY_CONFIGURATION_STBY_SAMP_TIME_640US: return STANDBY_CONFIGURATION_STBY_SAMP_TIME_640US; break;
		case STANDBY_CONFIGURATION_STBY_SAMP_TIME_1280US: return STANDBY_CONFIGURATION_STBY_SAMP_TIME_1280US; break;
		case STANDBY_CONFIGURATION_STBY_SAMP_TIME_2560US: return STANDBY_CONFIGURATION_STBY_SAMP_TIME_2560US; break;
	}
	return STANDBY_CONFIGURATION_STBY_SAMP_TIME_ERROR;	
}

// ***************************
// Donne le temps d'un cycle
// @Return le temps d'un cycle
// ***************************
GestionCAP1203::StbyCyTime GestionCAP1203::getStandbyConfigurationStbyCyTime(void) {	
	switch(genericRead8(REG_STANDBY_CONFIG, __PRETTY_FUNCTION__) & STANDBY_CONFIGURATION_STBY_CY_TIME_FILTER) {
		case STANDBY_CONFIGURATION_STBY_CY_TIME_35MS:  return STANDBY_CONFIGURATION_STBY_CY_TIME_35MS;  break;
		case STANDBY_CONFIGURATION_STBY_CY_TIME_70MS:  return STANDBY_CONFIGURATION_STBY_CY_TIME_70MS;  break;
		case STANDBY_CONFIGURATION_STBY_CY_TIME_105MS: return STANDBY_CONFIGURATION_STBY_CY_TIME_105MS; break;
		case STANDBY_CONFIGURATION_STBY_CY_TIME_140MS: return STANDBY_CONFIGURATION_STBY_CY_TIME_140MS; break;
	}
	return STANDBY_CONFIGURATION_STBY_CY_TIME_ERROR;	
}

// *********************************
// Mode de calcul du compteur
// @Return true somme; false moyenne
// *********************************
bool GestionCAP1203::isStandbyConfigurationAvgSum(void) {
	return genericRead8(REG_STANDBY_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)STANDBY_CONFIG_AVG_SUM;
}

// ******************************************************
// Positionne le registre de configration du mode standby
// @Param la configuration du mode standby
// @Return true si ok, false si erreur
// ******************************************************
bool GestionCAP1203::setStandbyConfiguration(bool pAvgSum, StbyAvg pStbyAvg, StbySampTime pStbySampTime, StbyCyTime pStbyCyTime) {
	uint8_t value;
	if(pAvgSum) {
		value = STANDBY_CONFIG_AVG_SUM | pStbyAvg | pStbySampTime | pStbyCyTime;
	} else {
		value = pStbyAvg | pStbySampTime | pStbyCyTime;
	}
	return genericWrite8(REG_STANDBY_CONFIG, value,__PRETTY_FUNCTION__);
}

// **************************************
// Donne la sensibilité en mode standby
// @Return la sensibilité en mode standby
// **************************************
GestionCAP1203::StbySense GestionCAP1203::getStandbySensibility(void) {	
	switch(genericRead8(REG_STANDBY_SENSITIVITY, __PRETTY_FUNCTION__) & STANDBY_SENSIBILITY_STBY_SENSE_FILTER) {
		case STANDBY_SENSIBILITY_STBY_SENSE_128X: return STANDBY_SENSIBILITY_STBY_SENSE_128X; break;
		case STANDBY_SENSIBILITY_STBY_SENSE_64X:  return STANDBY_SENSIBILITY_STBY_SENSE_64X;  break;
		case STANDBY_SENSIBILITY_STBY_SENSE_32X:  return STANDBY_SENSIBILITY_STBY_SENSE_32X;  break;
		case STANDBY_SENSIBILITY_STBY_SENSE_16X:  return STANDBY_SENSIBILITY_STBY_SENSE_16X;  break;
		case STANDBY_SENSIBILITY_STBY_SENSE_8X:   return STANDBY_SENSIBILITY_STBY_SENSE_8X;   break;
		case STANDBY_SENSIBILITY_STBY_SENSE_4X:   return STANDBY_SENSIBILITY_STBY_SENSE_4X;   break;
		case STANDBY_SENSIBILITY_STBY_SENSE_2X:   return STANDBY_SENSIBILITY_STBY_SENSE_2X;   break;
		case STANDBY_SENSIBILITY_STBY_SENSE_1X:   return STANDBY_SENSIBILITY_STBY_SENSE_1X;   break;
	}
	return STANDBY_SENSIBILITY_STBY_SENSE_ERROR;	
}

// *****************************************
// Positionne la sensibilité du mode standby
// @Param la sensibilité du mode standby
// @Return true si ok, false si erreur
// *****************************************
bool GestionCAP1203::setStandbySensibility(StbySense pStbySense) {
	return genericWrite8(REG_STANDBY_SENSITIVITY, pStbySense,__PRETTY_FUNCTION__);
}

// ********************************
// Donne le seuil en mode standby
// @Return le seuil en mode standby
// ********************************
uint8_t GestionCAP1203::getStandbyThreshold(void) {
	return genericRead8(REG_STANDBY_THRESH, __PRETTY_FUNCTION__);
}

// ***********************************
// Positionne le seuil en mode standby
// @Param le seuil en mode standby
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setStandbyThreshold(uint8_t pValue) {
	return genericWrite8(REG_STANDBY_THRESH, pValue,__PRETTY_FUNCTION__);
}

// ***************************
// Donne le registre config2
// @Return le registre config2
// ***************************
uint8_t GestionCAP1203::getConfiguration2(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__);
}

// ***********************************
// Positionne le registre config2
// @Param le registre config2
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setConfiguration2(uint8_t pValue) {
	return genericWrite8(REG_CONFIG_2, pValue,__PRETTY_FUNCTION__);
}

// **************************************************************************************************
// Demande le base count out
// @Return true si la calibration est répétée , false si la calibration utilise la limite du compteur
// Lire le registre REG_BASE_COUNT_OUT pour connaitre la touche en limite
// **************************************************************************************************
bool GestionCAP1203::isConfiguration2BcOutRecal(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & (uint8_t)CONFIG2_BC_OUT_RECAL;
}

// ******************************************************************************************
// Positionne le base count out pour répéter la calibration en cas de dépassement du compteur
// @Return true si ok, false si erreur
// ******************************************************************************************
bool GestionCAP1203::setConfiguration2BcOutRecal(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) | CONFIG2_BC_OUT_RECAL, __PRETTY_FUNCTION__);
}

// **********************************************************************************
// Positionne le base count out pour que la calibration utilise la limite du compteur
// @Return true si ok, false si erreur
// **********************************************************************************
bool GestionCAP1203::unSetConfiguration2BcOutRecal(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & ~CONFIG2_BC_OUT_RECAL, __PRETTY_FUNCTION__);
}

// ******************************************************
// Demande si le circuit réduit la consommation (inversé)
// @Return true si non, false si oui
// ******************************************************
bool GestionCAP1203::isConfiguration2BlkPwrCtrl(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & (uint8_t)CONFIG2_BLK_PWR_CTRL;
}

// ****************************************
// Le circuit ne réduit pas la consommation
// @Return true si ok, false si erreur
// ****************************************
bool GestionCAP1203::setConfiguration2BlkPwrCtrl(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) | CONFIG2_BLK_PWR_CTRL, __PRETTY_FUNCTION__);
}

// ***********************************
// Le circuit réduit la consommation
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::unSetConfiguration2BlkPwrCtrl(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & ~CONFIG2_BLK_PWR_CTRL, __PRETTY_FUNCTION__);
}

// ************************************************************************
// Demande si une interruption est généré si le compteur est en dépassement
// @Return true si oui, false si non
// ************************************************************************
bool GestionCAP1203::isConfiguration2BcOutInt(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & (uint8_t)CONFIG2_BC_OUT_INT;
}

// **********************************************************
// Générer une interruption si le compteur est en dépassement
// @Return true si ok, false si erreur
// **********************************************************
bool GestionCAP1203::setConfiguration2BcOutInt(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) | CONFIG2_BC_OUT_INT, __PRETTY_FUNCTION__);
}

// *****************************************************************
// Ne pas générer une interruption si le compteur est en dépassement
// @Return true si ok, false si erreur
// *****************************************************************
bool GestionCAP1203::unSetConfiguration2BcOutInt(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & ~CONFIG2_BC_OUT_INT, __PRETTY_FUNCTION__);
}

// *****************************************************
// Demande comment le bruit est visionné
// @Return false si Bruit RF et BF true si Bruit RF seul
// *****************************************************
bool GestionCAP1203::isConfiguration2ShowRfNoise(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & (uint8_t)CONFIG2_SHOW_RF_NOISE;
}

// ***********************************
// Afficher le bruit RF et BF
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setConfiguration2ShowRfNoise(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) | CONFIG2_SHOW_RF_NOISE, __PRETTY_FUNCTION__);
}

// *********************************************
// Afficher juste le bruit RF
// @Return true si ok, false si erreur
// *********************************************
bool GestionCAP1203::unSetConfiguration2ShowRfNoise(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & ~CONFIG2_SHOW_RF_NOISE, __PRETTY_FUNCTION__);
}

// *****************************************************
// Demande si une touche bruitée est déactivée (inversé)
// @Return true si non, false si oui
// *****************************************************
bool GestionCAP1203::isConfiguration2DisRfNoise(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & (uint8_t)CONFIG2_DIS_RF_NOISE;
}

// ************************************************
// Désactiver la désactivation des touches bruitées
// @Return true si ok, false si erreur
// ************************************************

bool GestionCAP1203::setConfiguration2DisRfNoise(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) | CONFIG2_DIS_RF_NOISE, __PRETTY_FUNCTION__);
}

// *********************************************
// Activer la désactivation des touches bruitées
// @Return true si ok, false si erreur
// *********************************************

bool GestionCAP1203::unSetConfiguration2DisRfNoise(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & ~CONFIG2_DIS_RF_NOISE, __PRETTY_FUNCTION__);
}

// *********************************************************************
// Demande si une interruption est généré en cas d'erreur de calibration
// @Return true si oui, false si non
// *********************************************************************
bool GestionCAP1203::isConfiguration2AcalFailInt(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & (uint8_t)CONFIG2_ACAL_FAIL_INT;
}

// ****************************************************
// Générer une interruption cas d'erreur de calibration
// @Return true si ok, false si erreur
// ****************************************************
bool GestionCAP1203::setConfiguration2AcalFailInt(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) | CONFIG2_ACAL_FAIL_INT, __PRETTY_FUNCTION__);
}

// ***********************************************************
// Ne pas générer une interruption cas d'erreur de calibration
// @Return true si ok, false si erreur
// ***********************************************************
bool GestionCAP1203::unSetConfiguration2AcalFailInt(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & ~CONFIG2_ACAL_FAIL_INT, __PRETTY_FUNCTION__);
}

// *************************************************************************
// Demande si une interruption est générée au relaché d'une touche (inversé)
// @Return true si non, false si oui
// *************************************************************************
bool GestionCAP1203::isConfiguration2IntRelN(void) {
	return genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & (uint8_t)CONFIG2_INT_REL_N;
}

// *******************************************************
// Ne pas générer une interruption au relaché d'une touche
// @Return true si ok, false si erreur
// *******************************************************
bool GestionCAP1203::setConfiguration2IntRelN(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) | CONFIG2_INT_REL_N, __PRETTY_FUNCTION__);
}

// ************************************************
// Générer une interruption au relaché d'une touche
// @Return true si ok, false si erreur
// ************************************************
bool GestionCAP1203::unSetConfiguration2IntRelN(void) {
	return genericWrite8(REG_CONFIG_2, genericRead8(REG_CONFIG_2, __PRETTY_FUNCTION__) & ~CONFIG2_INT_REL_N, __PRETTY_FUNCTION__);
}

// ***********************************************
// Donne le compteur "non touché" de la touche 1
// @Return le compteur "non touché" de la touche 1
// ***********************************************
uint8_t GestionCAP1203::getSensorInput1BaseCount(void) {
	return genericRead8(REG_SENSOR_INPUT_1_BASE_COUNT, __PRETTY_FUNCTION__);
}

// ***********************************************
// Donne le compteur "non touché" de la touche 2
// @Return le compteur "non touché" de la touche 2
// ***********************************************
uint8_t GestionCAP1203::getSensorInput2BaseCount(void) {
	return genericRead8(REG_SENSOR_INPUT_2_BASE_COUNT, __PRETTY_FUNCTION__);
}

// ***********************************************
// Donne le compteur "non touché" de la touche 3
// @Return le compteur "non touché" de la touche 3
// ***********************************************
uint8_t GestionCAP1203::getSensorInput3BaseCount(void) {
	return genericRead8(REG_SENSOR_INPUT_3_BASE_COUNT, __PRETTY_FUNCTION__);
}

// *********************
// Donne le bouton PWR
// @Return le bouton PWR
// *********************
GestionCAP1203::PwrBtn GestionCAP1203::getPowerButton(void) {	
	switch(genericRead8(REG_POWER_BUTTON, __PRETTY_FUNCTION__) & POWER_BUTTON_PWR_BTN_FILTER) {
		case POWER_BUTTON_PWR_BTN_CS1: return POWER_BUTTON_PWR_BTN_CS1; break;
		case POWER_BUTTON_PWR_BTN_CS2: return POWER_BUTTON_PWR_BTN_CS2; break;
		case POWER_BUTTON_PWR_BTN_CS3: return POWER_BUTTON_PWR_BTN_CS3; break;
	}
	return POWER_BUTTON_PWR_BTN_ERROR;	
}

// ***********************************
// Positionne le bouton PWR
// @Param le bouton PWR
// @Return true si ok, false si erreur
// ***********************************
bool GestionCAP1203::setPowerButton(PwrBtn pPwrBtn){
	return genericWrite8(REG_POWER_BUTTON, pPwrBtn, __PRETTY_FUNCTION__);
}

// ******************************************************************************
// Demande le temps pour que le bouton PWR fasse une interruption en mode Standby
// @Return le temps pour que le bouton PWR fasse une interruption en mode Standby
// ******************************************************************************
GestionCAP1203::StbyPwrTime GestionCAP1203::getPowerButtonConfigurationStbyPwrTime(void) {	
	switch(genericRead8(REG_POWER_BUTTON_CONFIG, __PRETTY_FUNCTION__) & POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_FILTER) {
		case POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_280MS:  return POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_280MS;  break;
		case POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_560MS:  return POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_560MS;  break;
		case POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_1120MS: return POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_1120MS; break;
		case POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_2240MS: return POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_2240MS; break;
	}
	return POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_ERROR;	
}

// *****************************************************************************
// Demande le temps pour que le bouton PWR fasse une interruption en mode normal
// @Return le temps pour que le bouton PWR fasse une interruption en mode normal
// *****************************************************************************
GestionCAP1203::PwrTime GestionCAP1203::getPowerButtonConfigurationPwrTime(void) {	
	switch(genericRead8(REG_POWER_BUTTON_CONFIG, __PRETTY_FUNCTION__) & POWER_BUTTON_CONFIGURATION_PWR_TIME_FILTER) {
		case POWER_BUTTON_CONFIGURATION_PWR_TIME_280MS:  return POWER_BUTTON_CONFIGURATION_PWR_TIME_280MS;  break;
		case POWER_BUTTON_CONFIGURATION_PWR_TIME_560MS:  return POWER_BUTTON_CONFIGURATION_PWR_TIME_560MS;  break;
		case POWER_BUTTON_CONFIGURATION_PWR_TIME_1120MS: return POWER_BUTTON_CONFIGURATION_PWR_TIME_1120MS; break;
		case POWER_BUTTON_CONFIGURATION_PWR_TIME_2240MS: return POWER_BUTTON_CONFIGURATION_PWR_TIME_2240MS; break;
	}
	return POWER_BUTTON_CONFIGURATION_PWR_TIME_ERROR;	
}

// **************************************************
// Demande si le bouton PWR est actif en mode Standby
// @Return true si oui, false si non
// **************************************************
bool GestionCAP1203::isPowerButtonConfigurationStbyPwrEn(void) {
	return genericRead8(REG_POWER_BUTTON_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)POWER_BUTTON_CONFIG_STBY_PWR_EN;
}

// *************************************************
// Demande si le bouton PWR est actif en mode normal
// @Return true si oui, false si non
// *************************************************
bool GestionCAP1203::isPowerButtonConfigurationPwrEn(void) {
	return genericRead8(REG_POWER_BUTTON_CONFIG, __PRETTY_FUNCTION__) & (uint8_t)POWER_BUTTON_CONFIG_PWR_EN;
}

// ***********************************************
// Positionne le registre de gestion du bouton PWR
// @Param le registre de gestion du bouton PWR
// @Return true si ok, false si erreur
// ***********************************************
bool GestionCAP1203::setPowerButtonConfiguration(bool pStbyPwrEn, StbyPwrTime pStbyPwrTime, bool pPwrEn, PwrTime pPwrTime) {
	uint8_t value = 0;
	if(pStbyPwrEn) {
		value = POWER_BUTTON_CONFIG_STBY_PWR_EN;
	}
	if(pPwrEn) {
		value |= POWER_BUTTON_CONFIG_PWR_EN | pStbyPwrTime | pPwrTime;
	} else {
		value |= pStbyPwrTime | pPwrTime;
	}
	return genericWrite8(REG_POWER_BUTTON_CONFIG, value,__PRETTY_FUNCTION__);
}

// **********************************************
// Donne la dernière calibration de la touche 1
// @return la dernière calibration de la touche 1
// **********************************************
uint16_t GestionCAP1203::getSensorInput1Calibration(void) {
	return (uint16_t)(genericRead8(REG_SENSOR_INPUT_CALIBRATION_LSB_1, __PRETTY_FUNCTION__) << 8) + 
	       (uint16_t)(genericRead8(REG_SENSOR_INPUT_1_CALIBRATION, __PRETTY_FUNCTION__) & SENSOR_INPUT_CALIBRATION_LSB_CS1);
}

// **********************************************
// Donne la dernière calibration de la touche 2
// @return la dernière calibration de la touche 2
// **********************************************
uint16_t GestionCAP1203::getSensorInput2Calibration(void){
	return (uint16_t)(genericRead8(REG_SENSOR_INPUT_CALIBRATION_LSB_1, __PRETTY_FUNCTION__) << 8) + 
	       (uint16_t)((genericRead8(REG_SENSOR_INPUT_2_CALIBRATION, __PRETTY_FUNCTION__) & SENSOR_INPUT_CALIBRATION_LSB_CS2) >> 2);
}

// **********************************************
// Donne la dernière calibration de la touche 3
// @return la dernière calibration de la touche 3
// **********************************************
uint16_t GestionCAP1203::getSensorInput3Calibration(void){
	return (uint16_t)(genericRead8(REG_SENSOR_INPUT_CALIBRATION_LSB_1, __PRETTY_FUNCTION__) << 8) + 
	       (uint16_t)((genericRead8(REG_SENSOR_INPUT_3_CALIBRATION, __PRETTY_FUNCTION__) & SENSOR_INPUT_CALIBRATION_LSB_CS3) >> 4);
}

// *********************
// Donne le Product ID
// @Return le Product ID
// *********************
uint8_t GestionCAP1203::getProductID(void) {
	return genericRead8(REG_PROD_ID, __PRETTY_FUNCTION__);
}


// *********************
// Donne le Vendor ID
// @Return le Vendor ID
// *********************
uint8_t GestionCAP1203::getVendorID(void) {
	return genericRead8(REG_MANUFACTURE_ID, __PRETTY_FUNCTION__);
}


// **********************
// Donne le Revision ID
// @Return le Revision ID
// **********************
uint8_t GestionCAP1203::getRevision(void) {
	return genericRead8(REG_REVISION, __PRETTY_FUNCTION__);
}

// ******************************************
// Vérifie que le circuit est bien un CAP1203
// @Return true si oui, false si non
// ******************************************
bool GestionCAP1203::isCAP1203(void) {
	if(getProductID() != PROD_ID_PRODUCT_ID) {
		return false;
	}
	if(getVendorID() != MANUFACTURE_ID_VENDOR_ID) {
		return false;
	}
	return true;
}
	
// ************************************
// Initialisation simple en mode active
// ************************************
bool GestionCAP1203::activeInit(void) {
	if(isCAP1203()) {
		// Active (defaut)
		active();
		// Active les 3 touches (défaut)
		setSensorInputEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		// 8 mesures de 1.28ms pour un cycle de 70ms (défaut)
		setAverageAndSampling(GestionCAP1203::AVG_AND_SAMPLING_AVG_8, GestionCAP1203::AVG_AND_SAMPLING_SAMP_TIME_1280US, GestionCAP1203::AVG_AND_SAMPLING_CYCLE_TIME_70MS);
		// sensibilité 32 (défaut)		
		setSensibilityControl(SENSITIVITY_CONTROL_DELTA_SENSE_32X, SENSITIVITY_CONTROL_BASE_SHIFT_256X);
		return true;
	} else {
		return false;
	}
}

// *******************************
// Initialisation en mode multiple
// *******************************
bool GestionCAP1203::multInit(void) {
	if(isCAP1203()) {
		// Active (defaut)
		active();
		// Active les 3 touches (défaut)
		setSensorInputEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		// 8 mesures de 1.28ms pour un cycle de 70ms (défaut)
		setAverageAndSampling(GestionCAP1203::AVG_AND_SAMPLING_AVG_8, GestionCAP1203::AVG_AND_SAMPLING_SAMP_TIME_1280US, GestionCAP1203::AVG_AND_SAMPLING_CYCLE_TIME_70MS);
		// sensibilité 32 (défaut)		
		setSensibilityControl(SENSITIVITY_CONTROL_DELTA_SENSE_32X, SENSITIVITY_CONTROL_BASE_SHIFT_256X);
		// Multitouche (test de deux touches, cs1 et cs3, avec interruption)
		setMultipleTouchConfiguration(true, GestionCAP1203::MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_2);
		setMultipleTouchPatternConfiguration(true, GestionCAP1203::MULTIPLE_TOUCHE_PATTERN_MTP_TH_375P, false, true);
		setMultipleTouchPattern(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		noRepeatCs1();
		noRepeatCs2();
		noRepeatCs3();
		noIntRelease();

		return true;
	} else {
		return false;
	}
}

// *************************************
// Initialisation simple en mode standby
// *************************************
bool GestionCAP1203::standbyInit(void) {
	if(isCAP1203()) {
		// Standby
		standby();
		// Active les 3 touches (défaut)
		setStandbyChannel(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		// 8 mesures de 1.28ms pour un cycle de 70ms (défaut)
		setStandbyConfiguration(false, GestionCAP1203::STANDBY_CONFIGURATION_STBY_AVG_8, GestionCAP1203::STANDBY_CONFIGURATION_STBY_SAMP_TIME_1280US, GestionCAP1203::STANDBY_CONFIGURATION_STBY_CY_TIME_70MS);
		// sensibilité 32 (défaut)
		setStandbySensibility(STANDBY_SENSIBILITY_STBY_SENSE_32X);
		return true;
	} else {
		return false;
	}
}

// ****************************
// Initialisation en mode power
// ****************************
bool GestionCAP1203::pwrInit(void) {
	if(isCAP1203()) {
		// Active (defaut)
		active();
		// Active les 3 touches (défaut)
		setSensorInputEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		// 8 mesures de 1.28ms pour un cycle de 70ms (défaut)
		setAverageAndSampling(GestionCAP1203::AVG_AND_SAMPLING_AVG_8, GestionCAP1203::AVG_AND_SAMPLING_SAMP_TIME_1280US, GestionCAP1203::AVG_AND_SAMPLING_CYCLE_TIME_70MS);
		// sensibilité 32 (défaut)		
		setSensibilityControl(SENSITIVITY_CONTROL_DELTA_SENSE_32X, SENSITIVITY_CONTROL_BASE_SHIFT_256X);
		// Power Button
		setPowerButton(GestionCAP1203::POWER_BUTTON_PWR_BTN_CS2);
		setPowerButtonConfiguration(false, GestionCAP1203::POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_1120MS, true, GestionCAP1203::POWER_BUTTON_CONFIGURATION_PWR_TIME_2240MS);

		return true;
	} else {
		return false;
	}
}

// **************************************
// Initialisation sans répétition sur Cs1
//   répétition lente sur Cs2 et Cs3
//   sans interruption au laché
// **************************************
bool GestionCAP1203::lowRepeatInit(void) {
	if(isCAP1203()) {
		// Active (defaut)
		active();
		// Active les 3 touches (défaut)
		setSensorInputEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		// 8 mesures de 1.28ms pour un cycle de 70ms (défaut)
		setAverageAndSampling(GestionCAP1203::AVG_AND_SAMPLING_AVG_8, GestionCAP1203::AVG_AND_SAMPLING_SAMP_TIME_1280US, GestionCAP1203::AVG_AND_SAMPLING_CYCLE_TIME_70MS);
		// sensibilité 32 (défaut)		
		setSensibilityControl(SENSITIVITY_CONTROL_DELTA_SENSE_32X, SENSITIVITY_CONTROL_BASE_SHIFT_256X);
		// Désactive le repeat de CS1
		noRepeatCs1();
		// autorepeat 560ms puis toute les 560ms
		setSensorInputConfig(GestionCAP1203::SENSOR_INPUT_M_PRESS_560MS);
		setSensorInputConfig(GestionCAP1203::SENSOR_INPUT_MAX_DUR_5600MS, GestionCAP1203::SENSOR_INPUT_RPT_RATE_560MS);
		// Pas d'interruption au release
		noIntRelease();
		return true;
	} else {
		return false;
	}
}

// **************************************************
// Initialisation en mode active sensibilité minimale
// **************************************************
bool GestionCAP1203::activeMinSensInit(void) {
	if(isCAP1203()) {
		// Active (defaut)
		active();
		// Active les 3 touches (défaut)
		setSensorInputEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		// 8 mesures de 1.28ms pour un cycle de 70ms (défaut)
		setAverageAndSampling(GestionCAP1203::AVG_AND_SAMPLING_AVG_8, GestionCAP1203::AVG_AND_SAMPLING_SAMP_TIME_1280US, GestionCAP1203::AVG_AND_SAMPLING_CYCLE_TIME_70MS);
		// sensibilité 32 (défaut)		
		setSensibilityControl(SENSITIVITY_CONTROL_DELTA_SENSE_1X, SENSITIVITY_CONTROL_BASE_SHIFT_256X);
		return true;
	} else {
		return false;
	}
}

// **************************************************
// Initialisation en mode active sensibilité maximale
// **************************************************
bool GestionCAP1203::activeMaxSensInit(void) {
	if(isCAP1203()) {
		// Active (defaut)
		active();
		// Active les 3 touches (défaut)
		setSensorInputEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
		// 8 mesures de 1.28ms pour un cycle de 70ms (défaut)
		setAverageAndSampling(GestionCAP1203::AVG_AND_SAMPLING_AVG_8, GestionCAP1203::AVG_AND_SAMPLING_SAMP_TIME_1280US, GestionCAP1203::AVG_AND_SAMPLING_CYCLE_TIME_70MS);
		// sensibilité 32 (défaut)		
		setSensibilityControl(SENSITIVITY_CONTROL_DELTA_SENSE_128X, SENSITIVITY_CONTROL_BASE_SHIFT_256X);
		return true;
	} else {
		return false;
	}
}

// ********************
// Reset default values
// ********************
void GestionCAP1203::reset(void) {
	setMainControl(MAIN_CONTROL_RESET);
	setSensibilityControl(GestionCAP1203::SENSITIVITY_CONTROL_DELTA_SENSE_32X, GestionCAP1203::SENSITIVITY_CONTROL_BASE_SHIFT_256X);
	setConfiguration(CONFIGURATION_RESET);
	setSensorInputEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
	setSensorInputConfig(GestionCAP1203::SENSOR_INPUT_MAX_DUR_5600MS, GestionCAP1203::SENSOR_INPUT_RPT_RATE_175MS);
	setSensorInputConfig(GestionCAP1203::SENSOR_INPUT_M_PRESS_280MS);
	setAverageAndSampling(GestionCAP1203::AVG_AND_SAMPLING_AVG_8, GestionCAP1203::AVG_AND_SAMPLING_SAMP_TIME_1280US, GestionCAP1203::AVG_AND_SAMPLING_CYCLE_TIME_70MS);
	setCalibrationActivateAndStatus(GestionCAP1203::OffCs1, GestionCAP1203::OffCs2, GestionCAP1203::OffCs3);
	setInterruptEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
	setRepeatRateEnable(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
	setMultipleTouchConfiguration(true, GestionCAP1203::MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_1);
	setMultipleTouchPatternConfiguration(false, GestionCAP1203::MULTIPLE_TOUCHE_PATTERN_MTP_TH_125P, false, false);
	setMultipleTouchPattern(GestionCAP1203::OnCs1, GestionCAP1203::OnCs2, GestionCAP1203::OnCs3);
	setRecalibrationConfig(true, false, false, GestionCAP1203::RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_16, GestionCAP1203::RECALIBRATION_CONFIGURATION_CAL_CFG_64_64);
	setSensorInputThreshold1(SENSOR_INPUT_THRESHOLD_RESET);
	setSensorInputThreshold2(SENSOR_INPUT_THRESHOLD_RESET);
	setSensorInputThreshold3(SENSOR_INPUT_THRESHOLD_RESET);
	setSensorInputNoiseThresholdCsBnTh(GestionCAP1203::SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_375P);
	setStandbyChannel(GestionCAP1203::OffCs1, GestionCAP1203::OffCs2, GestionCAP1203::OffCs3);
	setStandbyConfiguration(false, GestionCAP1203::STANDBY_CONFIGURATION_STBY_AVG_8, GestionCAP1203::STANDBY_CONFIGURATION_STBY_SAMP_TIME_1280US, GestionCAP1203::STANDBY_CONFIGURATION_STBY_CY_TIME_70MS);
	setStandbySensibility(GestionCAP1203::STANDBY_SENSIBILITY_STBY_SENSE_32X);
	setStandbyThreshold(SENSOR_INPUT_THRESHOLD_RESET);
	setConfiguration2(CONFIGURATION2_RESET);
	setPowerButton(GestionCAP1203::POWER_BUTTON_PWR_BTN_CS1);
	setPowerButtonConfiguration(false, GestionCAP1203::POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_1120MS, false, GestionCAP1203::POWER_BUTTON_CONFIGURATION_PWR_TIME_1120MS);
}

// ***********
// Destructeur
// ***********
GestionCAP1203::~GestionCAP1203(void) {
}


// ****************************************************
// Fonction generique de lecture d'un registre
// @param le registre
// @param le nom de la fonction appelante pour les logs
// @Return valeur lue si positif, erreur si negatif
// ****************************************************
int8_t GestionCAP1203::genericRead8(uint8_t pRegistre, const char* prettyFunction){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", prettyFunction);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", pRegistre);	

	if(isInitialize()) {
		Logger::log("DEBUG", "<-- ", false);
		Logger::log("DEBUG", prettyFunction);
		Logger::log("DEBUG", "");
		return(read8(pRegistre));
	}

	Logger::log("DEBUG", "    Erreur");
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", prettyFunction);
	Logger::log("DEBUG", "");

	return ERROR;
}

// ****************************************************
// Fonction generique d'ecriture d'un registre
// @param le registre
// @param la valeur à envoyer dans le registre
// @param le nom de la fonction appelante pour les logs
// @return true si ok, false si erreur
// ****************************************************
bool GestionCAP1203::genericWrite8(uint8_t pRegistre, uint8_t pValue, const char* prettyFunction){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", prettyFunction);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", pRegistre);	
	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", pValue);	

	if(isInitialize()) {
	Logger::log("DEBUG", "<-- ", false);
		Logger::log("DEBUG", prettyFunction);
		Logger::log("DEBUG", "");
		return(write8(pRegistre, pValue));
	}

	Logger::log("DEBUG", "    Erreur");
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", prettyFunction);
	Logger::log("DEBUG", "");

	return false;
}

#endif
