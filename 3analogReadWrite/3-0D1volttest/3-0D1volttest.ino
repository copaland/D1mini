ADC_MODE(ADC_VCC); // 3.3v voltage sensor
int vcc;

void setup() {
  Serial.begin(115200);
}

void loop() {
  vcc = ESP.getVcc();
  float dvcc = (float)vcc / 1024.0;
  Serial.println("Voltage: " + String(dvcc, 3) + "V");
  delay(500);
}
