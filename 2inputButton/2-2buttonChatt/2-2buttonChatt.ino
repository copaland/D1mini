/* 
 Ex2. 2-2buttonChatt.ino
 D1 mini Button chattering occurs 
*/
#include <ESP8266WiFi.h>

const int buttonPin = 4;//D2
const int ledPin = 2;//BUILTIN_LED D4

int sw = 0;
bool X = LOW;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT); 
}

void loop()
{
  sw = digitalRead(buttonPin);
  if (sw == HIGH) {
    if (X == HIGH) {
      X = LOW;
    } else {
      X = HIGH;
    }
    delay(1); 
  }
  
  if (X == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(10); 
}
