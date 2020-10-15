//7-5countOLED

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
uint8_t m = 0;
char m_str[4];

void setup(void) {
  u8g2.begin();  
}
void draw(void){
  u8g2.setFont(u8g2_font_logisoso62_tn);
  u8g2.drawStr(0,63,"9");
  u8g2.drawStr(33,63,":");
  u8g2.drawStr(50,63,m_str);
//  u8g2.drawStr(0,63,m_str);
}

void loop(void) {
  static unsigned long nextMil = millis() + 1000;  
  strcpy(m_str, u8x8_u8toa(m, 2));  
  /* convert m to a string with two digits */
 if(millis() > nextMil){
    nextMil = millis() + 1000; 
    m++;
    if ( m == 60 )
        m = 0;
    u8g2.firstPage();
    do {
        draw();
    } while ( u8g2.nextPage() );
  }
  delay(10);
}
