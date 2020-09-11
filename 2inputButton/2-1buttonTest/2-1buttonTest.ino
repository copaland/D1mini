/* 
 Ex2. 2-1buttonTest.ino
 D1 mini switch Button Test 
*/
//#include <ESP8266WiFi.h>

const int ledPin = 2; //D4 builtin LED
const int buttonPin = 4; //D2

int sw = 0; // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);//INPUT_PULLUP
}

void loop() {

  sw = digitalRead(buttonPin); //Pulldown
  // check if the pushbutton is pressed. 
  if (sw == HIGH) {   
    digitalWrite(ledPin, LOW); // turn LED on:
  } else {
  digitalWrite(ledPin, HIGH); // turn LED off:       
  }
}
