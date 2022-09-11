
#include "myMotors.h"

myMotorsClass::myMotorsClass() : motorsL(), motorsR(),speedDiffL(0),speedDiffR(0),lastSpeedUpdate(0), atTargetSpeed(0),actSpeedL(90),actSpeedR(90), encoderL(0),encoderR(0)
{
}

void myMotorsClass::init()
{
    motorsL.attach(S1Pin);
    motorsR.attach(S2Pin);
    delay(50);
   // pinMode(encoderLPin, INPUT_PULLUP);
   // pinMode(encoderRPin, INPUT_PULLUP);
    pinMode(encoderLPin, INPUT);
    pinMode(encoderRPin, INPUT);
    lastSpeedUpdate = millis();
    atTargetSpeed = false;
    writeData(90, 90);
}

void myMotorsClass::writeData(int s1, int s2)
{
    motorsL.write(s1);
    delay(50);
    motorsR.write(s2);
}

bool myMotorsClass::atTarget(int speedL2, int speedR2)
{
    // absolute value
    speedDiffL = actSpeedL > speedL2 ? actSpeedL - speedL2 : speedL2 - actSpeedL;
    speedDiffR = actSpeedR > speedR2 ? actSpeedR - speedR2 : speedR2 - actSpeedR;
    if ((speedDiffL < 2) || (speedDiffR < 2))
        return true;
    else
        return false;
}

void myMotorsClass::update(int speedL1, int speedR1)
{
   atTargetSpeed = atTarget(speedL1, speedR1);
   //DEBUB_PRINT(atTargetSpeed);
  //     Serial.print("from motors speed L = ");
  //  Serial.println(speedL1);
  //  Serial.println(atTargetSpeed);
   if ((millis() - lastSpeedUpdate > acceleration) && (!atTargetSpeed))
    {
        (actSpeedL < speedL1) ? actSpeedL = actSpeedL + speedDiffL / 5 : actSpeedL = actSpeedL;
        (actSpeedL > speedL1) ? actSpeedL = actSpeedL - speedDiffL / 5 : actSpeedL = actSpeedL;
        (actSpeedR < speedR1) ? actSpeedR = actSpeedR + speedDiffR / 5 : actSpeedR = actSpeedR;
        (actSpeedR > speedR1) ? actSpeedR = actSpeedR - speedDiffR / 5 : actSpeedR = actSpeedR;

        lastSpeedUpdate = millis();
        checkData();
        (actSpeedL <= 80 || actSpeedL >= 100 || actSpeedL == 90) ? motorsL.write(actSpeedL) : motorsL.write(90);
        delay(50);
        (actSpeedR <= 80 || actSpeedR >= 100 || actSpeedR == 90) ? motorsR.write(actSpeedR) : motorsR.write(90);
    }
}

void myMotorsClass::checkData()
{
    if (actSpeedL > 165) actSpeedL = 165;
    if (actSpeedL < 15)  actSpeedL = 15;
    if (actSpeedR > 165) actSpeedR = 165;
    if (actSpeedR < 15)  actSpeedR = 15;
}

void myMotorsClass::estop()
{
    motorsL.write(90);
    delay(50);
    motorsR.write(90);
}

void myMotorsClass::odometerL() 
{
    if (digitalRead(encoderLPin)){encoderL = encoderL + 1;}
    else {encoderL = encoderL - 1;}
}
    void myMotorsClass::odometerR() 
{
    if (digitalRead(encoderRPin)){encoderR = encoderR + 1;}
    else {encoderR = encoderR - 1;}
}
//void myMotorsClass::odometerR() {encoderR = encoderR + 1;}
int myMotorsClass::getEncoderL() {return encoderL;}
int myMotorsClass::getEncoderR() {return encoderR;}
void myMotorsClass::resetEncoders() {encoderL = 0;encoderR = 0;}
