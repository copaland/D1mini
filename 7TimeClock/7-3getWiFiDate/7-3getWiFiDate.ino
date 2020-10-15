//7-3getWiFiDate 날자 표
시 
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid     = "your-id";                               
const char *password = "your-pass";                             

// Define NTP Client to get time
WiFiUDP udp;
NTPClient timeClient(udp, "kr.pool.ntp.org");//32400

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(32400);//kr
}

void loop() {
  static unsigned long loopCnt = 0;
  static unsigned long nextMil = millis() + 1000;
  
  if(millis() > nextMil){
    nextMil = millis() + 1000;
    loopCnt++;
    
    timeClient.update(); 
    unsigned long epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
  
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon+1;
    int currentYear = ptm->tm_year+1900;
    Serial.println(loopCnt);
    Serial.printf("%04d-%02d-%02d\n",currentYear,currentMonth,monthDay);     
  }
  delay(1);
}
/*
 * //  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
 */
