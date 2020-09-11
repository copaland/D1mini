/*
  Ex3. 3-3ledFade.ino
  D1 mini LED fade PWM output
*/
//bright the LED is (0 = full, 512 = dim, 1023 = off)
int ledPin = D4;      // BUILTIN_LED
int value = 0;
int dir = 1;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if(millis()%10==0){
      value = value + dir;
      if((value == 0)||(value == 1023)) {
        dir = dir*-1;
      }
  }
  analogWrite(ledPin, value);
  delay(1);
}
