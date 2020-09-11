/*
  Ex3. 3-2analogPWM.ino
  D1 mini Analog read PWM output
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
int adcPin = A0;    // potentiometer
int ledPin = D4;      // LED
int POT = 0;  // store the sensor value
int mPOT = 0; //store mapping value

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(millis()%1000==0){
    POT = analogRead(adcPin); //0-999
    Serial.print("POT: ");
    Serial.println(POT);
    mPOT = map(POT, 0,1023,0,255);
    Serial.print("mPOT: ");
    Serial.println(mPOT);
  }
  analogWrite(ledPin,mPOT);
  delay(1);
}
