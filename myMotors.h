// myMotors.h

#ifndef MYMOTORS_H
#define MYMOTORS_H

#include <Arduino.h>
#include "Servo.h"


constexpr int S2Pin = 8;
constexpr int S1Pin = 10;
constexpr int acceleration = 30;
constexpr int encoderLPin = 4;  
constexpr int encoderRPin = 5;  

class myMotorsClass
{
private:
    Servo motorsL;
    Servo motorsR;
    int speedDiffL, speedDiffR;
    long lastSpeedUpdate;
    bool atTargetSpeed;
    int actSpeedL, actSpeedR;
    volatile long encoderL, encoderR;
    bool atTarget(int, int);
    static const int increment = 5;
    void writeData(int, int);
    void checkData();
    void resetEncoders();
public:
    myMotorsClass();
    void init();
    void estop();
    void update(int, int);
    void odometerL();
    void odometerR();
    int getEncoderL();
    int getEncoderR();   
};
#endif