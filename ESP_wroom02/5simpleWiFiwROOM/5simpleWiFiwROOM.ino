/*
//AP mode test OK good 20201015
//WiFi 설정 IoT-AP 연결 스마트고 프로젝트
ESP-WROOM-02 app control
D0  16 LED PULLUP 10K
D1  5 
D2  4 
D3  0 FLASH LEFT
D4  2    (SDA)
D5  14   (SCL)OK
D6  12 R UP
D7  13 B DOWN
D8  15 MOTOR G PULLDOWN 10K
D9  3 RX  
D10 1 TX  
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// AP mode WiFi settings
#define SSID_AP     "IoT-AP"   // for AP mode
#define PASSWORD_AP "12345678" // for AP mode

// pin settings
#define LED1_PIN    16   //d0 16 pin 1 of (D0)led
#define MOT1_PIN    15   //d8 15 pin 2 of (D8) motor
#define MOT_SPEED   1023      //speed motor (0-1023)

IPAddress local_ip(192, 168, 4, 1); //IP for AP mode
IPAddress gateway(192, 168, 4, 1); //IP for AP mode
IPAddress subnet(255, 255, 255, 0); //IP for AP mode
ESP8266WebServer server(80);

int set_mode = 1; //0 select mode action

// initialize
void setup() {
  Serial.begin(9600);
  Serial.println("Wifi Control");
  pinMode(LED1_PIN, OUTPUT);
  pinMode(MOT1_PIN, OUTPUT);

  // AP mode
  WiFi.softAP(SSID_AP, PASSWORD_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  // setup web server to handle specific HTTP requests
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/mot1on", HTTP_GET, handle_mot1on);
  server.on("/mot2on", HTTP_GET, handle_mot2on);
  server.on("/mot3on", HTTP_GET, handle_mot3on);
  server.on("/motoff", HTTP_GET, handle_motoff);
  server.onNotFound(handle_NotFound);

  //start server
  server.begin();
  Serial.println("ESP8266 web server started...");
}

// handle HTTP requests and arduino control 
void loop() { 
  server.handleClient();   
  auto_action();
}

// HTTP request: on connect
void handle_OnConnect() {
  //set_mode = 0; 
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go func 1
void handle_mot1on() {
  set_mode = 1; 
  Serial.println("Go mot1on...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go func 2
void handle_mot2on() {
  set_mode = 2; 
  Serial.println("Go mot2on...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go func 3
void handle_mot3on() {
  set_mode = 3; 
  Serial.println("Go mot3on...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go func 4
void handle_motoff() {
  set_mode = 4; 
  Serial.println("Go motoff...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: other
void handle_NotFound() {
  set_mode = 0; //LED1status=LOW; MOT1status=LOW;
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
}

// control mode select
void auto_action() {
  switch (set_mode) {
    case 0: // all off
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(MOT1_PIN, LOW);
      break;
    case 1: // MOTOR On
      digitalWrite(LED1_PIN, LOW);
      analogWrite(MOT1_PIN, 208);
      break;
    case 2: // MOTOR On
      digitalWrite(LED1_PIN, LOW);
      analogWrite(MOT1_PIN, 224);
      break;
    case 3: // MOTOR On
      digitalWrite(MOT1_PIN, LOW);
      analogWrite(MOT1_PIN, 248);
      break;
    case 4: // MOTOR Off
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(MOT1_PIN, LOW);
      break;  
  }
}

// output HTML web page for user
String SendHTML() {
  String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  html = "<!DOCTYPE html>\n";
  html += "<html>\n";
  html += "<head>\n";
  html += "<title>Wifi Control</title>\n";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "<style>\n";
  html += "html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html += "body {margin-top: 10px;} h2 {color: #444444;margin: 10px auto 10px;} h4 {color: #444444;margin-bottom: 10px;}\n";
  html += ".button {border: 5px solid green; color: white; width: 120px; height: 50px; margin: 5px; padding: 15px 15px; text-align: center; text-decoration: none; font-weight: bold; font-size: 20px; border-radius: 10px; box-shadow: 0 6px #999; cursor: pointer;}\n";
  html += ".button-on {background-color: #700000;}\n";
  html += ".button-off {background-color: #000070;}\n";
  html += ".button:active {background-color: #3e8e41; box-shadow: 0 5px #666; transform: translateY(4px);}\n";
  html += ".center {display: flex; justify-content: center; align-items: center; margin: 10px;}\n";
  html += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  html += "</style>\n";  
  html += "</head>\n";
  html += "<body>\n";
  html += "<div align=\"center\">\n";
  html += "<h2>Wifi Control</h2>\n";
  html += "<br>\n";
  html += "<form method=\"GET\">\n";
  html += "<input class=\"button button-on\" type=\"button\" value=\"1\" onclick=\"window.location.href='/mot1on'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-on\" type=\"button\" value=\"2\" onclick=\"window.location.href='/mot2on'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-on\" type=\"button\" value=\"3\" onclick=\"window.location.href='/mot3on'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-off\" type=\"button\" value=\"4\" onclick=\"window.location.href='/motoff'\">\n"; 
  html += "</form>\n";
  html += "</div>\n";
  html += "</body>\n";
  html += "</html>\n";
  return html;
}
