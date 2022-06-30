/*
 * Create a level (tool) using Sparkfun's LSM9DS1 IMU.
 * Light up a yellow LED when between five degrees and one degree of level.
 * Light up a green LED when within one degree of and while level.
 * Parts of this code were borrowed from Sparkfun's LSMDS1_Basic_I2C.ino.
*/

//include necessary libraries, SPI and Wire must be called before 9DS1
#include <SPI.h>
#include <Wire.h>
#include <SparkFunLSM9DS1.h>
#include <LSM9DS1_Types.h>
#include <LSM9DS1_Registers.h>

//create an object using LSM9DS1, does not have to be labeled imu
LSM9DS1 imu;

//declination of Winona, MN is 1 degree, 11 feet W (-1 11'). magnetometer x and y axis are flipped  so (+) instead of (-)
#define DECLINATION 1.

//define LED pins
int ledG = 2;
int ledY = 3;


void setup() {
  //enable LED pins as outputs
  pinMode(ledG, OUTPUT);  
  pinMode(ledY, OUTPUT);
  
  //begins I2C communication with IMU
  Wire.begin();

  // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  if (imu.begin() == false) { 
    while (1);
  }
  
}

void loop() {
  //updates accelerometer values when new data is available
  if ( imu.accelAvailable() ) {
    
    //read and update accelerometer variables
    imu.readAccel(); 
  }

  //declare variables used to calculate pitch and roll
  float aX = imu.calcAccel(imu.ax);
  float aY = imu.calcAccel(imu.ay);
  float aZ = imu.calcAccel(imu.az);
  
  //calculate pitch and roll in radians
  float roll = atan2(aY, aZ);
  float pitch = atan2(-aX, sqrt(aY * aY + aZ * aZ));
  
  //convert to degrees
  float rollDegree = roll *= 180.0 / PI;
  float pitchDegree = pitch *= 180.0 / PI;
  
  //within 5 degree and 1 degree of level, turn green LED on and yellow LED off
  if ( abs(rollDegree) < 5 && abs(rollDegree) >= 1.) {
    if (abs(pitchDegree) < 5 && abs(pitchDegree) >= 1.) {
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, HIGH);
    }
  }
  
  //within 1 degree and at level, turn green on and turn yellow off
  else if ( abs(rollDegree) < 1 && abs(pitchDegree) < 1) {
    digitalWrite(ledG, HIGH);
    digitalWrite(ledY, LOW);
  }
  
  //at 5 degrees or greater turn off both LEDs
  else {
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
  }
   
}
