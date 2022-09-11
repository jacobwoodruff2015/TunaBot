// myPhone.h

#ifndef MYPHONE_H
#define MYPHONE_H

class myPhoneClass
{
private:
    int speedL, speedR;
    void parseCommand(char input);
   
public:
    myPhoneClass(); 
    char btData;
    bool update();
    int getSpeedL();
    int getSpeedR();
    char getDataBT();

};

#endif