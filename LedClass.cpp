#include "LedClass.h"

LedClass::LedClass(byte pin) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  this->pin = pin;
  init();
}

void LedClass::init() {
  pinMode(pin, OUTPUT);
  off();
  state = 0;
}

void LedClass::on() {
  digitalWrite(pin, HIGH);
  state = 1;
}

void LedClass::off() {
  digitalWrite(pin, LOW);
  state = 0;
}
void LedClass::toggle() {
  if (state == 1){off();}
  if (state == 0){on();}
}
