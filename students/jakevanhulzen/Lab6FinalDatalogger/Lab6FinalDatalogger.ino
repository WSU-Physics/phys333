#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 rtc;
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor to open
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (!lis.begin(0x18)) {
    Serial.println("Could not start LIS3DH");
    while (1);
  }
  Serial.println("LIS3DH found!");

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");

  Serial.print("Data rate set to: ");
  switch (lis.getDataRate()) {
    case LIS3DH_DATARATE_1_HZ: Serial.println("1 Hz"); break;
    case LIS3DH_DATARATE_10_HZ: Serial.println("10 Hz"); break;
    case LIS3DH_DATARATE_25_HZ: Serial.println("25 Hz"); break;
    case LIS3DH_DATARATE_50_HZ: Serial.println("50 Hz"); break;
    case LIS3DH_DATARATE_100_HZ: Serial.println("100 Hz"); break;
    case LIS3DH_DATARATE_200_HZ: Serial.println("200 Hz"); break;
    case LIS3DH_DATARATE_400_HZ: Serial.println("400 Hz"); break;
    case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break;
  }
}

void loop() {
  // Flush out any waiting data
  while(Serial.available()){
    Serial.read();
  }

  // Wait for sensor to be ready
  while(Serial.read() != 82) { // ASCII value of 'R'
    delayMicroseconds(1);
  }

  // Read distance sensor data
  char dist[4]; // Four characters array
  int nbytes = Serial.readBytes(dist, 3);

  // Read timestamp
  DateTime now = rtc.now();
  String dataString = "";
  // Format timestamp
  dataString += String(now.year(), DEC);
  dataString += '/';
  dataString += String(now.month(), DEC);
  dataString += '/';
  dataString += String(now.day(), DEC);
  dataString += ",";
  dataString += String(now.hour(), DEC);
  dataString += ':';
  dataString += String(now.minute(), DEC);
  dataString += ':';
  dataString += String(now.second(), DEC);
  dataString += ",";

  // Read accelerometer data
  lis.read();
  sensors_event_t event;
  lis.getEvent(&event);

  // Format accelerometer data
  dataString += String(event.acceleration.x);
  dataString += ",";
  dataString += String(event.acceleration.y);
  dataString += ",";
  dataString += String(event.acceleration.z);

  // Add distance sensor data to dataString
  dataString += ",";
  dataString += String(dist); // Assuming dist is the distance sensor reading

  // Write to SD card
  File dataFile = SD.open("Lab6.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  } else {
    Serial.println("error opening Lab6.csv");
  }

  // Print data to Serial monitor
  Serial.println(dataString);

  delay(200); // Adjust delay as needed
}
