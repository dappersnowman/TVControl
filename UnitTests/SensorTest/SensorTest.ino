#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

int t;
sensors_event_t event;

void setup() {
  Serial.begin(9600);

  if(!accel.begin()) {
    Serial.println("LSM303 Accelerometer failed to initialize; Check Wiring");
    while(1);
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
  
  Serial.println("Sensor ready to record.");
}

void loop() {
  Serial.println("Enter '1' to display accel data");
  Serial.println("Enter '2' to display gyro data");
  Serial.println("Enter '3' to display magnetometer data");
  Serial.println("Enter '4' to display barometer data");

  while (Serial.available() == 0) {
    delay(10);
  }

  switch(Serial.parseInt()) {
    case 1:
      //accel
      t = millis();
      while ((millis() - t) < 20000) {
        //sensors_event_t event;
        accel.getEvent(&event);
        Serial.print("Time: "); Serial.print(millis() - t); Serial.print(" milliseconds ");
        Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
        Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
        Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");
        Serial.println("m/s^2");
      }
      break;
    case 2:
      //gyro
      t = millis();
      while ((millis() - t) < 20000) {
        //sensors_event_t event;
        gyro.getEvent(&event);
        Serial.print("Time: "); Serial.print(millis() - t); Serial.print(" milliseconds ");
        Serial.print("X: "); Serial.print(event.gyro.x); Serial.print(" ");
        Serial.print("Y: "); Serial.print(event.gyro.y); Serial.print(" ");
        Serial.print("Z: "); Serial.print(event.gyro.z); Serial.print(" ");
        Serial.println("rad/s");
      }
      break;
    case 3:
      //mag
      t = millis();
      while ((millis() - t) < 20000) {
        //sensors_event_t event;
        mag.getEvent(&event);
        Serial.print("Time: "); Serial.print(millis() - t); Serial.print(" milliseconds ");
        Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print(" ");
        Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print(" ");
        Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print(" ");
        Serial.println("uT");
      }
      break;
    case 4:
      //bar
      t = millis();
      while ((millis() - t) < 5000) {
        //sensors_event_t event;
        bmp.getEvent(&event);
        float temperature;
        bmp.getTemperature(&temperature);
        float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
        Serial.print("Press "); Serial.print(event.pressure); Serial.print(" hPa, ");
        Serial.print(temperature); Serial.print(" C, ");
        Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure, temperature)); Serial.println(" m");
      }
      break;
    default:
      Serial.println("Bad input. :(");
  }
}
