/*
 * https://www.programmersought.com/article/849010554/
 * 
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
//HTML homepage mainPage
static const char mainPage[] PROGMEM = u8R"(
  <!DOCTYPE html>
  <html>
  <head>
      <title>ESP8266</title>
      <meta name='viewport' content='width=device-width, initial-scale=1.0'>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
      <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
      .button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;
      text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
      .button2 {background-color: #77878A;}
      </style>  

    
  </head>
  <body>
      <h1>ESP8266 softAP</h1>
      <p><a href='call?led=ON'><button class='button'>ON</button></a></p>
      <br> 
      <p><a href='call?led=OFF'><button class='button button2'>OFF</button></a></p>                
  </body>
  </html>
)";

 // error path HTML
static const char errorPage[] PROGMEM= u8R"(
)";
 // Set the path HTML  
static const char settingPage[] PROGMEM= u8R"(
)";
 
 
 String ledState = u8"OFF"; // led status 
 ESP8266WebServer _esp8266WebServer(80); // define esp82666WebServer instance
 
void handleRoot() {//web root directory handler
     _esp8266WebServer.send(200, "text/html", mainPage);//"text/html": output in html format
}
 
void handleNotFound() {//The network path does not have a handler
     _esp8266WebServer.send(404, "text/html", errorPage);//"text/plain": plain unformatted output
}
 
void handleSetting() {//page setting handler
  _esp8266WebServer.send(200, "text/html", settingPage);
}
 
void ledStateHandel() {
  if (_esp8266WebServer.hasArg(u8"led")) {
    ledState = _esp8266WebServer.arg(u8"led");
    if (ledState == u8"ON") {
///      pinMode(D4, OUTPUT);
      digitalWrite(D4, HIGH);
    } else if (ledState == u8"OFF") {
///      pinMode(D4, OUTPUT);
      digitalWrite(D4, LOW);
    }
///    _esp8266WebServer.send(200, u8"text/plain", String(u8"OK"));
  }
}
 
 
 // setup() is executed once at startup
void setup() {
 
     // Server settings
  while (!WiFi.softAP(u8"kiki", u8"", 1,false));//ap account (AA), password (none) settings.
  _esp8266WebServer.on("/call", ledStateHandel);//Processing function with led variable
  _esp8266WebServer.on("/", handleRoot);
  _esp8266WebServer.onNotFound(handleNotFound);
  _esp8266WebServer.on("/setting", handleSetting);
  _esp8266WebServer.begin();
 
     //led is set to off state
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
 
}
 
 // loop() loop execution
void loop() {
  _esp8266WebServer.handleClient();
 
}
