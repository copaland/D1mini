/*  6-1stepDirControl
 *   D1,imi Simple Stepper Motor Control Code    
 */

// defines pins numbers //d4-2, d3-0, d2-4, d1-5
const int enaPin = 5; //d1-5
const int stepPin = 4; //d2-4
const int dirPin = 2; //d4-2
const int steps = 200; //1.8도
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enaPin,OUTPUT);
  digitalWrite(enaPin,LOW); 
}

void loop() {
  digitalWrite(dirPin,HIGH); //  Makes 200 pulses 
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses 
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
  delay(1000);
}
