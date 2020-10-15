/*
ESP-WROOM-02 button MOTOR TEST
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

#define LED_PIN   D0   //16 pin of (D0)led
#define SW_PIN    D3   //0 (D3)
#define MOT_PIN   D8   //15

bool X = LOW;
int Count = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOT_PIN, OUTPUT);
  Serial.begin(9600);     
}

void loop() {
  static unsigned long nextMil = millis() + 1000;

  if(millis() >= nextMil){
    nextMil = millis() + 1000;
  }
  if(digitalRead(SW_PIN)==LOW){
    while(digitalRead(SW_PIN)!= HIGH){
      delay(5);
    }
    X = !X;
    Count++;
    Serial.println(Count);
  }
  digitalWrite(LED_PIN, X);   // X is LED status
  digitalWrite(MOT_PIN, X);   // X is LED status
  delay(1);                      
}
