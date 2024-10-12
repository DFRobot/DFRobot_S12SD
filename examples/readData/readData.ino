/*!
 * @file  readAlsData.ino
 * @brief Run the routine to get UV intensity
 * @n connected table
 * @copyright   Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [fary](feng.yang@dfrobot.com)
 * @version     V1.0
 * @date        2021-08-31
 * @url         https://github.com/DFRobor/DFRobot_S12SD
 */
#include "DFRobot_S12SD.h"

#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#define UARTMODE //Serial mode
//#define I2CMODE //I2C mode
#if defined UARTMODE
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
  SoftwareSerial mySerial(/*rx =*/4, /*tx =*/5);
  DFRobot_S12SD s12sd( /*s =*/&mySerial);
#else
  DFRobot_S12SD s12sd(/*s =*/&Serial1);
#endif
#endif
#if defined I2CMODE
DFRobot_S12SD s12sd(/*pWire = */&Wire);
#endif

void setup()
{
  
#if defined UARTMODE
  //Init MCU communication serial port
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
  mySerial.begin(9600);
#elif defined(ESP32)
  Serial1.begin(9600, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  Serial1.begin(9600);
#endif
#endif
  Serial.begin(115200);
  
  while(s12sd.begin() != true){
    Serial.println(" Sensor initialize failed!!");
    delay(1000);
  }
  Serial.println(" Sensor  initialize success!!");
}
void loop()
{
  uint16_t voltage = s12sd.readUvOriginalData();//Read the UV voltage value
  uint16_t index  = s12sd.readUvIndexData();// Read the UV index,retuen 0-11
  uint16_t level = s12sd.readRiskLevelData();//Read the risk level,retren 0-4 (Low Risk,Moderate Risk,High Risk,Very High Risk,Extreme Risk)
  Serial.print("voltage:"); Serial.print(voltage); Serial.println(" mV");
  Serial.print("index:"); Serial.println(index);
  if(level==0)
    Serial.println("Low Risk");
  else if(level==1)
    Serial.println("Moderate Risk");
  else if(level==2)
    Serial.println("High Risk");
  else if(level==3)
    Serial.println("Very High Risk");
  else if(level==4)
    Serial.println("Extreme Risk");
  delay(100);
}
