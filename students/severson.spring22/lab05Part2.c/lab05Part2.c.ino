/*
 * Create a level (tool) using Sparkfun's LSM9DS1 IMU.
 * Light up a yellow LED when between five degrees and one degree of level.
 * Light up a green LED when within one degree of and while level.
*/

#include <SPI.h>
#include <Wire.h>
#include <SparkFunLSM9DS1.h>
#include <LSM9DS1_Types.h>
#include <LSM9DS1_Registers.h>


LSM9DS1 imu;

#define DECLINATION 1.

int ledG = 2;
int ledY = 3;

void setup() {
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  
  if (imu.begin() == false) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("float-check wiring.");
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are.");
    while (1);
  }
}

void loop() {
  if ( imu.accelAvailable() ) {
    imu.readAccel(); 
  }
  
  float aX = imu.calcAccel(imu.ax);
  float aY = imu.calcAccel(imu.ay);
  float aZ = imu.calcAccel(imu.az);
  
  float roll = atan2(aY, aZ);
  float pitch = atan2(-aX, sqrt(aY * aY + aZ * aZ));

  float rollDegree = roll *= 180.0 / PI;
  float pitchDegree = pitch *= 180.0 / PI;

  if ( abs(rollDegree) < 5 && abs(rollDegree) >= 1) {
    if (abs(pitchDegree) < 5 && abs(pitchDegree) >= 1) {
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, HIGH);
      if ( abs(rollDegree) < 1 && abs(rollDegree) >= 0) {
        if ( abs(pitchDegree) < 1 && abs(pitchDegree) >=0) {
        digitalWrite(ledG, HIGH);
        digitalWrite(ledY, LOW);
        }
      }
    }
  }
  else {
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
  }


  Serial.println(aX);
  Serial.println(aY);
  Serial.println(aZ);
  Serial.println(rollDegree);
  Serial.println(pitchDegree);
   
}
