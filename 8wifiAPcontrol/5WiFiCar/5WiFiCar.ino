// Simple WiFi-controlled car on NodeMCU V2 and L9110S motor drive board
// by Alan Wang
//https://www.hackster.io/alankrantas/simple-nodemcu-wifi-controlled-car-esp8266-c5491e
/*
L9110S
Vcc -> power
Gnd -> ground
A-1A (Right motor pin 2) -> D1 (GPIO 5)
A-1B (Right motor pin 1) -> D2 (GPIO 4)
B-1A (Left motor pin 2) -> D5 (GPIO 14)
B-2A (Left motor pin 2) -> D6 (GPIO 12)


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

// WiFi settings
#define WIFI_MODE           1                     // 1 = AP mode, 2 = STA mode
#define SSID_AP             "WiFi_Car"    // for AP mode
#define PASSWORD_AP         "12345678"            // for AP mode
#define SSID_STA            "your_wifi_ssid"      // for STA mode
#define PASSWORD_STA        "your_wifi_password"  // for STA mode

// motor settings
#define RIGHT_MOTOR_PIN1    4                     // pin 1 of right motor (D2)
#define RIGHT_MOTOR_PIN2    5                     // pin 2 of right motor (D1)
#define LEFT_MOTOR_PIN1     12                    // pin 1 of left motor (D6)
#define LEFT_MOTOR_PIN2     14                    // pin 2 of left motor (D5)
#define RIGHT_MOTOR_SPEED   1023                  //speed for right motor (0-1023)
#define LEFT_MOTOR_SPEED    1023                  //speed for left motor (0-1023)

IPAddress local_ip(192, 168, 4, 1); //IP for AP mode
IPAddress gateway(192, 168, 4, 1); //IP for AP mode
IPAddress subnet(255, 255, 255, 0); //IP for AP mode
ESP8266WebServer server(80);
int car_mode = 0; // set car drive mode (0 = stop)

// initialize
void setup() {
  Serial.begin(9600);
  Serial.println("Wifi Car");
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  car_control(); // stop the car

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
    Serial.println(WiFi.localIP()); //the IP is needed for connection in STA mode
  }

  // setup web server to handle specific HTTP requests
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/forward", HTTP_GET, handle_forward);
  server.on("/backward", HTTP_GET, handle_backward);
  server.on("/left", HTTP_GET, handle_left);
  server.on("/right", HTTP_GET, handle_right);
  server.on("/stop", HTTP_GET, handle_stop);
  server.onNotFound(handle_NotFound);

  //start server
  server.begin();
  Serial.println("ESP8266 web server started.");
}

// handle HTTP requests and control car
void loop() { 
  server.handleClient();
  car_control();
}

// HTTP request: on connect
void handle_OnConnect() {
  car_mode = 0;
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: stop car
void handle_stop() {
  car_mode = 0;
  Serial.println("Stopped");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go forward
void handle_forward() {
  car_mode = 1;
  Serial.println("Go forward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go backward
void handle_backward() {
  car_mode = 2;
  Serial.println("Go backward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn left
void handle_left() {
  car_mode = 3;
  Serial.println("Turn left...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn right
void handle_right() {
  car_mode = 4;
  Serial.println("Turn right...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: other
void handle_NotFound() {
  car_mode = 0;
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
}

// control car movement
void car_control() {
  switch (car_mode) {
    case 0: // stop car
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      break;
    case 1: // go forward
      analogWrite(RIGHT_MOTOR_PIN1, RIGHT_MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      analogWrite(LEFT_MOTOR_PIN1, LEFT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      break;
    case 2: // go backward
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, RIGHT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, LEFT_MOTOR_SPEED);
      break;
    case 3: // turn left
      analogWrite(RIGHT_MOTOR_PIN1, RIGHT_MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, LEFT_MOTOR_SPEED);
      break;
    case 4: // turn right
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, RIGHT_MOTOR_SPEED);
      analogWrite(LEFT_MOTOR_PIN1, LEFT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);

  }
}

// output HTML web page for user
String SendHTML() {
  String html = "<!DOCTYPE html>\n";
  html += "<html>\n";
  html += "<head>\n";
  html += "<title>Wifi Car</title>\n";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "</head>\n";
  html += "<body>\n";
  html += "<div align=\"center\">\n";
  html += "<h1>NodeMCU Wifi Car</h1>\n";
  html += "<br>\n";
  html += "<form method=\"GET\">\n";
  html += "<input type=\"button\" value=\"Go forward\" onclick=\"window.location.href='/forward'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Go backward\" onclick=\"window.location.href='/backward'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Turn left\" onclick=\"window.location.href='/left'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Turn right\" onclick=\"window.location.href='/right'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Car stop\" onclick=\"window.location.href='/stop'\">\n";
  html += "</form>\n";
  html += "</div>\n";
  html += "</body>\n";
  html += "</html>\n";
  return html;
}
