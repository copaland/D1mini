/*
  Ex3. 3-1analogRead.ino
  D1 mini Analog Input read POT
  Vout = R2/(R1+R2)*Vin = 100/(220+100)*3.2 = 1V
  -----A0 (VCC3.2V)
  |
 220K
  |--- ADC(0~1V)
 100K
  |
 GND
*/
//#include <ESP8266WiFi.h>

unsigned long preMillis=0;
int interval = 1000;

int adcPin = A0;  // potentiometer
int ledPin = D4;  // LED
int pwrPin = D5;  // ad power supply
int POT = 0;  // store the sensor value
bool X = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pwrPin, OUTPUT);
  pinMode(adcPin, INPUT);
  digitalWrite(pwrPin, HIGH);
  Serial.begin(115200);
}

void loop() {
//  if((millis()%1000)==0){
  unsigned long curMillis = millis();   
  if ((curMillis - preMillis) >= interval) 
  {  
    POT = analogRead(adcPin); //0-999
    Serial.println("POT: " + String(POT) + "-");
    X = !X;
    preMillis = curMillis;  //NOTE: 3 
  }
  digitalWrite(ledPin, X);
  delay(1);
}
