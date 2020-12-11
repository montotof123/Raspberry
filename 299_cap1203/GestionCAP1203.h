/*
 * GestionCAP1203.h
 *
 * Created on 05/12/2020
 * Author Totof
 *
 */
 
#ifndef __GestionCAP1203_H__
#define __GestionCAP1203_H__

#include <stdint.h>
#include "GestionI2C.h"

class GestionCAP1203 : GestionI2C {
	public:
		enum DeltaSense {
			SENSITIVITY_CONTROL_DELTA_SENSE_128X   = 0b00000000,
			SENSITIVITY_CONTROL_DELTA_SENSE_64X    = 0b00010000,
			SENSITIVITY_CONTROL_DELTA_SENSE_32X    = 0b00100000,
			SENSITIVITY_CONTROL_DELTA_SENSE_16X    = 0b00110000,
			SENSITIVITY_CONTROL_DELTA_SENSE_8X     = 0b01000000,
			SENSITIVITY_CONTROL_DELTA_SENSE_4X     = 0b01010000,
			SENSITIVITY_CONTROL_DELTA_SENSE_2X     = 0b01100000,
			SENSITIVITY_CONTROL_DELTA_SENSE_1X     = 0b01110000,
			SENSITIVITY_CONTROL_DELTA_SENSE_FILTER = 0b01110000,
			SENSITIVITY_CONTROL_DELTA_SENSE_ERROR  = -1
		};

		enum BaseShift {
			SENSITIVITY_CONTROL_BASE_SHIFT_1X     = 0b00000000,
			SENSITIVITY_CONTROL_BASE_SHIFT_2X     = 0b00000001,
			SENSITIVITY_CONTROL_BASE_SHIFT_4X     = 0b00000010,
			SENSITIVITY_CONTROL_BASE_SHIFT_8X     = 0b00000011,
			SENSITIVITY_CONTROL_BASE_SHIFT_16X    = 0b00000100,
			SENSITIVITY_CONTROL_BASE_SHIFT_32X    = 0b00000101,
			SENSITIVITY_CONTROL_BASE_SHIFT_64X    = 0b00000110,
			SENSITIVITY_CONTROL_BASE_SHIFT_128X   = 0b00000111,
			SENSITIVITY_CONTROL_BASE_SHIFT_256X   = 0b00001000,
			SENSITIVITY_CONTROL_BASE_SHIFT_FILTER = 0b00001111,
			SENSITIVITY_CONTROL_BASE_SHIFT_ERROR  = -1
		};

		enum MaxDur {
			SENSOR_INPUT_MAX_DUR_560MS   = 0b00000000,
			SENSOR_INPUT_MAX_DUR_840MS   = 0b00010000,
			SENSOR_INPUT_MAX_DUR_1120MS  = 0b00100000,
			SENSOR_INPUT_MAX_DUR_1400MS  = 0b00110000,
			SENSOR_INPUT_MAX_DUR_1680MS  = 0b01000000,
			SENSOR_INPUT_MAX_DUR_2240MS  = 0b01010000,
			SENSOR_INPUT_MAX_DUR_2800MS  = 0b01100000,
			SENSOR_INPUT_MAX_DUR_3360MS  = 0b01110000,
			SENSOR_INPUT_MAX_DUR_3920MS  = 0b10000000,
			SENSOR_INPUT_MAX_DUR_4480MS  = 0b10010000,
			SENSOR_INPUT_MAX_DUR_5600MS  = 0b10100000,
			SENSOR_INPUT_MAX_DUR_6720MS  = 0b10110000,
			SENSOR_INPUT_MAX_DUR_7840MS  = 0b11000000,
			SENSOR_INPUT_MAX_DUR_8906MS  = 0b11010000,
			SENSOR_INPUT_MAX_DUR_10080MS = 0b11100000,
			SENSOR_INPUT_MAX_DUR_11200MS = 0b11110000,
			SENSOR_INPUT_MAX_DUR_FILTER  = 0b11110000,
			SENSOR_INPUT_MAX_DUR_ERROR   = -1
		};

		enum RptRate {
			SENSOR_INPUT_RPT_RATE_35MS   = 0b00000000,
			SENSOR_INPUT_RPT_RATE_70MS   = 0b00000001,
			SENSOR_INPUT_RPT_RATE_105MS  = 0b00000010,
			SENSOR_INPUT_RPT_RATE_140MS  = 0b00000011,
			SENSOR_INPUT_RPT_RATE_175MS  = 0b00000100,
			SENSOR_INPUT_RPT_RATE_210MS  = 0b00000101,
			SENSOR_INPUT_RPT_RATE_245MS  = 0b00000110,
			SENSOR_INPUT_RPT_RATE_280MS  = 0b00000111,
			SENSOR_INPUT_RPT_RATE_315MS  = 0b00001000,
			SENSOR_INPUT_RPT_RATE_350MS  = 0b00001001,
			SENSOR_INPUT_RPT_RATE_385MS  = 0b00001010,
			SENSOR_INPUT_RPT_RATE_420MS  = 0b00001011,
			SENSOR_INPUT_RPT_RATE_455MS  = 0b00001100,
			SENSOR_INPUT_RPT_RATE_490MS  = 0b00001101,
			SENSOR_INPUT_RPT_RATE_525MS  = 0b00001110,
			SENSOR_INPUT_RPT_RATE_560MS  = 0b00001111,
			SENSOR_INPUT_RPT_RATE_FILTER = 0b00001111,
			SENSOR_INPUT_RPT_RATE_ERROR  = -1
		};

		enum MPress {
			SENSOR_INPUT_M_PRESS_35MS   = 0b00000000,
			SENSOR_INPUT_M_PRESS_70MS   = 0b00000001,
			SENSOR_INPUT_M_PRESS_105MS  = 0b00000010,
			SENSOR_INPUT_M_PRESS_140MS  = 0b00000011,
			SENSOR_INPUT_M_PRESS_175MS  = 0b00000100,
			SENSOR_INPUT_M_PRESS_210MS  = 0b00000101,
			SENSOR_INPUT_M_PRESS_245MS  = 0b00000110,
			SENSOR_INPUT_M_PRESS_280MS  = 0b00000111,
			SENSOR_INPUT_M_PRESS_315MS  = 0b00001000,
			SENSOR_INPUT_M_PRESS_350MS  = 0b00001001,
			SENSOR_INPUT_M_PRESS_385MS  = 0b00001010,
			SENSOR_INPUT_M_PRESS_420MS  = 0b00001011,
			SENSOR_INPUT_M_PRESS_455MS  = 0b00001100,
			SENSOR_INPUT_M_PRESS_490MS  = 0b00001101,
			SENSOR_INPUT_M_PRESS_525MS  = 0b00001110,
			SENSOR_INPUT_M_PRESS_560MS  = 0b00001111,
			SENSOR_INPUT_M_PRESS_FILTER = 0b00001111,
			SENSOR_INPUT_M_PRESS_ERROR  = -1
		};

		enum Avg {
			AVG_AND_SAMPLING_AVG_1      = 0b00000000,
			AVG_AND_SAMPLING_AVG_2      = 0b00010000,
			AVG_AND_SAMPLING_AVG_4      = 0b00100000,
			AVG_AND_SAMPLING_AVG_8      = 0b00110000,
			AVG_AND_SAMPLING_AVG_16     = 0b01000000,
			AVG_AND_SAMPLING_AVG_32     = 0b01010000,
			AVG_AND_SAMPLING_AVG_64     = 0b01100000,
			AVG_AND_SAMPLING_AVG_128    = 0b01110000,
			AVG_AND_SAMPLING_AVG_FILTER = 0b01110000,
			AVG_AND_SAMPLING_AVG_ERROR  = -1
		};

		enum SampTime {
			AVG_AND_SAMPLING_SAMP_TIME_320US  = 0b00000000,
			AVG_AND_SAMPLING_SAMP_TIME_640US  = 0b00000100,
			AVG_AND_SAMPLING_SAMP_TIME_1280US = 0b00001000,
			AVG_AND_SAMPLING_SAMP_TIME_2560US = 0b00001100,
			AVG_AND_SAMPLING_SAMP_TIME_FILTER = 0b00001100,
			AVG_AND_SAMPLING_SAMP_TIME_ERROR  = -1
		};

		enum CycleTime {
			AVG_AND_SAMPLING_CYCLE_TIME_35MS   = 0b00000000,
			AVG_AND_SAMPLING_CYCLE_TIME_70MS   = 0b00000001,
			AVG_AND_SAMPLING_CYCLE_TIME_105MS  = 0b00000010,
			AVG_AND_SAMPLING_CYCLE_TIME_140MS  = 0b00000011,
			AVG_AND_SAMPLING_CYCLE_TIME_FILTER = 0b00000011,
			AVG_AND_SAMPLING_CYCLE_TIME_ERROR  = -1
		};
		
		enum TouchCS1 {
			OnCs1  = 0b00000001,
			OffCs1 = 0b00000000
		};
		
		enum TouchCS2 {
			OnCs2  = 0b00000010,
			OffCs2 = 0b00000000
		};
		
		enum TouchCS3 {
			OnCs3  = 0b00000100,
			OffCs3 = 0b00000000
		};
		
		
		enum BMultT {
			MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_1      = 0b00000000,
			MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_2      = 0b00000100,
			MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_3      = 0b00001000,
			MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_FILTER = 0b00001100,
			MULTIPLE_TOUCH_CONFIGURATION_B_MULT_T_ERROR  = -1
		};

		enum MtpTh {
			MULTIPLE_TOUCHE_PATTERN_MTP_TH_125P   = 0b00000000,
			MULTIPLE_TOUCHE_PATTERN_MTP_TH_250P   = 0b00000100,
			MULTIPLE_TOUCHE_PATTERN_MTP_TH_375P   = 0b00001000,
			MULTIPLE_TOUCHE_PATTERN_MTP_TH_100P   = 0b00001100,
			MULTIPLE_TOUCHE_PATTERN_MTP_TH_FILTER = 0b00001100,
			MULTIPLE_TOUCHE_PATTERN_MTP_TH_ERROR  = -1
		};

		enum NegDeltaCnt {
			RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_8        = 0b00000000,
			RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_16       = 0b00001000,
			RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_32       = 0b00010000,
			RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_DISABLED = 0b00011000,
			RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_FILTER   = 0b00011000,
			RECALIBRATION_CONFIGURATION_NEG_DELTA_CNT_ERROR    = -1
		};

		enum CalCfg {
			RECALIBRATION_CONFIGURATION_CAL_CFG_16_16    = 0b00000000,
			RECALIBRATION_CONFIGURATION_CAL_CFG_32_32    = 0b00000001,
			RECALIBRATION_CONFIGURATION_CAL_CFG_64_64    = 0b00000010,
			RECALIBRATION_CONFIGURATION_CAL_CFG_128_128  = 0b00000011,
			RECALIBRATION_CONFIGURATION_CAL_CFG_256_256  = 0b00000100,
			RECALIBRATION_CONFIGURATION_CAL_CFG_256_1024 = 0b00000101,
			RECALIBRATION_CONFIGURATION_CAL_CFG_256_2048 = 0b00000110,
			RECALIBRATION_CONFIGURATION_CAL_CFG_256_4096 = 0b00000111,
			RECALIBRATION_CONFIGURATION_CAL_CFG_FILTER   = 0b00000111,
			RECALIBRATION_CONFIGURATION_CAL_CFG_ERROR    = -1
		};

		enum CsBnTh {
			SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_250P   = 0b00000000,
			SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_375P   = 0b00000001,
			SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_500P   = 0b00000010,
			SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_625P   = 0b00000011,
			SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_FILTER = 0b00000011,
			SENSOR_INPUT_NOISE_THRESHOLD_CS_BN_TH_ERROR  = -1
		};

		enum StbyAvg {
			STANDBY_CONFIGURATION_STBY_AVG_1      = 0b00000000,
			STANDBY_CONFIGURATION_STBY_AVG_2      = 0b00010000,
			STANDBY_CONFIGURATION_STBY_AVG_4      = 0b00100000,
			STANDBY_CONFIGURATION_STBY_AVG_8      = 0b00110000,
			STANDBY_CONFIGURATION_STBY_AVG_16     = 0b01000000,
			STANDBY_CONFIGURATION_STBY_AVG_32     = 0b01010000,
			STANDBY_CONFIGURATION_STBY_AVG_64     = 0b01100000,
			STANDBY_CONFIGURATION_STBY_AVG_128    = 0b01110000,
			STANDBY_CONFIGURATION_STBY_AVG_FILTER = 0b01110000,
			STANDBY_CONFIGURATION_STBY_AVG_ERROR  = -1
		};

		enum StbySampTime {
			STANDBY_CONFIGURATION_STBY_SAMP_TIME_320US  = 0b00000000,
			STANDBY_CONFIGURATION_STBY_SAMP_TIME_640US  = 0b00000100,
			STANDBY_CONFIGURATION_STBY_SAMP_TIME_1280US = 0b00001000,
			STANDBY_CONFIGURATION_STBY_SAMP_TIME_2560US = 0b00001100,
			STANDBY_CONFIGURATION_STBY_SAMP_TIME_FILTER = 0b00001100,
			STANDBY_CONFIGURATION_STBY_SAMP_TIME_ERROR  = -1
		};

		enum StbyCyTime {
			STANDBY_CONFIGURATION_STBY_CY_TIME_35MS   = 0b00000000,
			STANDBY_CONFIGURATION_STBY_CY_TIME_70MS   = 0b00000001,
			STANDBY_CONFIGURATION_STBY_CY_TIME_105MS  = 0b00000010,
			STANDBY_CONFIGURATION_STBY_CY_TIME_140MS  = 0b00000011,
			STANDBY_CONFIGURATION_STBY_CY_TIME_FILTER = 0b00000011,
			STANDBY_CONFIGURATION_STBY_CY_TIME_ERROR  = -1
		};

		enum StbySense {
			STANDBY_SENSIBILITY_STBY_SENSE_128X   = 0b00000000,
			STANDBY_SENSIBILITY_STBY_SENSE_64X    = 0b00000001,
			STANDBY_SENSIBILITY_STBY_SENSE_32X    = 0b00000010,
			STANDBY_SENSIBILITY_STBY_SENSE_16X    = 0b00000011,
			STANDBY_SENSIBILITY_STBY_SENSE_8X     = 0b00000100,
			STANDBY_SENSIBILITY_STBY_SENSE_4X     = 0b00000101,
			STANDBY_SENSIBILITY_STBY_SENSE_2X     = 0b00000110,
			STANDBY_SENSIBILITY_STBY_SENSE_1X     = 0b00000111,
			STANDBY_SENSIBILITY_STBY_SENSE_FILTER = 0b00000111,
			STANDBY_SENSIBILITY_STBY_SENSE_ERROR  = -1
		};

		enum PwrBtn {
			POWER_BUTTON_PWR_BTN_CS1    = 0b00000000,
			POWER_BUTTON_PWR_BTN_CS2    = 0b00000001,
			POWER_BUTTON_PWR_BTN_CS3    = 0b00000010,
			POWER_BUTTON_PWR_BTN_FILTER = 0b00000011,
			POWER_BUTTON_PWR_BTN_ERROR  = -1
		};

		enum StbyPwrTime {
			POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_280MS  = 0b00000000,
			POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_560MS  = 0b00010000,
			POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_1120MS = 0b00100000,
			POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_2240MS = 0b00110000,
			POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_FILTER = 0b00110000,
			POWER_BUTTON_CONFIGURATION_STBY_PWR_TIME_ERROR  = -1
		};

		enum PwrTime {
			POWER_BUTTON_CONFIGURATION_PWR_TIME_280MS  = 0b00000000,
			POWER_BUTTON_CONFIGURATION_PWR_TIME_560MS  = 0b00000001,
			POWER_BUTTON_CONFIGURATION_PWR_TIME_1120MS = 0b00000010,
			POWER_BUTTON_CONFIGURATION_PWR_TIME_2240MS = 0b00000011,
			POWER_BUTTON_CONFIGURATION_PWR_TIME_FILTER = 0b00000011,
			POWER_BUTTON_CONFIGURATION_PWR_TIME_ERROR  = -1
		};
		
		enum SensorInputCalibrationLSB {
			SENSOR_INPUT_CALIBRATION_LSB_CS1 = 0b00000011,
			SENSOR_INPUT_CALIBRATION_LSB_CS2 = 0b00001100,
			SENSOR_INPUT_CALIBRATION_LSB_CS3 = 0b00110000
		};

		// Constructeur
		GestionCAP1203(void);
		
		// Initialisation
		bool InitCAP1203(void);
		
		// REG_MAIN_CONTROL
		uint8_t getMainControl(void);
		bool setMainControl(uint8_t);
		
		bool isMainControlStby(void);
		// Synonyme
		#define isStandby isMainControlStby
		bool setMainControlStby(void);
		#define standby setMainControlStby
		bool unSetMainControlStby(void);
		#define active unSetMainControlStby
		
		bool isMainControlDSleep(void);
		#define isDeepSleep isMainControlDSleep
		bool setMainControlDSleep(void);
		#define deepSleep setMainControlDSleep
		bool unSetMainControlDSleep(void);
		#define wakeUp unSetMainControlDSleep

		bool isMainControlInt(void);
		#define isInterrupt isMainControlInt
		bool unSetMainControlInt(void);
		#define validInterrupt unSetMainControlInt
		
		// REG_GENERAL_STATUS      
		uint8_t getGeneralStatut(void);
		bool isGeneralStatutBcOut(void);
		bool isGeneralStatutAcalFail(void);
		bool isGeneralStatutPwr(void);
		#define isPwr isGeneralStatutPwr
		bool isGeneralStatutMult(void);
		#define isMult isGeneralStatutMult
		bool isGeneralStatutMtp(void);
		#define isMtp isGeneralStatutMtp
		bool isGeneralStatutTouch(void);
		#define isTouch isGeneralStatutTouch
		
		// REG_SENSOR_INPUT_STATUS    
		uint8_t getGeneralInputStatut(void);
		bool isGeneralInputStatutCs3(void);
		#define isCs3 isGeneralInputStatutCs3
		bool isGeneralInputStatutCs2(void);
		#define isCs2 isGeneralInputStatutCs2
		bool isGeneralInputStatutCs1(void);
		#define isCs1 isGeneralInputStatutCs1
		
		// REG_NOISE_FLAG_STATUS
		uint8_t getNoiseFlagStatus(void);
		bool isNoiseFlagStatutCs3(void);
		bool isNoiseFlagStatutCs2(void);
		bool isNoiseFlagStatutCs1(void);
		
		// REG_SENSOR_INPUT_1_DELTA_COUNT
		uint8_t getSensorInput1DeltaCount(void);
		
		// REG_SENSOR_INPUT_2_DELTA_COUNT
		uint8_t getSensorInput2DeltaCount(void);
		
		// REG_SENSOR_INPUT_3_DELTA_COUNT
		uint8_t getSensorInput3DeltaCount(void);
		
		// REG_SENSITIVITY_CONTROL
		DeltaSense getSensibilityControlDeltaSense(void);
		BaseShift getSensibilityControlBaseShift(void);
		bool setSensibilityControl(DeltaSense, BaseShift);
		
		// REG_CONFIG
		uint8_t getConfiguration(void);
		bool setConfiguration(uint8_t);
		
		bool isConfigurationTimeOut(void);
		bool setConfigurationTimeOut(void);
		bool unSetConfigurationTimeOut(void);
		
		bool isConfigurationDisDigNoise(void);
		bool setConfigurationDisDigNoise(void);
		bool unSetConfigurationDisDigNoise(void);
		
		bool isConfigurationDisAnaNoise(void);
		bool setConfigurationDisAnaNoise(void);
		bool unSetConfigurationDisAnaNoise(void);
		
		bool isConfigurationMaxDurEn(void);
		bool setConfigurationMaxDurEn(void);
		bool unSetConfigurationMaxDurEn(void);
		
		// REG_SENSOR_INPUT_ENABLE
		uint8_t getSensorInputEnable(void);
		bool setSensorInputEnable(TouchCS1, TouchCS2, TouchCS3);

		bool isSensorInputEnableCs3(void);
		bool setSensorInputEnableCs3(void);
		bool unSetSensorInputEnableCs3(void);

		bool isSensorInputEnableCs2(void);
		bool setSensorInputEnableCs2(void);
		bool unSetSensorInputEnableCs2(void);

		bool isSensorInputEnableCs1(void);
		bool setSensorInputEnableCs1(void);
		bool unSetSensorInputEnableCs1(void);

		// REG_SENSOR_INPUT_CONFIG
		MaxDur getSensorInputConfigMaxDur(void);
		RptRate getSensorInputConfigRptRate(void);
		bool setSensorInputConfig(MaxDur, RptRate);
		
		// REG_SENSOR_INPUT_CONFIG_2
		MPress getSensorInputConfigMPress(void);
		bool setSensorInputConfig(MPress);
		
		// REG_AVERAGING_AND_SAMPLE_CONFIG
		Avg getAverageAndSamplingAvg(void);
		SampTime getAverageAndSamplingSampTime(void);
		CycleTime getAverageAndSamplingCycleTime(void);
		bool setAverageAndSampling(Avg, SampTime, CycleTime);
		
		// REG_CALIBRATION_ACTIVATE_AND_STATUS
		uint8_t getCalibrationActivateAndStatus(void);
		bool setCalibrationActivateAndStatus(TouchCS1, TouchCS2, TouchCS3);

		bool isCalibrationActivateAndStatusCs3(void);
		bool setCalibrationActivateAndStatusCs3(void);

		bool isCalibrationActivateAndStatusCs2(void);
		bool setCalibrationActivateAndStatusCs2(void);

		bool isCalibrationActivateAndStatusCs1(void);
		bool setCalibrationActivateAndStatusCs1(void);
	
		// REG_INTERRUPT_ENABLE
		uint8_t getInterruptEnable(void);
		bool setInterruptEnable(TouchCS1, TouchCS2, TouchCS3);

		bool isInterruptEnableCs3(void);
		bool setInterruptEnableCs3(void);
		bool unSetInterruptEnableCs3(void);

		bool isInterruptEnableCs2(void);
		bool setInterruptEnableCs2(void);
		bool unSetInterruptEnableCs2(void);

		bool isInterruptEnableCs1(void);
		bool setInterruptEnableCs1(void);
		bool unSetInterruptEnableCs1(void);
	
		// REG_REPEAT_RATE_ENABLE
		uint8_t getRepeatRateEnable(void);
		bool setRepeatRateEnable(TouchCS1, TouchCS2, TouchCS3);
		#define repeat setRepeatRateEnable

		bool isRepeatRateEnableCs3(void);
		#define isRepeatCs3 isRepeatRateEnableCs3
		bool setRepeatRateEnableCs3(void);
		#define repeatCs3 setRepeatRateEnableCs3
		bool unSetRepeatRateEnableCs3(void);
		#define noRepeatCs3 unSetRepeatRateEnableCs3

		bool isRepeatRateEnableCs2(void);
		#define isRepeatCs2 isRepeatRateEnableCs2
		bool setRepeatRateEnableCs2(void);
		#define repeatCs2 setRepeatRateEnableCs2
		bool unSetRepeatRateEnableCs2(void);
		#define noRepeatCs2 unSetRepeatRateEnableCs2

		bool isRepeatRateEnableCs1(void);
		#define isRepeatCs1 isRepeatRateEnableCs1
		bool setRepeatRateEnableCs1(void);
		#define repeatCs1 setRepeatRateEnableCs1
		bool unSetRepeatRateEnableCs1(void);
		#define noRepeatCs1 unSetRepeatRateEnableCs1
	
		// REG_MULTIPLE_TOUCH_CONFIG
		BMultT getMultipleTouchConfigurationBMultT(void);
		bool isMultipleTouchConfigurationMultBlkEn(void);
		bool setMultipleTouchConfigurationMultBlkEn(void);
		bool unSetMultipleTouchConfigurationMultBlkEn(void);
		bool setMultipleTouchConfiguration(bool, BMultT);
		
		// REG_MULTIPLE_TOUCH_PATTERN_CONFIG
		MtpTh getMultipleTouchPatternConfigurationMtpTh(void);
		bool isMultipleTouchPatternConfigurationMtpEn(void);
		bool isMultipleTouchPatternConfigurationCompPtrn(void);
		bool isMultipleTouchPatternConfigurationMtpAlert(void);
		bool setMultipleTouchPatternConfiguration(bool, MtpTh, bool, bool);
			
		// REG_MULTIPLE_TOUCH_PATTERN
		uint8_t getMultipleTouchPattern(void);
		bool setMultipleTouchPattern(TouchCS1, TouchCS2, TouchCS3);

		bool isMultipleTouchPatternCs3(void);
		bool setMultipleTouchPatternCs3(void);
		bool unSetMultipleTouchPatternCs3(void);

		bool isMultipleTouchPatternCs2(void);
		bool setMultipleTouchPatternCs2(void);
		bool unSetMultipleTouchPatternCs2(void);

		bool isMultipleTouchPatternCs1(void);
		bool setMultipleTouchPatternCs1(void);
		bool unSetMultipleTouchPatternCs1(void);

		// REG_BASE_COUNT_OUT 
		uint8_t getBaseCountOutOfLimit(void);
		bool isBaseCountOutOfLimitCs3(void);
		bool isBaseCountOutOfLimitCs2(void);
		bool isBaseCountOutOfLimitCs1(void);
		
		// REG_RECALIBRATION_CONFIG
		NegDeltaCnt getRecalibrationConfigNegDeltaCnt(void);
		CalCfg getRecalibrationConfigCalCfg(void);
		bool isRecalibrationConfigButLdTh(void);
		bool isRecalibrationConfigNoClrIntd(void);
		bool isRecalibrationConfigNoClrNeg(void);
		bool setRecalibrationConfig(bool, bool, bool, NegDeltaCnt, CalCfg);
		
		// REG_SENSOR_1_INPUT_THRESH
		uint8_t getSensorInputThreshold1(void);
		bool setSensorInputThreshold1(uint8_t);
		
		// REG_SENSOR_2_INPUT_THRESH
		uint8_t getSensorInputThreshold2(void);
		bool setSensorInputThreshold2(uint8_t);
		
		// REG_SENSOR_3_INPUT_THRESH
		uint8_t getSensorInputThreshold3(void);
		bool setSensorInputThreshold3(uint8_t);
		
		// REG_SENSOR_INPUT_NOISE_THRESH
		CsBnTh getSensorInputNoiseThresholdCsBnTh(void);
		bool setSensorInputNoiseThresholdCsBnTh(CsBnTh);
		
		// REG_STANDBY_CHANNEL
		uint8_t getStandbyChannel(void);
		bool setStandbyChannel(TouchCS1, TouchCS2, TouchCS3);

		bool isStandbyChannelCs3(void);
		bool setStandbyChannelCs3(void);
		bool unSetStandbyChannelCs3(void);

		bool isStandbyChannelCs2(void);
		bool setStandbyChannelCs2(void);
		bool unSetStandbyChannelCs2(void);

		bool isStandbyChannelCs1(void);
		bool setStandbyChannelCs1(void);
		bool unSetStandbyChannelCs1(void);
		
		// REG_STANDBY_CONFIG
		StbyAvg getStandbyConfigurationStbyAvg(void);
		StbySampTime getStandbyConfigurationStbySampTime(void);
		StbyCyTime getStandbyConfigurationStbyCyTime(void);
		bool isStandbyConfigurationAvgSum(void);
		bool setStandbyConfiguration(bool, StbyAvg, StbySampTime, StbyCyTime);
		
		// REG_STANDBY_SENSITIVITY
		StbySense getStandbySensibility(void);
		bool setStandbySensibility(StbySense);
		
		// REG_STANDBY_THRESH
		uint8_t getStandbyThreshold(void);
		bool setStandbyThreshold(uint8_t);
		
		// REG_CONFIG_2
		uint8_t getConfiguration2(void);
		bool setConfiguration2(uint8_t);
		
		bool isConfiguration2BcOutRecal(void);
		bool setConfiguration2BcOutRecal(void);
		bool unSetConfiguration2BcOutRecal(void);
		
		bool isConfiguration2BlkPwrCtrl(void);
		bool setConfiguration2BlkPwrCtrl(void);
		bool unSetConfiguration2BlkPwrCtrl(void);
		
		bool isConfiguration2BcOutInt(void);
		bool setConfiguration2BcOutInt(void);
		bool unSetConfiguration2BcOutInt(void);
		
		bool isConfiguration2ShowRfNoise(void);
		bool setConfiguration2ShowRfNoise(void);
		bool unSetConfiguration2ShowRfNoise(void);
		
		bool isConfiguration2DisRfNoise(void);
		bool setConfiguration2DisRfNoise(void);
		bool unSetConfiguration2DisRfNoise(void);
		
		bool isConfiguration2AcalFailInt(void);
		bool setConfiguration2AcalFailInt(void);
		bool unSetConfiguration2AcalFailInt(void);
		
		bool isConfiguration2IntRelN(void);
		bool setConfiguration2IntRelN(void);
		#define noIntRelease setConfiguration2IntRelN
		bool unSetConfiguration2IntRelN(void);
		#define intRelease unSetConfiguration2IntRelN
		
		// REG_SENSOR_INPUT_1_BASE_COUNT
		uint8_t getSensorInput1BaseCount(void);
		
		// REG_SENSOR_INPUT_2_BASE_COUNT
		uint8_t getSensorInput2BaseCount(void);
		
		// REG_SENSOR_INPUT_3_BASE_COUNT
		uint8_t getSensorInput3BaseCount(void);
		
		// REG_POWER_BUTTON
		PwrBtn getPowerButton(void);
		bool setPowerButton(PwrBtn);
		
		// REG_POWER_BUTTON_CONFIG
		StbyPwrTime getPowerButtonConfigurationStbyPwrTime(void);
		PwrTime getPowerButtonConfigurationPwrTime(void);
		bool isPowerButtonConfigurationStbyPwrEn(void);
		bool isPowerButtonConfigurationPwrEn(void);
		bool setPowerButtonConfiguration(bool, StbyPwrTime, bool, PwrTime);
		
		// REG_SENSOR_INPUT_1_CALIBRATION
		uint16_t getSensorInput1Calibration(void);
		
		// REG_SENSOR_INPUT_2_CALIBRATION
		uint16_t getSensorInput2Calibration(void);
		
		// REG_SENSOR_INPUT_3_CALIBRATION
		uint16_t getSensorInput3Calibration(void);
		
		// REG_PROD_ID
		uint8_t getProductID(void);
		
		// REG_MANUFACTURE_ID
		uint8_t getVendorID(void);
		
		// REG_REVISION
		uint8_t getRevision(void);
		
		// Test circuit
		bool isCAP1203(void);
		
		// Reset default values
		void reset(void);
		
		// Initialisation
		bool activeInit(void);
		bool multInit(void);
		bool pwrInit(void);
		bool standbyInit(void);
		bool lowRepeatInit(void);
		bool activeMinSensInit(void);
		bool activeMaxSensInit(void);

		// Destructeur
		virtual ~GestionCAP1203(void);
	private:
		int8_t genericRead8(uint8_t, const char*);
		bool genericWrite8(uint8_t, uint8_t, const char*);

};

#endif
