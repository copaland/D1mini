/*----------------------------------------------*
 * Arduino Button Library v1.0                  *
 *----------------------------------------------*/
#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

//#include "kiki.h"
//#if ARDUINO >= 100
//#include <Arduino.h>
//#else
//#include <WProgram.h>
//#endif
class Button
{
    public:
        Button(uint8_t pin);
        uint8_t read();
    
    private:
        uint8_t _pin;           //arduino pin number
        uint8_t _puEnable;      //internal pullup resistor enabled
        uint8_t _invert;        //if 0, interpret high state as pressed, else interpret low state as pressed
        uint8_t _state;         //current button state
        uint8_t _lastState;     //previous button state
        uint8_t _changed;       //state changed since last read
        uint32_t _time;         //time of current state (all times are in ms)
        uint32_t _lastChange;   //time of last state change
        uint32_t _dbTime;       //debounce time
};

#endif
