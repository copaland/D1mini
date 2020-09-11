/* 
 Ex1. 1-1ledTest.ino
 D1 mini builtinLED Blink with Delay 
*/
const int ledPin = BUILTIN_LED; //2:D4

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, LOW); // LED on acive low 
  delay(1000); 
  digitalWrite(ledPin, HIGH); // LED off
  delay(1000);                      
}
