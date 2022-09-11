#ifndef SONARCLASS_H
#define SONARCLASS_H

#include <NewPing.h>
#include <Wire.h>

class sonarClass : public NewPing
{
private:
    int trigPin;
    int echoPin;
    int distanceSonar, distanceIR;
    bool checkObstacle();
    bool checkObstacleIR();
    void init();

public:
    sonarClass(int tPin, int ePin); 
    void updateSonar();
    int getDistanceSonar();
    float getDistanceIR();
    bool obstacleSonar;
    bool obstacleIR;
};

#endif
