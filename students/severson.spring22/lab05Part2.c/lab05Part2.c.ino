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
#define DECLINATION -1.;

LSM9DS1 imu;
 
void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);

}

void loop() {
  if (imu.gyroAvailable()) {
    imu.readGyro();
  }
  if (imu.accelAvailable()) {
    
  }
  if (imu.magAvailable()) {
    
  }
  
  float gX = imu.calcGyro(imu.gx);
  float gY = imu.calcGyro(imu.gy);
  float gZ = imu.calcGyro(imu.gz);
  float aX = imu.calcAccel(imu.ax);
  float aY = imu.calcAccel(imu.ay);
  float aZ = imu.calcAccel(imu.az);
  float mX = imu.calcMag(imu.mx);
  float mY = imu.calcMag(imu.my);
  float mZ = imu.calcMag(imu.mz);

  float roll = atan2(aY, aZ);
  float pitch = atan2(-aX, sqrt(aY * aY + aZ * aZ));
  float rollDegrees = roll *= 180.0 / PI;
  float pitchDegrees = pitch *= 180.0 / PI;

  while (( 1. <= abs(rollDegrees)) && (abs(rollDegrees) < 5.)) {
    while ((1. <= abs(pitchDegrees)) && (abs(pitchDegrees) < 5.)) {
      digitalWrite(ledYellow, HIGH);
    }
  }
  
   while (( 0. <= abs(rollDegrees)) && (abs(rollDegrees) < 1.)) {
    while (( 0. <= abs(pitchDegrees)) && (abs(pitchDegrees) < 1.)) {
      digitalWrite(ledGreen, HIGH);
   }
  }
  
}
