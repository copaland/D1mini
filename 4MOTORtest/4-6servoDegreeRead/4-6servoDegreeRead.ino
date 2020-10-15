/* 
 Ex4. 4-6servoDegreeRead.ino
 D1 mini port output 
WeMos D1 mini Pin Number  Arduino IDE Pin Number
A0     : POT 
D0  16
D1  5 : servo
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

#include <Servo.h>
const int ledPin = 2;//BUILTIN_LED D4
const int servoPin = 5; //D1
const int powerPin = 14;//D5

int POS = 0;
int DEG = 0;
Servo servo_5;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  
  servo_5.attach(servoPin);
  Serial.begin(9600);
}

void loop()
{
  POS = analogRead(A0);
  POS = map(POS, 0, 1023, 0, 180);
  servo_5.write(POS);
  DEG = servo_5.read();
  Serial.print("DEG: ");
  Serial.println(DEG);
  delay(15); // Wait for 15 millisecond(s)
}
