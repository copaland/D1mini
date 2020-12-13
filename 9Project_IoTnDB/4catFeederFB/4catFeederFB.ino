/* 20201210
D1mini PINMAP catFeederFB.ino
Tx  1
Rx  3
D1  5 (SCL)LED
D2  4 (SDA)button
D3  0 FLASH 
D4  2 <builtin LED>  
A0  ADC0
D0  16 wake 
D5  14 SCK  
D6  12 MISO 
D7  13 MOSI 
D8  15 SS 
firebase esp8266 client library
 */
//Firebase IoT Switch  

#include <FirebaseESP8266.h>
#include  <ESP8266WiFi.h>
#define WIFI_SSID "Your Wifi SSID"//"<Your Wifi SSID>"
#define WIFI_PASS "Your WiFi Password"//"<Your WiFi Password>"

#define FIREBASE_HOST "Firebase Project URL" //Firebase Project URL:Remove "https:", "/"
#define FIREBASE_AUTH "Firebase Auth Token"      //Firebase Auth Token

FirebaseData fbData;

const int enaPin = 2; //d1-5
const int stepPin = 4; //d2-4
const int dirPin = 5; //d4-2
const int steps = 200;//1.8도
int rpm = 10; //30
unsigned microsteps = 1;
unsigned long step_pulse=60*1000000L/steps/microsteps/rpm;

/*
인라인 함수(inline function): 함수의 실행 시간이 매우 짧다면, 
함수 호출에 걸리는 시간도 부담이 될때
일반적인 함수의 호출 과정을 거치지 않고, 
함수의 모든 코드를 호출된 자리에 바로 삽입하는 방식
*/
inline void microWaitUntil(unsigned long target_micros){
    yield(); //호출시 다른 작업에 제어권을 전달
    while (micros() < target_micros);
}
#define DELAY_MICROS(us) microWaitUntil(micros() + us)

bool X= LOW;
String curr = "";
String prev = "";
int cnt = 0;

void setup() {
  
 Serial.begin(9600);
 
   WiFi.begin (WIFI_SSID, WIFI_PASS);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enaPin,OUTPUT);
  digitalWrite(enaPin,LOW); 
}

void loop() {

  if(X==LOW){
    if (Firebase.get(fbData,"/CatDog/TURN")) {
      if (fbData.dataType() == "string") {
        String state = fbData.stringData();
        curr = state;
        Serial.print(curr);
        if(curr != prev){
          X = HIGH;
          prev = curr;
          cnt = curr.toInt();
        }
      }
    }     
  } else {
     ///action(cnt);
    move(cnt);  
  }
}


void setDirection(int direction){
    digitalWrite(dirPin, (direction<0) ? LOW : HIGH);
}

void move(long steps){
    if (steps >= 0){
        setDirection(1);
    } else {
        setDirection(-1);
        steps = -steps;
    }
    steps = steps * 25;

    unsigned long pulse_duration = step_pulse/2;
    while (steps--){
        digitalWrite(stepPin, HIGH);
        unsigned long next_edge = micros() + pulse_duration;
        microWaitUntil(next_edge);
        digitalWrite(stepPin, LOW);
        microWaitUntil(next_edge + pulse_duration);
    }
    X = LOW;
}
/*
void action(int c)
{
  int deg = c * 25;
///  digitalWrite(ledPin, HIGH);
 digitalWrite(LED_BUILTIN, LOW);
  delay(deg * 100);
 /// digitalWrite(ledPin, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  X = LOW;
}
*/
