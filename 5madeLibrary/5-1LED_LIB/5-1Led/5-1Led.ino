#include <Led.h>

/*5-1Led.ino
WeMos D1 mini Pin Number  Arduino IDE Pin Number
A0     : POT 
D0  16
D1  5
D2  4 : button
D3  0
D4  2 : Default LED
D5  14 : POT POWER OUT
D6  12 : motor
D7  13
D8  15
TX  1
RX  3 
*/
//#include <Led.h>

Led led(2); //uno 13, d1mini 2

void setup()
{   
}

void loop()
{
  led.LedHigh();
  delay(200);
  led.LedLow();
  delay(200); 
}
