#ifndef MYROBOT_H
#define MYROBOT_H

constexpr int trigFront = 33;
constexpr int echoFront = 33;

#include <Wire.h>
#include <SSD1306AsciiWire.h>
#include "sonarClass.h"
#include "LedClass.h"
#include "myMotors.h"
#include "myPhone.h"
#include "myIMU.h"  
//#include "PololuWheelEncoders.h"


#define debugROS             ////if defined they are turned off
//#define debugEncoders
#define debugPI
#define debugRemote
//#define debugMotors 
//#define debugDisplay
//#define debugSensors
//#define debugPhone
//#define debugIMU   

#define DEBUG
//not sure the scope
#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

class myRobotClass
{
private:
  myIMUClass myIMU;
  myPhoneClass myPhone;
  sonarClass sonar1;
  LedClass ledR;
  LedClass ledG;
  LedClass ledB;
  int16_t gotAcX,gotAcY,gotAcZ,gotGyX,gotGyY,gotGyZ;
  int setSpeedL;
  int setSpeedR;
  bool obsSonar;  
  bool obsIR;  

  int sonarD;
  int irD;
  static const int MPU_addr=0x68;  // I2C address of the MPU-6050.  use static const because it is the same constant everytime the function is called.
 
public:
  SSD1306AsciiWire myDisplay;
  myMotorsClass myMotors;

  myRobotClass();
  void initialize();
  void update();
  void updateDisplay(int x, int y, String data);
  void parseCommand(char);
};
#endif
