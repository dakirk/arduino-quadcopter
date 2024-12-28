/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo ESC1;     // create servo object to control the ESC
Servo ESC2;
Servo ESC3;
Servo ESC4;

int esc1Min = 6;
int esc1Max = 80;
int esc2Min = 37;
int esc2Max = 125;
int esc3Min = 41;
int esc3Max = 130;
int esc4Min = 39;
int esc4Max = 128;

int storedThrottle = 0;

int throttle;  // value from the analog pin

void escInit() {
  ESC1.attach(5,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(2,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC3.attach(3,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC4.attach(4,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 

  ESC1.write(0);
  ESC2.write(0);
  ESC3.write(0);
  ESC4.write(0);
  delay(3000);
}

void rcInit() {
  // put your setup code here, to run once:
  float dutyArr[6] = {0,0,0,0,0,0};
  for (int i = 0; i < 6; i++) {
    pinMode(int(52 - 2*i), INPUT);
  }
}

float readRcInput() {
  // put your main code here, to run repeatedly:
  float dutyArr[6] = {};
 
  for (int i = 0; i < 6; i++) {
    unsigned long highDuration = pulseIn(int(52 - 2*i), HIGH, 40000);
    // unsigned long lowDuration = pulseIn(int(52 - 2*i), LOW);
    dutyArr[i] = constrain((float)highDuration/1000 - 1, 0, 1);
    // Serial.println(to_string(i) + " " + to_string(dutyArr[i]));
    Serial.print(i);
    Serial.print(" ");
    Serial.print(dutyArr[i]);
    Serial.print(" ");
  }
  Serial.println("");

  return dutyArr[3];
}

void writeMotors(int throttle) {
  //potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  //potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  Serial.print("throttle: ");
  Serial.println(throttle);

  if (throttle == 0) {
    ESC1.write(0);
    ESC2.write(0);
    ESC3.write(0);
    ESC4.write(0);
  }

  if (throttle != storedThrottle) {
    Serial.println("change!");
    ESC1.write(map(throttle, 0, 100, esc1Min, esc1Max));    // Send the signal to the ESC
    ESC2.write(map(throttle, 0, 100, esc2Min, esc2Max));    // Send the signal to the ESC
    ESC3.write(map(throttle, 0, 100, esc3Min, esc3Max));    // Send the signal to the ESC
    ESC4.write(map(throttle, 0, 100, esc4Min, esc4Max));    // Send the signal to the ESC
  }
  storedThrottle = throttle;

  delay(200);
}

void setup() {
  Serial.begin(115200);
  rcInit();
  escInit();
}

void loop() {
  float throttle = readRcInput();
  writeMotors(throttle*100);
}
