/*
 * GestionADXL362.cpp
 *
 * Driver pour l'accéléromètre ADXL362
 *
 * Created on 22/08/2020
 * Author Totof
 *
 */
 
#include "GestionADXL362.h"
#include "GestionADXL362Reg.h"
#include "Logger.h"

// *****************
// Constructeur vide
// *****************
GestionADXL362::GestionADXL362(void){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// ****************
// Constructeur
// @Param canal SPI
// ****************
GestionADXL362::GestionADXL362(Channel canal){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", " canal = ", false);
	Logger::log("DEBUG", canal);	

	initADXL362(canal);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// ********************************************************************
// Initialisation
// Doit être appelé explicitement si le constructeur vide a été utilisé
// @Param canal SPI
// ********************************************************************
bool GestionADXL362::initADXL362(Channel canal){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", " canal = ", false);
	Logger::log("DEBUG", canal);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return initSpi(canal, speed_33);
}

// ***************************************
// Donne le Device ID d'Analog Device (AD)
// @Return Device ID
// ***************************************
uint8_t GestionADXL362::getDevId(void){
	return genericRead8(ADXL362_REG_DEVID_AD, __PRETTY_FUNCTION__);
}

// *************************
// Donne le MEMS du circuit
// @Return MEMS
// *************************
uint8_t GestionADXL362::getMicroElectroMechanicalSystemId(void){
	return genericRead8(ADXL362_REG_DEVID_MST, __PRETTY_FUNCTION__);
}

// ***************
// Donne le PartId
// @Return PartId
// ***************
uint8_t GestionADXL362::getPartId(void){
	return genericRead8(ADXL362_REG_PARTID, __PRETTY_FUNCTION__);
}

// *******************
// Donne le RevisionId
// @Return RevisionId
// *******************
uint8_t GestionADXL362::getRevId(void){
	return genericRead8(ADXL362_REG_REVID, __PRETTY_FUNCTION__);
}

// ********************************
// Indique si c'est bien un ADXL362 
// @Return true si oui false sinon
// ********************************
bool GestionADXL362::isADXL362Device(void){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	if(getDevId() != ADXL362_DEVICE_AD) {
		Logger::log("DEBUG", "    Erreur");
		Logger::log("DEBUG", "<-- ", false);
		Logger::log("DEBUG", __PRETTY_FUNCTION__);
		Logger::log("DEBUG", "");
		return false;
	}
	if(getMicroElectroMechanicalSystemId() != ADXL362_DEVICE_MST) {
		Logger::log("DEBUG", "    Erreur");
		Logger::log("DEBUG", "<-- ", false);
		Logger::log("DEBUG", __PRETTY_FUNCTION__);
		Logger::log("DEBUG", "");
		return false;
	}
	if(getPartId() != ADXL362_PART_ID) {
		Logger::log("DEBUG", "    Erreur");
		Logger::log("DEBUG", "<-- ", false);
		Logger::log("DEBUG", __PRETTY_FUNCTION__);
		Logger::log("DEBUG", "");
		return false;
	}
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return true;
}

// ********************************
// Donne la valeur 8bit sur l'axe X 
// @Return valeur 8bit sur l'axe X
// ********************************
int8_t GestionADXL362::getXAxis8Msb(void){
	return genericRead8(ADXL362_REG_XDATA, __PRETTY_FUNCTION__);
}

// ********************************
// Donne la valeur 8bit sur l'axe Y 
// @Return valeur 8bit sur l'axe Y
// ********************************
int8_t GestionADXL362::getYAxis8Msb(void){
	return genericRead8(ADXL362_REG_YDATA, __PRETTY_FUNCTION__);
}

// ********************************
// Donne la valeur 8bit sur l'axe Z 
// @Return valeur 8bit sur l'axe Z
// ********************************
int8_t GestionADXL362::getZAxis8Msb(void){
	return genericRead8(ADXL362_REG_ZDATA, __PRETTY_FUNCTION__);
}

// **************************************
// Donne le contenu du registre de status 
// @Return le registre de status 
// **************************************
uint8_t GestionADXL362::getStatus(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__);
}

// ********************
// Status error 
// @Return status error
// ********************
bool GestionADXL362::isError(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_ERR_USER_REGS;
}

// ********************
// Status awake 
// @Return status awake
// ********************
bool GestionADXL362::isAwake(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_AWAKE;
}

// **********************
// Status inactif 
// @Return status inactif
// **********************
bool GestionADXL362::isInactif(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_INACT;
}

// ********************
// Status actif 
// @Return status actif
// ********************
bool GestionADXL362::isActif(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_ACT;
}

// ***************************
// Status fifo overrun 
// @Return status fifo overrun 
// ***************************
bool GestionADXL362::isFifoOverrun(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_FIFO_OVERRUN;
}

// *****************************
// Status fifo watermark  
// @Return status fifo watermark
// *****************************
bool GestionADXL362::isFifoWatermark(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_FIFO_WATERMARK;
}

// *************************
// Status fifo ready 
// @Return status fifo ready 
// *************************
bool GestionADXL362::isFifoReady(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_FIFO_RDY;
}

// *************************
// Status data ready 
// @Return status data ready
// *************************
bool GestionADXL362::isDataReady(void){
	return genericRead8(ADXL362_REG_STATUS, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_STATUS_DATA_RDY;
}

// **************************************
// Donne le nombre de mesure dans le Fifo 
// @Return nombre de mesure dans le Fifo 
// **************************************
uint16_t GestionADXL362::getFifoEntries(void){
	return genericRead16(ADXL362_REG_FIFO_L, __PRETTY_FUNCTION__);
}

// ******************
// Mesure sur l'axe X 
// @Return axe X
// ******************
int16_t GestionADXL362::getXAxisData(void){
	return genericRead16(ADXL362_REG_XDATA_L, __PRETTY_FUNCTION__);
}

// ******************
// Mesure sur l'axe X 
// @Return axe X
// ******************
float GestionADXL362::getXAxisG(void){
	float selectrange = 0.0F;
	switch(getRange()) {
		case R2G: selectrange = 2.0F; break;
		case R4G: selectrange = 4.0F; break;
		case R8G: selectrange = 8.0F; break;
	}
	return (float)getXAxisData() / (1000.0F / (selectrange / 2.0F));
}

// ******************
// Mesure sur l'axe Y 
// @Return axe Y
// ******************
int16_t GestionADXL362::getYAxisData(void){
	return genericRead16(ADXL362_REG_YDATA_L, __PRETTY_FUNCTION__);
}

// ******************
// Mesure sur l'axe Y 
// @Return axe Y
// ******************
float GestionADXL362::getYAxisG(void){
	float selectrange = 0.0F;
	switch(getRange()) {
		case R2G: selectrange = 2.0F; break;
		case R4G: selectrange = 4.0F; break;
		case R8G: selectrange = 8.0F; break;
	}
	return (float)getYAxisData() / (1000.0F / (selectrange / 2.0F));
}

// ******************
// Mesure sur l'axe Z 
// @Return axe Z
// ******************
int16_t GestionADXL362::getZAxisData(void){
	return genericRead16(ADXL362_REG_ZDATA_L, __PRETTY_FUNCTION__);
}

// ******************
// Mesure sur l'axe Z 
// @Return axe Z
// ******************
float GestionADXL362::getZAxisG(void){
	float selectrange = 0.0F;
	switch(getRange()) {
		case R2G: selectrange = 2.0F; break;
		case R4G: selectrange = 4.0F; break;
		case R8G: selectrange = 8.0F; break;
	}
	return (float)getZAxisData() / (1000.0F / (selectrange / 2.0F));
}

// ******************************************
// Mesure de la temperature 
// Attention: ce n'est pas la température
//            ambiante, mais celle du circuit 
// @Return temperature
// ******************************************
uint16_t GestionADXL362::getTemperatureData(void){
	return genericRead16(ADXL362_REG_TEMP_L, __PRETTY_FUNCTION__);
}

// ******************************************
// Mesure de la temperature en degré celcius
// Attention: ce n'est pas la température
//            ambiante, mais celle du circuit 
// @Return temperature
// ******************************************
float GestionADXL362::getTemperatureCelcius(void){
	return (float)getTemperatureData() * 0.065F;
}

// **********
// Soft Reset 
// **********
uint8_t GestionADXL362::softReset(void){
	return genericWrite8(ADXL362_REG_SOFT_RESET, ADXL362_RESET_KEY, __PRETTY_FUNCTION__);
}

// *********************************************************
// Donne la valeur d'activite pour la detection de mouvement 
// @Return valeur d'activite
// *********************************************************
uint16_t GestionADXL362::getActivityThreshold(void){
	return genericRead16(ADXL362_REG_THRESH_ACT_L, __PRETTY_FUNCTION__);
}

// **************************************************************
// Positionne la valeur d'activite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// **************************************************************
uint8_t GestionADXL362::setActivityThreshold(uint16_t pValue){
	return genericWrite16(ADXL362_REG_THRESH_ACT_L, pValue, __PRETTY_FUNCTION__);
}

// ********************************************************
// Donne le temps d'activite pour la detection de mouvement 
// @Return temps d'activite
// ********************************************************
uint8_t GestionADXL362::getActivityTime(void){
	return genericRead8(ADXL362_REG_TIME_ACT, __PRETTY_FUNCTION__);
}

// *************************************************************
// Positionne le temps d'activite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// *************************************************************
uint8_t GestionADXL362::setActivityTime(uint8_t pValue){
	return genericWrite8(ADXL362_REG_TIME_ACT, pValue,__PRETTY_FUNCTION__);
}

// ***********************************************************
// Donne la valeur d'inactivite pour la detection de mouvement 
// @Return valeur d'inactivite
// ***********************************************************
uint16_t GestionADXL362::getInactivityThreshold(void){
	return genericRead16(ADXL362_REG_THRESH_INACT_L, __PRETTY_FUNCTION__);
}

// ****************************************************************
// Positionne la valeur d'inactivite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// ****************************************************************
uint8_t GestionADXL362::setInactivityThreshold(uint16_t pValue){
	return genericWrite16(ADXL362_REG_THRESH_INACT_L, pValue, __PRETTY_FUNCTION__);
}

// **********************************************************
// Donne le temps d'inactivite pour la detection de mouvement 
// @Return temps d'inactivite
// **********************************************************
uint16_t GestionADXL362::getInactivityTime(void){
	return genericRead16(ADXL362_REG_TIME_INACT_L, __PRETTY_FUNCTION__);
}

// ***************************************************************
// Positionne le temps d'inactivite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// ***************************************************************
uint8_t GestionADXL362::setInactivityTime(uint16_t pValue){
	return genericWrite16(ADXL362_REG_TIME_INACT_L, pValue, __PRETTY_FUNCTION__);
}

// ********************************************
// Donne l'état du registre activité/inactivité
// @Return le registre activité/inactivité
// ********************************************
uint8_t GestionADXL362::getActivityInactivity(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__);
}

// *************************************************
// Positionne l'état du registre activité/inactivité
// @Return le nombre d'octet ecrit
// *************************************************
uint8_t GestionADXL362::setActivityInactivity(uint8_t pValue){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, pValue, __PRETTY_FUNCTION__);
}

// *********************************
// Donne le mode de fonctionnement
// @Return le mode de fonctionnement
// *********************************
GestionADXL362::LinkLoop GestionADXL362::getLinkLoopMode(void){
	switch(genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & 0b00110000) {
		case 0b00000000: return defaultMode; break;
		case 0b00010000: return linked;      break;
		case 0b00100000: return defaultMode; break;
		case 0b00110000: return loop;        break;
	}
	return linkLoopError;
}

// ************************************
// Positionne le mode de fonctionnement
// @Param Le mode de fonctionnement
// @Return le nombre d'octet ecrit
// ************************************
uint8_t GestionADXL362::setLinkLoopMode(GestionADXL362::LinkLoop pValue){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, (genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & linkLoopMask) | pValue, __PRETTY_FUNCTION__);
}

// *******************************************
// Détecte l'inactivité en absolue ou en delta 
// @Return mode de détection de l'inactivité
// @Values 1 delta, 0 absolue
// *******************************************
bool GestionADXL362::isInactRef(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_ACT_INACT_CTL_INACT_REF;
}

// ************************************************
// Positionne la détection de l'inactivité en delta 
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setInactRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) | ADXL362_ACT_INACT_CTL_INACT_REF, __PRETTY_FUNCTION__);
}

// **************************************************
// Positionne la détection de l'inactivité en absolue 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::unSetInactRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & ~ADXL362_ACT_INACT_CTL_INACT_REF, __PRETTY_FUNCTION__);
}

// ***********************************************
// Demande si la détection d'inactivité est active
// @Return true si oui, false si non
// ***********************************************
bool GestionADXL362::isInactEnable(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_ACT_INACT_CTL_INACT_EN;
}

// ********************************
// Active la détection d'inactivité 
// @Return le nombre d'octet ecrit
// ********************************
uint8_t GestionADXL362::setInactEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) | ADXL362_ACT_INACT_CTL_INACT_EN, __PRETTY_FUNCTION__);
}

// **********************************
// Déactive la détection d'inactivité 
// @Return le nombre d'octet ecrit
// **********************************
uint8_t GestionADXL362::unSetInactEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & ~ADXL362_ACT_INACT_CTL_INACT_EN, __PRETTY_FUNCTION__);
}

// *****************************************
// Détecte l'activité en absolue ou en delta 
// @Return 1 delta, 0 absolue 
// *****************************************
bool GestionADXL362::isActRef(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_ACT_INACT_CTL_ACT_REF;
}

// *******************************************
// Positionne la détection d'activité en delta 
// @Return le nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::setActRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) | ADXL362_ACT_INACT_CTL_ACT_REF, __PRETTY_FUNCTION__);
}

// *********************************************
// Positionne la détection d'activité en absolue 
// @Return le nombre d'octet ecrit
// *********************************************
uint8_t GestionADXL362::unSetActRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & ~ADXL362_ACT_INACT_CTL_ACT_REF, __PRETTY_FUNCTION__);
}

// *********************************************
// Demande si la détection d'activité est active
// @Return true si oui, false si non 
// *********************************************
bool GestionADXL362::isActEnable(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_ACT_INACT_CTL_ACT_EN;
}

// *******************************
// Active la détection d'activité 
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setActEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) | ADXL362_ACT_INACT_CTL_ACT_EN, __PRETTY_FUNCTION__);
}

// ********************************
// Déactive la détection d'activité 
// @Return le nombre d'octet ecrit
// ********************************
uint8_t GestionADXL362::unSetActEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL, __PRETTY_FUNCTION__) & ~ADXL362_ACT_INACT_CTL_ACT_EN, __PRETTY_FUNCTION__);
}

// **************************************************
// Donne le contenu du registre de control des FIFO 
// @Return le contenu du registre de control des FIFO
// **************************************************
uint8_t GestionADXL362::getFifoControl(void){
	return genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__);
}

// *****************************************************
// Positionne le contenu du registre de control des FIFO 
// @Return le nombre d'octet ecrit
// *****************************************************
uint8_t GestionADXL362::setFifoControl(uint8_t pValue){
	return genericWrite8(ADXL362_REG_FIFO_CTL, pValue, __PRETTY_FUNCTION__);
}

// **********************************************************************************************
// 9eme bit du nombre de mesures du FIFO
// @Return le 9eme bit indiquant qu'il y a au moins 256 mesures dans le FIFO sur les 512 posibles
// **********************************************************************************************
bool GestionADXL362::isAboveHalf(void){
	return genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_FIFO_CTL_AH;
}

// *****************************************************************
// Positionne le 9eme bit du pointeur FIFO à 1 (donc au delà de 256)
// @Return le nombre d'octet ecrit
// *****************************************************************
uint8_t GestionADXL362::setAboveHalf(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) | ADXL362_FIFO_CTL_AH, __PRETTY_FUNCTION__);
}

// ************************************************************
// Positionne le 9eme bit du pointeur FIFO à 0 (donc avant 256) 
// @Return le nombre d'octet ecrit
// ************************************************************
uint8_t GestionADXL362::unSetAboveHalf(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) & ~ADXL362_FIFO_CTL_AH, __PRETTY_FUNCTION__);
}

// *************************************************
// Demande si la temperature est stocké dans le FIFO 
// @Return true si oui, false si non
// *************************************************
bool GestionADXL362::isTemperature(void){
	return genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_FIFO_CTL_FIFO_TEMP;
}

// ***************************************
// La temperature sera stocké dans le FIFO 
// @Return le nombre d'octet ecrit
// ***************************************
uint8_t GestionADXL362::setTemperature(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) | ADXL362_FIFO_CTL_FIFO_TEMP, __PRETTY_FUNCTION__);
}

// **********************************************
// La temperature ne sera pas stocké dans le FIFO 
// @Return le nombre d'octet ecrit
// **********************************************
uint8_t GestionADXL362::unSetTemperature(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) & ~ADXL362_FIFO_CTL_FIFO_TEMP, __PRETTY_FUNCTION__);
}

// *****************************************
// Donne le mode de fonctionnement du FIFO 
// @Return le mode de fonctionnement du FIFO 
// *****************************************
GestionADXL362::FifoMode GestionADXL362::getFifoMode(void){
		switch(genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) & 0b00000011) {
		case 0b00000000: return disabled   ; break;
		case 0b00000001: return oldestSaved; break;
		case 0b00000010: return stream     ; break;
		case 0b00000011: return triggered  ; break;
	}
	return fifoModeError;
}

// ********************************************
// Positionne le mode de fonctionnement du FIFO 
// @Return le nombre d'octet ecrit
// ********************************************
uint8_t GestionADXL362::setFifoMode(GestionADXL362::FifoMode pValue){
	return genericWrite8(ADXL362_REG_FIFO_CTL, (genericRead8(ADXL362_REG_FIFO_CTL, __PRETTY_FUNCTION__) & fifoModeMask) | pValue, __PRETTY_FUNCTION__);
}

// *******************************************************************
// Donne les 8 premiers bits du nombre de mesures voulue dans le FIFO
// @Return les 8 premiers bits du nombre de mesure voulue dans le FIFO
// *******************************************************************
uint8_t GestionADXL362::getFifoSamples(void){
	return genericRead8(ADXL362_REG_FIFO_SAMPLES, __PRETTY_FUNCTION__);
}

// **********************************************************************
// Positionne les 8 premiers bits du nombre de mesure voulue dans le FIFO
// @Return le nombre d'octet ecrit
// **********************************************************************
uint8_t GestionADXL362::setFifoSamples(uint8_t pValue){
	return genericWrite8(ADXL362_REG_FIFO_SAMPLES, pValue, __PRETTY_FUNCTION__);
}

// *****************************************************
// Donne le nombre de mesures totale voulue dans le FIFO
// @Return le nombre de mesure dans le FIFO
// *****************************************************
uint16_t GestionADXL362::getFullFifoSamples(void){
	return isAboveHalf() * 256 + genericRead8(ADXL362_REG_FIFO_SAMPLES, __PRETTY_FUNCTION__);
}


// ***********************************************
// Donne le registre de mapping d'interruption 1 
// @Return le registre de mapping d'interruption 1 
// ***********************************************
uint8_t GestionADXL362::getIntMap1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__);
}

// **************************************************
// Positionne le registre de mapping d'interruption 1 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setIntMap1(uint8_t pValue){
	return genericWrite8(ADXL362_REG_INTMAP1, pValue, __PRETTY_FUNCTION__);
}

// ***********************************************
// Demande si l'interruption est active niveau bas
// @Return true si oui, false sinon
// ***********************************************
bool GestionADXL362::isActiveLow1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_INT_LOW;
}

// *******************************************
// Positionne l'interruption active niveau bas 
// @Return le nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::setActiveLow1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_INT_LOW, __PRETTY_FUNCTION__);
}

// ********************************************
// Positionne l'interruption active niveau haut 
// @Return le nombre d'octet ecrit
// ********************************************
uint8_t GestionADXL362::unSetActiveLow1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_INT_LOW, __PRETTY_FUNCTION__);
}

// ***********************************************************
// Demande si il y a interruption quand le circuit se reveille
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isAwake1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_AWAKE;
}

// *****************************************
// interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setAwake1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_AWAKE, __PRETTY_FUNCTION__);
}

// ***********************************************
// Pas d'interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetAwake1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_AWAKE, __PRETTY_FUNCTION__);
}

// *************************************************************
// Demande si il y a interruption quand l'inactivité est détecté 
// @Return true si oui, false si non
// *************************************************************
bool GestionADXL362::isInactif1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_INACT;
}

// **************************************************
// @Param interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setInactif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_INACT, __PRETTY_FUNCTION__);
}

// ********************************************************
// @Param pas d'interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// ********************************************************
uint8_t GestionADXL362::unSetInactif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_INACT, __PRETTY_FUNCTION__);
}

// ***********************************************************
// Demande si il y a interruption quand l'activité est détecté 
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isActif1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_ACT;
}

// *****************************************
// Interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setActif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_ACT, __PRETTY_FUNCTION__);
}

// ***********************************************
// Pas d'interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetActif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_ACT, __PRETTY_FUNCTION__);
}

// ***********************************************************************************************
// Demande si il y a interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return true si oui, false si non
// ***********************************************************************************************
bool GestionADXL362::isFifoOverrun1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_FIFO_OVERRUN;
}

// *****************************************************************************
// Interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// *****************************************************************************
uint8_t GestionADXL362::setFifoOverrun1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_FIFO_OVERRUN, __PRETTY_FUNCTION__);
}

// ***********************************************************************************
// Pas d'interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// ***********************************************************************************
uint8_t GestionADXL362::unSetFifoOverrun1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_FIFO_OVERRUN, __PRETTY_FUNCTION__);
}

// *********************************************************************************************
// Demande si il y a interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return true si oui, false si non
// *********************************************************************************************
bool GestionADXL362::isFifoWatermark1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_FIFO_WATERMARK;
}

// ***************************************************************************
// Interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// ***************************************************************************
uint8_t GestionADXL362::setFifoWatermark1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_FIFO_WATERMARK, __PRETTY_FUNCTION__);
}

// *********************************************************************************
// Pas d'interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// *********************************************************************************
uint8_t GestionADXL362::unSetFifoWatermark1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_FIFO_WATERMARK, __PRETTY_FUNCTION__);
}

// ******************************************************************
// Demande si il y a interruption si au moins une mesure dans le FIFO
// @Return true si oui, false si non
// ******************************************************************
bool GestionADXL362::isFifoReady1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_FIFO_READY;
}

// ************************************************
// Interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setFifoReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_FIFO_READY, __PRETTY_FUNCTION__);
}

// ******************************************************
// Pas d'interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::unSetFifoReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_FIFO_READY, __PRETTY_FUNCTION__);
}

// ************************************************************************
// Demande si il y a interruption si une mesure est disponible à la lecture
// @Return true si oui, false si non
// ************************************************************************
bool GestionADXL362::isDataReady1(void){
	return genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP1_DATA_READY;
}

// ******************************************************
// Interruption si une mesure est disponible à la lecture
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::setDataReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) | ADXL362_INTMAP1_DATA_READY, __PRETTY_FUNCTION__);
}

// ************************************************************
// Pas d'interruption si une mesure est disponible à la lecture 
// @Return le nombre d'octet ecrit
// ************************************************************
uint8_t GestionADXL362::unSetDataReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP1_DATA_READY, __PRETTY_FUNCTION__);
}

// ***********************************************
// Donne le registre de mapping d'interruption 2 
// @Return le registre de mapping d'interruption 2 
// ***********************************************
uint8_t GestionADXL362::getIntMap2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__);
}

// **************************************************
// Positionne le registre de mapping d'interruption 2 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setIntMap2(uint8_t pValue){
	return genericWrite8(ADXL362_REG_INTMAP2, pValue, __PRETTY_FUNCTION__);
}

// ***********************************************
// Demande si l'interruption est active niveau bas
// @Return true si oui, false sinon
// ***********************************************
bool GestionADXL362::isActiveLow2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_INT_LOW;
}

// *******************************************
// Positionne l'interruption active niveau bas 
// @Return le nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::setActiveLow2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_INT_LOW, __PRETTY_FUNCTION__);
}

// ********************************************
// Positionne l'interruption active niveau haut 
// @Return le nombre d'octet ecrit
// ********************************************
uint8_t GestionADXL362::unSetActiveLow2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_INT_LOW, __PRETTY_FUNCTION__);
}

// ***********************************************************
// Demande si il y a interruption quand le circuit se reveille
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isAwake2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_AWAKE;
}

// *****************************************
// interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setAwake2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_AWAKE, __PRETTY_FUNCTION__);
}

// ***********************************************
// Pas d'interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetAwake2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_AWAKE, __PRETTY_FUNCTION__);
}

// **************************************************
// @Param interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// **************************************************
bool GestionADXL362::isInactif2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_INACT;
}

// **************************************************
// @Param interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setInactif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_INACT, __PRETTY_FUNCTION__);
}

// ********************************************************
// @Param pas d'interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// ********************************************************
uint8_t GestionADXL362::unSetInactif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_INACT, __PRETTY_FUNCTION__);
}

// ***********************************************************
// Demande si il y a interruption quand l'activité est détecté 
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isActif2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_ACT;
}

// *****************************************
// Interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setActif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_ACT, __PRETTY_FUNCTION__);
}

// ***********************************************
// Pas d'interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetActif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_ACT, __PRETTY_FUNCTION__);
}

// ***********************************************************************************************
// Demande si il y a interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return true si oui, false si non
// ***********************************************************************************************
bool GestionADXL362::isFifoOverrun2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_FIFO_OVERRUN;
}

// *****************************************************************************
// Interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// *****************************************************************************
uint8_t GestionADXL362::setFifoOverrun2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_FIFO_OVERRUN, __PRETTY_FUNCTION__);
}

// ***********************************************************************************
// Pas d'interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// ***********************************************************************************
uint8_t GestionADXL362::unSetFifoOverrun2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_FIFO_OVERRUN, __PRETTY_FUNCTION__);
}

// *********************************************************************************************
// Demande si il y a interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return true si oui, false si non
// *********************************************************************************************
bool GestionADXL362::isFifoWatermark2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_FIFO_WATERMARK;
}

// ***************************************************************************
// Interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// ***************************************************************************
uint8_t GestionADXL362::setFifoWatermark2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_FIFO_WATERMARK, __PRETTY_FUNCTION__);
}

// *********************************************************************************
// Pas d'interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// *********************************************************************************
uint8_t GestionADXL362::unSetFifoWatermark2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_FIFO_WATERMARK, __PRETTY_FUNCTION__);
}

// ******************************************************************
// Demande si il y a interruption si au moins une mesure dans le FIFO
// @Return true si oui, false si non
// ******************************************************************
bool GestionADXL362::isFifoReady2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_FIFO_READY;
}

// ************************************************
// Interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setFifoReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_FIFO_READY, __PRETTY_FUNCTION__);
}

// ******************************************************
// Pas d'interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::unSetFifoReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_FIFO_READY, __PRETTY_FUNCTION__);
}

// ************************************************************************
// Demande si il y a interruption si une mesure est disponible à la lecture
// @Return true si oui, false si non
// ************************************************************************
bool GestionADXL362::isDataReady2(void){
	return genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_INTMAP2_DATA_READY;
}

// ******************************************************
// Interruption si une mesure est disponible à la lecture
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::setDataReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) | ADXL362_INTMAP2_DATA_READY, __PRETTY_FUNCTION__);
}

// ************************************************************
// Pas d'interruption si une mesure est disponible à la lecture 
// @Return le nombre d'octet ecrit
// ************************************************************
uint8_t GestionADXL362::unSetDataReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2, __PRETTY_FUNCTION__) & ~ADXL362_INTMAP2_DATA_READY, __PRETTY_FUNCTION__);
}

// *************************************
// Donne le registre de filter control
// @Return le registre de filter control
// *************************************
uint8_t GestionADXL362::getFilterControl(void){
	return genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__);
}

// ****************************************
// Positionne le registre de filter control
// @Return le nombre d'octet ecrit
// ****************************************
uint8_t GestionADXL362::setFilterControl(uint8_t pValue){
	return genericWrite8(ADXL362_REG_FILTER_CTL, pValue, __PRETTY_FUNCTION__);
}

// *****************
// Donne l'échelle
// @Return l'échelle
// *****************
GestionADXL362::Range GestionADXL362::getRange(void){
	switch(genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & 0b11000000) {
		case 0b00000000: return R2G; break;
		case 0b01000000: return R4G; break;
		case 0b10000000: 
		case 0b11000000: return R8G; break;
	}
	return rangeError;
}

// *************************
// Positionne l'échelle 
// @Return le nombre d'octet ecrit
// *************************
uint8_t GestionADXL362::setRange(GestionADXL362::Range pValue){
	return genericWrite8(ADXL362_REG_FILTER_CTL, (genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & rangeMask) | pValue, __PRETTY_FUNCTION__);
}

// **********************************
// Demande si le filtre est postionné
// @Return true si oui, false si non
// **********************************
bool GestionADXL362::isHalfBandWidth(void){
	return genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_FILTER_CTL_HALF_BW;
}

// *********************************
// Positionne le filtre antialiasing
// @Return le nombre d'octet ecrit
// *********************************
uint8_t GestionADXL362::setHalfBandWidth(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) | ADXL362_FILTER_CTL_HALF_BW, __PRETTY_FUNCTION__);
}

// *****************************************************
// Positionne le filtre pour une bande passante maximale
// @Return le nombre d'octet ecrit
// *****************************************************
uint8_t GestionADXL362::unSetHalfBandWidth(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & ~ADXL362_FILTER_CTL_HALF_BW, __PRETTY_FUNCTION__);
}

// ***************************************************************
// Demande si le signal de synchronisation sur int2 est postionnée 
// @Return true si oui, false si non
// ***************************************************************
bool GestionADXL362::isExternalSample(void){
	return genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_FILTER_CTL_EXT_SAMPLE;
}

// ************************************************
// Positionne le signal de synchronisation sur int2
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setExternalSample(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) | ADXL362_FILTER_CTL_EXT_SAMPLE, __PRETTY_FUNCTION__);
}

// ****************************************************
// Positionne le signal de synchronisation int2 sur off
// @Return le nombre d'octet ecrit
// ****************************************************
uint8_t GestionADXL362::unSetExternalSample(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & ~ADXL362_FILTER_CTL_EXT_SAMPLE, __PRETTY_FUNCTION__);
}

// *************************************
// Donne la fréquence d'échantillonage
// @Return la fréquence d'échantillonage
// *************************************
GestionADXL362::DataRate GestionADXL362::getDataRate(void){
	switch(genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & 0b00000111) {
		case 0b00000000: return DR12p5; break;
		case 0b00000001: return DR25; break;
		case 0b00000010: return DR50; break;
		case 0b00000011: return DR100; break;
		case 0b00000100: return DR200; break;
		case 0b00000101: 
		case 0b00000110: 
		case 0b00000111: return DR400; break;
	}
	return dataRateError;
}

// ****************************************
// Positionne la fréquence d'échantillonage
// @Return le nombre d'octet ecrit
// ****************************************
uint8_t GestionADXL362::setDataRate(GestionADXL362::DataRate pValue){
	return genericWrite8(ADXL362_REG_FILTER_CTL, (genericRead8(ADXL362_REG_FILTER_CTL, __PRETTY_FUNCTION__) & dataRateMask) | pValue, __PRETTY_FUNCTION__);
}

// *********************************
// Donne le registre power control
// @Return le registre power control
// *********************************
uint8_t GestionADXL362::getPowerControl(void){
	return genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__);
}

// ************************************
// Positionne le registre power control 
// @Return le nombre d'octet ecrit
// ************************************
uint8_t GestionADXL362::setPowerControl(uint8_t pValue){
	return genericWrite8(ADXL362_REG_POWER_CTL, pValue, __PRETTY_FUNCTION__);
}

// *********************************
// Demande si l'horloge est externe
// @Return true si oui, false si non
// *********************************
bool GestionADXL362::isExternalClock(void){
	return genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_POWER_CTL_EXT_CLK;
}

// *******************************
// Positionne l'horloge externe 
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setExternalClock(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) | ADXL362_POWER_CTL_EXT_CLK, __PRETTY_FUNCTION__);
}

// *******************************
// Positionne l'horloge interne
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::unSetExternalClock(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & ~ADXL362_POWER_CTL_EXT_CLK, __PRETTY_FUNCTION__);
}

// *****************
// Donne le filtre
// @Return le filtre
// *****************
GestionADXL362::Noise GestionADXL362::getNoise(void){
	switch(genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & 0b00110000) {
		case 0b00000000: return normal; break;
		case 0b00010000: return lowNoise; break;
		case 0b00100000: return ultraLowNoise; break;
	}
	return noiseError;
}

// *******************************
// Positionne le filtre
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setNoise(GestionADXL362::Noise pValue){
	return genericWrite8(ADXL362_REG_POWER_CTL, (genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & noiseMask) | pValue, __PRETTY_FUNCTION__);
}

// *******************************************************
// Demande si le circuit est en mode consommation minimale
// @Return true si oui, false si non
// *******************************************************
bool GestionADXL362::isWakeUp(void){
	return genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_POWER_CTL_WAKEUP;
}

// ***************************************************
// Positionne le circuit en mode consommation minimale
// @Return le nombre d'octet ecrit
// ***************************************************
uint8_t GestionADXL362::setWakeUp(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) | ADXL362_POWER_CTL_WAKEUP, __PRETTY_FUNCTION__);
}

// **************************************************
// Positionne le circuit en mode consommation normale
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::unSetWakeUp(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & ~ADXL362_POWER_CTL_WAKEUP, __PRETTY_FUNCTION__);
}

// *******************************************************************
// Demande si le circuit passe en économie d'énergie si il est inactif
// @Return true si oui, false si non
// *******************************************************************
bool GestionADXL362::isAutoSleep(void){
	return genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_POWER_CTL_AUTOSLEEP;
}

// *************************************************************
// Positionne le circuit en économie d'énergie si il est inactif
// @Return le nombre d'octet ecrit
// *************************************************************
uint8_t GestionADXL362::setAutoSleep(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) | ADXL362_POWER_CTL_AUTOSLEEP, __PRETTY_FUNCTION__);
}

// ******************************************************
// Positionne le circuit en mode normal si il est inactif
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::unSetAutoSleep(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & ~ADXL362_POWER_CTL_AUTOSLEEP, __PRETTY_FUNCTION__);
}

// *************************
// Donne le mode de mesure
// @Return le mode de mesure
// *************************
GestionADXL362::Measure GestionADXL362::getMeasure(void){
	switch(genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & 0b00000011) {
		case 0b00000000: return standby; break;
		case 0b00000010: return measurement; break;
	}
	return measureError;
}

// *******************************
// Positionne le mode de mesure
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setMeasure(GestionADXL362::Measure pValue){
	return genericWrite8(ADXL362_REG_POWER_CTL, (genericRead8(ADXL362_REG_POWER_CTL, __PRETTY_FUNCTION__) & measureMask) | pValue, __PRETTY_FUNCTION__);
}

// *************************
// Demande si le circuit est en auto test 
// @Return true si oui, false si non
// *************************
bool GestionADXL362::isSelfTest(void){
	return genericRead8(ADXL362_REG_SELF_TEST, __PRETTY_FUNCTION__) & (uint8_t)ADXL362_SELF_TEST_ST;
}

// **********************************
// Positionne le circuit en auto test
// @Return le nombre d'octet ecrit
// **********************************
uint8_t GestionADXL362::setSelfTest(void){
	return genericWrite8(ADXL362_REG_SELF_TEST, genericRead8(ADXL362_REG_SELF_TEST, __PRETTY_FUNCTION__) | ADXL362_SELF_TEST_ST, __PRETTY_FUNCTION__);
}

// *******************************************************
// Positionne le circuit est en mode fonctionnement normal
// @Return le nombre d'octet ecrit
// *******************************************************
uint8_t GestionADXL362::unSetSelfTest(void){
	return genericWrite8(ADXL362_REG_SELF_TEST, genericRead8(ADXL362_REG_SELF_TEST, __PRETTY_FUNCTION__) & ~ADXL362_SELF_TEST_ST, __PRETTY_FUNCTION__);
}

// *************************************
// Autonomous Motion switch du datasheet
// *************************************
void GestionADXL362::sampleInit1(void) {
	// Activité 250mG
	setActivityThreshold(0x00FA);
	// Inactivité 150mG
	setInactivityThreshold(0x0096);
	// Inactivité 5s
	setInactivityTime(0x001E);
	// Loop mode detect activité et inactivité
	setActivityInactivity(0x3F);
	// Awake to INT2
	setIntMap2(0x40);
	// start
	setPowerControl(0x0A);
}

// ***********
// Low energie
// ***********
void GestionADXL362::sampleInit2(void) {
	// Activité 100mG
	setActivityThreshold(0x0064);
	// Inactivité 150mG
	setInactivityThreshold(0x0096);
	// Inactivité 1s
	setInactivityTime(0x0006);
	// Loop mode detect activité et inactivité
	setActivityInactivity(0x3F);
	// Awake to INT2
	setIntMap2(0x10);
	// start
	setPowerControl(0x0E);
}

// ************************
// Initialisation interrupt
// ************************
void GestionADXL362::sampleInit3(void) {
	// Activité 250mG
	setActivityThreshold(0x001F);
	// Activité 0.1s
	setActivityTime(0x02);
	// Loop mode detect activité et inactivité
	setActivityInactivity(0x15);
	// Awake to INT2
	setIntMap1(0x10);
	// DataReady to INT2
	setIntMap2(0x01);
	// start
	setPowerControl(0x0A);
}

// *******************************************
// Fonction generique de lecture d'un registre
// @Return valeur
// *******************************************
uint8_t GestionADXL362::genericRead8(uint8_t pRegistre, const char* prettyFunction){
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

// ***********************************************
// Fonction generique de lecture de deux registres
// @Return valeur
// ***********************************************
uint16_t GestionADXL362::genericRead16(uint8_t pRegistre, const char* prettyFunction){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", prettyFunction);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", pRegistre);	

	if(isInitialize()) {
		Logger::log("DEBUG", "<-- ", false);
		Logger::log("DEBUG", prettyFunction);
		Logger::log("DEBUG", "");
		return(read16(pRegistre));
	}

	Logger::log("DEBUG", "    Erreur");
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", prettyFunction);
	Logger::log("DEBUG", "");

	return ERROR;
}

// *******************************************
// Fonction generique d'ecriture d'un registre
// @Return nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::genericWrite8(uint8_t pRegistre, uint8_t pValue, const char* prettyFunction){
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

	return ERROR;
}

// ***********************************************
// Fonction generique d'ecriture de deux registres
// @Return nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::genericWrite16(uint8_t pRegistre, uint16_t pValue, const char* prettyFunction){
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
		return(write16(pRegistre, pValue));
	}

	Logger::log("DEBUG", "    Erreur");
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", prettyFunction);
	Logger::log("DEBUG", "");

	return ERROR;
}

// *********************************
// Lit le contenu de la mémoire Fifo
// *********************************
void GestionADXL362::getFifoData(uint16_t pNombreValeur){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", " pNombreValeur = ", false);
	Logger::log("DEBUG", pNombreValeur);	
	
	fifoData[0] = ADXL362_READ_FIFO;
	
	Logger::log("DEBUG", " fifoData[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)fifoData[0]);	

	read(fifoData, sizeof(pNombreValeur));

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

// ****************************
// Lit une valeur d'un registre
// @Param le registre
// @Return la valeur
// ****************************
uint8_t GestionADXL362::read8(uint8_t pRegistre){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", pRegistre);	

	spiData8[0] = ADXL362_READ_REG;
	spiData8[1] = pRegistre;
	
	Logger::log("DEBUG", " spiData8[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[0]);	
	Logger::log("DEBUG", " spiData8[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[1]);	

	read(spiData8, sizeof(spiData8));

	Logger::log("DEBUG", " spiData8[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[0]);	
	Logger::log("DEBUG", " spiData8[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[1]);	
	Logger::log("DEBUG", " spiData8[2] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[2]);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");

	return spiData8[2];
}

// ********************************
// Lit une valeur de deux registres
// @Param le premier registre
// @Return la valeur
// ********************************
uint16_t GestionADXL362::read16(uint8_t pRegistre){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", pRegistre);	

	spiData16[0] = ADXL362_READ_REG;
	spiData16[1] = pRegistre;
	
	Logger::log("DEBUG", " spiData16[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[0]);	
	Logger::log("DEBUG", " spiData16[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[1]);	

	read(spiData16, sizeof(spiData16));

	Logger::log("DEBUG", " spiData16[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[0]);	
	Logger::log("DEBUG", " spiData16[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[1]);	
	Logger::log("DEBUG", " spiData16[2] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[2]);	
	Logger::log("DEBUG", " spiData16[3] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[3]);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");

	return ((spiData16[3] << 8) + spiData16[2]);
}

// **********************************
// Ecrit une valeur dans un registre
// @Param le registre
// @Return le nombre de valeur ecrite
// **********************************
uint8_t GestionADXL362::write8(uint8_t pRegistre, uint8_t pValue){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", pRegistre);	
	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", pValue);	

	spiData8[0] = ADXL362_WRITE_REG;
	spiData8[1] = pRegistre;
	spiData8[2] = pValue;
	
	Logger::log("DEBUG", " spiData8[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[0]);	
	Logger::log("DEBUG", " spiData8[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[1]);	
	Logger::log("DEBUG", " spiData8[2] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[2]);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return write(spiData8, sizeof(spiData8));
}

// ************************************
// Ecrit une valeur dans deux registres
// @Param le premier registre
// @Return le nombre de valeur ecrite
// ************************************
uint8_t GestionADXL362::write16(uint8_t pRegistre, uint16_t pValue){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", pRegistre);	
	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", pValue);	

	spiData16[0] = ADXL362_WRITE_REG;
	spiData16[1] = pRegistre;
	spiData16[2] = (uint8_t)(pValue & 0x00FF);
	spiData16[3] = (uint8_t)(pValue >> 8);
	
	Logger::log("DEBUG", " spiData16[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[0]);	
	Logger::log("DEBUG", " spiData16[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[1]);	
	Logger::log("DEBUG", " spiData16[2] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[2]);	
	Logger::log("DEBUG", " spiData16[3] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData16[3]);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return write(spiData16, sizeof(spiData16));
}

// ***********
// Destructeur
// ***********
GestionADXL362::~GestionADXL362(){
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
};
