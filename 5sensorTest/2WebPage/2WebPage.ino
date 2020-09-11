/* 
 Ex2. 2WebPage.ino
Web page read from www.example.com 
*/

#include "ESP8266WiFi.h"

// WiFi parameters
const char* ssid = "dlink-EBE2";//"wifi-name";
const char* password = "zdcvm97008";//"wifi-pass";

//Host
const char* host = "www.example.com";
const int httpPort = 80;

void setup()
{  
  // Start Serial
  Serial.begin(115200);
  
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connectint to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());// Print the IP address 
}

void loop() {
  Serial.print("Connecting to : "); 
  Serial.println(host); 
  
  // Handle TCP connection
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }

  //send the request to the server
  client.print(String("GET /") + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(10);
 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("Closing connection-----------!");
  delay(5000);
}
