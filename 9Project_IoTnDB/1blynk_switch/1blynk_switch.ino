/************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest
    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    
D1mini PINMAP
Tx  1
Rx  3
D1  5 (SCL)
D2  4 (SDA)button
D3  0 FLASH 
D4  2 <LED>  
A0  ADC0
D0  16 wake 
D5  14 SCK  
D6  12 MISO 
D7  13 MOSI 
D8  15 SS 
 ************************************
  Blynk using a LED widget on your phone!

  App project setup:
    LED widget on V1
 *************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#ifndef STASSID
  #define STASSID "YourNetworkName"
  #define STAPASS "YourPassword"
#endif

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";//"YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = STASSID;//"YourNetworkName";
char pass[] = STAPASS;//"YourPassword";

const int ledPin = 2; //D4
const int btnPin = 4; //D2 // Select your pin with physical button

BlynkTimer timer;
void checkPhysicalButton();

int ledState = LOW;
int btnState = LOW;

// Every time we connect to the cloud...
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V2);

  // Alternatively, you could override server state using:
  ///Blynk.virtualWrite(V2, ledState);
}

// When App button is pushed - switch the state
BLYNK_WRITE(V2) {
  ledState = param.asInt();
//  BLYNK_PRINT.println(ledState);//Serial.println(param.asStr());
  digitalWrite(ledPin, ledState);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin) == HIGH) {
    // btnState is used to avoid sequential toggles
    if (btnState != HIGH) {

      // Toggle LED state
      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      // Update Button Widget
      Blynk.virtualWrite(V2, ledState);
    }
    btnState = HIGH;
  } else {
    btnState = LOW;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup physical button pin (active low)
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT); //(active HIGH)
  timer.setInterval(10L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
 // delay(1);
}
