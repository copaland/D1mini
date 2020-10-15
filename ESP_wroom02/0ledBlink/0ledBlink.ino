/*
ESP-WROOM-02 Blink LED
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

void setup() {
  pinMode(LED_PIN, OUTPUT);     
}

void loop() {
  digitalWrite(LED_PIN, LOW);   // Turn the LED on LOW
  delay(1000);                      
  digitalWrite(LED_PIN, HIGH);  // Turn the LED off 
  delay(1000);                      
}
