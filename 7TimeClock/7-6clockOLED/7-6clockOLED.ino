/*
//7-6clockOLED D1mini OLED 시간 표시 
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

const char* ssid = "dlink-EBE2";//"wifi-name";
const char* password = "zdcvm97008";//"wifi-pass";                          
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
// Initialize a NTPClient to get time
  timeClient.begin();
// timeClient.setTimeOffset(32400);//kr
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
 int clockCentreX = 22;//64
 int clockCentreY = 32;//32
  // Now draw the clock face
  u8g2.drawCircle(clockCentreX, clockCentreY, 21); // main outer circle
  u8g2.drawCircle(clockCentreX, clockCentreY, 2);  // small inner circle
  //
  //hour ticks
  for( int z=0; z < 360;z= z + 30 ){
  //Begin at 0° and stop at 360°
    float angle = z ;
    angle=(angle/57.29577951) ; //Convert degrees to radians
    int x2=(clockCentreX+(sin(angle)*20));
    int y2=(clockCentreY-(cos(angle)*20));
    int x3=(clockCentreX+(sin(angle)*(20-5)));
    int y3=(clockCentreY-(cos(angle)*(20-5)));
    u8g2.drawLine(x2,y2,x3,y3);
  }
  // display second hand
  float angle = SC*6;//now.second()*6 ;
  angle=(angle/57.29577951) ; //Convert degrees to radians  
  int x3=(clockCentreX+(sin(angle)*(20)));
  int y3=(clockCentreY-(cos(angle)*(20)));
  u8g2.drawLine(clockCentreX,clockCentreY,x3,y3);
  //
  // display minute hand
  angle = MM * 6 ;//angle = now.minute() * 6 ;
  angle=(angle/57.29577951) ; //Convert degrees to radians  
  x3=(clockCentreX+(sin(angle)*(20-3)));
  y3=(clockCentreY-(cos(angle)*(20-3)));
  u8g2.drawLine(clockCentreX,clockCentreY,x3,y3);
  //
  // display hour hand
  angle = HH * 30 + int((MM / 12) * 6 );
//  angle = now.hour() * 30 + int((now.minute() / 12) * 6 )   ;
  angle=(angle/57.29577951) ; //Convert degrees to radians  
  x3=(clockCentreX+(sin(angle)*(20-11)));
  y3=(clockCentreY-(cos(angle)*(20-11)));
  u8g2.drawLine(clockCentreX,clockCentreY,x3,y3);

  u8g2.setFont(u8g2_font_logisoso16_tn);
  sprintf(tbuffer, "%02d:%02d.%02d\n",HH,MM,SC);
  u8g2.drawStr(50,42, tbuffer);  
}
  
