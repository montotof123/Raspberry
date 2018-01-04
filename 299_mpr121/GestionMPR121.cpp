/*
 * GestionMPR121.cpp
 *
 * on: 20 december 2017
 *      Author: totof
 * Controle un module MPR121
 */
 
#include "GestionMPR121.h"

// *****************
// Constructeur vide
// *****************
GestionMPR121::GestionMPR121() {
}

// ******************************
// Constructeur
// @Param l'adresse I2C du module
// ******************************
GestionMPR121::GestionMPR121(AdresseMpr121 address) {
	init(address);
}

// ******************************
// Constructeur
// @Param l'adresse I2C du module
// @Param GPIO branche sur IRQ
// ******************************
GestionMPR121::GestionMPR121(AdresseMpr121 address, PinGPIO interrupt) {
	init(address, interrupt);
}

// *******************************
// Initialisation
// @Param l'adresse I2C du module
// @Return true si ok, false sinon
// *******************************
bool GestionMPR121::init(AdresseMpr121 address) {
	GestionI2C::init(address);
	return isInitialize();
}

// *******************************
// Initialisation
// @Param l'adresse I2C du module
// @Param GPIO branche sur IRQ
// @Return true si ok, false sinon
// *******************************
bool GestionMPR121::init(AdresseMpr121 address, PinGPIO pinInterrupt) {
	GestionI2C::init(address);
	interrupt.init(pinInterrupt);
	return isInitialize();
}

// *****************************
// Donne l'etat des electrodes
// 0x00 0x01
// @Return l'etat des electrodes
// *****************************
uint16_t GestionMPR121::getAllTouchStatus(void) {
	touchRead = true;
	touchStatut = read16(REG_TOUCH_STATUS_LSB) & TOUCH_MASK;
	return touchStatut;
}

// ***********************************************
// Donne l'etat d'une electrode
// 0x00 0x01
// @Param le numero de l'electrode
// @Param force la mesure des electrodes
// @Return l'etat de l'electrode
// ***********************************************
bool GestionMPR121::getTouchStatus(Electrode electrode, bool readTouch) {
	// Demande la lecture des touches
	if(readTouch) {
		getAllTouchStatus();
	}
	// Les touches n'ont jamais ete lue
	if(!touchRead) {
		getAllTouchStatus();
	}
	switch(electrode) {
		case ELE0:  return touchStatut & TOUCH_0;
		case ELE1:  return touchStatut & TOUCH_1;
		case ELE2:  return touchStatut & TOUCH_2;
		case ELE3:  return touchStatut & TOUCH_3;
		case ELE4:  return touchStatut & TOUCH_4;
		case ELE5:  return touchStatut & TOUCH_5;
		case ELE6:  return touchStatut & TOUCH_6;
		case ELE7:  return touchStatut & TOUCH_7;
		case ELE8:  return touchStatut & TOUCH_8;
		case ELE9:  return touchStatut & TOUCH_9;
		case ELE10: return touchStatut & TOUCH_10;
		case ELE11: return touchStatut & TOUCH_11;
		case ELEPROX: return touchStatut & TOUCH_PROX;
	}
}

// **********************************
// Donne l'etat du flag Over Current
// 0x00 0x01
// @Param force la mesure du bit OVCF
// @Return l'etat de la touche
// **********************************
bool GestionMPR121::getOverCurrentFlag(bool readOVCF) {
	// Demande la lecture du bit OVCF
	if(readOVCF) {
		getAllTouchStatus();
	}
	// Le bit OVCF n'a jamais ete lu
	if(!touchRead) {
		getAllTouchStatus();
	}
	return touchStatut & OVCF16;
}

// *************************************************
// Force le bit Over Current Flag pour remise a zero
// 0x00 0x01
// Remettre le module en mode Run pour redemarrage
// @Return true si ok, false sinon
// *************************************************
bool GestionMPR121::setOverCurrent(void) {
	return write8(REG_TOUCH_STATUS_LSB, OVCF8);	
}

// ***************************************
// Donne l'etat des status out of range 
// 0x02 0x03
// @Return l'etat des status out of range
// stocke egalement l'etat dans outOfRange
// ***************************************
uint16_t GestionMPR121::getOutOfRange(void) {
	outOfRangeRead = true;
	outOfRange = read16(REG_OOR_STATUS_LSB);
	return outOfRange;
}

// ****************************************
// Donne l'etat du flag ACFF lu du registre
// 0x02 0x03
// @Return l'etat du flag ACFF
// ****************************************
bool GestionMPR121::isAutoConfigFailFlagFromRegister(void) {
	return getOutOfRange() & ACFF;
}

// ****************************************
// Donne l'etat du flag ARFF lu du registre
// 0x02 0x03
// @Return l'etat du flag ARFF
// ****************************************
bool GestionMPR121::isAutoReConfigFailFlagFromRegister(void) {
	return getOutOfRange() & ARFF;
}

// **************************************************************
// Donne l'etat du flag outofrange d'une electrode lu du registre
// 0x02 0x03
// @Return l'etat du flag outofrange d'un electrode
// **************************************************************
bool GestionMPR121::isOutOfRangeFromRegister(Electrode electrode) {
	switch(electrode) {
		case ELE0:  getOutOfRange() & TOUCH_0;
		case ELE1:  getOutOfRange() & TOUCH_1;
		case ELE2:  getOutOfRange() & TOUCH_2;
		case ELE3:  getOutOfRange() & TOUCH_3;
		case ELE4:  getOutOfRange() & TOUCH_4;
		case ELE5:  getOutOfRange() & TOUCH_5;
		case ELE6:  getOutOfRange() & TOUCH_6;
		case ELE7:  getOutOfRange() & TOUCH_7;
		case ELE8:  getOutOfRange() & TOUCH_8;
		case ELE9:  getOutOfRange() & TOUCH_9;
		case ELE10: getOutOfRange() & TOUCH_10;
		case ELE11: getOutOfRange() & TOUCH_11;
		case ELEPROX: getOutOfRange() & TOUCH_PROX;
	}
}

// **********************************************************
// Donne l'etat du flag ACFF venant de la variable outOfRange
// Lit la variable si necessaire
// 0x02 0x03
// @Return l'etat du flag ACFF
// **********************************************************
bool GestionMPR121::isAutoConfigFailFlagFromRead(void) {
	if(!outOfRangeRead) {
		getOutOfRange();
	}
	return outOfRange & ACFF;
}

// **********************************************************
// Donne l'etat du flag ARFF venant de la variable outOfRange
// Lit la variable si necessaire
// 0x02 0x03
// @Return l'etat du flag ARFF
// **********************************************************
bool GestionMPR121::isAutoReConfigFailFlagFromRead(void) {
	if(!outOfRangeRead) {
		getOutOfRange();
	}
	return outOfRange & ARFF;
}

// ***********************************************************************************
// Donne l'etat du flag outofrange d'une electrode lu venant de la variable outOfRange
// Lit la variable si necessaire
// 0x02 0x03
// @Return l'etat du flag outofrange d'une electrode
// ***********************************************************************************
bool GestionMPR121::isOutOfRangeFromRead(Electrode electrode) {
	if(!outOfRangeRead) {
		getOutOfRange();
	}
	switch(electrode) {
		case ELE0:  outOfRange & TOUCH_0;
		case ELE1:  outOfRange & TOUCH_1;
		case ELE2:  outOfRange & TOUCH_2;
		case ELE3:  outOfRange & TOUCH_3;
		case ELE4:  outOfRange & TOUCH_4;
		case ELE5:  outOfRange & TOUCH_5;
		case ELE6:  outOfRange & TOUCH_6;
		case ELE7:  outOfRange & TOUCH_7;
		case ELE8:  outOfRange & TOUCH_8;
		case ELE9:  outOfRange & TOUCH_9;
		case ELE10: outOfRange & TOUCH_10;
		case ELE11: outOfRange & TOUCH_11;
		case ELEPROX: outOfRange & TOUCH_PROX;
	}
}


// *************************************************
// Lit toutes les donnees des electrodes en une fois
// 0x04 0x1D
// Permet une cohérence temporelle des donnees
// @Return la liste des donnees des electrodes
// *************************************************
std::list<int8_t> GestionMPR121::getAllElectrodeData(void) {
	dataRead = true;
	// !!!!!!ATTENTION!!!!!!
	// Je n'arrive pas a positionner le pointeur de donnees, la lecture d'un bloc demarre toujours au registre 0
	data = GestionI2C::readList(REG_TOUCH_STATUS_LSB, REG_ELEPROX_FILTERED_DATA_MSB + 1);
	// Retire les 4 premiers car on veut commencer au 5eme
	for(RegistreMpr121 reg = REG_TOUCH_STATUS_LSB; reg != REG_ELE0_FILTERED_DATA_LSB; ++reg) {
		data.pop_front();
	}
	return data;
}

// ***********************************************************************
// Donne les donnees d'une electrode lues par la methode getAllElectrodeData
// 0x04 0x1D
// @Param le numéro de l'electrode
// ***********************************************************************
uint16_t GestionMPR121::getElectrodeDataFromAllRead(Electrode electrode) {
	union electrodeTypeData{
		uint16_t uData;
		int8_t iData[2];
	};	
	electrodeTypeData electrodeData;
	
	// Si les donnees n'ont pas ete lues, on les lit
	if(!dataRead) {
		getAllElectrodeData();
	}
	
	// Recherche de la valeur dans la liste
	int compteur = 0;
	for (int8_t value : data) {
		if(compteur == electrode * 2) {
		  electrodeData.iData[0] = value;
		}
		if(compteur == electrode * 2 + 1) {
		  electrodeData.iData[1] = value;
		}
		compteur++;
	}
	return electrodeData.uData;
}

// *******************************************************
// Donne les donnees d'une electrode lues dans le registre
// 0x04 0x1D
// @Param le numéro de l'electrode
// @Remark flag error a true si electrode invalide
// *******************************************************
uint16_t GestionMPR121::getElectrodeDataFromRegister(Electrode electrode) {
	switch(electrode) {
		case ELE0:  return read16(REG_ELE0_FILTERED_DATA_LSB);
		case ELE1:  return read16(REG_ELE1_FILTERED_DATA_LSB);
		case ELE2:  return read16(REG_ELE2_FILTERED_DATA_LSB);
		case ELE3:  return read16(REG_ELE3_FILTERED_DATA_LSB);
		case ELE4:  return read16(REG_ELE4_FILTERED_DATA_LSB);
		case ELE5:  return read16(REG_ELE5_FILTERED_DATA_LSB);
		case ELE6:  return read16(REG_ELE6_FILTERED_DATA_LSB);
		case ELE7:  return read16(REG_ELE7_FILTERED_DATA_LSB);
		case ELE8:  return read16(REG_ELE8_FILTERED_DATA_LSB);
		case ELE9:  return read16(REG_ELE9_FILTERED_DATA_LSB);
		case ELE10: return read16(REG_ELE10_FILTERED_DATA_LSB);
		case ELE11: return read16(REG_ELE11_FILTERED_DATA_LSB);
		case ELEPROX: return read16(REG_ELEPROX_FILTERED_DATA_LSB);
	}
}

// ************************************************
// Lit toutes les donnees des baselines en une fois
// 0x1E 0x2A
// Permet une cohérence temporelle des donnees
// @Return la liste des donnees des baselines
// ************************************************
std::list<int8_t> GestionMPR121::getAllBaselineValue(void) {
	baselineRead = true;
	// !!!!!!ATTENTION!!!!!!
	// Je n'arrive pas a positionner le pointeur de donnees, la lecture d'un bloc demarre toujours au registre 0
	baseline = GestionI2C::readList(REG_TOUCH_STATUS_LSB, REG_ELEPROX_BASELINE + 1);
	// Retire les premiers car on veut commencer a baseline de element0
	for(RegistreMpr121 reg = REG_TOUCH_STATUS_LSB; reg != REG_ELE0_BASELINE; ++reg) {
		baseline.pop_front();
	}
	return baseline;
}

// ************************************************************************
// Donne les donnees d'une baseline lues par la methode getAllBaselineValue
// 0x1E 0x2A
// @Param le numéro de l'electrode
// @Remark flag error a true si electrode invalide
// ************************************************************************
uint8_t GestionMPR121::getBaselineValueFromAllRead(Electrode electrode) {
	// Si les donnees n'ont pas ete lues, on les lit
	if(!baselineRead) {
		getAllBaselineValue();
	}
	
	// Recherche de la valeur dans la liste
	int compteur = 0;
	for (int8_t value : baseline) {
		if(compteur == electrode) {
		  return value;
		}
		compteur++;
	}
}

// ******************************************************
// Donne les donnees d'une baseline lues dans le registre
// 0x1E 0x2A
// @Param le numéro de l'electrode
// @Remark flag error a true si electrode invalide
// ******************************************************
uint8_t GestionMPR121::getBaselineValueFromRegister(Electrode electrode) {
	switch(electrode) {
		case ELE0:  return read8(REG_ELE0_BASELINE);
		case ELE1:  return read8(REG_ELE1_BASELINE);
		case ELE2:  return read8(REG_ELE2_BASELINE);
		case ELE3:  return read8(REG_ELE3_BASELINE);
		case ELE4:  return read8(REG_ELE4_BASELINE);
		case ELE5:  return read8(REG_ELE5_BASELINE);
		case ELE6:  return read8(REG_ELE6_BASELINE);
		case ELE7:  return read8(REG_ELE7_BASELINE);
		case ELE8:  return read8(REG_ELE8_BASELINE);
		case ELE9:  return read8(REG_ELE9_BASELINE);
		case ELE10: return read8(REG_ELE10_BASELINE);
		case ELE11: return read8(REG_ELE11_BASELINE);
		case ELEPROX: return read8(REG_ELEPROX_BASELINE);
	}
}

// ***********************************************
// Positionne une baseline
// 0x1E 0x2A
// @Param le numéro de l'electrode
// @Remark flag error a true si electrode invalide
// ***********************************************
bool GestionMPR121::setBaselineValue(Electrode electrode, uint8_t value) {
	switch(electrode) {
		case ELE0:  return write8(REG_ELE0_BASELINE, value);
		case ELE1:  return write8(REG_ELE1_BASELINE, value);
		case ELE2:  return write8(REG_ELE2_BASELINE, value);
		case ELE3:  return write8(REG_ELE3_BASELINE, value);
		case ELE4:  return write8(REG_ELE4_BASELINE, value);
		case ELE5:  return write8(REG_ELE5_BASELINE, value);
		case ELE6:  return write8(REG_ELE6_BASELINE, value);
		case ELE7:  return write8(REG_ELE7_BASELINE, value);
		case ELE8:  return write8(REG_ELE8_BASELINE, value);
		case ELE9:  return write8(REG_ELE9_BASELINE, value);
		case ELE10: return write8(REG_ELE10_BASELINE, value);
		case ELE11: return write8(REG_ELE11_BASELINE, value);
		case ELEPROX: return write8(REG_ELEPROX_BASELINE, value);
	}	
}

// *********************************************************************************
// Lit d'un coup les registres de status, overflow, data et baseline
// Positionne les donnees dans les variables touchStatut, outOfRange, data, baseline
// Positionne les flag de lecture touchRead, outOfRangeRead, dataRead, baselineRead
// Recommender dans le datasheet, permer d'avoir un etat complet coherent
// 0x00 0x2A
// *********************************************************************************
void GestionMPR121::getFullData(void) {
	union data2Bytes{
		uint16_t uData;
		int8_t iData[2];
	};
	data2Bytes touchStatutData;
	data2Bytes outOfRangeData;
	
	// Lecture globale
	std::list<int8_t>readData = GestionI2C::readList(REG_TOUCH_STATUS_LSB, REG_ELEPROX_BASELINE + 1);
	
	// 0x00 - 0x01
	touchRead = true;
	touchStatutData.iData[0] = readData.front();
	readData.pop_front();
	touchStatutData.iData[1] = readData.front();
	readData.pop_front();
	touchStatut = touchStatutData.uData;
	
	// 0x02 - 0x03
	outOfRangeRead = true;
	outOfRangeData.iData[0] = readData.front();
	readData.pop_front();
	outOfRangeData.iData[1] = readData.front();
	readData.pop_front();
	outOfRange = outOfRangeData.uData;
	
	// 0x04 - 0x1D
	dataRead = true;
	data.clear();
	for(RegistreMpr121 reg = REG_ELE0_FILTERED_DATA_LSB; reg != REG_ELE0_BASELINE; ++reg) {
		data.push_back(readData.front());
		readData.pop_front();
	}

	// 0x1E - 0x2A
	baselineRead = true;
	baseline.clear();
	for(RegistreMpr121 reg = REG_ELE0_BASELINE; reg != REG_MHD_RISING; ++reg) {
		baseline.push_back(readData.front());
		readData.pop_front();
	}
}


// *********************
// Donne le MHD Rising
// 0x2B
// @Return le MHD Rising
// *********************
uint8_t GestionMPR121::getElementMaximumHalfDeltaRising(void) {
	return read8(REG_MHD_RISING);
}

// ***********************************
// Positionne le MHD Rising
// 0x2B
// @Param le MHD Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementMaximumHalfDeltaRising(uint8_t value) {
	return write8(REG_MHD_RISING, value);
}

// *********************
// Donne le NHD Rising
// 0x2C
// @Return le NHD Rising
// *********************
uint8_t GestionMPR121::getElementNoiseHalfDeltaRising(void) {
	return read8(REG_NHD_RISING);
}

// ***********************************
// Positionne le NHD Rising
// 0x2C
// @Param le NHD Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementNoiseHalfDeltaRising(uint8_t value) {
	return write8(REG_NHD_RISING, value);
}

// *********************
// Donne le NCL Rising
// 0x2D
// @Return le NCL Rising
// *********************
uint8_t GestionMPR121::getElementNoiseCountLimitRising(void) {
	return read8(REG_NCL_RISING);
}

// ***********************************
// Positionne le NCL Rising
// 0x2D
// @Param le NCL Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementNoiseCountLimitRising(uint8_t value) {
	return write8(REG_NCL_RISING, value);
}

// *********************
// Donne le FDL Rising
// 0x2E
// @Return le FDL Rising
// *********************
uint8_t GestionMPR121::getElementFilterDelayCountLimitRising(void) {
	return read8(REG_FDL_RISING);
}

// ***********************************
// Positionne le FDL Rising
// 0x2E
// @Param le FDL Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementFilterDelayCountLimitRising(uint8_t value) {
	return write8(REG_FDL_RISING, value);
}

// **********************
// Donne le MHD Falling
// 0x2F
// @Return le MHD Falling
// **********************
uint8_t GestionMPR121::getElementMaximumHalfDeltaFalling(void) {
	return read8(REG_MHD_FALLING);
}

// ***********************************
// Positionne le MHD Falling
// 0x2F
// @Param le MHD Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementMaximumHalfDeltaFalling(uint8_t value) {
	return write8(REG_MHD_FALLING, value);
}

// **********************
// Donne le NHD Falling
// 0x30
// @Return le NHD Falling
// **********************
uint8_t GestionMPR121::getElementNoiseHalfDeltaFalling(void) {
	return read8(REG_NHD_FALLING);
}

// ***********************************
// Positionne le NHD Falling
// 0x30
// @Param le NHD Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementNoiseHalfDeltaFalling(uint8_t value) {
	return write8(REG_NHD_FALLING, value);
}

// **********************
// Donne le NCL Falling
// 0x31
// @Return le NCL Falling
// **********************
uint8_t GestionMPR121::getElementNoiseCountLimitFalling(void) {
	return read8(REG_NCL_FALLING);
}

// ***********************************
// Positionne le NCL Falling
// 0x31
// @Param le NCL Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementNoiseCountLimitFalling(uint8_t value) {
	return write8(REG_NCL_FALLING, value);
}

// **********************
// Donne le FDL Falling
// 0x32
// @Return le FDL Falling
// **********************
uint8_t GestionMPR121::getElementFilterDelayCountLimitFalling(void) {
	return read8(REG_FDL_FALLING);
}

// ***********************************
// Positionne le FDL Falling
// 0x32
// @Param le FDL Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementFilterDelayCountLimitFalling(uint8_t value) {
	return write8(REG_FDL_FALLING, value);
}

// **********************
// Donne le NHD Touched
// 0x33
// @Return le NHD Touched
// **********************
uint8_t GestionMPR121::getElementNoiseHalfDeltaTouched(void) {
	return read8(REG_NHD_TOUCHED);
}

// ***********************************
// Positionne le NHD Touched
// 0x33
// @Param le NHD Touched
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementNoiseHalfDeltaTouched(uint8_t value) {
	return write8(REG_NHD_TOUCHED, value);
}

// **********************
// Donne le NCL Touched
// 0x34
// @Return le NCL Touched
// **********************
uint8_t GestionMPR121::getElementNoiseCountLimitTouched(void) {
	return read8(REG_NCL_TOUCHED);
}

// ***********************************
// Positionne le NCL Touched
// 0x34
// @Param le NCL Touched
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementNoiseCountLimitTouched(uint8_t value) {
	return write8(REG_NCL_TOUCHED, value);
}

// **********************
// Donne le FDL Touched
// 0x35
// @Return le FDL Touched
// **********************
uint8_t GestionMPR121::getElementFilterDelayCountLimitTouched(void) {
	return read8(REG_FDL_TOUCHED);
}

// ***********************************
// Positionne le FDL Touched
// 0x35
// @Param le FDL Touched
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setElementFilterDelayCountLimitTouched(uint8_t value) {
	return write8(REG_FDL_TOUCHED, value);
}

// *********************
// Donne le MHD Rising
// 0x36
// @Return le MHD Rising
// *********************
uint8_t GestionMPR121::getEleProximityMaximumHalfDeltaRising(void) {
	return read8(REG_ELEPROX_MHD_RISING);
}

// ***********************************
// Positionne le MHD Rising
// 0x36
// @Param le MHD Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityMaximumHalfDeltaRising(uint8_t value) {
	return write8(REG_ELEPROX_MHD_RISING, value);
}

// *********************
// Donne le NHD Rising
// 0x37
// @Return le NHD Rising
// *********************
uint8_t GestionMPR121::getEleProximityNoiseHalfDeltaRising(void) {
	return read8(REG_ELEPROX_NHD_RISING);
}

// ***********************************
// Positionne le NHD Rising
// 0x37
// @Param le NHD Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityNoiseHalfDeltaRising(uint8_t value) {
	return write8(REG_ELEPROX_NHD_RISING, value);
}

// *********************
// Donne le NCL Rising
// 0x38
// @Return le NCL Rising
// *********************
uint8_t GestionMPR121::getEleProximityNoiseCountLimitRising(void) {
	return read8(REG_ELEPROX_NCL_RISING);
}

// ***********************************
// Positionne le NCL Rising
// 0x38
// @Param le NCL Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityNoiseCountLimitRising(uint8_t value) {
	return write8(REG_ELEPROX_NCL_RISING, value);
}

// *********************
// Donne le FDL Rising
// 0x39
// @Return le FDL Rising
// *********************
uint8_t GestionMPR121::getEleProximityFilterDelayCountLimitRising(void) {
	return read8(REG_ELEPROX_FDL_RISING);
}

// ***********************************
// Positionne le FDL Rising
// 0x39
// @Param le FDL Rising
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityFilterDelayCountLimitRising(uint8_t value) {
	return write8(REG_ELEPROX_FDL_RISING, value);
}

// **********************
// Donne le MHD Falling
// 0x3A
// @Return le MHD Falling
// **********************
uint8_t GestionMPR121::getEleProximityMaximumHalfDeltaFalling(void) {
	return read8(REG_ELEPROX_MHD_FALLING);
}

// ***********************************
// Positionne le MHD Falling
// 0x3A
// @Param le MHD Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityMaximumHalfDeltaFalling(uint8_t value) {
	return write8(REG_ELEPROX_MHD_FALLING, value);
}

// **********************
// Donne le NHD Falling
// 0x3B
// @Return le NHD Falling
// **********************
uint8_t GestionMPR121::getEleProximityNoiseHalfDeltaFalling(void) {
	return read8(REG_ELEPROX_NHD_FALLING);
}

// ***********************************
// Positionne le NHD Falling
// 0x3V
// @Param le NHD Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityNoiseHalfDeltaFalling(uint8_t value) {
	return write8(REG_ELEPROX_NHD_FALLING, value);
}

// **********************
// Donne le NCL Falling
// 0x3C
// @Return le NCL Falling
// **********************
uint8_t GestionMPR121::getEleProximityNoiseCountLimitFalling(void) {
	return read8(REG_ELEPROX_NCL_FALLING);
}

// ***********************************
// Positionne le NCL Falling
// 0x3C
// @Param le NCL Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityNoiseCountLimitFalling(uint8_t value) {
	return write8(REG_ELEPROX_NCL_FALLING, value);
}

// **********************
// Donne le FDL Falling
// 0x3D
// @Return le FDL Falling
// **********************
uint8_t GestionMPR121::getEleProximityFilterDelayCountLimitFalling(void) {
	return read8(REG_ELEPROX_FDL_FALLING);
}

// ***********************************
// Positionne le FDL Falling
// 0x3D
// @Param le FDL Falling
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityFilterDelayCountLimitFalling(uint8_t value) {
	return write8(REG_ELEPROX_FDL_FALLING, value);
}

// **********************
// Donne le NHD Touched
// 0x3E
// @Return le NHD Touched
// **********************
uint8_t GestionMPR121::getEleProximityNoiseHalfDeltaTouched(void) {
	return read8(REG_ELEPROX_NHD_TOUCHED);
}

// ***********************************
// Positionne le NHD Touched
// 0x3E
// @Param le NHD Touched
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityNoiseHalfDeltaTouched(uint8_t value) {
	return write8(REG_ELEPROX_NHD_TOUCHED, value);
}

// **********************
// Donne le NCL Touched
// 0x3F
// @Return le NCL Touched
// **********************
uint8_t GestionMPR121::getEleProximityNoiseCountLimitTouched(void) {
	return read8(REG_ELEPROX_NCL_TOUCHED);
}

// ***********************************
// Positionne le NCL Touched
// 0x3F
// @Param le NCL Touched
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityNoiseCountLimitTouched(uint8_t value) {
	return write8(REG_ELEPROX_NCL_TOUCHED, value);
}

// **********************
// Donne le FDL Touched
// 0x40
// @Return le FDL Touched
// **********************
uint8_t GestionMPR121::getEleProximityFilterDelayCountLimitTouched(void) {
	return read8(REG_ELEPROX_FDL_TOUCHED);
}

// ***********************************
// Positionne le FDL Touched
// 0x40
// @Param le FDL Touched
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setEleProximityFilterDelayCountLimitTouched(uint8_t value) {
	return write8(REG_ELEPROX_FDL_TOUCHED, value);
}

// **************************************************
// Donne le seuil de declenchement pour une electrode
// 0x41 0x5A
// @Param le numero de la touche
// @Return la valeur du seuil
// @Remark flag error a true si electrode invalide
// **************************************************
uint8_t GestionMPR121::getTouchThreshold(Electrode electrode) {
	switch(electrode) {
		case ELE0:	return read8(REG_ELE0_TOUCH_THRESHOLD); 
		case ELE1:	return read8(REG_ELE1_TOUCH_THRESHOLD); 
		case ELE2:	return read8(REG_ELE2_TOUCH_THRESHOLD); 
		case ELE3:	return read8(REG_ELE3_TOUCH_THRESHOLD); 
		case ELE4:	return read8(REG_ELE4_TOUCH_THRESHOLD); 
		case ELE5:	return read8(REG_ELE5_TOUCH_THRESHOLD); 
		case ELE6:	return read8(REG_ELE6_TOUCH_THRESHOLD); 
		case ELE7:	return read8(REG_ELE7_TOUCH_THRESHOLD); 
		case ELE8:	return read8(REG_ELE8_TOUCH_THRESHOLD); 
		case ELE9:	return read8(REG_ELE9_TOUCH_THRESHOLD); 
		case ELE10: return read8(REG_ELE10_TOUCH_THRESHOLD); 
		case ELE11: return read8(REG_ELE11_TOUCH_THRESHOLD); 
		case ELEPROX: return read8(REG_ELEPROX_TOUCH_THRESHOLD); 
	}
}

// ***************************************************************
// Positionne le seuil de declenchement pour toutes les electrodes
// 0x41 0x5A
// @Param la valeur du seuil
// @Return la bonne execution des write
// ***************************************************************		
bool GestionMPR121::setAllTouchThreshold(uint8_t value) {
	bool result = true;
	for(Electrode electrode = ELE0; electrode != ELEPROX; ++electrode) {
		result &= setTouchThreshold(electrode, value);
	}
	return result;
	
}

// *******************************************************
// Positionne le seuil de declenchement pour une electrode
// 0x41 0x5A
// @Param le numero de la touche
// @Param la valeur du seuil
// @Return la bonne execution du write
// *******************************************************
bool GestionMPR121::setTouchThreshold(Electrode electrode, uint8_t value) {
	switch(electrode) {
		case ELE0:	return write8(REG_ELE0_TOUCH_THRESHOLD, value); 
		case ELE1:	return write8(REG_ELE1_TOUCH_THRESHOLD, value); 
		case ELE2:	return write8(REG_ELE2_TOUCH_THRESHOLD, value); 
		case ELE3:	return write8(REG_ELE3_TOUCH_THRESHOLD, value); 
		case ELE4:	return write8(REG_ELE4_TOUCH_THRESHOLD, value); 
		case ELE5:	return write8(REG_ELE5_TOUCH_THRESHOLD, value); 
		case ELE6:	return write8(REG_ELE6_TOUCH_THRESHOLD, value); 
		case ELE7:	return write8(REG_ELE7_TOUCH_THRESHOLD, value); 
		case ELE8:	return write8(REG_ELE8_TOUCH_THRESHOLD, value); 
		case ELE9:	return write8(REG_ELE9_TOUCH_THRESHOLD, value); 
		case ELE10: return write8(REG_ELE10_TOUCH_THRESHOLD, value); 
		case ELE11: return write8(REG_ELE11_TOUCH_THRESHOLD, value); 
		case ELEPROX: return write8(REG_ELEPROX_TOUCH_THRESHOLD, value); 
	}
}

// ************************************************
// Donne le seuil de relachement pour une electrode
// 0x41 0x5A
// @Param le numero de la touche
// @Return la valeur du seuil
// @Remark flag error a true si electrode invalide
// ************************************************
uint8_t GestionMPR121::getReleaseThreshold(Electrode electrode) {
	error = false;
	switch(electrode) {
		case ELE0:	return read8(REG_ELE0_RELEASE_THRESHOLD); 
		case ELE1:	return read8(REG_ELE1_RELEASE_THRESHOLD); 
		case ELE2:	return read8(REG_ELE2_RELEASE_THRESHOLD); 
		case ELE3:	return read8(REG_ELE3_RELEASE_THRESHOLD); 
		case ELE4:	return read8(REG_ELE4_RELEASE_THRESHOLD); 
		case ELE5:	return read8(REG_ELE5_RELEASE_THRESHOLD); 
		case ELE6:	return read8(REG_ELE6_RELEASE_THRESHOLD); 
		case ELE7:	return read8(REG_ELE7_RELEASE_THRESHOLD); 
		case ELE8:	return read8(REG_ELE8_RELEASE_THRESHOLD); 
		case ELE9:	return read8(REG_ELE9_RELEASE_THRESHOLD); 
		case ELE10: return read8(REG_ELE10_RELEASE_THRESHOLD); 
		case ELE11: return read8(REG_ELE11_RELEASE_THRESHOLD); 
		case ELEPROX: return read8(REG_ELEPROX_RELEASE_THRESHOLD); 
		default: error = true; return 0;
	}
}

// *************************************************************
// Positionne le seuil de relachement pour toutes les electrodes
// 0x41 0x5A
// @Param la valeur du seuil
// @Return la bonne execution des write
// *************************************************************		
bool GestionMPR121::setAllReleaseThreshold(uint8_t value) {
	bool result = true;
	for(Electrode electrode = ELE0; electrode != ELEPROX; ++electrode) {
		result &= setReleaseThreshold(electrode, value);
	}
	return result;
	
}

// *****************************************************
// Positionne le seuil de relachement pour une electrode
// 0x41 0x5A
// @Param le numero de la touche
// @Param la valeur du seuil
// @Return la bonne execution du write
// @Remark flag error a true si electrode invalide
// *****************************************************
bool GestionMPR121::setReleaseThreshold(Electrode electrode, uint8_t value) {
	error = false;
	switch(electrode) {
		case ELE0:	return write8(REG_ELE0_RELEASE_THRESHOLD, value); 
		case ELE1:	return write8(REG_ELE1_RELEASE_THRESHOLD, value); 
		case ELE2:	return write8(REG_ELE2_RELEASE_THRESHOLD, value); 
		case ELE3:	return write8(REG_ELE3_RELEASE_THRESHOLD, value); 
		case ELE4:	return write8(REG_ELE4_RELEASE_THRESHOLD, value); 
		case ELE5:	return write8(REG_ELE5_RELEASE_THRESHOLD, value); 
		case ELE6:	return write8(REG_ELE6_RELEASE_THRESHOLD, value); 
		case ELE7:	return write8(REG_ELE7_RELEASE_THRESHOLD, value); 
		case ELE8:	return write8(REG_ELE8_RELEASE_THRESHOLD, value); 
		case ELE9:	return write8(REG_ELE9_RELEASE_THRESHOLD, value); 
		case ELE10: return write8(REG_ELE10_RELEASE_THRESHOLD, value); 
		case ELE11: return write8(REG_ELE11_RELEASE_THRESHOLD, value); 
		case ELEPROX: return write8(REG_ELEPROX_RELEASE_THRESHOLD, value); 
		default: error = true; return false;
	}
}

// *******************************************************
// Donne le nombre d'appui sur une touche pour l'activer
// 0x5B
// @Return le nombre d'appui sur une touche pour l'activer
// *******************************************************
uint8_t GestionMPR121::getTouchDebounce(void) {
	switch(read8(REG_DEBOUNCE_TOUCH_AND_RELEASE) & TOUCH_DEBOUNCE) {
		case TOUCH_DEBOUNCE_0: return 0;
		case TOUCH_DEBOUNCE_1: return 1;
		case TOUCH_DEBOUNCE_2: return 2;
		case TOUCH_DEBOUNCE_3: return 3;
		case TOUCH_DEBOUNCE_4: return 4;
		case TOUCH_DEBOUNCE_5: return 5;
		case TOUCH_DEBOUNCE_6: return 6;
		case TOUCH_DEBOUNCE_7: return 7;
	}
}

// **********************************************************
// Donne le nombre d'appui sur une touche pour la deactiver
// 0x5B
// @Return le nombre d'appui sur une touche pour la deactiver
// **********************************************************
uint8_t GestionMPR121::getReleaseDebounce(void) {
	switch(read8(REG_DEBOUNCE_TOUCH_AND_RELEASE) & RELEASE_DEBOUNCE) {
		case RELEASE_DEBOUNCE_0: return 0;
		case RELEASE_DEBOUNCE_1: return 1;
		case RELEASE_DEBOUNCE_2: return 2;
		case RELEASE_DEBOUNCE_3: return 3;
		case RELEASE_DEBOUNCE_4: return 4;
		case RELEASE_DEBOUNCE_5: return 5;
		case RELEASE_DEBOUNCE_6: return 6;
		case RELEASE_DEBOUNCE_7: return 7;
	}
}

// **************************************************************************
// Positionne le nombre d'appui sur une touche pour l'activer ou la deactiver
// 0x5B
// @Param le nombre d'appui sur une touche pour l'activer
// @Param le nombre d'appui sur une touche pour la deactiver
// @Return la bonne execution du write
// **************************************************************************
bool GestionMPR121::setTouchReleaseDebounce(TouchDebounce touch, ReleaseDebounce release) {
	return write8(REG_DEBOUNCE_TOUCH_AND_RELEASE, touch | release);
}

// ********************************************
// Donne le First Filter Iterations
// 0x5C
// @Return la valeur du First Filter Iterations
// ********************************************
FirstFilterIterations GestionMPR121::getFirstFilterIterations(void) {
	switch(read8(REG_AFE_CONFIGURATION1) & FFI) {
		case FFI6Samples:  return FFI6Samples;
		case FFI10Samples: return FFI10Samples;
		case FFI18Samples: return FFI18Samples;
		case FFI34Samples: return FFI34Samples;
	}	
}

// ***********************************************
// Donne le courant de charge decharge
// 0x5C
// @Return la valeur du courant de charge decharge
// ***********************************************
ChargeDischargeCurrent GestionMPR121::getChargeDisChargeCurrent(void) {
	return static_cast<ChargeDischargeCurrent>(read8(REG_AFE_CONFIGURATION1) & CDC);
}

// *********************************************
// Donne le temps de charge decharge
// 0x5D
// @Return la valeur du temps de charge decharge
// *********************************************
ChargeDischargeTime GestionMPR121::getChargeDischargeTime(void) {
	switch(read8(REG_AFE_CONFIGURATION2) & CDT) {
		case CDTInvalid: return CDTInvalid;
		case CDT05US:    return CDT05US;
		case CDT1US:     return CDT1US;
		case CDT2US:     return CDT2US;
		case CDT4US:     return CDT4US;
		case CDT8US:     return CDT8US;
		case CDT16US:    return CDT16US;
		case CDT32US:    return CDT32US;
	}
}

// *********************************************
// Donne le Second Filter Iterations
// 0x5D
// @Return la valeur du Second Filter Iterations
// *********************************************
SecondFilterIterations GestionMPR121::getSecondFilterIterations(void) {
	switch(read8(REG_AFE_CONFIGURATION2) & SFI) {
		case SFI4:  return SFI4;
		case SFI6:  return SFI6;
		case SFI10: return SFI10;
		case SFI18: return SFI18;
	}
}

// ************************************************
// Donne le Electrode Sample Interval
// 0x5D
// @Return la valeur de l'Electrode Sample Interval
// ************************************************
ElectrodeSampleInterval GestionMPR121::getElectrodeSampleInterval(void) {
	switch(read8(REG_AFE_CONFIGURATION2) & ESI) {
		case ESI1:   return ESI1;
		case ESI2:   return ESI2;
		case ESI4:   return ESI4;
		case ESI8:   return ESI8;
		case ESI16:  return ESI16;
		case ESI32:  return ESI32;
		case ESI64:  return ESI64;
		case ESI128: return ESI128;
	}
}

// *************************************************************************************************************************************************************
// Positionne les valeurs des First Filter Iterations, courant de charge decharge, temps de charge decharge, Second Filter Iterations, Electrode Sample Interval
// 0x5C 0x5D
// @Param First Filter Iterations
// @Param Courant de charge decharge
// @Param Temps de charge decharge (CDC global si CDC individuel non utilise 0x5F 0x6B)
// @Param Second Filter Iterations
// @Param Electrode Sample Interval
// @Return la bonne execution du write
// *************************************************************************************************************************************************************
bool GestionMPR121::setAFEConfiguration(FirstFilterIterations ffi, ChargeDischargeCurrent cdc, ChargeDischargeTime cdt, SecondFilterIterations sfi, ElectrodeSampleInterval esi) {
	return write8(REG_AFE_CONFIGURATION1, ffi | cdc) & write8(REG_AFE_CONFIGURATION2, cdt | sfi | esi);	
}

// *******************************************
// Donne la mise a jour du registre baseline
// 0x5E
// @Return la mise a jour du registre baseline
// *******************************************
CalibrationLockBit GestionMPR121::getCalibrationLockBit(void) {
	switch(read8(REG_ELECTRODE_CONFIGURATION) & CALIBRATION_LOCK_BIT) {
		case BASELINE_TRACKING_ENABLE:                 return BASELINE_TRACKING_ENABLE;
		case CALIBRATION_LOCK:                         return CALIBRATION_LOCK;
		case BASELINE_TRACKING_AND_INITIALIZE_ENABLE1: return BASELINE_TRACKING_AND_INITIALIZE_ENABLE1;
		case BASELINE_TRACKING_AND_INITIALIZE_ENABLE2: return BASELINE_TRACKING_AND_INITIALIZE_ENABLE2;
	}
}

// ***************************************************************
// Donne les electrodes utilisees pour la detection de proximite
// 0x5E
// @Return les electrodes utilisees pour la detection de proximite
// ***************************************************************
ElectrodeProximityElectrode GestionMPR121::getElectrodeProximityElectrode(void) {
	switch(read8(REG_ELECTRODE_CONFIGURATION) & ELEPROX_BIT) {
		case ELEPROX_DISABLED: return ELEPROX_DISABLED;
		case ELEPROX0_1:       return ELEPROX0_1;
		case ELEPROX0_3:       return ELEPROX0_3;
		case ELEPROX0_11:      return ELEPROX0_11;
	}
}

// ******************************************************
// Donne les electrodes utilisees pour la mesure simple
// 0x5E
// @Return les electrodes utilisees pour la mesure simple
// ******************************************************
ElectrodeEnabled GestionMPR121::getElectrodeEnabled(void) {
	switch(read8(REG_ELECTRODE_CONFIGURATION) & ELE_BIT) {
		case ELECTRODE_DISABLED: return ELECTRODE_DISABLED;
		case ELECTRODE0:         return ELECTRODE0;
		case ELECTRODE0_1:       return ELECTRODE0_1;
		case ELECTRODE0_2:       return ELECTRODE0_2;
		case ELECTRODE0_3:       return ELECTRODE0_3;
		case ELECTRODE0_4:       return ELECTRODE0_4;
		case ELECTRODE0_5:       return ELECTRODE0_5;
		case ELECTRODE0_6:       return ELECTRODE0_6;
		case ELECTRODE0_7:       return ELECTRODE0_7;
		case ELECTRODE0_8:       return ELECTRODE0_8;
		case ELECTRODE0_9:       return ELECTRODE0_9;
		case ELECTRODE0_10:      return ELECTRODE0_10;
		case ELECTRODE0_11:      return ELECTRODE0_11;
	}	
}

// ********************************************************************************************************************************************************************
// Positionne les valeurs des mise a jour du registre baseline, les electrodes utilisees pour la detection de proximite, les electrodes utilisees pour la mesure simple
// 0x5E
// @Param la valeur des mise a jour du registre baseline
// @Param les electrodes utilisees pour la detection de proximite
// @Param les electrodes utilisees pour la mesure simple
// @Remark si aucune electrode utilisee pour la detection et les mesures alors le module est en mode stop, sinon il est en mode run
// @Return la bonne execution du write
// ********************************************************************************************************************************************************************
bool GestionMPR121::setElectrodeConfiguration(CalibrationLockBit cl, ElectrodeProximityElectrode eleprox, ElectrodeEnabled ele) {
	return write8(REG_ELECTRODE_CONFIGURATION, cl| eleprox | ele );
}

// ************************************************************
// Passe le module en mode stop en n'utilisant aucune electrode
// 0x5E
// @Return la bonne execution du write
// ************************************************************
bool GestionMPR121::stop(void) {
	return write8(REG_ELECTRODE_CONFIGURATION, BASELINE_TRACKING_ENABLE | ELEPROX_DISABLED | ELECTRODE_DISABLED);	
}

// ************************************************************************************************************************************************
// Passe le module en mode run en indiquant les electrodes utilisees pour la detection de proximite, les electrodes utilisees pour la mesure simple
// 0x5E
// @Param les electrodes utilisees pour la detection de proximite
// @Param les electrodes utilisees pour la mesure simple
// @Remark si aucune electrode utilisee pour la detection et les mesures alors le module est en mode stop, sinon il est en mode run
// @Return la bonne execution du write
// *************************************************************************************************************************************************
bool GestionMPR121::run(ElectrodeProximityElectrode eleprox, ElectrodeEnabled ele) {
	return write8(REG_ELECTRODE_CONFIGURATION, BASELINE_TRACKING_ENABLE| eleprox | ele );
}

// ************************************************************************************
// Donne le CDC individuel pour chaque electrode si 0 alors CDC global est utilise 0x5C
// Charge par l'Auto Config si active
// 0x5F 0x6A
// @Param le numero de l'electrode
// @Return la valeur du CDC de l'electrode
// @Remark flag error a true si electrode invalide
// ************************************************************************************
ChargeDischargeCurrent GestionMPR121::getElectrodeChargeCurrent(Electrode electrode) {
	error = false;
	switch(electrode) {
		case ELE0:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE0_ELECTRODE_CURRENT)); 
		case ELE1:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE1_ELECTRODE_CURRENT)); 
		case ELE2:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE2_ELECTRODE_CURRENT)); 
		case ELE3:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE3_ELECTRODE_CURRENT)); 
		case ELE4:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE4_ELECTRODE_CURRENT)); 
		case ELE5:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE5_ELECTRODE_CURRENT)); 
		case ELE6:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE6_ELECTRODE_CURRENT)); 
		case ELE7:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE7_ELECTRODE_CURRENT)); 
		case ELE8:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE8_ELECTRODE_CURRENT)); 
		case ELE9:	return static_cast<ChargeDischargeCurrent>(read8(REG_ELE9_ELECTRODE_CURRENT)); 
		case ELE10: return static_cast<ChargeDischargeCurrent>(read8(REG_ELE10_ELECTRODE_CURRENT)); 
		case ELE11: return static_cast<ChargeDischargeCurrent>(read8(REG_ELE11_ELECTRODE_CURRENT)); 
		default: error = true; return CDC0;
	}
}

// *****************************************************************************************
// Positionne le CDC individuel pour chaque electrode si 0 alors CDC global est utilise 0x5C
// Charge par l'Auto Config si active
// 0x5F 0x6A
// @Param le numero de l'electrode
// @Param la valeur (0 a 63)
// @Return la bonne execution du write
// *****************************************************************************************
bool GestionMPR121::setElectrodeChargeCurrent(Electrode electrode, ChargeDischargeCurrent value) {
	error = false;
	switch(electrode) {
		case ELE0:	return write8(REG_ELE0_ELECTRODE_CURRENT, value); 
		case ELE1:	return write8(REG_ELE1_ELECTRODE_CURRENT, value); 
		case ELE2:	return write8(REG_ELE2_ELECTRODE_CURRENT, value); 
		case ELE3:	return write8(REG_ELE3_ELECTRODE_CURRENT, value); 
		case ELE4:	return write8(REG_ELE4_ELECTRODE_CURRENT, value); 
		case ELE5:	return write8(REG_ELE5_ELECTRODE_CURRENT, value); 
		case ELE6:	return write8(REG_ELE6_ELECTRODE_CURRENT, value); 
		case ELE7:	return write8(REG_ELE7_ELECTRODE_CURRENT, value); 
		case ELE8:  return write8(REG_ELE8_ELECTRODE_CURRENT, value); 
		case ELE9:	return write8(REG_ELE9_ELECTRODE_CURRENT, value); 
		case ELE10: return write8(REG_ELE10_ELECTRODE_CURRENT, value); 
		case ELE11: return write8(REG_ELE11_ELECTRODE_CURRENT, value); 
		default: error = true; return false;
	}
}

// ***************************************************************************************
// Donne le CDC individuel pour electrode proximity si 0 alors CDC global est utilise 0x5C
// Charge par l'Auto Config si active
// 0x6B
// @Return la valeur du CDC de l'electrode proximity
// ***************************************************************************************
ChargeDischargeCurrent GestionMPR121::getElectrodeProximityChargeCurrent(void) {
	return static_cast<ChargeDischargeCurrent>(read8(REG_ELEPROX_ELECTRODE_CURRENT)); 
}

// **********************************************************************************************
// Positionne le CDC individuel pour l'electrode proximity si 0 alors CDC global est utilise 0x5C
// Charge par l'Auto Config si active
// 0x6B
// @Param la valeur (0 a 63)
// @Return la bonne execution du write
// **********************************************************************************************
bool GestionMPR121::setElectrodeProximityChargeCurrent(ChargeDischargeCurrent value) {
	return write8(REG_ELEPROX_ELECTRODE_CURRENT, value); 
}

// ************************************************************************************
// Donne le CDT individuel pour chaque electrode si 0 alors CDT global est utilise 0x5D
// Charge par l'Auto Config si active
// 0x6C 0x71
// @Param le numero de l'electrode
// @Return la valeur du CDT de l'electrode
// @Remark flag error a true si electrode invalide
// ************************************************************************************
ChargeDischargeTime GestionMPR121::getElectrodeChargeTime(Electrode electrode) {
	error = false;
	uint8_t chargeDischargeTime;
	switch(electrode) {
		case ELE0:	chargeDischargeTime = (read8(REG_ELE0_ELE1_CHARGE_TIME) & ChargeTime0_2_4_6_8_10) << 4; 
		case ELE1:	chargeDischargeTime = read8(REG_ELE0_ELE1_CHARGE_TIME) & ChargeTime1_3_5_7_9_11; 
		case ELE2:	chargeDischargeTime = (read8(REG_ELE2_ELE3_CHARGE_TIME) & ChargeTime0_2_4_6_8_10) << 4; 
		case ELE3:	chargeDischargeTime = read8(REG_ELE2_ELE3_CHARGE_TIME) & ChargeTime1_3_5_7_9_11; 
		case ELE4:	chargeDischargeTime = (read8(REG_ELE4_ELE5_CHARGE_TIME) & ChargeTime0_2_4_6_8_10) << 4; 
		case ELE5:	chargeDischargeTime = read8(REG_ELE4_ELE5_CHARGE_TIME) & ChargeTime1_3_5_7_9_11; 
		case ELE6:	chargeDischargeTime = (read8(REG_ELE6_ELE7_CHARGE_TIME) & ChargeTime0_2_4_6_8_10) << 4; 
		case ELE7:	chargeDischargeTime = read8(REG_ELE6_ELE7_CHARGE_TIME) & ChargeTime1_3_5_7_9_11; 
		case ELE8:	chargeDischargeTime = (read8(REG_ELE8_ELE9_CHARGE_TIME) & ChargeTime0_2_4_6_8_10) << 4; 
		case ELE9:	chargeDischargeTime = read8(REG_ELE8_ELE9_CHARGE_TIME) & ChargeTime1_3_5_7_9_11; 
		case ELE10: chargeDischargeTime = (read8(REG_ELE10_ELE11_CHARGE_TIME) & ChargeTime0_2_4_6_8_10) << 4;  
		case ELE11: chargeDischargeTime = read8(REG_ELE10_ELE11_CHARGE_TIME) & ChargeTime1_3_5_7_9_11; 
		default: error = true; return CDTInvalid;
	}
	switch(chargeDischargeTime) {
		case CDTInvalid: return CDTInvalid;
		case CDT05US:    return CDT05US;
		case CDT1US:     return CDT1US;
		case CDT2US:     return CDT2US;
		case CDT4US:     return CDT4US;
		case CDT8US:     return CDT8US;
		case CDT16US:    return CDT16US;
		case CDT32US:    return CDT32US;
		default: error = true; return CDTInvalid;
	}
}

// *****************************************************************************************
// Positionne le CDT individuel pour chaque electrode si 0 alors CDT global est utilise 0x5D
// Charge par l'Auto Config si active
// 0x6C 0x71
// @Param le numero de l'electrode
// @Param la valeur
// @Return la bonne execution du write
// @Remark flag error a true si electrode invalide
// *****************************************************************************************
bool GestionMPR121::setElectrodeChargeTime(Electrode electrode, ChargeDischargeTime cdt) {
	error = false;
	switch(electrode) {
		case ELE0:	return write8(REG_ELE0_ELE1_CHARGE_TIME, read8(REG_ELE0_ELE1_CHARGE_TIME) & ChargeTime1_3_5_7_9_11 | (cdt >> 4)); 
		case ELE1:	return write8(REG_ELE0_ELE1_CHARGE_TIME, read8(REG_ELE0_ELE1_CHARGE_TIME) & ChargeTime0_2_4_6_8_10 | cdt); 
		case ELE2:	return write8(REG_ELE2_ELE3_CHARGE_TIME, read8(REG_ELE2_ELE3_CHARGE_TIME) & ChargeTime1_3_5_7_9_11 | (cdt >> 4)); 
		case ELE3:	return write8(REG_ELE2_ELE3_CHARGE_TIME, read8(REG_ELE2_ELE3_CHARGE_TIME) & ChargeTime0_2_4_6_8_10 | cdt); 
		case ELE4:	return write8(REG_ELE4_ELE5_CHARGE_TIME, read8(REG_ELE4_ELE5_CHARGE_TIME) & ChargeTime1_3_5_7_9_11 | (cdt >> 4)); 
		case ELE5:	return write8(REG_ELE4_ELE5_CHARGE_TIME, read8(REG_ELE4_ELE5_CHARGE_TIME) & ChargeTime0_2_4_6_8_10 | cdt); 
		case ELE6:	return write8(REG_ELE6_ELE7_CHARGE_TIME, read8(REG_ELE6_ELE7_CHARGE_TIME) & ChargeTime1_3_5_7_9_11 | (cdt >> 4)); 
		case ELE7:	return write8(REG_ELE6_ELE7_CHARGE_TIME, read8(REG_ELE6_ELE7_CHARGE_TIME) & ChargeTime0_2_4_6_8_10 | cdt); 
		case ELE8:	return write8(REG_ELE8_ELE9_CHARGE_TIME, read8(REG_ELE8_ELE9_CHARGE_TIME) & ChargeTime1_3_5_7_9_11 | (cdt >> 4)); 
		case ELE9:	return write8(REG_ELE8_ELE9_CHARGE_TIME, read8(REG_ELE8_ELE9_CHARGE_TIME) & ChargeTime0_2_4_6_8_10 | cdt); 
		case ELE10: return write8(REG_ELE10_ELE11_CHARGE_TIME, read8(REG_ELE10_ELE11_CHARGE_TIME) & ChargeTime1_3_5_7_9_11 | (cdt >> 4)); 
		case ELE11: return write8(REG_ELE10_ELE11_CHARGE_TIME, read8(REG_ELE10_ELE11_CHARGE_TIME) & ChargeTime0_2_4_6_8_10 | cdt); 
		default: error = true; return false;
	}
}

// ***************************************************************************************
// Donne le CDT individuel pour electrode proximity si 0 alors CDT global est utilise 0x5D
// Charge par l'Auto Config si active
// 0x72
// @Return la valeur du CDT de l'electrode proximity
// ***************************************************************************************
ChargeDischargeTime GestionMPR121::getElectrodeProximityChargeTime(void) {
	uint8_t chargeDischargeTime;

	switch(chargeDischargeTime) {
		case CDTInvalid: return CDTInvalid;
		case CDT05US:    return CDT05US;
		case CDT1US:     return CDT1US;
		case CDT2US:     return CDT2US;
		case CDT4US:     return CDT4US;
		case CDT8US:     return CDT8US;
		case CDT16US:    return CDT16US;
		case CDT32US:    return CDT32US;
		default: error = true; return CDTInvalid;
	}
}

// **********************************************************************************************
// Positionne le CDT individuel pour l'electrode proximity si 0 alors CDT global est utilise 0x5D
// Charge par l'Auto Config si active
// 0x72
// @Param la valeur
// @Return la bonne execution du write
// **********************************************************************************************
bool GestionMPR121::setElectrodeProximityChargeTime(ChargeDischargeTime cdt) {
	return write8(REG_ELEPROX_CHARGE_TIME, cdt >> 4); 
}

// ****************************************
// Donne la fonction programmee sur un gpio
// 0x73 0x74 0x76 0x77
// @Param le gpio
// @Return la fonction du gpio
// ****************************************
GPIOFunction GestionMPR121::getGPIOFunction(GPIONumber gpio) {
	// Si enabled a 0 alors gpio desactive
	if(!read8(REG_GPIO_ENABLE) & gpio) {
		return GPIODisabled;
	}
	// Direction
	if(read8(REG_GPIO_DIRECTION_CONTROL) & gpio) {
		// Si direction a 1 output
		switch(read8(REG_GPIO_CONTROL_0) & gpio) {
			// Si control0 a 0 input port
			case 0:  return GPIOInput;
			default: switch(read8(REG_GPIO_CONTROL_1) & gpio) {
						case 0:  return GPIOInputPullDown;
						default: return GPIOInputPullUp;
					}
		}
	} else {
		// Si direction a 0 input
		switch(read8(REG_GPIO_CONTROL_1) & gpio) {
			// Si control0 a 0 output port
			case 0:  return GPIOOutput;
			default: switch(read8(REG_GPIO_CONTROL_1) & gpio) {
						case 0:  return GPIOOutputLowSideMOS;
						default: return GPIOOutputHighSideMOS;
					}
		}
	}
}

// ****************************************
// Positionne la fonction programmee sur les gpio
// 0x73 0x74 0x76 0x77
// @Param le gpio7
// @Param le gpio6
// @Param le gpio5
// @Param le gpio4
// @Param le gpio3
// @Param le gpio2
// @Param le gpio1
// @Param le gpio0
// @Return la bonne execution du write
// ****************************************	
bool GestionMPR121::setGPIOFunction(GPIOFunction functionGPIO7, GPIOFunction functionGPIO6, GPIOFunction functionGPIO5, GPIOFunction functionGPIO4, GPIOFunction functionGPIO3, GPIOFunction functionGPIO2, GPIOFunction functionGPIO1, GPIOFunction functionGPIO0) {
	uint8_t gpioCtrl0 = 0;
	uint8_t gpioCtrl1 = 0;
	uint8_t gpioDirection = 0;
	uint8_t gpioEnable = 0xFF;
	GPIONumber gpio;

	gpio = D7;
	switch(functionGPIO7) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	gpio = D6;
	switch(functionGPIO6) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	gpio = D5;
	switch(functionGPIO5) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	gpio = D4;
	switch(functionGPIO4) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	gpio = D3;
	switch(functionGPIO3) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	gpio = D2;
	switch(functionGPIO2) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	gpio = D1;
	switch(functionGPIO1) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	gpio = D0;
	switch(functionGPIO0) {
		case GPIODisabled: gpioEnable &= !gpio; break;
		case GPIOInput: break;
		case GPIOInputPullDown: gpioCtrl0 |= gpio; break;
		case GPIOInputPullUp: gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutput: gpioDirection |= gpio; break;
		case GPIOOutputHighSideMOS: gpioDirection |= gpio;  gpioCtrl0 |= gpio; gpioCtrl1 |= gpio; break;
		case GPIOOutputLowSideMOS: gpioDirection |= gpio; gpioCtrl0 |= gpio; break;
	}
	
	return write8(REG_GPIO_CONTROL_0, gpioCtrl0) | write8(REG_GPIO_CONTROL_1, gpioCtrl1) | write8(REG_GPIO_DIRECTION_CONTROL, gpioDirection) | write8(REG_GPIO_ENABLE, gpioEnable);
	
}

// ******************************
// Donne la valeur sur les gpio
// 0x75
// @Return la valeur sur les gpio
// ******************************
uint8_t GestionMPR121::getGPIOData(void) {
	return read8(REG_GPIO_DATA);
}

// ***********************************
// Positionne la valeur sur les gpio
// 0x75
// @Param la valeur sur les gpio
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setGPIOData(uint8_t value) {
	return write8(REG_GPIO_DATA, value);
}

// *******************************
// Indique si un GPIO est a 1
// 0x75
// @Return true si oui false sinon
// *******************************
bool GestionMPR121::isGPIODataOn(GPIONumber gpio) {
	return read8(REG_GPIO_DATA) & gpio;
}

// *******************************
// Indique si un GPIO est a 0
// 0x75
// @Return true si oui false sinon
// *******************************
bool GestionMPR121::isGPIODataOff(GPIONumber gpio) {
	return !read8(REG_GPIO_DATA) & gpio;
}

// **********************************
// Force des gpio a 1
// 0x78
// @Param numero gpio
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::setGPIOData(GPIONumber gpioA, GPIONumber gpioB, GPIONumber gpioC, GPIONumber gpioD, GPIONumber gpioE, GPIONumber gpioF, GPIONumber gpioG, GPIONumber gpioH) {
	return write8(REG_GPIO_DATA_SET, gpioA | gpioB | gpioC | gpioD | gpioE | gpioF | gpioG | gpioH);
}

// **********************************
// Force des gpio a 0
// 0x79
// @Param numero gpio
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::clearGPIOData(GPIONumber gpioA, GPIONumber gpioB, GPIONumber gpioC, GPIONumber gpioD, GPIONumber gpioE, GPIONumber gpioF, GPIONumber gpioG, GPIONumber gpioH) {
	return write8(REG_GPIO_DATA_CLEAR, gpioA | gpioB | gpioC | gpioD | gpioE | gpioF | gpioG | gpioH);
}

// **********************************
// Inverse l'etat de gpio
// 0x7A
// @Param numero gpio
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Param numero gpio (optionnel)
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::toggleGPIOData(GPIONumber gpioA, GPIONumber gpioB, GPIONumber gpioC, GPIONumber gpioD, GPIONumber gpioE, GPIONumber gpioF, GPIONumber gpioG, GPIONumber gpioH) {
	return write8(REG_GPIO_DATA_TOGGLE, gpioA | gpioB | gpioC | gpioD | gpioE | gpioF | gpioG | gpioH);
}

// **************************
// Donne le nombre d'essais
// 0x7B
// @Return le nombre d'essais
// **************************
AutoConfigAFES GestionMPR121::getAutoConfigAFES(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL0) & AFES) {
		case AFE6Samples:  return AFE6Samples;
		case AFE10Samples: return AFE10Samples;
		case AFE18Samples: return AFE18Samples;
		case AFE34Samples: return AFE34Samples;
	}
}

// ******************************************
// Donne le nombre d'auto essais ou reessais
// 0x7B
// @Return le nombre d'auto essais ou reessais
// *******************************************
AutoConfigRetry GestionMPR121::getAutoConfigRetry(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL0) & RETRY) {
		case NORETRY:     return NORETRY;
		case RETRY2Times: return RETRY2Times;
		case RETRY4Times: return RETRY4Times;
		case RETRY8Times: return RETRY8Times;
	}
}

// ********************************************
// Donne le mode de changement de la baseline
// 0x7B
// @Return le mode de changement de la baseline
// ********************************************
AutoConfigBaseline GestionMPR121::getAutoConfigBaseline(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL0) & BVA) {
		case BaselineNoChange:     return BaselineNoChange;
		case BaselineChangeTo0:    return BaselineChangeTo0;
		case BaselineSetValue5MSB: return BaselineSetValue5MSB;
		case BaselineSetValue:     return BaselineSetValue;
	}
}

// ***********************************
// Indique si l'AutoReConfig est actif
// 0x7B
// @Return AutoReConfig actif ou non
// ***********************************
AutoReConfigActive GestionMPR121::getAutoReConfig(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL0) & ARE) {
		case AutoReConfigEnable :  return AutoReConfigEnable;
		case AutoReConfigDisable : return AutoReConfigDisable;
	}
}

// *********************************
// Indique si l'AutoConfig est actif
// 0x7B
// @Return AutoConfig actif ou non
// *********************************
AutoConfigActive GestionMPR121::getAutoConfig(void) {
	switch( read8(REG_AUTO_CONFIG_CONTROL0) & ACE) {
		case AutoConfigEnable :  return AutoConfigEnable;
		case AutoConfigDisable : return AutoConfigDisable;
	}
}

// ********************************************************************************************************
// Indique si le charge time search est positionne par l'autoConfig sinon c'est le CTC global ou individuel
// 0x7C
// @Return charge time search
// ********************************************************************************************************
ChargeTimeSearch GestionMPR121::getChargeTimeSearch(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL1) & SCTS) {
		case SkipChargeTimeSearch : return SkipChargeTimeSearch;
		case DoChargeTimeSearch :   return DoChargeTimeSearch;
	}
}

// **********************************************************
// Indique si une erreur d'autoConfig genere une interruption
// 0x7C
// @Return est ce que l'autoConfig genere une interruption
// **********************************************************
AutoConfigInterrupt GestionMPR121::getAutoConfigInterrupt(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL1) & OORIE) {
		case AutoConfigInterruptFailEnable :  return AutoConfigInterruptFailEnable;
		case AutoConfigInterruptFailDisable : return AutoConfigInterruptFailDisable;
	}
}

// ************************************************************
// Indique si une erreur d'autoReConfig genere une interruption
// 0x7C
// @Return est ce que l'autoReConfig genere une interruption
// ************************************************************
AutoReConfigInterrupt GestionMPR121::getAutoReConfigInterrupt(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL1) & ARFIE) {
		case AutoReConfigInterruptFailEnable :  return AutoReConfigInterruptFailEnable;
		case AutoReConfigInterruptFailDisable : return AutoReConfigInterruptFailDisable;
	}
}

// **********************************************************
// Indique si une erreur d'outOfRange genere une interruption
// 0x7C
// @Return est ce que l'outOfRange genere une interruption
// **********************************************************
OutOfRangeInterrupt GestionMPR121::getOutOfRangeInterrupt(void) {
	switch(read8(REG_AUTO_CONFIG_CONTROL1) & ACFIE) {
		case OutOfRangeInterruptEnable :  return OutOfRangeInterruptEnable;
		case OutOfRangeInterruptDisable : return OutOfRangeInterruptDisable;
	}
}

// ***************************************
// Programme l'autoConfiguration du module
// 0x7B 0x7C
// @Param AFES
// @Param RETRY
// @Param BVA
// @Param ARE
// @Param ACE
// @Param SCTS
// @Param OORIE
// @Param ARFIE
// @Param ACFIE
// @Return la bonne execution du write
// ***************************************
bool GestionMPR121::setAutoConfigure(AutoConfigAFES afes, AutoConfigRetry retry, AutoConfigBaseline bva, AutoReConfigActive are, AutoConfigActive ace, ChargeTimeSearch scts, AutoConfigInterrupt oorie, AutoReConfigInterrupt arfie, OutOfRangeInterrupt acfie) {
	return write8(REG_AUTO_CONFIG_CONTROL0, afes | retry | bva | are | ace) | write8(REG_AUTO_CONFIG_CONTROL1, scts | oorie | arfie | acfie);
}

// ****************************************************************
// Donne la valeur max que les electrodes ne doivent pas depasser
// 0x7D
// @Return la valeur max que les electrodes ne doivent pas depasser
// ****************************************************************
uint8_t GestionMPR121::getUpperSiteLimit(void) {
	return read8(REG_AUTO_CONFIG_USL);
}

// *******************************************************************
// Positionne la valeur max que les electrodes ne doivent pas depasser
// 0x7D
// @Param la valeur max
// @Return la bonne execution du write
// *******************************************************************
bool GestionMPR121::setUpperSiteLimit(uint8_t value) {
	return write8(REG_AUTO_CONFIG_USL, value);
}

// ****************************************************************
// Donne la valeur min que les electrodes ne doivent pas depasser
// 0x7E
// @Return la valeur min que les electrodes ne doivent pas depasser
// ****************************************************************
uint8_t GestionMPR121::getLowerSiteLimit(void) {
	return read8(REG_AUTO_CONFIG_LSL);
}

// *******************************************************************
// Positionne la valeur min que les electrodes ne doivent pas depasser
// 0x7E
// @Param la valeur min
// @Return la bonne execution du write
// *******************************************************************
bool GestionMPR121::setLowerSiteLimit(uint8_t value) {
	return write8(REG_AUTO_CONFIG_LSL, value);
}

// ********************************************************************************
// Donne la valeur que les electrodes doivent avoir si elles ne sont pas touchees
// 0x7F
// @Return la valeur que les electrodes doivent avoir si elles ne sont pas touchees
// ********************************************************************************
uint8_t GestionMPR121::getTargetLevel(void) {
	return read8(REG_AUTO_CONFIG_TARGET_LEVEL);
}

// ***********************************************************************************
// Positionne la valeur que les electrodes doivent avoir si elles ne sont pas touchees
// 0x7F
// @Param la valeur que les electrodes doivent avoir si elles ne sont pas touchees
// @Return la bonne execution du write
// ***********************************************************************************
bool GestionMPR121::setTargetLevel(uint8_t value) {
	return write8(REG_AUTO_CONFIG_TARGET_LEVEL, value);
}

// ***********************************
// RESET le module
// 0x80
// @Return la bonne execution du write
// ***********************************
bool GestionMPR121::reset(void) {
	return write8(REG_SOFT_RESET_REGISTER, RESET);
}

// **********************************************************************
// Active le PWM d'une sortie GPIO
// 0x81 0x84
// Voir datasheet AN3894
// Attention: il faut commencer un pwm par un set, un clear bloque le pwm
// @Param la gpio
// @Param la valeur du pwm (16 valeurs)
// @Return la bonne execution du write
// **********************************************************************
bool GestionMPR121::setPwm(GPIONumber gpio, PwmValues value) {
	uint8_t pwm0 = read8(REG_PWM0);
	uint8_t pwm1 = read8(REG_PWM1);
	uint8_t pwm2 = read8(REG_PWM2);
	uint8_t pwm3 = read8(REG_PWM3);
	switch(gpio) {
		case D0: return write8(REG_PWM0, (pwm0 & 0xF0) + value);
		case D1: return write8(REG_PWM0, (pwm0 & 0x0F) + (value << 4));
		case D2: return write8(REG_PWM1, (pwm1 & 0xF0) + value);
		case D3: return write8(REG_PWM1, (pwm1 & 0x0F) + (value << 4));
		case D4: return write8(REG_PWM2, (pwm2 & 0xF0) + value);
		case D5: return write8(REG_PWM2, (pwm2 & 0x0F) + (value << 4));
		case D6: return write8(REG_PWM3, (pwm3 & 0xF0) + value);
		case D7: return write8(REG_PWM3, (pwm3 & 0x0F) + (value << 4));
	}
}

// *************************************
// Donne le PWM d'une sortie GPIO
// 0x81 0x84
// Voir datasheet AN3894
// @Param la gpio
// @Return la valeur du pwm (16 valeurs)
// *************************************
PwmValues GestionMPR121::getPwm(GPIONumber gpio) {
	switch(gpio) {
		case D0: return static_cast<PwmValues>(read8(REG_PWM0) & 0x0F);
		case D1: return static_cast<PwmValues>(read8(REG_PWM0) >> 4);
		case D2: return static_cast<PwmValues>(read8(REG_PWM1) & 0x0F);
		case D3: return static_cast<PwmValues>(read8(REG_PWM1) >> 4);
		case D4: return static_cast<PwmValues>(read8(REG_PWM2) & 0x0F);
		case D5: return static_cast<PwmValues>(read8(REG_PWM2) >> 4);
		case D6: return static_cast<PwmValues>(read8(REG_PWM3) & 0x0F);
		case D7: return static_cast<PwmValues>(read8(REG_PWM3) >> 4);
	}
}

// *************************************
// Donne la broche GPIO d'interruption
// @Return la broche GPIO d'interruption
// *************************************
GestionPinGPIO GestionMPR121::getInterrupt(void) {
	return interrupt;
}

// ******************************
// Donne l'etat du flag d'erreur
// @Return l'etat du flag d'erreur
// *******************************
bool GestionMPR121::getError(void) {
	return error;
}

// *********************************************************
// Initialisation du module pour 12 electrodes independantes
// @Return la bonne execution de la config
// *********************************************************
bool GestionMPR121::config12Electrodes(void) {
	bool result = true;
	result &= reset();
	result &= setElementMaximumHalfDeltaRising(0x01);
	result &= setElementNoiseHalfDeltaRising(0x01);
	result &= setElementNoiseCountLimitRising(0x10);
	result &= setElementFilterDelayCountLimitRising(0x20);
	result &= setElementMaximumHalfDeltaFalling(0x01);
	result &= setElementNoiseHalfDeltaFalling(0x01);
	result &= setElementNoiseCountLimitFalling(0x10);
	result &= setElementFilterDelayCountLimitFalling(0x20);
	result &= setElementNoiseHalfDeltaTouched(0x01);
	result &= setElementNoiseCountLimitTouched(0x10);
	result &= setElementFilterDelayCountLimitTouched(0xFF);
	result &= setEleProximityMaximumHalfDeltaRising(0x0F);
	result &= setEleProximityNoiseHalfDeltaRising(0x0F);
	result &= setEleProximityNoiseCountLimitRising(0x00);
	result &= setEleProximityFilterDelayCountLimitRising(0x00);
	result &= setEleProximityMaximumHalfDeltaFalling(0x01);
	result &= setEleProximityNoiseHalfDeltaFalling(0x01);
	result &= setEleProximityNoiseCountLimitFalling(0xFF);
	result &= setEleProximityFilterDelayCountLimitFalling(0xFF);
	result &= setEleProximityNoiseHalfDeltaTouched(0x00);
	result &= setEleProximityNoiseCountLimitTouched(0x00);
	result &= setEleProximityFilterDelayCountLimitTouched(0x00);
	result &= setTouchReleaseDebounce(TOUCH_DEBOUNCE_1, RELEASE_DEBOUNCE_1);
	result &= setAFEConfiguration(FFI34Samples, CDC63, CDT05US, SFI10, ESI1); //0xff30
	result &= setAutoConfigure(AFE6Samples, NORETRY, BaselineNoChange, AutoReConfigDisable, AutoConfigDisable, DoChargeTimeSearch, AutoConfigInterruptFailDisable, AutoReConfigInterruptFailDisable, OutOfRangeInterruptDisable);
	result &= setUpperSiteLimit(0x00);
	result &= setLowerSiteLimit(0x00);
	result &= setTargetLevel(0x00);
	result &= setElectrodeConfiguration(BASELINE_TRACKING_AND_INITIALIZE_ENABLE2, ELEPROX_DISABLED, ELECTRODE0_11);
	result &= setAllTouchThreshold(40);
	result &= setAllReleaseThreshold(20);
	return result;
}

// *****************************************************************************
// Initialisation du module avec toutes les electrodes en detection de proximite
// @Return la bonne execution de la config
// *****************************************************************************
bool GestionMPR121::configAllElectrodeProximity(void) {
	bool result = true;
	result &= reset();
	result &= setElementMaximumHalfDeltaRising(0x01);
	result &= setElementNoiseHalfDeltaRising(0x01);
	result &= setElementNoiseCountLimitRising(0x10);
	result &= setElementFilterDelayCountLimitRising(0x20);
	result &= setElementMaximumHalfDeltaFalling(0x01);
	result &= setElementNoiseHalfDeltaFalling(0x01);
	result &= setElementNoiseCountLimitFalling(0x10);
	result &= setElementFilterDelayCountLimitFalling(0x20);
	result &= setElementNoiseHalfDeltaTouched(0x01);
	result &= setElementNoiseCountLimitTouched(0x10);
	result &= setElementFilterDelayCountLimitTouched(0xFF);
	result &= setEleProximityMaximumHalfDeltaRising(0x0F);
	result &= setEleProximityNoiseHalfDeltaRising(0x0F);
	result &= setEleProximityNoiseCountLimitRising(0x00);
	result &= setEleProximityFilterDelayCountLimitRising(0x00);
	result &= setEleProximityMaximumHalfDeltaFalling(0x01);
	result &= setEleProximityNoiseHalfDeltaFalling(0x01);
	result &= setEleProximityNoiseCountLimitFalling(0xFF);
	result &= setEleProximityFilterDelayCountLimitFalling(0xFF);
	result &= setEleProximityNoiseHalfDeltaTouched(0x00);
	result &= setEleProximityNoiseCountLimitTouched(0x00);
	result &= setEleProximityFilterDelayCountLimitTouched(0x00);
	result &= setTouchReleaseDebounce(TOUCH_DEBOUNCE_1, RELEASE_DEBOUNCE_1);
	result &= setAFEConfiguration(FFI34Samples, CDC63, CDT05US, SFI10, ESI1); //0xff30
	result &= setAutoConfigure(AFE6Samples, NORETRY, BaselineNoChange, AutoReConfigDisable, AutoConfigDisable, DoChargeTimeSearch, AutoConfigInterruptFailDisable, AutoReConfigInterruptFailDisable, OutOfRangeInterruptDisable);
	result &= setUpperSiteLimit(0x00);
	result &= setLowerSiteLimit(0x00);
	result &= setTargetLevel(0x00);
	result &= setElectrodeConfiguration(BASELINE_TRACKING_AND_INITIALIZE_ENABLE2, ELEPROX0_11, ELECTRODE_DISABLED);
	result &= setAllTouchThreshold(40);
	result &= setAllReleaseThreshold(20);
}

// *********************************************************
// Initialisation du module pour 12 electrodes independantes
// @Return la bonne execution de la config
// *********************************************************
bool GestionMPR121::configAuto12Electrodes(void) {
	bool result = true;
	result &= reset();
	result &= setAutoConfigure(AFE18Samples, RETRY4Times, BaselineSetValue, AutoReConfigDisable, AutoConfigEnable, DoChargeTimeSearch, AutoConfigInterruptFailEnable, AutoReConfigInterruptFailEnable, OutOfRangeInterruptEnable);
	result &= setUpperSiteLimit(202);
	result &= setLowerSiteLimit(131);
	result &= setTargetLevel(182);
	result &= setElectrodeConfiguration(BASELINE_TRACKING_AND_INITIALIZE_ENABLE2, ELEPROX_DISABLED, ELECTRODE0_11);
	result &= setAllTouchThreshold(200);
	result &= setAllReleaseThreshold(10);
	return result;
}

// *********************************************************
// Initialisation du module pour 12 electrodes independantes
// @Return la bonne execution de la config
// *********************************************************
bool GestionMPR121::configAuto8Electrodes4prox(void) {
	bool result = true;
	result &= reset();
	result &= setAutoConfigure(AFE18Samples, RETRY4Times, BaselineSetValue, AutoReConfigDisable, AutoConfigEnable, DoChargeTimeSearch, AutoConfigInterruptFailEnable, AutoReConfigInterruptFailEnable, OutOfRangeInterruptEnable);
	result &= setUpperSiteLimit(202);
	result &= setLowerSiteLimit(140);
	result &= setTargetLevel(170);
	result &= setElectrodeConfiguration(BASELINE_TRACKING_AND_INITIALIZE_ENABLE2, ELEPROX0_3, ELECTRODE0_11);
	result &= setAllTouchThreshold(50);
	result &= setAllReleaseThreshold(20);
	return result;
}

// ******************************************************************
// Initialisation du module pour 4 electrodes independantes et 8 gpio
// @Return la bonne execution de la config
// ******************************************************************
bool GestionMPR121::config4Electrodes8Gpio(void) {
	bool result = true;
	result &= reset();
	result &= setAutoConfigure(AFE18Samples, RETRY4Times, BaselineSetValue, AutoReConfigDisable, AutoConfigEnable, DoChargeTimeSearch, AutoConfigInterruptFailEnable, AutoReConfigInterruptFailEnable, OutOfRangeInterruptEnable);
	result &= setUpperSiteLimit(202);
	result &= setLowerSiteLimit(140);
	result &= setTargetLevel(170);
	result &= setElectrodeConfiguration(BASELINE_TRACKING_AND_INITIALIZE_ENABLE2, ELEPROX_DISABLED, ELECTRODE0_3);
	result &= setAllTouchThreshold(50);
	result &= setAllReleaseThreshold(20);
	return result;
}

// *****************************
// Lit un registre
// Utilisee juste en debug
// @Param le registre
// @return la valeur du registre
// *****************************
uint8_t GestionMPR121::getRegister(RegistreMpr121 reg) {
	return read8(reg);
}

// **********************************
// Ecrit une valeur dans un registre
// Utilisee juste en debug
// @Param le registre
// @Param la valeur
// @return La bonne execution du write
// ***********************************
bool GestionMPR121::setRegister(RegistreMpr121 reg, uint8_t value) {
	return write8(reg, value);
}

