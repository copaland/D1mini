/* 
 Ex2. 2-3simpleDebounce.ino
 D1 mini Button Simple debounce using while statement 
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
    while(digitalRead(buttonPin) != LOW){
      delay(10);
    }
    X = !X;
  }
  if(X){
    digitalWrite(ledPin, HIGH);  // LED off
  } else { //PUSH ON
    digitalWrite(ledPin, LOW); // LED on 
  }
  delay(10); 
}
