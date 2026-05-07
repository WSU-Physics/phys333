#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "RTClib.h"
#include <SD.h>

Adafruit_MPU6050 mpu;

RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int chipSelect = 10;
File dataFile;

bool loggingBadPosture = false;

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
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  rtc.start();


  float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
  float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
  float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
  float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
  int offset = round(deviation_ppm / drift_unit);

  Serial.print("Offset is "); Serial.println(offset); // Print to control offset

/*---SD Card---*/
Serial.print("Initializing SD card...");

if (!SD.begin(chipSelect)) {
  Serial.println("FAILED");
  while (1);
}

Serial.println("SUCCESS");

dataFile = SD.open("posture.csv", FILE_WRITE);

if (dataFile) {
  dataFile.println("Date, Time, Roll, Posture");
  dataFile.close();
} else {
  Serial.println("Could not open posture.csv");
}
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

/*---Posture---*/
  float deviate = fabs(Roll - baseAngle);
  bool badPosture = deviate > limitAngle;

/*---Clock---*/
  DateTime now = rtc.now();

    Serial.print(now.year());
    Serial.print("/");
    Serial.print(now.month());
    Serial.print("/");
    Serial.print(now.day());
    Serial.print(", ");

    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.print(now.second());
    Serial.print(", ");

    Serial.print("Roll: ");
    Serial.print(Roll);

    if (badPosture) {
      Serial.println(" BAD");
    }
    else {
      Serial.println(" GOOD");
    }

  delay(1000);

/*---Vibration Motor---*/
if (badPosture) {

  // Start timing when bad posture first begins
  if (!timingBad) {
    timingBad = true;
    badStart = millis();
  }

  // Check if bad posture has lasted too long
  if (millis() - badStart >= badLimit) {
\
    if (!loggingBadPosture) {
      loggingBadPosture = true;
      logPosture("START", now, Roll);
    }

    logPosture("BAD", now, Roll);

    // Only buzz every few seconds, not constantly
    if (millis() - lastbuzzON >= buzzWAIT) {
      vibAlarm();
      lastbuzzON = millis();
    }
  }

} else {
  // Good posture again, so reset everything
  if (loggingBadPosture) {
    loggingBadPosture = false;
    logPosture("END", now, Roll);
  }

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

void logPosture(String eventType, DateTime now, float Roll){

  dataFile = SD.open("posture.csv", FILE_WRITE);

  if (dataFile) {

    dataFile.print(eventType);
    dataFile.print(",");

    dataFile.print(now.year());
    dataFile.print("/");
    dataFile.print(now.month());
    dataFile.print("/");
    dataFile.print(now.day());
    dataFile.print(",");

    dataFile.print(now.hour());
    dataFile.print(":");
    dataFile.print(now.minute());
    dataFile.print(":");
    dataFile.print(now.second());
    dataFile.print(",");

    dataFile.print("Roll:");
    dataFile.print(Roll);

    dataFile.close();
  } else {
    Serial.println("Error opening posture.csv");
  }
}
