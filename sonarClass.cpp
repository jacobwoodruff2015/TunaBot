
#include "sonarClass.h"
#include <NewPing.h>

sonarClass::sonarClass(int trig, int echo) : NewPing(trig, echo, 200), trigPin(trig), echoPin(echo)
{
	init();
}

void sonarClass::init()
{
}
void sonarClass::updateSonar()
	{
		distanceSonar = ping_cm();
		//distanceIR = 2076 / (analogRead(A4) - 11);
		distanceIR = ((2*2476) / (analogRead(A4) - 1))-1;
		obstacleSonar = checkObstacle();
        obstacleIR = checkObstacleIR();

	}

bool sonarClass::checkObstacle()
{
	if ((distanceSonar > 20) || (distanceSonar == 0))
		return 0;
	return 1; // 1 is obstacle present
}

bool sonarClass::checkObstacleIR()
{
	if ((distanceIR > 20) || (distanceIR== 0))
		return 0;
	return 1; // 1 is obstacle present
}

int sonarClass::getDistanceSonar() {return distanceSonar;}
float sonarClass::getDistanceIR() {return distanceIR;}

