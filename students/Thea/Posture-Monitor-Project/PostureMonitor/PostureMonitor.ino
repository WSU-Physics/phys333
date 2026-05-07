#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "RTClib.h"

Adafruit_MPU6050 mpu;

RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


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
  if (!mpu.begin(0x69)) {
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

/*---Clock---*/
#ifndef ESP8266
  while (!Serial); 
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2026, 5, 5, 10, 11, 0));
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  rtc.start();


  float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
  float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
  float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
  float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
  int offset = round(deviation_ppm / drift_unit);

  Serial.print("Offset is "); Serial.println(offset); // Print to control offset
}

void loop() {
/*---Get Sensor Events---*/
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

/*---Variables Simplified---*/
  float Ax = accel.acceleration.x;
  float Ay = accel.acceleration.y;
  float Az = accel.acceleration.z;
  float T = temp.temperature;

/*---Calculate Pitch/Roll---*/
  float Roll = atan2(Ay, Az) * 180 / PI;
  float Pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180 / PI;

/*---Print Data---*/
  //Serial.print("Ax:"); Serial.print(Ax); Serial.print(" ");
  //Serial.print("Ay:"); Serial.print(Ay); Serial.print(" ");
  //Serial.print("Az:"); Serial.print(Az); Serial.print(" ");

  Serial.print("Roll:"); Serial.print(Roll); Serial.print(" ");
  //Serial.print("P:"); Serial.print(Pitch); Serial.print(" ");

  Serial.print("Temperature: "); Serial.println(T);

  Serial.println("");

/*---Clock---*/
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

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
