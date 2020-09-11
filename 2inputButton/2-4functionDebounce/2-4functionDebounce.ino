/* 
 Ex2. 2-4functionDebounce.ino
 D1 mini Button debounce using functions
*/
#include <ESP8266WiFi.h>

const int ledPin=2; //2번 핀을 사용하는 LED 상수 정의
const int buttonPin=4; //버튼을 4번 핀에 지정

int count=0;
boolean lastButton=LOW; //이전 버튼의 눌림 상태를 Boolean형 변수로 선언
boolean currentButton=LOW; //현재 버튼의 눌림 상태를 Boolean형 변수로 선언
boolean X=false; //현재 LED의 점멸 상태를 Boolean형 변수로 선언

void setup()
{
    pinMode(ledPin, OUTPUT); //LED(2번 핀)를 출력으로 지정
    pinMode(buttonPin, INPUT); //BUTTON(4번 핀)을 입력으로 지정
    Serial.begin(9600);
}
boolean debounce(boolean last)
{
    boolean current=digitalRead(buttonPin); //현재 버튼 상태를 확인
    if(last!=current) //이전 버튼 상태와 현재 버튼 상태가 다름
    {
        delay(5); //5ms 동안 기다림
        current=digitalRead(buttonPin); //current에 현재 버튼 상태를 저장
    }
    return current; //current 변수값을 반환
}
void loop()
{
    currentButton=debounce(lastButton); //디바운싱 처리된 버튼값을 읽음
    if(lastButton==LOW && currentButton==HIGH) //버튼을 누름
    {
        X=!X; //LED 점멸 상태를 나타내는 ledOn 변수값을 바꿈
        count++;
        Serial.println(count);
    }
    lastButton=currentButton; //이전 버튼값을 현재 버튼값으로 변경

    digitalWrite(ledPin, X); //LED 점멸 상태를 바꿈
  delay(1);
}
