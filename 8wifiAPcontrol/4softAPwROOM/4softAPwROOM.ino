/*
//softAP test OK good 20200911
//WiFi 설정 AI-TINKER_xxxxxx 연결
//192.168.4.1/read
//192.168.4.1/led/1 ;on
//192.168.4.1/led/0 ;off
D0  16 LED PULLUP 10K
D1  5 
D2  4 
D3  0 FLASH
D4  2    (SDA
D5  14   (SCL
D6  12 R
D7  13 B
D8  15 G PULLDOWN 10K
TX  1
RX  3
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "kiki";
//const char* ssid = ""; // wifi 이름
//const char* password = "";//패스워드

/////////////////////
// Pin Definitions //
/////////////////////
const int led1Pin = 16; //D0 WROOM LED
const int led2Pin = 15; //D8
bool LED1status = LOW;
bool LED2status = LOW;

//const int adcPin = A0; // The only analog pin on the Thing
//const int swPin = D2; // Digital pin to be read
//const int pwrPin = D5; //analog power source

//WiFiServer server(80);
ESP8266WebServer server(80);
void setup() 
{
  initHardware();
  setupWiFi();
//handle

  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);  
  server.onNotFound(handle_NotFound);
    
  server.begin();
}

void loop() 
{
  // Check if a client has connected
///  WiFiClient client = server.available();
///  if (!client) {
///    return;
///  }

  server.handleClient();
  if(LED1status){
    digitalWrite(led1Pin, HIGH);
  } else {
    digitalWrite(led1Pin, LOW);
  }

  if(LED2status){
    digitalWrite(led2Pin, HIGH);
  } else {
    digitalWrite(led2Pin, LOW);
  } 
}  

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("M1 Status: OFF | M2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("M1 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("M1 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("M2 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("M2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h2>MOTOR CONTROL</h2>\n";
  
   if(led1stat)
  {ptr +="<p>MOTOR1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>MOTOR1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>MOTOR2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>MOTOR2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP); //softAP
  //AI-THINKER_DA3BD9
  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Thing " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void initHardware()
{
  Serial.begin(115200);
///  pinMode(swPin, INPUT_PULLUP);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  
///  pinMode(pwrPin, OUTPUT);
///  digitalWrite(pwrPin, HIGH);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  // Don't need to set ANALOG_PIN as input, 
}
