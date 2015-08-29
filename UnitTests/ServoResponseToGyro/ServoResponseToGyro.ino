#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

#define SERVOPIN 9
#define TRIALTIME 20000 //20000 milliseconds = 20 seconds
#define VELGAIN 1.0 //180 deg/s --> 180 degree deflection
#define ACCELGAIN 1.0 //180 deg/s^2 --> 180 degree deflection

//Initialization of hardware
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

//Global variable initialization
sensors_event_t event;
Servo servo;
int maxAngle = 180;
int minAngle = 0;

//Function Prototypes
void posResponse(void);
void velResponse(void);
void accelResponse(void);

void setup() {
  Serial.begin(9600);

  if(!accel.begin()) {
    Serial.println("LSM303 Accelerometer failed to initialize; Check Wiring");
    while(1); //Stop program if hardware fails to initialize
  }
  if(!mag.begin()) {
    Serial.println("LSM303 Magnetometer failed to initialize; Check Wiring");
    while(1);
  }
  if(!bmp.begin()) {
    Serial.println("BMP085 barometer failed to initialize; Check Wiring or I2C ADDR");
    while(1);
  }
  if(!gyro.begin()) {
    Serial.println("L3GD20 gyro failed to initialize; Check Wiring or I2C ADDR");
    while(1);
  }
  Serial.println("Sensor ready  to record.");

  servo.attach(SERVOPIN);
  servo.write(90);
  Serial.println("Servo has been initialized.");
}

void loop() {
  Serial.println(" ");
  Serial.println("Input 1 for position based response; deg --> deg");
  Serial.println("Input 2 for velocity based response; deg/s --> deg");
  Serial.println("Input 3 for acceleration based response; deg/s^2 --> deg");
  Serial.println(" ");

  while (Serial.available() == 0) {
    delay(10);
  }

  switch(Serial.parseInt()) {
    case 1:
      Serial.println("Beginning position based response");
      posResponse();
      break;
    case 2:
      Serial.println("Beginning velocity based response");
      velResponse();
      break;
    case 3:
      Serial.println("Beginning acceleration based response");
      accelResponse();
      break;
    default:
      Serial.println("Sorry. Bad Input :(");
  }
}

void posResponse(void) {
  int t; //Current time
  int tInit; //Time at start of function
  int tPast; //Recorded time during last cycle
  float gSpeed; //Recorded speed of gyro
  float gPos = 90.0; //Interpolated position of gyro
  int sPos = 90; //Rounded position of gyro, drives servo position
  tInit = millis();
  t = tInit;

  while ((millis() - tInit) < TRIALTIME) {
    gyro.getEvent(&event);
    gSpeed = (event.gyro.z * (180.0/6.28)); //deg/s
    tPast = t;
    t = millis();
    gPos += (gSpeed * ((float)(t - tPast)) * (1.0/1000.0)); //deg
    
    if (gPos > 180.0) {
      gPos = 180.0;
    }
    else if (gPos < 0.0) {
      gPos = 0.0;
    }

    sPos = (int) gPos;
    if ((gPos - ((float) sPos)) > 0.5) { //easy way to perform rounding
      sPos += 1;
    }
    servo.write(sPos);
    delay(10); //Smooths out motion and prevents floating point drift
  }
}

void velResponse(void) {
  int tInit = millis(); //Time at start of function
  float gSpeed; //Recorded speed of gyro
  int sPos = 90; //Rounded position of gyro, drives servo position

  while((millis() - tInit) < TRIALTIME) {
    gyro.getEvent(&event);
    gSpeed = (event.gyro.z * (180.0/6.28)); //deg/s
    sPos = ((int) (gSpeed * VELGAIN)) + 90;
    servo.write(sPos);
    delay(10);
  }
}

void accelResponse(void) {
  int t; //Current time
  int tInit; //Time at start of function
  int tPast; //Recorded time during last cycle
  float gSpeed; //Recorded speed of gyro
  float gSpeedLast; //Recorded speed of gyro during last cycle
  float gAccel; //Average accel of gyro during cycle
  int sPos; //Calculated desired position of servo
  tInit = millis();
  t = tInit;

  while ((millis() - tInit) < TRIALTIME) {
    gyro.getEvent(&event);
    tPast = t;
    t = millis();
    gSpeedLast = gSpeed;
    gSpeed = (event.gyro.z * (180.0/6.28)); //deg/s
    gAccel = (gSpeed - gSpeedLast) / ((float)(t - tPast)); //deg/s^2
    sPos = ((int) (gSpeed * ACCELGAIN)) + 90;
    servo.write(sPos);
    delay(10);
  }
}

