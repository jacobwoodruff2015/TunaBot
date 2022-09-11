#ifndef LEDCLASS_H
#define LEDCLASS_H

#include <Arduino.h>

class LedClass {
  
  private:
    byte pin;
    byte state;
  public:
    LedClass(byte pin);
    void init();
    void on();
    void off();
    void toggle();
};

#endif