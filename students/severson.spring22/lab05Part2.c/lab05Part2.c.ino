/*
 * Attempt to create a level (tool) using Sparkfun's LSM9DS1 IMU.
 * Light up a yellow LED when within five degrees of level.
 * Light up a green LED when within one degree of level.
 * All of the following 9DOF code is ripped from Sparkfun's LSMDS1_Basic_I2C example.
 * Only the code to light up the LEDs is original.
 */

#include <Wire.h>
#include <SPI.h>
#include <LSM9DS1_Types.h>
#include <SparkFunLSM9DS1.h>
#include <LSM9DS1_Registers.h>

int ledGreen = 2;
int ledYellow = 3;
#define DECLINATION -1;

LSM9DS1 imu;
 
void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  Serial.begin(115200);
  Wire.begin();

}

void loop() {
  if (imu.gyroAvailable()) {
    imu.readGyro();
  }
  if (imu.accelAvailable()) {
    imu.readAccel();
  }
  if (imu.magAvailable()) {
    imu.readMag();
  }
  imu.calcGyro(imu.gx);
  imu.calcGyro(imu.gy);
  imu.calcGyro(imu.gz);
  imu.calcAccel(imu.ax);
  imu.calcAccel(imu.ay);
  imu.calcAccel(imu.az);
  imu.calcMag(imu.mx);
  imu.calcMag(imu.my);
  imu.calcMag(imu.mz);
  
  float roll = atan2(imu.ay, imu.az);
  roll *= 180.0 / PI;
  float pitch = atan2(-imu.ax, sqrt(imu.ay * imu.ay + imu.az * imu.az));
  pitch *= 180.0 / PI;

  while (( 1 <= abs(roll) < 5) &&  (1 < abs(pitch) < 5)) {
    digitalWrite(ledYellow, HIGH);
  }
  while (( 0 <= abs(roll) < 1) && ( 0 <= abs(pitch) < 1)) {
    digitalWrite(ledGreen, HIGH);
  }
  
  

}
