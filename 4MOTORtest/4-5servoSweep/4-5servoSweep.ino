/* 
 Ex4. 4-5servoMotorSweep.ino
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

#include <Servo.h> //서보 라이브러리를 불러옵니다.
 
Servo myservo;  // 서보를 제어할 서보 오브젝트를 만듭니다.        
int pos = 0;     // 서보 위치를 저장할 변수를 선언합니다.

void setup() 
{ 
  myservo.attach(3);  // 핀 3의 서보를 서보 오브젝트에 연결합니다.
} 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // 0도에서 180도로 이동합니다.
  {                                  // 이동할때 각도는 1도씩 이동합니다. 
    myservo.write(pos);         // 'pos'변수의 위치로 서보를 이동시킵니다.
    delay(15);                     // 서보 명령 간에 20ms를 기다립니다.
  } 
  for(pos = 180; pos>=1; pos-=1)  // 180도에서 0도로 이동합니다.
  {                                
    myservo.write(pos);           // 서보를 반대방향으로 이동합니다.
    delay(15);                       // 서보 명령 간에 20ms를 기다립니다.
  } 
}
