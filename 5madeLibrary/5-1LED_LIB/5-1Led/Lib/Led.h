//Led.h ÆÄÀÏ 
#ifndef LED_H    
#define LED_H

#include <Arduino.h>
/*
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
#endif
*/
class Led
{
  private:
      int LedPin;
  public:
      Led(int Pin){ 
         LedPin = Pin;
         pinMode(LedPin, OUTPUT);         
      }
      ~Led(){
      }
public:
      void LedHigh();
      void LedLow();
};

#endif
