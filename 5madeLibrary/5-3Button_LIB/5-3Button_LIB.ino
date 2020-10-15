/*
  Control an LED on Pin 13 with Button 
*/

#include <Button.h>   // include library

#define led 2//D4      
#define SW1 4//D2

Button button(SW1);
 
bool state = 0; 
bool X = 0;       
int cnt = 0; 

void setup() {
  pinMode(led, OUTPUT);       
  pinMode(SW1, INPUT);   
  Serial.begin(9600);   
}

void loop() {
  state = button.read();
  if (state == LOW) {
    while(button.read() != HIGH){
      delay(1);
    }
    X = !X;
  }
  if (X == HIGH) {//if (state == HIGH) {
    digitalWrite(led, HIGH);      // turn LED on:
  } else {
    digitalWrite(led, LOW);       // turn LED off:
  }
  Serial.println(state);
  delay(1);
}
