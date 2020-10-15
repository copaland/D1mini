/* 
 Ex4. 4-2dcMotorPWMSpeed.ino
 D1 mini port output 
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
//#include <ESP8266WiFi.h>

const int ledPin = 2;//BUILTIN_LED D4
const int motorPin = 12;//D6

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
    for(int i=0; i<256; i++)
    {
        analogWrite(motorPin, i);
        delay(10);
    }
    delay(2000);
    for(int i=255; i>=0; i--)
    {
        analogWrite(motorPin, i);
        delay(10);
    }
    delay(2000);
}
