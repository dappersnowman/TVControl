#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <QueueArray.h>

/* Assign a unique ID to the sensors */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

  float a[10];
  QueueArray <float> Q;

void setup() {
}


void loop() {
  sensors_event_t event;
  gyro.getEvent(&event);
  Q.push(event.gyro.z);
  Q.push(-1*event.gyro.y);
  Q.push(event.gyro.x);
  accel.getEvent(&event);
  Q.push(event.acceleration.z);
  Q.push(-1*event.acceleration.y);
  Q.push(event.acceleration.x);
  mag.getEvent(&event);
  Q.push(event.magnetic.z);
  Q.push(-1*event.magnetic.y);
  Q.push(event.magnetic.x);
  bmp.getEvent(&event);
  if(event.pressure){
    float temperature;
    bmp.getTemperature(&temperature);
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA; 
  Q.push((bmp.pressureToAltitude(seaLevelPressure,event.pressure,temperature)));
  }
  Q.push((float)millis());
delay(100);
}
