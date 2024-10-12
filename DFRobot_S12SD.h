/*!
 * @file DFRobot_S12SD.h
 * @brief This is the user manual of S12SD
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [Fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2023-09-25
 * @url https://github.com/DFRobor/DFRobot_S12SD
 */
#ifndef DFROBOT_S12SD_H
#define DFROBOT_S12SD_H

#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_RTU.h"
#include "String.h"
#if (defined ARDUINO_AVR_UNO) && (defined ESP8266)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif

//#define ENABLE_DBG ///< Open the macro, and you can see the detailed procedure of the program.
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

class DFRobot_S12SD:public DFRobot_RTU{
public:
  #define S12SD_DEVICE_ADDR                            0X23
  #define S12SD_INPUTREG_UVS_DATA                      0x06     ///<UVS data
  #define S12SD_INPUTREG_UVS_INDEX                     0x07     ///<UVS index
  #define S12SD_INPUTREG_RISK_LEVEL                    0x08     ///<RISK LEVEL   
  #define S12SD_DEVICE_PID                             0x427c   ///<RISK LEVEL   
  /**
   * @fn DFRobot_S12SD
   * @brief DFRobot_S12SD constructor
   * @param pWire I2C pointer to the TowWire stream, which requires calling begin in the demo to init Arduino I2C config.
   */
  DFRobot_S12SD(TwoWire *pWire = &Wire);

  /**
   * @fn DFRobot_S12SD
   * @brief DFRobot_S12SD constructor
   * @param s   : The serial port pointer to the Stream, which requires calling begin in the demo to init communication serial port config of Arduino main controller, in line with that of SEN0540 device slave.
   * @n DFRobot_S12SD serial port config: 9600 baud rate, 8-bit data bit, no check bit, 1 stop bit, the parameters can't be changed.
   */
  DFRobot_S12SD(Stream *s);
  ~DFRobot_S12SD(){};

  /**
   * @fn begin
   * @brief Init s12sd device
   * @return Return value init status
   * @retval true  Succeed
   * @retval false Failed
   */
  bool begin(void);

  /**
   * @fn readUvOriginalData
   * @brief Read the UV voltage value (0-3300)
   * @return voltage value (mV)
   */
  uint16_t readUvOriginalData(void);

  /**
   * @fn readUvIndexData
   * @brief Read the UV Index
   * @return UV Index
   */
  uint16_t readUvIndexData(void);

  /**
   * @fn readRiskLevelData
   * @brief Read the risk level
   * @return 0-4 (Low Risk,Moderate Risk,High Risk,Very High Risk,Extreme Risk)
   */
  uint16_t readRiskLevelData(void);


private:
  uint8_t  readReg(uint16_t reg, void *pBuf, uint8_t size);
  TwoWire   *_pWire = NULL;
  Stream    *_s = NULL;
  uint8_t   _addr=S12SD_DEVICE_ADDR;
};


#endif
