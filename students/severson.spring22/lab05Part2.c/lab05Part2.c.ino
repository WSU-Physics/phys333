/*
 * Create a level (tool) using Sparkfun's LSM9DS1 IMU.
 * Light up a yellow LED when between five degrees and one degree of level.
 * Light up a green LED when within one degree of and while level.
*/

#include <SPI.h>
#include <Wire.h>
#include <LSM9DS1_Types.h>
#include <SparkFunLSM9DS1.h>
#include <LSM9DS1_Registers.h>

LSM9DS1 imu;

#define ledG 2
#define ledY 3

void setup() {
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
  
}

void loop() {
  if ( imu.accelAvailable() ) {
    imu.readAccel(); 
  //}
  float ax = imu.calcAccel(imu.ax);
  float ay = imu.calcAccel(imu.ay);
  float az = imu.calcAccel(imu.az);
  
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));

  float rollDegree = roll *= 180.0 / PI;
  float pitchDegree = pitch *= 180.0 / PI;

  if ( abs(rollDegree) < 5 && abs(rollDegree) >= 1) {
    if (abs(pitchDegree) < 5 && abs(pitchDegree) >= 1) {
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, HIGH);
      if ( abs(rollDegree) < 1 && abs(pitchDegree) < 1) {
        digitalWrite(ledG, HIGH);
        digitalWrite(ledY, LOW);
      }
    }
  }
  else {
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
  }
  } 
}
