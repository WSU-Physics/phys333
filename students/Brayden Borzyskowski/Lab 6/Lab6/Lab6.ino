#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "RTClib.h"
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
RTC_DS1307 rtc;

const int chipSelect = 10;
const long logInterval = 1; // Log data every 5 seconds
unsigned long lastLogTime = 0;

struct SensorData {
  DateTime timestamp;
  float accelerationX;
  float accelerationY;
  float accelerationZ;
  float angle;
  int distance;
};

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);

  if (!lis.begin(0x18)) {
    Serial.println("Couldn't start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1) yield();
  }
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  if (!SD.begin(10)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  String dataLog = "datalog.csv";
  if (!SD.exists(dataLog.c_str())) {
    File dataFile = SD.open(dataLog.c_str(), FILE_WRITE);
    if (dataFile) {
      dataFile.println("Timestamp,X,Y,Z,Distance");
      dataFile.close();
    } else {
      Serial.println("Error opening datalog.csv");
    }
  }
  
  DDRB |= 0b11111100;
}

void loop() {
  if (millis() - lastLogTime >= logInterval) {
    // Time to log data
    lastLogTime = millis();

    // Read accelerometer data
    sensors_event_t event;
    lis.getEvent(&event);

    // Read distance data from serial port
    int distance = readDistance();

    // Get current timestamp
    DateTime timestamp = rtc.now();

    // Create a struct to hold the sensor data
    SensorData sensorData;
    sensorData.timestamp = timestamp;
    sensorData.accelerationX = event.acceleration.x;
    sensorData.accelerationY = event.acceleration.y;
    sensorData.accelerationZ = event.acceleration.z;
    sensorData.distance = distance;
    sensorData.angle = angle;

    // Write sensor data to SD card
    writeDataToSD(sensorData);
  }
}

int readDistance() {
  int distance = 0;
  while (Serial.available() <= 0); // Wait until data is available
  char serialCharacter = Serial.read();
  if (serialCharacter == 'R') {
    for (int i = 0; i < 3; i++) {
      while (Serial.available() <= 0); // Wait until data is available
      char digit = Serial.read();
      distance = distance * 10 + (digit - '0');
    }
  }
  return distance;
}

//float angle = map(atan2(event.acceleration.y, event.acceleration.z) * 180.0 / PI, -90, 90, 0, 180);

void writeDataToSD(SensorData data) {
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(data.timestamp.timestamp()); // Timestamp
    dataFile.print(",");
    dataFile.print(data.accelerationX); // X acceleration
    dataFile.print(",");
    dataFile.print(data.accelerationY); // Y acceleration
    dataFile.print(",");
    dataFile.print(data.accelerationZ); // Z acceleration
    dataFile.print(",");
    dataFile.print(data.distance); // Distance
    dataFile.print(",");
    dataFile.print(data.angle); // Angle
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("Error writing to datalog.csv");
  }
}
