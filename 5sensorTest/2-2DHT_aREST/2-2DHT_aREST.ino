/* 
 Ex2-2. 2DHT_arest.ino
 aREST.io API를 사용하여 온도와 습도 측정하기 
*/
#include "ESP8266WiFi.h"
#include <aREST.h>
#include "DHT.h"

// DHT11 sensor pins
#define DHTPIN D1 //5
#define DHTTYPE DHT11

// Create aREST instance
aREST rest = aREST();

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// WiFi parameters
//const char* ssid = "wifi-name";
//const char* password = "wifi-pass";

const char* ssid = "dlink-EBE2";//"wifi-name";
const char* password = "zdcvm97008";//"wifi-pass";

// The port to listen for incoming TCP connections 
#define httpPort   80

// Create an instance of the server
WiFiServer server(httpPort);

// Variables to be exposed to the API
float temperature;
float humidity;

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
  
  // Init DHT 
  dht.begin();
  
  // Init variables and expose them to REST API
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
    
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
  
}

void loop() {
    
  // Reading temperature and humidity
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
 
}
