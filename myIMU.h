#ifndef MYIMU_H
#define MYIMU_H

#include <Wire.h>

class myIMUClass
{
private:
  static const int MPU_addr=0x68;  // I2C address of the MPU-6050
  int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
  
public:
  myIMUClass();
  void initialize();
  void updateIMU();
  int16_t getAcX();
  int16_t getAcY();
  int16_t getAcZ();
  int16_t getGyX();
  int16_t getGyY();
  int16_t getGyZ();
};
#endif
