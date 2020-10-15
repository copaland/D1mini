/* 
 Ex4. 4-3dcMoterPOTSpeed
 D1 mini port output 
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

//const int buttonPin = 4;//D2
const int ledPin = 2;//BUILTIN_LED D4
const int motorPin = 12;//D6
const int powerPin = 14;//D5

int POT = 0;
int mPOT = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  Serial.begin(9600);
}

void loop()
{
  POT = analogRead(A0);
  mPOT = map(POT, 0, 1023, 255, 0);
  analogWrite(motorPin, mPOT);//
//  Serial.print("POT: ");
//  Serial.print(POT);
//  Serial.print("mPOT: ");
//  Serial.println(mPOT);
  delay(10); // Wait for 10 millisecond(s)
}
