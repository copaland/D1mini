/*
  Ex3. 3-4readVoltage.ino
  D1 mini Read voltage through analog port
  Vout = R2/(R1+R2)*Vin = 100/(220+100)*3.2 = 1V
  -[180K]----A0 (VCC3.2V) [Vcc5.0V]
  |
 220K
  |--- ADC(0~1V)
 100K
  |
 GND
*/

//bright the LED is (0 = full, 512 = dim, 1023 = off)
float Vref = 3.3; 
float RatioFactor = 1.0-((3.3-3.227)/3.227);//3.227);//real/meas

int adcPin = A0;    // potentiometer
int ledPin = D4;      // LED
int pwrPin = D5;  // ad power supply
int POT = 0;  // store the sensor value
float VOLT = 0;
bool X = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pwrPin, OUTPUT);
  pinMode(adcPin, INPUT);
  digitalWrite(pwrPin, HIGH);  
  Serial.begin(115200);
}

void loop() {
  if(millis()%1000==0){
    POT = analogRead(adcPin); //0-999
//    Serial.println("POT: " + String(POT) + ": ");
    
    VOLT = POT * (Vref / 1023.0);
    Serial.print("Volt: " + String(VOLT) + "v");
    float rVOLT = VOLT*RatioFactor;
    Serial.println(" : " + String(rVOLT) + "V"); 
    X = !X; 
  }
  digitalWrite(ledPin, X);
  delay(1);
}
