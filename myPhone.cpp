#include "myPhone.h"
#include "myRobot.h" //for the Serial2 initialization

myPhoneClass::myPhoneClass() : speedL(90), speedR(90),btData(char('a')) {}

bool myPhoneClass::update()
{
	 if (Serial2.available() > 0)
    {
        btData = Serial2.read();
        parseCommand(btData);
        /*
        String value = Serial.readStringUntil('#');
        if (value.length()==7)
        {
            String angle = value.substring(0,3);
            String strength = value.substring(3,6);
            String button = value.substring(6,8);
            Serial.flush();
            value = "";
        }
        */
        return true;
    }
    return false;
    
}

void myPhoneClass::parseCommand(char input)
{
    switch (input)
    {
    case 'a':
        speedL = 135;
        speedR = 135;
        break;

    case 'c':
        speedL = 155;
        speedR = 125;
        break;

    case 'b':
        speedL = 125;
        speedR = 155;
        break;

    case 'd':
        speedL = 90;
        speedR = 90;
        break;

    case 'f':
        speedL = 145;
        speedR = 145;
        break;

    case 'h':
        speedL = 45;
        speedR = 45;
        break;
    case 'e':
        speedL = 90;
        speedR = 90;
        break;
    case 'g':
        speedL = 90;
        speedR = 90;
        break;

    default:
        break;
    }
}
int myPhoneClass::getSpeedL()
{
    return speedL;
}

int myPhoneClass::getSpeedR()
{
    return speedR;
}

char myPhoneClass::getDataBT()
{
    return btData;
}
