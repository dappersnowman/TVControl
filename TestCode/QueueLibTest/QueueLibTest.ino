#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

/* Assign a unique ID to the sensors */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

float DataQueue[100000][11];
int readPoint = 0;
int writePoint = 0;

void pushToQueue(float * event) {
  DataQueue[writePoint] = event;
  writePoint += 1;
  if (writePoint >= 100000) {
    writePoint = 0;
  }
}

float* pullFromQueue(void) {
  float stagingArray[11];
  stagingArray = DataQueue[readPoint];
  readPoint += 1;
  if (readPoint >= 100000) {
    readPoint = 0;
  }
  return stagingArray;
}

float* readFromQueue(void) {
  float stagingArray[11];
  stagingArray = DataQueue[readPoint];
  return stagingArray;
}

int countQueue(void) {
  return (writePoint - readPoint);
}

void setup() {
  Serial.begin(9600);
}


void loop() {
  float stagingArray[11];
  sensors_event_t event;
  gyro.getEvent(&event);
  stagingArray[0] = event.gyro.z;
  stagingArray[1] -1*event.gyro.y;
  stagingArray[2] = event.gyro.x;
  accel.getEvent(&event);
  stagingArray[3] = event.acceleration.z;
  stagingArray[4] = -1*event.acceleration.y;
  stagingArray[5] = event.acceleration.x;
  mag.getEvent(&event);
  stagingArray[6] = event.magnetic.z;
  stagingArray[7] = -1*event.magnetic.y;
  stagingArray[8] = event.magnetic.x;
  bmp.getEvent(&event);
  if(event.pressure){
    float temperature;
    bmp.getTemperature(&temperature);
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    stagingArray[9] = (bmp.pressureToAltitude(seaLevelPressure,event.pressure,temperature));
  }
  stagingArray[10] = (float)millis();
  pushToQueue(stagingArray);
  delay(100);
  
  Serial.print("Count: ");
  Serial.println(countQueue());
  Serial.print("First Value: ");
  Serial.println(readFromQueue());
  Serial.print("PulledValues: ");
  
  stagingArray
}
