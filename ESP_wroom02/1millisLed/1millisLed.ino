/*
ESP-WROOM-02 millisLED
D0  16 LED PULLUP 10K
D1  5 
D2  4 
D3  0 FLASH PROG
D4  2    (SDA)
D5  14   (SCL)OK
D6  12 R UP
D7  13 B DOWN
D8  15 MOTOR G PULLDOWN 10K
D9  3 RX  
D10 1 TX  
*/

//#include <ESP8266WiFi.h>

#define LED_PIN    D0   //16 pin of (D0)led
bool X = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);     
}

void loop() {
  static unsigned long nextMil = millis() + 500;

  if(millis() >= nextMil){
    nextMil = millis() + 500;
    X = !X;
  }
  digitalWrite(LED_PIN, X);   // X is LED status
  delay(1);                      
}
