// 8getTimeClock1S Unix Time 

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const char *ssid     = "your-id";                              
const char *password = "your-pass";                             

int previousMin = 0;
int previousSec = 0;

WiFiUDP udp;
//GMT+9 :9x60x60, 3600000mS=1hrx60x60x1000
NTPClient timeClient(udp, "kr.pool.ntp.org",32400, 3600000);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 200 );
    Serial.print ( "." );
  }
  timeClient.begin();
//  timeClient.setTimeOffset(32400);//kr
}

void loop() {
  timeClient.update();

  int currentSec = timeClient.getSeconds();
  
  if (previousSec != currentSec) {
    previousSec = currentSec;

    Serial.print(timeClient.getFormattedTime());
    Serial.print(" ");
    int currentMin = timeClient.getMinutes();
    int currentTime = timeClient.getHours();   
    Serial.printf("%02d:%02d.%02d\n",currentTime,currentMin,currentSec);

    //int currentTime = timeClient.getHours() * 10000 + currentMin * 100 + currentSec;
  }
  delay(1);
}
