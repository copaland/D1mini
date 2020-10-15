/*  6-2stepFuncControl
 *   D1 Stepper Motor Control Example Code    
 */

// defines pins numbers //d4-2, d3-0, d2-4, d1-5
const int enaPin = 5; //d1-5
const int stepPin = 4; //d2-4
const int dirPin = 2; //d4-2

const int steps = 200;//1.8도
int rpm = 120;
unsigned microsteps = 1; // for 1:16 microsteps is 16
unsigned long step_pulse=60*1000000L/steps/microsteps/rpm;//5000;

/* 주어진 rpm 값으로 마이크로 초 단위의 스텝 펄스를 계산
 * calculate the step pulse in microseconds for a given rpm value.
 * 60[s/min] * 1000000[us/s] / microsteps / steps / rpm
 */
#define STEP_PULSE(steps, microsteps, rpm) (60*1000000L/steps/microsteps/rpm)

 /*
인라인 함수(inline function): 함수의 실행 시간이 매우 짧다면, 
함수 호출에 걸리는 시간도 부담이 될때
일반적인 함수의 호출 과정을 거치지 않고, 
함수의 모든 코드를 호출된 자리에 바로 삽입하는 방식
*/
inline void microWaitUntil(unsigned long target_micros){
    yield(); //호출시 다른 작업에 제어권을 전달
    while (micros() < target_micros);
}
#define DELAY_MICROS(us) microWaitUntil(micros() + us)

void setDirection(int direction);
void move(long steps);
inline void rotate(int deg){
        rotate((long)deg);
};

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enaPin,OUTPUT);
  digitalWrite(enaPin,LOW); 
}
void loop() {
  move(200);
  delay(1000); 
  move(-200);
  delay(1000);
  
}


/*
 * DIR: forward HIGH, reverse LOW
 */
void setDirection(int direction){
    digitalWrite(dirPin, (direction<0) ? LOW : HIGH);
}

void move(long steps){
    if (steps >= 0){
        setDirection(1);
    } else {
        setDirection(-1);
        steps = -steps;
    }

    unsigned long pulse_duration = step_pulse/2;
    while (steps--){
        digitalWrite(stepPin, HIGH);
        unsigned long next_edge = micros() + pulse_duration;
        microWaitUntil(next_edge);
        digitalWrite(stepPin, LOW);
        microWaitUntil(next_edge + pulse_duration);
    }
}













/*
 * Move the motor a given number of degrees (1-360)
 */
void rotate(long deg){
    long steps = (deg * steps * microsteps) / 360.0;
    move(steps);
}
