/*
//7-7clockOLEDkor    D1mini 한글 OLED 시간 표시 
CLOCK USE Network time
OLEd using U8g2lib Library
Wire OLED:
  VCC +5v
  GND GND
  SDA Analog pin D2 //4
  SCL Analog pin D1 //5
*/
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <U8g2lib.h>//
//  #include <SPI.h>
#include <Wire.h> //i2c
 
// Replace with your network credentials
const char *ssid     = "your-id";                               
const char *password = "your-pass";                             
char dbuffer[32];
char tbuffer[32];
char htemp[8];
char mtemp[8];
int CD = 0;
int CM = 0;
int CY = 0;
int HH = 0;
int MM = 0;
int SC = 0;
bool X=LOW;

  String thisTime = "";
  String thisDay = "";
  
// setup u8g object
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
  
// Define NTP Client to get time
WiFiUDP udp;
NTPClient timeClient(udp, "kr.pool.ntp.org",32400);//32400

void draw(void);

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
  
  u8g2.begin();
  u8g2.enableUTF8Print(); // enable UTF8 support
// Initialize a NTPClient to get time
  timeClient.begin();
// timeClient.setTimeOffset(32400);//kr
}

void loop() {
  static unsigned long loopCnt = 0;
  static unsigned long nextMil = millis() + 1000;

  u8g2.setFont(u8g2_font_unifont_t_korean1);  
  u8g2.setFontDirection(0);
  
  if(millis() > nextMil){
    nextMil = millis() + 1000;
    loopCnt++;
    
    timeClient.update(); 
    unsigned long epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime); 

    CD = ptm->tm_mday;
    CM = ptm->tm_mon+1;
    CY = ptm->tm_year+1900;
    HH = ptm->tm_hour;
    MM = ptm->tm_min;
    SC = ptm->tm_sec;
    
    Serial.println(loopCnt);
    sprintf(dbuffer, "%04d-%02d-%02d\n",CY,CM,CD);
    Serial.printf(dbuffer);//Serial.printf("%04d-%02d-%02d\n",CY,CM,CD);
    sprintf(tbuffer, "%02d:%02d.%02d\n",HH,MM,SC);
    Serial.printf(tbuffer);//Serial.printf("%02d:%02d.%02d\n",HH,MM,SC); 
  // picture loop
    u8g2.firstPage();  
    do {
      draw();
    } while( u8g2.nextPage() );  
  }
    
  delay(10);
  __asm__("nop\n");
}
 /*
void draw(void) { 
  u8g2.setFont(u8g2_font_profont15_tn);//
  u8g2.drawStr(10,12, dbuffer);

  u8g2.setFont(u8g2_font_logisoso24_tn);
  u8g2.drawStr(10,60, tbuffer);
}
*/
void draw(void) {
  u8g2.setFont(u8g2_font_unifont_t_korean1);  
    u8g2.setCursor(10, 15);
    u8g2.print("안녕! 시계");    // Korean 

  u8g2.setFont(u8g2_font_logisoso28_tn);
  sprintf(tbuffer, "%02d:%02d.%02d\n",HH,MM,SC);
  u8g2.drawStr(0,63, tbuffer);  
}
  
