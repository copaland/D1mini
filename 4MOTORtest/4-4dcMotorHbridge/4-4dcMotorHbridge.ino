// Ex4. 4-4 dcMotorHbridge.ino
//Arduino UNO with L293D

#define BTN_DIR 13
#define POT  0
#define EN1  3
#define M1A  4 //1A
#define M1B  7 //2A

int pos, veloc, oldpos=-1;

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(BTN_DIR, INPUT);
  digitalWrite(EN1, LOW);//BRAKE
}
void loop(){
  pos = analogRead(POT);
  if (pos != oldpos){
    veloc = map(pos, 0, 1023, 0, 255);
    analogWrite(EN1, veloc);
    oldpos = pos;
  }
  if (digitalRead(BTN_DIR)==LOW){
    digitalWrite(M1A, HIGH);  
    digitalWrite(M1B, LOW);
  }
  else{
    digitalWrite(M1A, LOW);  
    digitalWrite(M1B, HIGH);
  }
  delay(200);
}
