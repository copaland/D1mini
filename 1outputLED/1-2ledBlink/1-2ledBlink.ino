/* 
 Ex1. 1-2ledBlink.ino
 D1 mini LED Blink Without Delay 
*/
//#include <ESP8266WiFi.h>

int ledState = LOW;     
const long interval = 1000;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //2:D4
}

void loop()
{
  if((millis() % interval)==0) { 
    if (ledState == LOW)
      ledState = HIGH;  // LED *off*
    else
      ledState = LOW;   // LED *on*   
  }
  digitalWrite(LED_BUILTIN, ledState);
  delay(1);
}
