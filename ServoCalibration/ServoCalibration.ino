//Calibrating a servo with output wires soldered to the internal potentiometer.
//Output both input and output streams to serial

#include <Servo.h>

void sweep();
void stepResponse();
void rampResponse();
void sinusoidalResponse();

Servo servo;
int maxAngle = 180;
int minAngle = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
}

void loop() {
  Serial.println("Ready to record");
  Serial.println("Input 1 for sweep and hold");
  Serial.println("Input 2 for step response");
  Serial.println("Input 3 for ramp response");
  Serial.println("Input 4 for sinusoidal response");
  Serial.println("Input 5 to change max and min");
  Serial.print("Current max = ");
  Serial.println(maxAngle);
  Serial.print("Current min = ");
  Serial.println(minAngle);
  
  while(Serial.available() == 0) {
    delay(10);
  }
  
  switch(Serial.parseInt()) {
    case 1:
      Serial.println("Beginning sweep and hold trial");
      sweep();
      break;
    case 2:
      Serial.println("Beginning step response trial");
      stepResponse();
      break;
    case 3:
      Serial.println("Beginning ramp response trial");
      rampResponse();
      break;
    case 4:
      Serial.println("Beginning sinusoidal response trial");
      sinusoidalResponse();
      break;
    case 5:
      Serial.println("Input new max angle");
      while(Serial.available() == 0) {
        delay(10);
      }
      maxAngle = Serial.parseInt();
      Serial.println("Input new min angle");
      while(Serial.available() == 0) {
        delay(10);
      }
      minAngle = Serial.parseInt();
    default:
      Serial.println("Bad input :(");
  }
}

void stepResponse() {
  int refInit = 45; //Start Point
  int refStep = 135; //End Point
  
  if (refStep > maxAngle) {
    int refDiff = refStep-maxAngle;
    refStep = refStep - refDiff;
    refInit = refInit - refDiff;
  }
  else if (minAngle > refInit) {
    int refDiff = minAngle - refInit;
    refStep = refStep + refDiff;
    refInit = refInit + refDiff;
  }
  
  int ref = refInit; //reference input to be written to serial
  servo.write(ref);
  delay(1000);
  Serial.println("Time (milli) : Input (deg) : Output (v)");
  unsigned long tstart = millis();
  
  while ((millis() - tstart) < 1000) {
    if ((millis() - tstart) > 500) {
      ref = refStep;
    }
    servo.write(ref);
    Serial.print(millis() - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  Serial.println("Sweep Finished");
}

void sweep() {
  float refSpeed = 180.0/1000.0; //degrees per millisecond
  unsigned long elapsedTime = 0;
  
  //Starting at minimum
  int ref = 0;
  servo.write(ref);
  delay(1000);
  
  Serial.println("Time (milli) : Input (deg) : Output (v)");
  unsigned long tstart = millis();
  while ((millis() - tstart < 500)) {
    Serial.print(millis() - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime = millis() - tstart;
  
  //Sweep Up
  tstart = millis();
  while(ref < 180) {
    ref = (int)((millis() - tstart)*refSpeed);
    servo.write(ref);
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime += millis() - tstart;
  
  //Hold at max
  tstart = millis();
  ref = 180;
  servo.write(ref);
  while((millis() - tstart) < 500) {
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime += millis() - tstart;
  
  //Sweep Down
  tstart = millis();
  while(ref > 0) {
    ref = (int)(180.0 - (((float)(millis() - tstart))*refSpeed));
    servo.write(ref);
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime += millis() - tstart;
  
  //Hold at down
  tstart = millis();
  ref = 0;
  servo.write(ref);
  while((millis() - tstart) < 500) {
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  Serial.println("Sweep Trial Complete");
}

void rampResponse() {
  float refSpeed = 180.0/1000.0; //degrees per millisecond
  unsigned long elapsedTime = 0;
  
  //Starting at minimum
  int ref = minAngle;
  servo.write(ref);
  delay(1000);
  
  Serial.println("Time (milli) : Input (deg) : Output (v)");
  unsigned long tstart = millis();
  while ((millis() - tstart < 500)) {
    Serial.print(millis() - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime = millis() - tstart;
  
  //Sweep Up
  tstart = millis();
  while(ref < maxAngle) {
    ref = (int)((millis() - tstart)*refSpeed) + minAngle;
    servo.write(ref);
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime += millis() - tstart;
  
  //Hold at max
  tstart = millis();
  ref = maxAngle;
  servo.write(ref);
  while((millis() - tstart) < 500) {
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime += millis() - tstart;
  
  //Sweep Down
  tstart = millis();
  while(ref > minAngle) {
    ref = (int)(((float)(maxAngle)) - (((float)(millis() - tstart))*refSpeed));
    servo.write(ref);
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  elapsedTime += millis() - tstart;
  
  //Hold at down
  tstart = millis();
  ref = minAngle;
  servo.write(ref);
  while((millis() - tstart) < 500) {
    Serial.print(millis() + elapsedTime - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
  Serial.println("Ramp Response Trial Complete");
}

void sinusoidalResponse() { //Need to fix ref calculation
  int period = 1000; //milliseconds
  int neutralPoint = minAngle + ((maxAngle-minAngle)/2);
  int range = 60; //degrees
  if ((maxAngle-neutralPoint) < range) {
    range = (maxAngle-neutralPoint);
  }
  servo.write(neutralPoint);
  int ref = neutralPoint;
  delay(500);
  Serial.println("Time (milli) : Input (deg) : Output (v)");
  unsigned long tstart = millis();
  
  while((millis() - tstart) < (period * 2)) {
    ref = range*(sin((((float)(millis()-tstart))*6.28) / ((float)period)));
    servo.write(ref);
    Serial.print(millis() - tstart);
    Serial.print(" : ");
    Serial.print(ref);
    Serial.print(" : ");
    Serial.println(analogRead(A0));
  }
}
