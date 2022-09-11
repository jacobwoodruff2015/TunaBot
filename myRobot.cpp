#include "myRobot.h"

myRobotClass::myRobotClass() : myIMU(), myPhone(), sonar1(33, 33),
                               ledR(45), ledG(47), ledB(46),
                               gotAcX(0), gotAcY(0), gotAcZ(0), gotGyX(0), gotGyY(0), gotGyZ(0),
                               setSpeedL(90), setSpeedR(90),
                               obsSonar(1), obsIR(1), sonarD(0), irD(0), myDisplay(), myMotors()
{
    pinMode(A4, INPUT);  // battery voltage
    pinMode(A10, INPUT); // other battery voltage
}

void myRobotClass::initialize()
{
    Serial.begin(57600);
    Serial2.begin(9600);

    pinMode(A4, INPUT);
    ledR.init();
    ledG.init();
    ledB.init();
#ifndef debugDisplay
    ledB.on();
    if (TWCR == 0)
    {
        Wire.begin();
    }
    Wire.setClock(400000L);
    myDisplay.begin(&Adafruit128x64, 0x3C);
    delay(1000); ledB.off();
    myDisplay.setFont(Adafruit5x7);
    myDisplay.clear();
    myDisplay.set2X();
    myDisplay.println("Tuna");
    Serial.println("begin");
#endif
#ifndef debugIMU
    if (TWCR == 0)
    {
        Wire.begin();
    }
#endif

#ifndef debugMotors
    ledG.on();
    myMotors.init();
    delay(1000);
    ledG.off();
#endif
}

void myRobotClass::update()
{
    static long sensorDelay = millis();
    delay(50);
#ifndef debugPI
    if (Serial.available())
    {
        fromPI = Serial.read();
        if (fromPI == 1)
        {
            speedL = 110;
            speedR = 130;
        }
        if (fromPI == 2)
        {
            speedL = 120;
            speedR = 120;
        }
        if (fromPI == 3)
        {
            speedL = 130;
            speedR = 110;
        }
        if (fromPI == 4)
        {
            speedL = 60;
            speedR = 60;
        }
        if (fromPI == 5)
        {
            speedL = 90;
            speedR = 90;
        }
        while (Serial.read() >= 0)
        {
        }
        // delay(50);
        // parseCommand(val); // parse the input
    }
#endif

#ifndef debugRemote
    myRemote.update();
    if (myRemote.newData)
    {
        diffSteerData();
        if (myRemote.encoderBool)
            myMotors.resetEncoders();
        myRemote.newData = false;
    }
#endif

#ifndef debugPhone
    if (myPhone.update())
    {
        setSpeedL = myPhone.getSpeedL();
        setSpeedR = myPhone.getSpeedR();
        String btString = "bt " + String(myPhone.getDataBT());
        String btStringSpeed = "bt " + String(setSpeedL) + " " + String(setSpeedR);
        // updateDisplay(60, 0, btString);
    }
#endif

    if ((millis() - sensorDelay) > 50)
    {
        // ledR.toggle();
        // ledG.toggle();
        // ledB.toggle();
        sensorDelay = millis();
#ifndef debugSensors
        sonar1.updateSonar();
        sonarD = sonar1.getDistanceSonar();
        irD = sonar1.getDistanceIR();
        obsSonar = sonar1.obstacleSonar; // 1 is obstacle present
        obsIR = sonar1.obstacleIR;       // 1 is obstacle present

        ledR.off();
        ledG.off();
        ledB.off();
        if (obsSonar)
        {
            ledR.on();
        }
        if (obsIR)
        {
            ledB.on();
        }
        if (!obsSonar && !(obsIR))
        {
            ledG.on();
        }
        String sonarstring = "sonar " + String(sonarD) + " " + String(irD);
        updateDisplay(0, 2, sonarstring);
        float voltA = (10 * analogRead(A4)) / 1024.0;
        //float voltB = (10 * analogRead(A10)) / 1024.0;
        String voltstring = "V " + String(voltA) + " "; //+ String(voltB);
        myDisplay.set1X();
        updateDisplay(0, 6, voltstring);
        myDisplay.set2X();
#endif
#ifndef debugIMU
        myIMU.updateIMU();
        gotAcX = myIMU.getAcX();
        String imuAString = "ax " + String(gotAcX) + " " + String(myIMU.getAcY()) + " " + String(myIMU.getAcZ());
        String imuVString = "vx " + String(myIMU.getGyX()) + " " + String(myIMU.getGyY()) + " " +String(myIMU.getGyZ());
        myDisplay.set1X();
        updateDisplay(0, 5, imuAString);
        updateDisplay(45, 6, imuVString);
        myDisplay.set2X();

        // updateDisplay(4, 0, imuVString);
#endif
    }
#ifndef debugMotors
    if (obsSonar)
    {
        setSpeedL = 90;
        setSpeedR = 90;
    }
    // Serial.print("from motors, obstacle: ");Serial.println(obstacle);
    // Serial.print("from motors, setSpeedL: ");Serial.println(setSpeedL);
    myMotors.update(setSpeedL, setSpeedR);
    // String motorString = "s" + String(myMotors.actSpeedL);
    // updateDisplay(0,0,motorString);
#endif
}

void myRobotClass::updateDisplay(int x, int y, String data)
{
    ;
#ifndef debugDisplay
    myDisplay.setCursor(x, y);
    myDisplay.clearToEOL();
    myDisplay.print(data);
#endif
}
