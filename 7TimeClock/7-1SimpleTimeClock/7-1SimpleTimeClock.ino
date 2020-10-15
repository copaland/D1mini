//7-1SimpleTimeClock Unix Time 

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h> //가상의 시간 서버 클러스터

const char *ssid     = "your-id";                              
const char *password = "your-pass";                             

WiFiUDP udp;
NTPClient timeClient(udp, "kr.pool.ntp.org,32400");//GMT+9

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 200 );
    Serial.print ( "." );
  }
  
  timeClient.begin();

  timeClient.update();
  
  Serial.println();
  Serial.println(timeClient.getFormattedTime());
}

void loop() {
  delay(1);
}
