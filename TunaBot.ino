
#include <Arduino.h>
#include "myRobot.h"
#include <avr/wdt.h>

// timer 0 (controls pin 13, 4);
// timer 1 (controls pin 12, 11);
// timer 2 (controls pin 10, 9);
// timer 3 (controls pin 5, 3, 2);
// timer 4 (controls pin 8, 7, 6);

myRobotClass myRobot;

#ifndef debugEncoders
long encoderLOut = 0;
long encoderROut = 0;

// volatile long encoderL = 0;
// volatile long encoderR = 0;
constexpr int encoderLIntPin = 18; // interupts
constexpr int encoderRIntPin = 19; // interupts

long lastTime;

void odometerL_ISR() { myRobot.myMotors.odometerL(); }
void odometerR_ISR() { myRobot.myMotors.odometerR(); }

// void odometerL_ISR() {encoderL = encoderL + 1;}
// void odometerR_ISR() {encoderR = encoderR + 1;}
#endif

#ifndef debugROS
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Joy.h>

void cmd_vel_cb(const geometry_msgs::Twist &twist)
{
  float demandx = twist.linear.x;
  float demandz = twist.angular.z;
  myRobot.setSpeedL = (0.5 + (demandx + demandz / 2)) * 180;
  myRobot.setSpeedR = (0.5 + (demandx - demandz / 2)) * 180;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", cmd_vel_cb);
ros::NodeHandle nh;
#endif

void setup()
{
  wdt_enable(WDTO_2S);
  myRobot.initialize();
#ifndef debugEncoders
  pinMode(encoderLIntPin, INPUT_PULLUP);
  pinMode(encoderRIntPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderLIntPin), odometerR_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderRIntPin), odometerL_ISR, RISING);
#endif
#ifndef debugROS
  nh.initNode();
  nh.subscribe(sub);
#endif
  pinMode(A2, OUTPUT);
  // digitalWrite(A2, HIGH);
  // delay(500);
  // digitalWrite(A2, LOW);
  // delay(500);
  // tone(A2,200);
  // delay(500);
  // noTone(A2);
}

void loop()
{
  wdt_reset();
#ifndef debugEncoders
  static long encoderDelay = millis();
#ifndef debugDisplay
  if ((millis() - encoderDelay) > 100)
  {
    encoderDelay = millis();
    noInterrupts();
    encoderLOut = myRobot.myMotors.getEncoderL();
    encoderROut = myRobot.myMotors.getEncoderR();
    // encoderLOut = encoderL;
    // encoderROut = encoderR;
    interrupts();
    myRobot.myDisplay.set1X();
    myRobot.myDisplay.setCursor(0, 4);
    myRobot.myDisplay.clearToEOL();
    String enc = "enc " + String(encoderLOut) + " " + String(encoderROut);
    myRobot.myDisplay.print(enc);
    myRobot.myDisplay.set2X();
  }
#endif
#endif
  myRobot.update();

#ifndef debugROS
  nh.spinOnce();
  delay(50);
#endif
}