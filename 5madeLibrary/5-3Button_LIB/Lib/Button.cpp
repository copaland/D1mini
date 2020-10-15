
#include "Button.h"

Button::Button(uint8_t pin){
    _pin = pin;
    _puEnable = 0;
    _invert = 0;//1						
    _dbTime = 0; //
    pinMode(_pin, INPUT);
    _state = digitalRead(_pin);
    if (_invert != 0) _state = !_state;
    _time = millis();
    _lastState = _state;
    _changed = 0;
    _lastChange = _time;
}

uint8_t Button::read(void)
{
    static uint32_t ms;
    static uint8_t pinVal;

    ms = millis();
    pinVal = digitalRead(_pin);
    if (_invert != 0) pinVal = !pinVal;
    if (ms - _lastChange < _dbTime) {
        _time = ms;
        _changed = 0;
        return _state;
    }
    else {
        _lastState = _state;
        _state = pinVal;
        _time = ms;
        if (_state != _lastState)   {
            _lastChange = ms;
            _changed = 1;
        }
        else {
            _changed = 0;
        }
        return _state;
    }
}
