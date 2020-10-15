/* 
 Ex4. 4-1dcMotorOnOff.ino
 D1 mini port output Button input
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

const int buttonPin = 4;//D2
const int ledPin = 2;//BUILTIN_LED D4
const int motorPin = 12;//D6

bool X = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    while (digitalRead(buttonPin) != LOW) {
      delay(5); // Wait for 5 millisecond(s)
    }
    if (X == HIGH) { X = LOW;
    } else { X = HIGH; }
  }
  if (X == HIGH) {
    // MOTOR-ON
    digitalWrite(motorPin, HIGH);
  } else {
    // MOTOR-OFF
    digitalWrite(motorPin, LOW);
  }
  delay(1); // Wait for 1 millisecond(s)
}
