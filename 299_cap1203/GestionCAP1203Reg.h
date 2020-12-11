/*
 * GestionCAP1203Reg.h
 *
 * Created on 05/12/2020
 * Author Totof
 *
 */

#ifndef __GestionCAP1203Reg_H__
#define __GestionCAP1203Reg_H__

#define I2C_ADDR                                     0x28

#define REG_MAIN_CONTROL                             0x00
#define REG_GENERAL_STATUS                           0x02
#define REG_SENSOR_INPUT_STATUS                      0x03
#define REG_NOISE_FLAG_STATUS                        0x0A
#define REG_SENSOR_INPUT_1_DELTA_COUNT               0x10
#define REG_SENSOR_INPUT_2_DELTA_COUNT               0x11
#define REG_SENSOR_INPUT_3_DELTA_COUNT               0x12
#define REG_SENSITIVITY_CONTROL                      0x1F
#define REG_CONFIG                                   0x20
#define REG_SENSOR_INPUT_ENABLE                      0x21
#define REG_SENSOR_INPUT_CONFIG                      0x22
#define REG_SENSOR_INPUT_CONFIG_2                    0x23
#define REG_AVERAGING_AND_SAMPLE_CONFIG              0x24
#define REG_CALIBRATION_ACTIVATE_AND_STATUS          0x26
#define REG_INTERRUPT_ENABLE                         0x27
#define REG_REPEAT_RATE_ENABLE                       0x28
#define REG_MULTIPLE_TOUCH_CONFIG                    0x2A
#define REG_MULTIPLE_TOUCH_PATTERN_CONFIG            0x2B
#define REG_MULTIPLE_TOUCH_PATTERN                   0x2D
#define REG_BASE_COUNT_OUT                           0x2E
#define REG_RECALIBRATION_CONFIG                     0x2F
#define REG_SENSOR_1_INPUT_THRESH                    0x30
#define REG_SENSOR_2_INPUT_THRESH                    0x31
#define REG_SENSOR_3_INPUT_THRESH                    0x32
#define REG_SENSOR_INPUT_NOISE_THRESH                0x38
#define REG_STANDBY_CHANNEL                          0x40
#define REG_STANDBY_CONFIG                           0x41
#define REG_STANDBY_SENSITIVITY                      0x42
#define REG_STANDBY_THRESH                           0x43
#define REG_CONFIG_2                                 0x44
#define REG_SENSOR_INPUT_1_BASE_COUNT                0x50
#define REG_SENSOR_INPUT_2_BASE_COUNT                0x51
#define REG_SENSOR_INPUT_3_BASE_COUNT                0x52
#define REG_POWER_BUTTON                             0x60
#define REG_POWER_BUTTON_CONFIG                      0x61
#define REG_SENSOR_INPUT_1_CALIBRATION               0xB1
#define REG_SENSOR_INPUT_2_CALIBRATION               0xB2
#define REG_SENSOR_INPUT_3_CALIBRATION               0xB3
#define REG_SENSOR_INPUT_CALIBRATION_LSB_1           0xB9
#define REG_PROD_ID                                  0xFD
#define REG_MANUFACTURE_ID                           0xFE
#define REG_REVISION                                 0xFF

#define CS3                                          0b00000100
#define CS2                                          0b00000010
#define CS1                                          0b00000001

#define MAIN_CONTROL_STBY                            0b00100000
#define MAIN_CONTROL_DSLEEP                          0b00010000
#define MAIN_CONTROL_INT                             0b00000001

#define GENERAL_STATUS_BC_OUT                        0b01000000
#define GENERAL_STATUS_ACAIL_FAIL                    0b00100000
#define GENERAL_STATUS_PWR                           0b00010000
#define GENERAL_STATUS_MULT                          0b00000100
#define GENERAL_STATUS_MTP                           0b00000010
#define GENERAL_STATUS_TOUCH                         0b00000001

#define CONFIG_TIMEOUT                               0b10000000        
#define CONFIG_DIS_DIG_NOISE                         0b00100000              
#define CONFIG_DIS_ANA_NOISE                         0b00010000              
#define CONFIG_MAX_DUR_EN                            0b00001000      

#define MULTIPLE_TOUCH_CONFIG_MULTI_BLK_EN           0b10000000

#define MULTIPLE_TOUCH_PATTERN_CONFIG_MTP_EN         0b10000000
#define MULTIPLE_TOUCH_PATTERN_CONFIG_COMP_PTRN      0b00000010
#define MULTIPLE_TOUCH_PATTERN_CONFIG_MTP_ALERT      0b00000001

#define RECALIBRATION_CONFIG_BUT_LD_TH               0b10000000
#define RECALIBRATION_CONFIG_NO_CLR_INTD             0b01000000
#define RECALIBRATION_CONFIG_NO_CLR_NEG              0b00100000

#define STANDBY_CONFIG_AVG_SUM                       0b10000000

#define CONFIG2_BC_OUT_RECAL                         0b01000000        
#define CONFIG2_BLK_PWR_CTRL                         0b00100000        
#define CONFIG2_BC_OUT_INT                           0b00010000        
#define CONFIG2_SHOW_RF_NOISE                        0b00001000        
#define CONFIG2_DIS_RF_NOISE                         0b00000100        
#define CONFIG2_ACAL_FAIL_INT                        0b00000010        
#define CONFIG2_INT_REL_N                            0b00000001        

#define POWER_BUTTON_CONFIG_STBY_PWR_EN              0b01000000
#define POWER_BUTTON_CONFIG_PWR_EN                   0b00000100

#define PROD_ID_PRODUCT_ID                           0x6D
#define MANUFACTURE_ID_VENDOR_ID                     0x5D

#define MAIN_CONTROL_RESET                           0x00
#define CONFIGURATION_RESET                          0x20                    
#define SENSOR_INPUT_THRESHOLD_RESET                 0x40
#define CONFIGURATION2_RESET                         0x40                    
 
#endif