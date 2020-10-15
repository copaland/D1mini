//Led.cpp ÆÄÀÏ
#include <Arduino.h>
/*
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
#endif
*/
#include "Led.h¡°

void Led::LedHigh()
{
  digitalWrite(LedPin,HIGH);
}

void Led::LedLow()
{
  digitalWrite(LedPin,LOW);
}
