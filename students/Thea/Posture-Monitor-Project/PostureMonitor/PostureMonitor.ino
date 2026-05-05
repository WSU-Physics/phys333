#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

/*---Vibration Motor---*/
const int vibPin = 9;
const unsigned long badLimit = 5000;
const unsigned long buzzON = 300;
const unsigned long buzzWAIT = 3000;
unsigned long badStart = 0;
unsigned long lastbuzzON = 0;
bool timingBad = false;

/*---Posture---*/
float baseAngle = 65.0;
float limitAngle = 25.0;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

/*---Is It Connected?---*/
  if (!mpu.begin()) {
    Serial.println("Not Found.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

/*---Set Ranges---*/
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

/*---Vibration Motor---*/
  pinMode(vibPin, OUTPUT);
  analogWrite(vibPin, 0);

}

void loop() {
/*---Get Sensor Events---*/
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

/*---Variables Simplified---*/
  float Ax = accel.acceleration.x;
  float Ay = accel.acceleration.y;
  float Az = accel.acceleration.z;
  float Gx = gyro.gyro.x;
  float Gy = gyro.gyro.y;
  float Gz = gyro.gyro.z;
  float T = temp.temperature;

/*---Calculate Pitch/Roll---*/
  float Roll = atan2(Ay, Az) * 180 / PI;
  float Pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180 / PI;

/*---Print Data---*/
  Serial.print("Ax:"); Serial.print(Ax); Serial.print(" ");
  Serial.print("Ay:"); Serial.print(Ay); Serial.print(" ");
  Serial.print("Az:"); Serial.print(Az); Serial.print(" ");

  //Serial.print("Gx:"); Serial.print(Gx); Serial.print(" ");
  //Serial.print("Gy:"); Serial.print(Gy); Serial.print(" ");
  //Serial.print("Gz:"); Serial.print(Gz); Serial.print(" ");

  Serial.print("R:"); Serial.print(Roll); Serial.print(" ");
  Serial.print("P:"); Serial.print(Pitch); Serial.print(" ");

  //Serial.print("Dev:"); Serial.print(deviate); Serial.print(" ");
  //Serial.print("Bad:"); Serial.print(badPosture); Serial.print(" ");

  Serial.print("T: "); Serial.println(T);

  Serial.println("");
  delay(1000);

/*---Posture---*/
float deviate = fabs(Roll - baseAngle);
bool badPosture = deviate > limitAngle; 

/*---Vibration Motor---*/
if (badPosture) {

  // Start timing when bad posture first begins
  if (!timingBad) {
    timingBad = true;
    badStart = millis();
  }

  // Check if bad posture has lasted too long
  if (millis() - badStart >= badLimit) {

    // Only buzz every few seconds, not constantly
    if (millis() - lastbuzzON >= buzzWAIT) {
      vibAlarm();
      lastbuzzON = millis();
    }
  }

} else {
  // Good posture again, so reset everything
  timingBad = false;
  badStart = 0;
  analogWrite(vibPin, 0);
}


}

void vibAlarm() {
  analogWrite(vibPin, 150);
  delay(buzzON);
  analogWrite(vibPin, 0);
}
