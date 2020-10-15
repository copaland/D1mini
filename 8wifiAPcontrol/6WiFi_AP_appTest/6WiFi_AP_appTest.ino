/*
//AP mode test OK good 20201001
//WiFi 설정 IoT-AP 연결
//led button test
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

// WiFi settings
#define WIFI_MODE   1// 1 = AP mode, 2 = STA mode
#define SSID_AP     "IoT-AP"    // for AP mode
#define PASSWORD_AP "12345678" // for AP mode
#define SSID_STA     "dlink-EBE2"     // wifi_ssid for STA mode
#define PASSWORD_STA "zdcvm97008" // wifi_password for STA mode

// pin settings
#define LED1_PIN    2   //16 pin 1 of (D0)led
#define LED2_PIN    4   //15 pin 2 of (D8) motor
#define MOT_SPEED   1023      //speed motor (0-1023)

IPAddress local_ip(192, 168, 4, 1); //IP for AP mode
IPAddress gateway(192, 168, 4, 1); //IP for AP mode
IPAddress subnet(255, 255, 255, 0); //IP for AP mode
ESP8266WebServer server(80);
int set_mode = 0; //select mode action
bool LED1status = LOW;
bool LED2status = LOW;

// initialize
void setup() {
  Serial.begin(9600);
  Serial.println("Wifi Control");
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  if (WIFI_MODE == 1) { // AP mode
    WiFi.softAP(SSID_AP, PASSWORD_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
  } else { // STA mode
    WiFi.begin(SSID_STA, PASSWORD_STA);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP()); //
  }

  // setup web server to handle specific HTTP requests
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);

  //start server
  server.begin();
  Serial.println("ESP8266 web server started...");
  Serial.println(WiFi.localIP());
}

// handle HTTP requests and arduino control 
void loop() { 
  server.handleClient();
  ardu_action();
}

// HTTP request: on connect
void handle_OnConnect() {
  set_mode = 0; //LED1status=LOW; LED2status=LOW;
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}
/*
// HTTP request: all off
void handle_alloff() {
  set_mode = 0; LED1status=LOW; MOT1status=LOW;
  Serial.println("All off");
  server.send(200, "text/html", SendHTML());
}
*/
// HTTP request: go func 1
void handle_led1on() {
  set_mode = 1; //LED1status=LOW; MOT1status=HIGH;
  Serial.println("Go led1on...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go func 2
void handle_led1off() {
  set_mode = 2; //MOT1status=HIGH; LED1status=HIGH; 
  Serial.println("Go led1off...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go func 3
void handle_led2on() {
  set_mode = 3; //MOT1status=HIGH; //MOT1status=LOW;
  Serial.println("Go led2on...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go func 4
void handle_led2off() {
  set_mode = 4; //MOT1status=HIGH;
  Serial.println("Go led2off...");
  server.send(200, "text/html", SendHTML());
}
/*
// HTTP request: go func 5
void handle_mot1speed() {
  set_mode = 5; MOT1status=HIGH;
  Serial.println("Go mot1speed...");
  server.send(200, "text/html", SendHTML());
}
*/

// HTTP request: other
void handle_NotFound() {
  set_mode = 0; LED1status=LOW; LED2status=LOW;
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
}

// control mode select
void ardu_action() {
  switch (set_mode) {
    case 0: // all off
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      ///analogWrite(MOT1_PIN, 192);
      break;
    case 1: // LED1 On
      digitalWrite(LED1_PIN, HIGH);
 //     digitalWrite(LED2_PIN, LOW);
      break;
    case 2: // LED1 OFF
      digitalWrite(LED1_PIN, LOW);
 //     digitalWrite(LED2_PIN, LOW);
      break;
    case 3: // LED2 On
 //     digitalWrite(MOT1_PIN, LOW);
      digitalWrite(LED2_PIN, HIGH);
      break;
    case 4: // LED2 OFF
//      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, LOW);
      break;
///    case 5: // MOT_SPEED
///      analogWrite(MOT1_PIN, MOT_SPEED);
///      break;   
  }
}

// output HTML web page for user
String SendHTML() {
  String html = "<!DOCTYPE html>\n";
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
  html += "<input class=\"button button-on\" type=\"button\" value=\"1\" onclick=\"window.location.href='/led1on'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-off\" type=\"button\" value=\"2\" onclick=\"window.location.href='/led1off'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-on\" type=\"button\" value=\"3\" onclick=\"window.location.href='/led2on'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-off\" type=\"button\" value=\"4\" onclick=\"window.location.href='/led2off'\">\n"; 
  html += "</form>\n";
  html += "</div>\n";
  html += "</body>\n";
  html += "</html>\n";
  return html;
}
