/*
 * GestionMCU6050.cpp
 *
 *  Created on: 28 january 2017
 *      Author: totof
 * Controle un module MPU6050
 */

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "GestionMPU6050.h"

namespace std {

// *************************
// Constructeur
// @param adresse du circuit 
// *************************
GestionMPU6050::GestionMPU6050(Adresse pAddress) {
	fd = wiringPiI2CSetup(pAddress);
}

// ****************************
// Lit la valeur d'un registre
// @param pRegistre le registre
// @return la valeur lue
// ****************************
unsigned char GestionMPU6050::readUChar(Registre pRegistre) {
	return (unsigned char)wiringPiI2CReadReg8(fd, pRegistre);
}

// *********************************
// Ecrit une valeur dans un registre
// @param pRegistre le registre
// @param la valeur a ecrire
// *********************************
void GestionMPU6050::writeUChar(Registre pRegistre, unsigned char pValeur) {
	wiringPiI2CWriteReg8(fd, pRegistre, pValeur);
}

// **************************************************
// Initialization par defaut
// Gyroscope a 250deg/s
// Accelerometre 2G
// Horloge sur X Gyro (meilleur que la clock interne)
// Active l'appareil
// **************************************************
void GestionMPU6050::defaultInitialize() {
    setClockSource(PLL_XGYRO);
    setFullScaleRangeGyro(FS_250);
    setFullScaleRangeAccel(FS_2G);
    unSleep();
}
		
//++++++++++++++++++++++++++++++++++++++++
// Registre 06 07 06h 07h REG_XA_OFFS_H
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getXAccelOffset() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_XA_OFFS_H);	
	dataAccel.uCData[0] = readUChar(REG_XA_OFFS_L_TC);	
	return dataAccel.sData;
}

void GestionMPU6050::setXAccelOffset(short offset) {
	data dataAccel;
	
	dataAccel.sData = offset;
	writeUChar(REG_XA_OFFS_H, dataAccel.uCData[1]);	
	writeUChar(REG_XA_OFFS_L_TC, dataAccel.uCData[0]);	
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 08 09 08h 09h REG_YA_OFFS_H
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getYAccelOffset() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_YA_OFFS_H);	
	dataAccel.uCData[0] = readUChar(REG_YA_OFFS_L_TC);	
	return dataAccel.sData;
}

void GestionMPU6050::setYAccelOffset(short offset) {
	data dataAccel;
	
	dataAccel.sData = offset;
	writeUChar(REG_YA_OFFS_H, dataAccel.uCData[1]);	
	writeUChar(REG_YA_OFFS_L_TC, dataAccel.uCData[0]);	
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 10 11 0Ah 0Bh REG_ZA_OFFS_H
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getZAccelOffset() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_ZA_OFFS_H);	
	dataAccel.uCData[0] = readUChar(REG_ZA_OFFS_L_TC);	
	return dataAccel.sData;
}

void GestionMPU6050::setZAccelOffset(short offset) {
	data dataAccel;
	
	dataAccel.sData = offset;
	writeUChar(REG_ZA_OFFS_H, dataAccel.uCData[1]);	
	writeUChar(REG_ZA_OFFS_L_TC, dataAccel.uCData[0]);	
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 13 0Dh SELF_TEST_X
// Registre 16 10h SELF_TEST_A
//++++++++++++++++++++++++++++++++++++++++
unsigned char GestionMPU6050::getXATest() {
	return ((readUChar(REG_SELF_TEST_X) >> 3) | ((readUChar(REG_SELF_TEST_A) & XA_TEST_L) >> 4));
}

void GestionMPU6050::setXATest(unsigned char pValue) {
	writeUChar(REG_SELF_TEST_X, ((pValue << 3) & A_TEST_H) | (readUChar(REG_SELF_TEST_X) & ~A_TEST_H));
	writeUChar(REG_SELF_TEST_A, ((pValue << 4) & XA_TEST_L) | (readUChar(REG_SELF_TEST_A) & ~XA_TEST_L));
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 14 0Eh SELF_TEST_Y
// Registre 16 10h SELF_TEST_A
//++++++++++++++++++++++++++++++++++++++++
unsigned char GestionMPU6050::getYATest() {
	return ((readUChar(REG_SELF_TEST_Y) >> 3) | ((readUChar(REG_SELF_TEST_A) & YA_TEST_L) >> 2));
}

void GestionMPU6050::setYATest(unsigned char pValue) {
	writeUChar(REG_SELF_TEST_Y, ((pValue << 3) & A_TEST_H) | (readUChar(REG_SELF_TEST_Y) & ~A_TEST_H));
	writeUChar(REG_SELF_TEST_A, ((pValue << 2) & YA_TEST_L) | (readUChar(REG_SELF_TEST_A) & ~YA_TEST_L));
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 15 0Fh SELF_TEST_Z
// Registre 16 10h SELF_TEST_A
//++++++++++++++++++++++++++++++++++++++++
unsigned char GestionMPU6050::getZATest() {
	return ((readUChar(REG_SELF_TEST_Z) >> 3) | ((readUChar(REG_SELF_TEST_A) & ZA_TEST_L)));
}

void GestionMPU6050::setZATest(unsigned char pValue) {
	writeUChar(REG_SELF_TEST_Z, ((pValue << 3) & A_TEST_H) | (readUChar(REG_SELF_TEST_Z) & ~A_TEST_H));
	writeUChar(REG_SELF_TEST_A, ((pValue) & ZA_TEST_L) | (readUChar(REG_SELF_TEST_A) & ~ZA_TEST_L));
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 19 13h XG_OFFS_USRH
// Registre 20 14h XG_OFFS_USRL
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getXGyroOffset() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_XG_OFFS_USRH);	
	dataAccel.uCData[0] = readUChar(REG_XG_OFFS_USRL);	
	return dataAccel.sData;
}

void GestionMPU6050::setXGyroOffset(short offset) {
	data dataAccel;
	
	dataAccel.sData = offset;
	writeUChar(REG_XG_OFFS_USRH, dataAccel.uCData[1]);	
	writeUChar(REG_XG_OFFS_USRL, dataAccel.uCData[0]);	
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 21 15h YG_OFFS_USRH
// Registre 22 16h YG_OFFS_USRL
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getYGyroOffset() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_YG_OFFS_USRH);	
	dataAccel.uCData[0] = readUChar(REG_YG_OFFS_USRL);	
	return dataAccel.sData;
}

void GestionMPU6050::setYGyroOffset(short offset) {
	data dataAccel;
	
	dataAccel.sData = offset;
	writeUChar(REG_YG_OFFS_USRH, dataAccel.uCData[1]);	
	writeUChar(REG_YG_OFFS_USRL, dataAccel.uCData[0]);	
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 23 17h ZG_OFFS_USRH
// Registre 24 18h ZG_OFFS_USRL
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getZGyroOffset() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_ZG_OFFS_USRH);	
	dataAccel.uCData[0] = readUChar(REG_ZG_OFFS_USRL);	
	return dataAccel.sData;
}

void GestionMPU6050::setZGyroOffset(short offset) {
	data dataAccel;
	
	dataAccel.sData = offset;
	writeUChar(REG_ZG_OFFS_USRH, dataAccel.uCData[1]);	
	writeUChar(REG_ZG_OFFS_USRL, dataAccel.uCData[0]);	
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 25 19h SMPRT_DIV
//++++++++++++++++++++++++++++++++++++++++
void GestionMPU6050::setSampleRateDivider(unsigned char pValue) {
	writeUChar(REG_SMPLRT_DIV, pValue);
}

unsigned short GestionMPU6050::getSampleRateDivider() {
	return readUChar(REG_SMPLRT_DIV);
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 26 1Ah CONFIG
//++++++++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits EXT_SYNC_SET
//----------------------------------
unsigned char GestionMPU6050::getExtSyncSet() {
	return (readUChar(REG_CONFIG) >> 3);
}

void GestionMPU6050::setExtSyncSet(unsigned char pValue) {
	writeUChar(REG_CONFIG, (pValue << 3) | (readUChar(REG_CONFIG) & ~EXT_SYNC_SET));
}

//----------------------------------
// Bits DLPF_CFG
//----------------------------------
unsigned char GestionMPU6050::getDlpfCfg() {
	return (readUChar(REG_CONFIG) & DLPF_CFG);
}

void GestionMPU6050::setDlpfCfg(unsigned char pValue) {
	writeUChar(REG_CONFIG, (pValue) | (readUChar(REG_CONFIG) & ~DLPF_CFG));
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 27 1Bh GYRO_CONFIG
//++++++++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits FS_SEL
//----------------------------------
void GestionMPU6050::setFullScaleRangeGyro(GyroSensibility pRange) {
	writeUChar(REG_GYRO_CONFIG, (readUChar(REG_GYRO_CONFIG) & GYRO_MASK) | pRange);
}

unsigned short GestionMPU6050::getFullScaleRangeGyro() {
	return readUChar(REG_GYRO_CONFIG) & ~GYRO_MASK;
}

//----------------------------------
// Bits XG_ST
//----------------------------------
void GestionMPU6050::enableGyroXSelfTest() {
    writeUChar(REG_GYRO_CONFIG, readUChar(REG_GYRO_CONFIG) | XG_ST);
}

void GestionMPU6050::disableGyroXSelfTest() {
    writeUChar(REG_GYRO_CONFIG, readUChar(REG_GYRO_CONFIG) & ~XG_ST);
}

bool GestionMPU6050::isGyroXSelfTest() {
    return readUChar(REG_GYRO_CONFIG) & XG_ST;
}

//----------------------------------
// Bits YG_ST
//----------------------------------
void GestionMPU6050::enableGyroYSelfTest() {
    writeUChar(REG_GYRO_CONFIG, readUChar(REG_GYRO_CONFIG) | YG_ST);
}

void GestionMPU6050::disableGyroYSelfTest() {
    writeUChar(REG_GYRO_CONFIG, readUChar(REG_GYRO_CONFIG) & ~YG_ST);
}

bool GestionMPU6050::isGyroYSelfTest() {
    return readUChar(REG_GYRO_CONFIG) & YG_ST;
}

//----------------------------------
// Bits ZG_ST
//----------------------------------
void GestionMPU6050::enableGyroZSelfTest() {
    writeUChar(REG_GYRO_CONFIG, readUChar(REG_GYRO_CONFIG) | ZG_ST);
}

void GestionMPU6050::disableGyroZSelfTest() {
    writeUChar(REG_GYRO_CONFIG, readUChar(REG_GYRO_CONFIG) & ~ZG_ST);
}

bool GestionMPU6050::isGyroZSelfTest() {
    return readUChar(REG_GYRO_CONFIG) & ZG_ST;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 28 1Ch ACCEL_CONFIG
//++++++++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits AFS_SEL
//----------------------------------
void GestionMPU6050::setFullScaleRangeAccel(AccelSensibility pRange) {
	writeUChar(REG_ACCEL_CONFIG, (readUChar(REG_ACCEL_CONFIG) & ACCEL_MASK) | pRange);
}

unsigned short GestionMPU6050::getFullScaleRangeAccel() {
	return readUChar(REG_ACCEL_CONFIG) & ~ACCEL_MASK;
}

//----------------------------------
// Bits XA_ST
//----------------------------------
void GestionMPU6050::enableAccelXSelfTest() {
    writeUChar(REG_ACCEL_CONFIG, readUChar(REG_ACCEL_CONFIG) | XA_ST);
}

void GestionMPU6050::disableAccelXSelfTest() {
    writeUChar(REG_ACCEL_CONFIG, readUChar(REG_ACCEL_CONFIG) & ~XA_ST);
}

bool GestionMPU6050::isAccelXSelfTest() {
    return readUChar(REG_ACCEL_CONFIG) & XA_ST;
}

//----------------------------------
// Bits YA_ST
//----------------------------------
void GestionMPU6050::enableAccelYSelfTest() {
    writeUChar(REG_ACCEL_CONFIG, readUChar(REG_ACCEL_CONFIG) | YA_ST);
}

void GestionMPU6050::disableAccelYSelfTest() {
    writeUChar(REG_ACCEL_CONFIG, readUChar(REG_ACCEL_CONFIG) & ~YA_ST);
}

bool GestionMPU6050::isAccelYSelfTest() {
    return readUChar(REG_ACCEL_CONFIG) & YA_ST;
}

//----------------------------------
// Bits ZA_ST
//----------------------------------
void GestionMPU6050::enableAccelZSelfTest() {
    writeUChar(REG_ACCEL_CONFIG, readUChar(REG_ACCEL_CONFIG) | ZA_ST);
}

void GestionMPU6050::disableAccelZSelfTest() {
    writeUChar(REG_ACCEL_CONFIG, readUChar(REG_ACCEL_CONFIG) & ~ZA_ST);
}

bool GestionMPU6050::isAccelZSelfTest() {
    return readUChar(REG_ACCEL_CONFIG) & ZA_ST;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 31 1Fh MOT_THR
//++++++++++++++++++++++++++++++++++++++++
void GestionMPU6050::setMotionDetectionThreshold(unsigned char pValue) {
	writeUChar(REG_MOT_THR, pValue);
}

unsigned short GestionMPU6050::getMotionDetectionThreshold() {
	return readUChar(REG_MOT_THR);
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 35 23h FIFO_EN
//++++++++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits TEMP_FIFO_EN
//----------------------------------
void GestionMPU6050::enableTempFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | TEMP_FIFO_EN);
}

void GestionMPU6050::disableTempFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~TEMP_FIFO_EN);
}

bool GestionMPU6050::isTempFifo() {
    return readUChar(REG_FIFO_EN) & TEMP_FIFO_EN;
}

//----------------------------------
// Bits XG_FIFO_EN
//----------------------------------
void GestionMPU6050::enableXgFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | XG_FIFO_EN);
}

void GestionMPU6050::disableXgFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~XG_FIFO_EN);
}

bool GestionMPU6050::isXgFifo() {
    return readUChar(REG_FIFO_EN) & XG_FIFO_EN;
}

//----------------------------------
// Bits YG_FIFO_EN
//----------------------------------
void GestionMPU6050::enableYgFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | YG_FIFO_EN);
}

void GestionMPU6050::disableYgFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~YG_FIFO_EN);
}

bool GestionMPU6050::isYgFifo() {
    return readUChar(REG_FIFO_EN) & YG_FIFO_EN;
}

//----------------------------------
// Bits ZG_FIFO_EN
//----------------------------------
void GestionMPU6050::enableZgFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | ZG_FIFO_EN);
}

void GestionMPU6050::disableZgFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~ZG_FIFO_EN);
}

bool GestionMPU6050::isZgFifo() {
    return readUChar(REG_FIFO_EN) & ZG_FIFO_EN;
}

//----------------------------------
// Bits ACCEL_FIFO_EN
//----------------------------------
void GestionMPU6050::enableAccelFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | ACCEL_FIFO_EN);
}

void GestionMPU6050::disableAccelFifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~ACCEL_FIFO_EN);
}

bool GestionMPU6050::isAccelFifo() {
    return readUChar(REG_FIFO_EN) & ACCEL_FIFO_EN;
}

//----------------------------------
// Bits SLV2_FIFO_EN
//----------------------------------
void GestionMPU6050::enableSlv2Fifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | SLV2_FIFO_EN);
}

void GestionMPU6050::disableSlv2Fifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~SLV2_FIFO_EN);
}

bool GestionMPU6050::isSlv2Fifo() {
    return readUChar(REG_FIFO_EN) & SLV2_FIFO_EN;
}

//----------------------------------
// Bits SLV1_FIFO_EN
//----------------------------------
void GestionMPU6050::enableSlv1Fifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | SLV1_FIFO_EN);
}

void GestionMPU6050::disableSlv1Fifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~SLV1_FIFO_EN);
}

bool GestionMPU6050::isSlv1Fifo() {
    return readUChar(REG_FIFO_EN) & SLV1_FIFO_EN;
}

//----------------------------------
// Bits SLV0_FIFO_EN
//----------------------------------
void GestionMPU6050::enableSlv0Fifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) | SLV0_FIFO_EN);
}

void GestionMPU6050::disableSlv0Fifo() {
    writeUChar(REG_FIFO_EN, readUChar(REG_FIFO_EN) & ~SLV0_FIFO_EN);
}

bool GestionMPU6050::isSlv0Fifo() {
    return readUChar(REG_FIFO_EN) & SLV0_FIFO_EN;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 36 24h I2C_MASTER_CONTROL
//++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++
// Registre 37 38 39 25h 26h 27h I2C_SLAVE0_CONTROL
//+++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++
// Registre 40 41 42 28h 29h 2Ah I2C_SLAVE1_CONTROL
//+++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++
// Registre 43 44 45 2Bh 2Ch 2Dh I2C_SLAVE2_CONTROL
//+++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++
// Registre 46 47 48 2Eh 2Fh 30h I2C_SLAVE3_CONTROL
//+++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Registre 49 50 51 52 53 31h 32h 33h 34h 35h I2C_SLAVE4_CONTROL
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
// Registre 54 36h I2C_MASTER_STATUS
//++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++
// Registre 55 37h INT PIN
//++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits INT_LEVEL
//----------------------------------
void GestionMPU6050::intPinActiveLow() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) | INT_LEVEL);
}

bool GestionMPU6050::isIntPinActiveLow() {
    return readUChar(REG_INT_PIN_CFG) & INT_LEVEL;
}

void GestionMPU6050::intPinActiveHigh() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) & ~INT_LEVEL);
}

bool GestionMPU6050::isIntPinActiveHigh() {
    return !readUChar(REG_INT_PIN_CFG) & INT_LEVEL;
}

//----------------------------------
// Bits INT_OPEN
//----------------------------------
void GestionMPU6050::intPinOpenDrain() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) | INT_OPEN);
}

bool GestionMPU6050::isIntPinOpenDrain() {
    return readUChar(REG_INT_PIN_CFG) & INT_OPEN;
}

void GestionMPU6050::intPinPushPull() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) & ~INT_OPEN);
}

bool GestionMPU6050::isIntPinPushPull() {
    return !readUChar(REG_INT_PIN_CFG) & INT_OPEN;
}

//----------------------------------
// Bits LATCH_INT_EN
//----------------------------------
void GestionMPU6050::intPinHeldHigh() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) | LATCH_INT_EN);
}

bool GestionMPU6050::isIntPinHeldHigh() {
    return readUChar(REG_INT_PIN_CFG) & LATCH_INT_EN;
}

void GestionMPU6050::intPinPulse() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) & ~LATCH_INT_EN);
}

bool GestionMPU6050::isIntPinPulse() {
    return !readUChar(REG_INT_PIN_CFG) & LATCH_INT_EN;
}

//----------------------------------
// Bits INT_RD_CLEAR
//----------------------------------
void GestionMPU6050::statusClearedByAnyRead() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) | INT_RD_CLEAR);
}

bool GestionMPU6050::isstatusClearedByAnyRead() {
    return readUChar(REG_INT_PIN_CFG) & INT_RD_CLEAR;
}

void GestionMPU6050::statusClearedByReadIntStatus() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) & ~INT_RD_CLEAR);
}

bool GestionMPU6050::isStatusClearedByReadIntStatus() {
    return !readUChar(REG_INT_PIN_CFG) & INT_RD_CLEAR;
}

//----------------------------------
// Bits FSYNC_INT_LEVEL
//----------------------------------
void GestionMPU6050::fsyncPinActiveLow() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) | FSYNC_INT_LEVEL);
}

bool GestionMPU6050::isFsyncPinActiveLow() {
    return readUChar(REG_INT_PIN_CFG) & FSYNC_INT_LEVEL;
}

void GestionMPU6050::fsyncPinActiveHigh() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) & ~FSYNC_INT_LEVEL);
}

bool GestionMPU6050::isfsyncPinActiveHigh() {
    return !readUChar(REG_INT_PIN_CFG) & FSYNC_INT_LEVEL;
}

//----------------------------------
// Bits FSYNC_INT_EN
//----------------------------------
void GestionMPU6050::disableFsyncPinInterrupt() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) | FSYNC_INT_EN);
}

bool GestionMPU6050::isDisableFsyncPinInterrupt() {
    return readUChar(REG_INT_PIN_CFG) & FSYNC_INT_EN;
}

void GestionMPU6050::enableFsyncPinInterrupt() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) & ~FSYNC_INT_EN);
}

bool GestionMPU6050::isEnableFsyncPinInterrupt() {
    return !readUChar(REG_INT_PIN_CFG) & FSYNC_INT_EN;
}

//----------------------------------
// Bits I2C_BYPASS_EN
//----------------------------------
void GestionMPU6050::directlyAccessAuxI2C() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) | I2C_BYPASS_EN);
}

bool GestionMPU6050::isDirectlyAccessAuxI2C() {
    return readUChar(REG_INT_PIN_CFG) & I2C_BYPASS_EN;
}

void GestionMPU6050::notDirectlyAccessAuxI2C() {
    writeUChar(REG_INT_PIN_CFG, readUChar(REG_INT_PIN_CFG) & ~I2C_BYPASS_EN);
}

bool GestionMPU6050::isNotDirectlyAccessAuxI2C() {
    return !readUChar(REG_INT_PIN_CFG) & I2C_BYPASS_EN;
}

//++++++++++++++++++++++++++++++++++
// Registre 56 38h INTERRUPT ENABLE
//++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits MOT_EN
//----------------------------------
void GestionMPU6050::enableDetectionInterrupt() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) | MOT_EN);
}

bool GestionMPU6050::isEnableDetectionInterrupt() {
    return readUChar(REG_INT_ENABLE) & MOT_EN;
}

void GestionMPU6050::disableDetectionInterrupt() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) & ~MOT_EN);
}

bool GestionMPU6050::isDisableDetectionInterrupt() {
    return !readUChar(REG_INT_ENABLE) & MOT_EN;
}

//----------------------------------
// Bits FIFO_OFLOW_EN
//----------------------------------
void GestionMPU6050::enableFifoOverflow() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) | FIFO_OFLOW_EN);
}

bool GestionMPU6050::isEnableFifoOverflow() {
    return readUChar(REG_INT_ENABLE) & FIFO_OFLOW_EN;
}

void GestionMPU6050::disableFifoOverflow() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) & ~FIFO_OFLOW_EN);
}

bool GestionMPU6050::isDisableFifoOverflow() {
    return !readUChar(REG_INT_ENABLE) & FIFO_OFLOW_EN;
}

//----------------------------------
// Bits I2C_MST_INT_EN
//----------------------------------

void GestionMPU6050::enableI2CMasterInterrupt() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) | I2C_MST_INT_EN);
}

bool GestionMPU6050::isEnableI2CMasterInterrupt() {
    return readUChar(REG_INT_ENABLE) & I2C_MST_INT_EN;
}

void GestionMPU6050::disableI2CMasterInterrupt() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) & ~I2C_MST_INT_EN);
}

bool GestionMPU6050::isDisableI2CMasterInterrupt() {
    return !readUChar(REG_INT_ENABLE) & I2C_MST_INT_EN;
}

//----------------------------------
// Bits DATA_RDY_EN
//----------------------------------
void GestionMPU6050::enableDataReadyInterrupt() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) | DATA_RDY_EN);
}

bool GestionMPU6050::isEnableDataReadyInterrupt() {
    return readUChar(REG_INT_ENABLE) & DATA_RDY_EN;
}

void GestionMPU6050::disableDataReadyInterrupt() {
    writeUChar(REG_INT_ENABLE, readUChar(REG_INT_ENABLE) & ~DATA_RDY_EN);
}

bool GestionMPU6050::isDisableDataReadyInterrupt() {
    return !readUChar(REG_INT_ENABLE) & DATA_RDY_EN;
}


//++++++++++++++++++++++++++++++++++
// Registre 58 38h INTERRUPT STATUS
//++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits MOT_INT
//----------------------------------
bool GestionMPU6050::isInterruptGenerated() {
    return readUChar(REG_INT_STATUS) & MOT_INT;
}

//----------------------------------
// Bits FIFO_OFLOW_INT
//----------------------------------
bool GestionMPU6050::isFifoOverflow() {
    return readUChar(REG_INT_STATUS) & FIFO_OFLOW_INT;
}

//----------------------------------
// Bits I2C_MST_INT
//----------------------------------
bool GestionMPU6050::isI2CMasterInterrupt() {
    return readUChar(REG_INT_STATUS) & I2C_MST_INT;
}

//----------------------------------
// Bits DATA_RDY_INT
//----------------------------------
bool GestionMPU6050::isDataReady() {
    return readUChar(REG_INT_STATUS) & DATA_RDY_INT;
}


//++++++++++++++++++++++++++++++++++++++++
// Registre 59 60 3Bh 3Ch ACCEL_XOUT
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getAccelX() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_ACCEL_XOUT_H);	
	dataAccel.uCData[0] = readUChar(REG_ACCEL_XOUT_L);	
	return dataAccel.sData;
}

float GestionMPU6050::getAccelXG() {
	switch(getFullScaleRangeAccel()){
		case FS_2G: return (float)getAccelX() / (float)LSB_FS_2G; break;
		case FS_4G: return (float)getAccelX() / (float)LSB_FS_4G; break;
		case FS_8G: return (float)getAccelX() / (float)LSB_FS_8G; break;
		case FS_16G: return (float)getAccelX() / (float)LSB_FS_16G; break;
	}
}

float GestionMPU6050::getAccelXMS() {
	return getAccelXG() * EARTH_GRAVITY_0;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 61 62 3Dh 3Eh ACCEL_YOUT
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getAccelY() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_ACCEL_YOUT_H);	
	dataAccel.uCData[0] = readUChar(REG_ACCEL_YOUT_L);	
	return dataAccel.sData;
}

float GestionMPU6050::getAccelYG() {
	switch(getFullScaleRangeAccel()){
		case FS_2G: return (float)getAccelY() / (float)LSB_FS_2G; break;
		case FS_4G: return (float)getAccelY() / (float)LSB_FS_4G; break;
		case FS_8G: return (float)getAccelY() / (float)LSB_FS_8G; break;
		case FS_16G: return (float)getAccelY() / (float)LSB_FS_16G; break;
	}
}

float GestionMPU6050::getAccelYMS() {
	return getAccelYG() * EARTH_GRAVITY_0;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 63 64 3Fh 40h ACCEL_ZOUT
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getAccelZ() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_ACCEL_ZOUT_H);	
	dataAccel.uCData[0] = readUChar(REG_ACCEL_ZOUT_L);	
	return dataAccel.sData;
}

float GestionMPU6050::getAccelZG() {
	switch(getFullScaleRangeAccel()){
		case FS_2G: return (float)getAccelZ() / (float)LSB_FS_2G; break;
		case FS_4G: return (float)getAccelZ() / (float)LSB_FS_4G; break;
		case FS_8G: return (float)getAccelZ() / (float)LSB_FS_8G; break;
		case FS_16G: return (float)getAccelZ() / (float)LSB_FS_16G; break;
	}
}

float GestionMPU6050::getAccelZMS() {
	return getAccelZG() * EARTH_GRAVITY_0;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 65 66 41h 42h TEMP_OUT
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getTemp() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_TEMP_OUT_H);	
	dataAccel.uCData[0] = readUChar(REG_TEMP_OUT_L);	
	return dataAccel.sData;
}

float GestionMPU6050::getTempDeg() {
	return (float)getTemp() / 340.0 + 36.53;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 67 68 43h 44h GYRO_XOUT
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getGyroX() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_GYRO_XOUT_H);	
	dataAccel.uCData[0] = readUChar(REG_GYRO_XOUT_L);	
	return dataAccel.sData;
}

float GestionMPU6050::getGyroXDegS() {
	switch(getFullScaleRangeGyro()){
		case FS_250: return (float)getGyroX() / (float)LSB_FS_250_10 * 10.0; break;
		case FS_500: return (float)getGyroX() / (float)LSB_FS_500_10 * 10.0; break;
		case FS_1000: return (float)getGyroX() / (float)LSB_FS_1000_10 * 10.0; break;
		case FS_2000: return (float)getGyroX() / (float)LSB_FS_2000_10 * 10.0; break;
	}
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 69 70 45h 46h GYRO_YOUT
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getGyroY() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_GYRO_YOUT_H);	
	dataAccel.uCData[0] = readUChar(REG_GYRO_YOUT_L);	
	return dataAccel.sData;
}

float GestionMPU6050::getGyroYDegS() {
	switch(getFullScaleRangeGyro()){
		case FS_250: return (float)getGyroY() / (float)LSB_FS_250_10 * 10.0; break;
		case FS_500: return (float)getGyroY() / (float)LSB_FS_500_10 * 10.0; break;
		case FS_1000: return (float)getGyroY() / (float)LSB_FS_1000_10 * 10.0; break;
		case FS_2000: return (float)getGyroY() / (float)LSB_FS_2000_10 * 10.0; break;
	}
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 71 72 47h 48h GYRO_ZOUT
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getGyroZ() {
	data dataAccel;
	
	dataAccel.uCData[1] = readUChar(REG_GYRO_ZOUT_H);	
	dataAccel.uCData[0] = readUChar(REG_GYRO_ZOUT_L);	
	return dataAccel.sData;
}

float GestionMPU6050::getGyroZDegS() {
	switch(getFullScaleRangeGyro()){
		case FS_250: return (float)getGyroZ() / (float)LSB_FS_250_10 * 10.0; break;
		case FS_500: return (float)getGyroZ() / (float)LSB_FS_500_10 * 10.0; break;
		case FS_1000: return (float)getGyroZ() / (float)LSB_FS_1000_10 * 10.0; break;
		case FS_2000: return (float)getGyroZ() / (float)LSB_FS_2000_10 * 10.0; break;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++
// Registre 73 to 96 49h to 60h EXTERNAL SENSOR DATA
//++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++
// Registre 99 63h I2C STAVE0 DATA OUT
//++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++
// Registre 100 64h I2C STAVE1 DATA OUT
//++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++
// Registre 101 65h I2C STAVE2 DATA OUT
//++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++
// Registre 102 66h I2C STAVE3 DATA OUT
//++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++
// Registre 103 67h I2C MASTER DELAY CONTROL
//++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++
// Registre 104 68h SIGNAL PATH RESET
//++++++++++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits GYRO_RESET
//----------------------------------
void GestionMPU6050::gyroReset() {
    writeUChar(REG_SIGNAL_PATH_RESET, GYRO_RESET);
}

//----------------------------------
// Bits ACCEL_RESET
//----------------------------------
void GestionMPU6050::accelReset() {
    writeUChar(REG_SIGNAL_PATH_RESET, ACCEL_RESET);
}

//----------------------------------
// Bits TEMP_RESET
//----------------------------------
void GestionMPU6050::tempReset() {
    writeUChar(REG_SIGNAL_PATH_RESET, TEMP_RESET);
}

//++++++++++++++++++++++++++++++++++++++++++
// Registre 105 69h MOTION DETECTION CONTROL
//++++++++++++++++++++++++++++++++++++++++++
void GestionMPU6050::AccelDelayPowerOn(AccelOnDelay pValue) {
    writeUChar(REG_MOT_DETECT_CTRL, pValue);
}

//++++++++++++++++++++++++++++++++++++++++++
// Registre 106 6Ah USER CONTROL
//++++++++++++++++++++++++++++++++++++++++++

//----------------------------------
// Bits FIFO_EN
//----------------------------------
void GestionMPU6050::enableFIFO() {
    writeUChar(REG_USER_CTRL, readUChar(REG_USER_CTRL) | FIFO_EN);
}

bool GestionMPU6050::isEnableFIFO() {
    return readUChar(REG_USER_CTRL) & FIFO_EN;
}

void GestionMPU6050::disableFIFO() {
    writeUChar(REG_USER_CTRL, readUChar(REG_USER_CTRL) & ~FIFO_EN);
}

bool GestionMPU6050::isDisableFIFO() {
    return !readUChar(REG_USER_CTRL) & FIFO_EN;
}

//----------------------------------
// Bits I2C_MST_EN
//----------------------------------
void GestionMPU6050::enableI2CMasterMode() {
    writeUChar(REG_USER_CTRL, readUChar(REG_USER_CTRL) | I2C_MST_EN);
}

bool GestionMPU6050::isEnableI2CMasterMode() {
    return readUChar(REG_USER_CTRL) & I2C_MST_EN;
}

void GestionMPU6050::disableI2CMasterMode() {
    writeUChar(REG_USER_CTRL, readUChar(REG_USER_CTRL) & ~I2C_MST_EN);
}

bool GestionMPU6050::isDisableI2CMasterMode() {
    return !readUChar(REG_USER_CTRL) & I2C_MST_EN;
}

//----------------------------------
// Bits FIFO_RESET
//----------------------------------
void GestionMPU6050::FIFOReset() {
    writeUChar(REG_USER_CTRL, readUChar(REG_USER_CTRL) | FIFO_RESET);
}

//----------------------------------
// Bits I2C_MST_RESET
//----------------------------------
void GestionMPU6050::I2CMasterReset() {
    writeUChar(REG_USER_CTRL, readUChar(REG_USER_CTRL) | I2C_MST_RESET);
}

//----------------------------------
// Bits SIG_COND_RESET
//----------------------------------
void GestionMPU6050::signalPathSensorsReset() {
    writeUChar(REG_USER_CTRL, readUChar(REG_USER_CTRL) | SIG_COND_RESET);
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 107 6Bh PWR_MGMT_1
//++++++++++++++++++++++++++++++++++++++++

//----------------------------------
// Bit DEVICE_RESET
//----------------------------------
void GestionMPU6050::deviceReset() {
    writeUChar(REG_PWR_MGMT_1, DEVICE_RESET);
}

//----------------------------------
// Bit SLEEP
//----------------------------------
void GestionMPU6050::sleep() {
    writeUChar(REG_PWR_MGMT_1, readUChar(REG_PWR_MGMT_1) | SLEEP);
}

void GestionMPU6050::unSleep() {
    writeUChar(REG_PWR_MGMT_1, readUChar(REG_PWR_MGMT_1) & ~SLEEP);
}

bool GestionMPU6050::isSleep() {
    return readUChar(REG_PWR_MGMT_1) & SLEEP;
}

//----------------------------------
// Bit CYCLE
//----------------------------------
void GestionMPU6050::cycle() {
    writeUChar(REG_PWR_MGMT_1, readUChar(REG_PWR_MGMT_1) | CYCLE);
}

void GestionMPU6050::noCycle() {
    writeUChar(REG_PWR_MGMT_1, readUChar(REG_PWR_MGMT_1) & ~CYCLE);
}

bool GestionMPU6050::isCycle() {
    return readUChar(REG_PWR_MGMT_1) & CYCLE;
}

//----------------------------------
// Bit TEMP_DIS
//----------------------------------
void GestionMPU6050::disableTemperatureSensor() {
    writeUChar(REG_PWR_MGMT_1, readUChar(REG_PWR_MGMT_1) | TEMP_DIS);
}

void GestionMPU6050::enableTemperatureSensor() {
    writeUChar(REG_PWR_MGMT_1, readUChar(REG_PWR_MGMT_1) & ~TEMP_DIS);
}

bool GestionMPU6050::isTemperatureSensorEnable() {
    return readUChar(REG_PWR_MGMT_1) & TEMP_DIS;
}

//----------------------------------
// Bits CLKSEL
//----------------------------------
void GestionMPU6050::setClockSource(Clock pSource) {
    writeUChar(REG_PWR_MGMT_1, (readUChar(REG_PWR_MGMT_1) & CLOCK_MASK) | pSource);
}

unsigned short GestionMPU6050::getClockSource() {
    return readUChar(REG_PWR_MGMT_1) & ~CLOCK_MASK;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 108 6Ch POWER MANAGEMENT 2
//++++++++++++++++++++++++++++++++++++++++
//----------------------------------
// Bits LP_WAKE_CTRL
//----------------------------------
void GestionMPU6050::setLpWakeCtrl(LpWakeCtrl pFreq) {
    writeUChar(REG_PWR_MGMT_2, (readUChar(REG_PWR_MGMT_2) & LP_WAKE_CTRL_MASK) | pFreq);
}

unsigned short GestionMPU6050::getLpWakeCtrl() {
    return readUChar(REG_PWR_MGMT_2) & ~LP_WAKE_CTRL_MASK;
}

//----------------------------------
// Bit STBY_XA
//----------------------------------
void GestionMPU6050::stanbyXA() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) | STBY_XA);
}

void GestionMPU6050::activaXA() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) & ~STBY_XA);
}

bool GestionMPU6050::isStanbyXA() {
    return readUChar(REG_PWR_MGMT_2) & STBY_XA;
}

//----------------------------------
// Bit STBY_YA
//----------------------------------
void GestionMPU6050::stanbyYA() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) | STBY_YA);
}

void GestionMPU6050::activaYA() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) & ~STBY_YA);
}

bool GestionMPU6050::isStanbyYA() {
    return readUChar(REG_PWR_MGMT_2) & STBY_YA;
}

//----------------------------------
// Bit STBY_ZA
//----------------------------------
void GestionMPU6050::stanbyZA() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) | STBY_ZA);
}

void GestionMPU6050::activaZA() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) & ~STBY_ZA);
}

bool GestionMPU6050::isStanbyZA() {
    return readUChar(REG_PWR_MGMT_2) & STBY_ZA;
}

//----------------------------------
// Bit STBY_XG
//----------------------------------
void GestionMPU6050::stanbyXG() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) | STBY_XG);
}

void GestionMPU6050::activaXG() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) & ~STBY_XG);
}

bool GestionMPU6050::isStanbyXG() {
    return readUChar(REG_PWR_MGMT_2) & STBY_XG;
}

//----------------------------------
// Bit STBY_YG
//----------------------------------
void GestionMPU6050::stanbyYG() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) | STBY_YG);
}

void GestionMPU6050::activaYG() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) & ~STBY_YG);
}

bool GestionMPU6050::isStanbyYG() {
    return readUChar(REG_PWR_MGMT_2) & STBY_YG;
}

//----------------------------------
// Bit STBY_ZG
//----------------------------------
void GestionMPU6050::stanbyZG() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) | STBY_ZG);
}

void GestionMPU6050::activaZG() {
    writeUChar(REG_PWR_MGMT_2, readUChar(REG_PWR_MGMT_2) & ~STBY_ZG);
}

bool GestionMPU6050::isStanbyZG() {
    return readUChar(REG_PWR_MGMT_2) & STBY_ZG;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 114 115 72h 73h FIFO COUNT REGISTERS
//++++++++++++++++++++++++++++++++++++++++
short GestionMPU6050::getFIFOCount() {
	data dataCount;
	
	dataCount.uCData[1] = readUChar(REG_FIFO_COUNTH);	
	dataCount.uCData[0] = readUChar(REG_FIFO_COUNTL);	
	return dataCount.sData;
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 116 74h FIFO READ WRITE
//++++++++++++++++++++++++++++++++++++++++
unsigned char GestionMPU6050::getFIFOValue() {
	return readUChar(REG_FIFO_R_W);
}

void GestionMPU6050::setFIFOValue(unsigned char pValue) {
	writeUChar(REG_FIFO_R_W, pValue);
}

//++++++++++++++++++++++++++++++++++++++++
// Registre 117 75h WHO_AM_I
//++++++++++++++++++++++++++++++++++++++++
unsigned short GestionMPU6050::whoAmI() {
    return (unsigned short)readUChar(REG_WHO_AM_I);
}

bool GestionMPU6050::isConnectionOK() {
    return whoAmI() == WHO_AM_I_DEFAULT;
}

// *************************
// Destructeur
// *************************
GestionMPU6050::~GestionMPU6050() {
	deviceReset();
}

}

