/*
 * GestionMCU6050.h
 *
 *  Created on: 28 january 2017
 *      Author: totof
 * Controle un module MPU6050
 */

#ifndef _GESTION_MPU6050_H_
#define _GESTION_MPU6050_H_

#define WHO_AM_I_DEFAULT 0x68
#define EARTH_GRAVITY_0 9.80665

namespace std {

enum Adresse {
	ADDRESS_AD0_LOW = 0x68,
	ADDRESS_AD0_HIGH = 0x69
};

enum Registre {
	REG_XG_OFFS_TC = 0x00, //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
	REG_YG_OFFS_TC = 0x01, //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
	REG_ZG_OFFS_TC = 0x02, //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
	REG_X_FINE_GAIN = 0x03, //[7:0] X_FINE_GAIN
	REG_Y_FINE_GAIN = 0x04, //[7:0] Y_FINE_GAIN
	REG_Z_FINE_GAIN = 0x05, //[7:0] Z_FINE_GAIN
	REG_XA_OFFS_H = 0x06, //[15:0] XA_OFFS
	REG_XA_OFFS_L_TC = 0x07,
	REG_YA_OFFS_H = 0x08, //[15:0] YA_OFFS
	REG_YA_OFFS_L_TC = 0x09,
	REG_ZA_OFFS_H = 0x0A, //[15:0] ZA_OFFS
	REG_ZA_OFFS_L_TC = 0x0B,
	REG_SELF_TEST_X = 0x0D, //[7:5] XA_TEST[4-2], [4:0] XG_TEST[4-0]
	REG_SELF_TEST_Y = 0x0E, //[7:5] YA_TEST[4-2], [4:0] YG_TEST[4-0]
	REG_SELF_TEST_Z = 0x0F, //[7:5] ZA_TEST[4-2], [4:0] ZG_TEST[4-0]
	REG_SELF_TEST_A = 0x10, //[5:4] XA_TEST[1-0], [3:2] YA_TEST[1-0], [1:0] ZA_TEST[1-0]
	REG_XG_OFFS_USRH = 0x13, //[15:0] XG_OFFS_USR
	REG_XG_OFFS_USRL = 0x14,
	REG_YG_OFFS_USRH = 0x15, //[15:0] YG_OFFS_USR
	REG_YG_OFFS_USRL = 0x16,
	REG_ZG_OFFS_USRH = 0x17, //[15:0] ZG_OFFS_USR
	REG_ZG_OFFS_USRL = 0x18,
	REG_SMPLRT_DIV = 0x19,
	REG_CONFIG = 0x1A,
	REG_GYRO_CONFIG = 0x1B,
	REG_ACCEL_CONFIG = 0x1C,
	REG_FF_THR = 0x1D,
	REG_FF_DUR = 0x1E,
	REG_MOT_THR = 0x1F,
	REG_MOT_DUR = 0x20,
	REG_ZRMOT_THR = 0x21,
	REG_ZRMOT_DUR = 0x22,
	REG_FIFO_EN = 0x23,
	REG_I2C_MST_CTRL = 0x24,
	REG_I2C_SLV0_ADDR = 0x25,
	REG_I2C_SLV0_REG = 0x26,
	REG_I2C_SLV0_CTRL = 0x27,
	REG_I2C_SLV1_ADDR = 0x28,
	REG_I2C_SLV1_REG = 0x29,
	REG_I2C_SLV1_CTRL = 0x2A,
	REG_I2C_SLV2_ADDR = 0x2B,
	REG_I2C_SLV2_REG = 0x2C,
	REG_I2C_SLV2_CTRL = 0x2D,
	REG_I2C_SLV3_ADDR = 0x2E,
	REG_I2C_SLV3_REG = 0x2F,
	REG_I2C_SLV3_CTRL = 0x30,
	REG_I2C_SLV4_ADDR = 0x31,
	REG_I2C_SLV4_REG = 0x32,
	REG_I2C_SLV4_DO = 0x33,
	REG_I2C_SLV4_CTRL = 0x34,
	REG_I2C_SLV4_DI = 0x35,
	REG_I2C_MST_STATUS = 0x36,
	REG_INT_PIN_CFG = 0x37,
	REG_INT_ENABLE = 0x38,
	REG_DMP_INT_STATUS = 0x39,
	REG_INT_STATUS = 0x3A,
	REG_ACCEL_XOUT_H = 0x3B,
	REG_ACCEL_XOUT_L = 0x3C,
	REG_ACCEL_YOUT_H = 0x3D,
	REG_ACCEL_YOUT_L = 0x3E,
	REG_ACCEL_ZOUT_H = 0x3F,
	REG_ACCEL_ZOUT_L = 0x40,
	REG_TEMP_OUT_H = 0x41,
	REG_TEMP_OUT_L = 0x42,
	REG_GYRO_XOUT_H = 0x43,
	REG_GYRO_XOUT_L = 0x44,
	REG_GYRO_YOUT_H = 0x45,
	REG_GYRO_YOUT_L = 0x46,
	REG_GYRO_ZOUT_H = 0x47,
	REG_GYRO_ZOUT_L = 0x48,
	REG_EXT_SENS_DATA_00 = 0x49,
	REG_EXT_SENS_DATA_01 = 0x4A,
	REG_EXT_SENS_DATA_02 = 0x4B,
	REG_EXT_SENS_DATA_03 = 0x4C,
	REG_EXT_SENS_DATA_04 = 0x4D,
	REG_EXT_SENS_DATA_05 = 0x4E,
	REG_EXT_SENS_DATA_06 = 0x4F,
	REG_EXT_SENS_DATA_07 = 0x50,
	REG_EXT_SENS_DATA_08 = 0x51,
	REG_EXT_SENS_DATA_09 = 0x52,
	REG_EXT_SENS_DATA_10 = 0x53,
	REG_EXT_SENS_DATA_11 = 0x54,
	REG_EXT_SENS_DATA_12 = 0x55,
	REG_EXT_SENS_DATA_13 = 0x56,
	REG_EXT_SENS_DATA_14 = 0x57,
	REG_EXT_SENS_DATA_15 = 0x58,
	REG_EXT_SENS_DATA_16 = 0x59,
	REG_EXT_SENS_DATA_17 = 0x5A,
	REG_EXT_SENS_DATA_18 = 0x5B,
	REG_EXT_SENS_DATA_19 = 0x5C,
	REG_EXT_SENS_DATA_20 = 0x5D,
	REG_EXT_SENS_DATA_21 = 0x5E,
	REG_EXT_SENS_DATA_22 = 0x5F,
	REG_EXT_SENS_DATA_23 = 0x60,
	REG_MOT_DETECT_STATUS = 0x61,
	REG_I2C_SLV0_DO = 0x63,
	REG_I2C_SLV1_DO = 0x64,
	REG_I2C_SLV2_DO = 0x65,
	REG_I2C_SLV3_DO = 0x66,
	REG_I2C_MST_DELAY_CTRL = 0x67,
	REG_SIGNAL_PATH_RESET = 0x68,
	REG_MOT_DETECT_CTRL = 0x69,
	REG_USER_CTRL = 0x6A,
	REG_PWR_MGMT_1 = 0x6B,
	REG_PWR_MGMT_2 = 0x6C,
	REG_BANK_SEL = 0x6D,
	REG_MEM_START_ADDR = 0x6E,
	REG_MEM_R_W = 0x6F,
	REG_DMP_CFG_1 = 0x70,
	REG_DMP_CFG_2 = 0x71,
	REG_FIFO_COUNTH = 0x72,
	REG_FIFO_COUNTL = 0x73,
	REG_FIFO_R_W = 0x74,
	REG_WHO_AM_I = 0x75
};

enum Clock {
	INTERNAL = 0x00,   //xxxx x000
	PLL_XGYRO = 0x01,  //xxxx x001
	PLL_YGYRO = 0x02,  //xxxx x010
	PLL_ZGYRO = 0x03,  //xxxx x011
	EXT32K = 0x04,     //xxxx x100
	EXT19M = 0x05,     //xxxx x101
	KEEP_RESET = 0x07, //xxxx x111
	CLOCK_MASK = 0xF8  //1111 1xxx     
};

enum PowerManagement1 {
	DEVICE_RESET = 0x80, //1xxx xxxx
	SLEEP = 0x40,        //x1xx xxxx
	CYCLE = 0x20,        //xx1x xxxx
	TEMP_DIS = 0x08	     //xxxx 1xxx
};

enum LpWakeCtrl {
	LP_WAKE_CTRL_MASK = 0x3F, // xx111111
	LP_WAKE_CTRL_1_25HZ = 0x00, // 00xxxxxx
	LP_WAKE_CTRL_5HZ = 0x40, // 01xxxxxx
	LP_WAKE_CTRL_20HZ = 0x80, // 10xxxxxx
	LP_WAKE_CTRL_40HZ = 0xB0 // 11xxxxxx
};

enum PowerManagement2 {
	STBY_XA = 0x20, // xx1xxxxx
	STBY_YA = 0x10, // xxx1xxxx
	STBY_ZA = 0x08, // xxxx1xxx
	STBY_XG = 0x04, // xxxxx1xx
	STBY_YG = 0x02, // xxxxxx1x
	STBY_ZG = 0x01 // xxxxxxx1
};

enum GyroSensibility {
	FS_250 = 0x00,   //xxx0 0xxx
	FS_500 = 0x08,   //xxx0 1xxx
	FS_1000 = 0x10,  //xxx1 0xxx
	FS_2000 = 0x18,  //xxx1 1xxx
	LSB_FS_250_10 = 1310, 
	LSB_FS_500_10 = 655,  
	LSB_FS_1000_10 = 328,  
	LSB_FS_2000_10 = 164, 
	GYRO_MASK = 0xE7 //111x x111
};

enum GyroConfiguration {
	XG_ST = 0x80, //1xxx xxxx
	YG_ST = 0x40, //x1xx xxxx
	ZG_ST = 0x20  //xx1x xxxx
};

enum AccelSensibility {
	FS_2G = 0x00,     //xxx0 0xxx
	FS_4G = 0x08,     //xxx0 1xxx
	FS_8G = 0x10,     //xxx1 0xxx
	FS_16G = 0x18,    //xxx1 1xxx
	LSB_FS_2G = 16384, 
	LSB_FS_4G = 8192,  
	LSB_FS_8G = 4096,  
	LSB_FS_16G = 2048, 
	ACCEL_MASK = 0xE7 //111x x111
};

enum AccelConfiguration {
	XA_ST = 0x80, //1xxx xxxx
	YA_ST = 0x40, //x1xx xxxx
	ZA_ST = 0x20  //xx1x xxxx
};

enum FifoEnable {
	TEMP_FIFO_EN = 0x80, //1xxx xxxx
	XG_FIFO_EN = 0x40, //x1xx xxxx
	YG_FIFO_EN = 0x20, //xx1x xxxx
	ZG_FIFO_EN = 0x10, //xxx1 xxxx
	ACCEL_FIFO_EN = 0x08, //xxxx 1xxx
	SLV2_FIFO_EN = 0x04, //xxxx x1xx
	SLV1_FIFO_EN = 0x02, //xxxx xx1x
	SLV0_FIFO_EN = 0x01 //xxxx xxx1
};

enum SelfTest {
	A_TEST_H = 0xE0, // 111xxxxx
	XA_TEST_L = 0x30, // xx11xxxx
	YA_TEST_L = 0x0B, // xxxx11xx
	ZA_TEST_L = 0x03, // xxxxxx11
	G_TEST = 0x1F // xxx11111
};

enum Config {
	EXT_SYNC_SET = 0x38, // xx111xxx
	DLPF_CFG = 0x07 // xxxxx111
};

enum IntPinCfg {
	INT_LEVEL = 0x80, //1xxx xxxx
	INT_OPEN = 0x40, //x1xx xxxx
	LATCH_INT_EN = 0x20, //xx1x xxxx
	INT_RD_CLEAR = 0x10, //xxx1 xxxx
	FSYNC_INT_LEVEL = 0x08, //xxxx 1xxx
	FSYNC_INT_EN = 0x04, //xxxx x1xx
	I2C_BYPASS_EN = 0x02 //xxxx xx1x
};

enum IntEnable {
	MOT_EN = 0x40, //x1xx xxxx
	FIFO_OFLOW_EN = 0x10, //xxx1 xxxx
	I2C_MST_INT_EN = 0x08, //xxxx 1xxx
	DATA_RDY_EN = 0x01 //xxxx xxx1
};

enum IntStatus {
	MOT_INT = 0x40, //x1xx xxxx
	FIFO_OFLOW_INT = 0x10, //xxx1 xxxx
	I2C_MST_INT = 0x08, //xxxx 1xxx
	DATA_RDY_INT = 0x01 //xxxx xxx1
};

enum Reset {
	GYRO_RESET = 0x04, // xxxx x1xx
	ACCEL_RESET = 0x02, // xxxx xx1x
	TEMP_RESET = 0x01 // xxxx xxx1
};

enum AccelOnDelay {
	DELAY_0 = 0x00, //xx00 xxxx
	DELAY_1 = 0x10, //xx01 xxxx
	DELAY_2 = 0x20, //xx10 xxxx
	DELAY_3 = 0x30 //xx11 xxxx
};

enum UserControl {
	FIFO_EN = 0x40, //x1xx xxxx
	I2C_MST_EN = 0x20, //xx1x xxxx
	FIFO_RESET = 0x04, //xxxx x1xx
	I2C_MST_RESET = 0x02, //xxxx xx1x
	SIG_COND_RESET = 0x01 //xxxx xxx1
};

class GestionMPU6050 {
    public:
		GestionMPU6050(Adresse);
		void defaultInitialize();
		
		short getXAccelOffset();
		short getYAccelOffset();
		short getZAccelOffset();
		void setXAccelOffset(short);
		void setYAccelOffset(short);
		void setZAccelOffset(short);
		
		unsigned char getXATest();
		void setXATest(unsigned char);
		unsigned char getYATest();
		void setYATest(unsigned char);
		unsigned char getZATest();
		void setZATest(unsigned char);
		
		short getXGyroOffset();
		short getYGyroOffset();
		short getZGyroOffset();
		void setXGyroOffset(short);
		void setYGyroOffset(short);
		void setZGyroOffset(short);

		void setSampleRateDivider(unsigned char);
		unsigned short getSampleRateDivider();
		unsigned char getExtSyncSet();
		void setExtSyncSet(unsigned char);
		unsigned char getDlpfCfg();
		void setDlpfCfg(unsigned char);

		void setFullScaleRangeGyro(GyroSensibility);
		unsigned short getFullScaleRangeGyro();
		void disableGyroXSelfTest();
		void enableGyroXSelfTest();
		bool isGyroXSelfTest();
		void disableGyroYSelfTest();
		void enableGyroYSelfTest();
		bool isGyroYSelfTest();
		void disableGyroZSelfTest();
		void enableGyroZSelfTest();
		bool isGyroZSelfTest();
		
		void setFullScaleRangeAccel(AccelSensibility);
		unsigned short getFullScaleRangeAccel();
		void disableAccelXSelfTest();
		void enableAccelXSelfTest();
		bool isAccelXSelfTest();
		void disableAccelYSelfTest();
		void enableAccelYSelfTest();
		bool isAccelYSelfTest();
		void disableAccelZSelfTest();
		void enableAccelZSelfTest();
		bool isAccelZSelfTest();

		void setMotionDetectionThreshold(unsigned char pValue);
		unsigned short getMotionDetectionThreshold();
		void enableTempFifo();
		void disableTempFifo();
		bool isTempFifo();
		void enableXgFifo();
		void disableXgFifo();
		bool isXgFifo();
		void enableYgFifo();
		void disableYgFifo();
		bool isYgFifo();
		void enableZgFifo();
		void disableZgFifo();
		bool isZgFifo();
		void enableAccelFifo();
		void disableAccelFifo();
		bool isAccelFifo();
		void enableSlv2Fifo();
		void disableSlv2Fifo();
		bool isSlv2Fifo();
		void enableSlv1Fifo();
		void disableSlv1Fifo();
		bool isSlv1Fifo();
		void enableSlv0Fifo();
		void disableSlv0Fifo();
		bool isSlv0Fifo();
		void intPinActiveLow();
		bool isIntPinActiveLow();
		void intPinActiveHigh();
		bool isIntPinActiveHigh();
		void intPinOpenDrain();
		bool isIntPinOpenDrain();
		void intPinPushPull();
		bool isIntPinPushPull();
		void intPinHeldHigh();
		bool isIntPinHeldHigh();
		void intPinPulse();
		bool isIntPinPulse();
		void statusClearedByAnyRead();
		bool isstatusClearedByAnyRead();
		void statusClearedByReadIntStatus();
		bool isStatusClearedByReadIntStatus();
		void fsyncPinActiveLow();
		bool isFsyncPinActiveLow();
		void fsyncPinActiveHigh();
		bool isfsyncPinActiveHigh();
		void disableFsyncPinInterrupt();
		bool isDisableFsyncPinInterrupt();
		void enableFsyncPinInterrupt();
		bool isEnableFsyncPinInterrupt();
		void directlyAccessAuxI2C();
		bool isDirectlyAccessAuxI2C();
		void notDirectlyAccessAuxI2C();
		bool isNotDirectlyAccessAuxI2C();
		void enableDetectionInterrupt();
		bool isEnableDetectionInterrupt();
		void disableDetectionInterrupt();
		bool isDisableDetectionInterrupt();
		void enableFifoOverflow();
		bool isEnableFifoOverflow();
		void disableFifoOverflow();
		bool isDisableFifoOverflow();
		void enableI2CMasterInterrupt();
		bool isEnableI2CMasterInterrupt();
		void disableI2CMasterInterrupt();
		bool isDisableI2CMasterInterrupt();
		void enableDataReadyInterrupt();
		bool isEnableDataReadyInterrupt();
		void disableDataReadyInterrupt();
		bool isDisableDataReadyInterrupt();
		bool isInterruptGenerated();
		bool isFifoOverflow();
		bool isI2CMasterInterrupt();
		bool isDataReady();
 		
		short getAccelX();
		float getAccelXG();
		float getAccelXMS();
		short getAccelY();
		float getAccelYG();
		float getAccelYMS();
		short getAccelZ();
		float getAccelZG();
		float getAccelZMS();
		short getTemp();
		float getTempDeg();
		short getGyroX();
		float getGyroXDegS();
		short getGyroY();
		float getGyroYDegS();
		short getGyroZ();
		float getGyroZDegS();
		
		void gyroReset();
		void accelReset();
		void tempReset();
		void AccelDelayPowerOn(AccelOnDelay);
		void enableFIFO();
		bool isEnableFIFO();
		void disableFIFO();
		bool isDisableFIFO();
		void enableI2CMasterMode();
		bool isEnableI2CMasterMode();
		void disableI2CMasterMode();
		bool isDisableI2CMasterMode();
		void FIFOReset();
		void I2CMasterReset();
		void signalPathSensorsReset();

		void deviceReset(); 
		void sleep();
		void unSleep();
		bool isSleep();
		void cycle();
		void noCycle();
		bool isCycle();
		void disableTemperatureSensor();
		void enableTemperatureSensor();
		bool isTemperatureSensorEnable();
		void setClockSource(Clock);
		unsigned short getClockSource();

		void setLpWakeCtrl(LpWakeCtrl);
		unsigned short getLpWakeCtrl();
		void stanbyXA();
		void activaXA();
		bool isStanbyXA();
		void stanbyYA();
		void activaYA();
		bool isStanbyYA();
		void stanbyZA();
		void activaZA();
		bool isStanbyZA();
		void stanbyXG();
		void activaXG();
		bool isStanbyXG();
		void stanbyYG();
		void activaYG();
		bool isStanbyYG();
		void stanbyZG();
		void activaZG();
		bool isStanbyZG();
		short getFIFOCount();
		unsigned char getFIFOValue();
		void setFIFOValue(unsigned char);

		unsigned short whoAmI();
		bool isConnectionOK();
		
		virtual ~GestionMPU6050();

    private:
		union data{
			short sData;
			unsigned char uCData[2];
		};	
        int fd;
		unsigned char readUChar(Registre);
		void writeUChar(Registre, unsigned char);
};
}

#endif /* _GESTION_MPU6050_H_ */