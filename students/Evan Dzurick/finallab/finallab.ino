#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <SD.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
File dataFile;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!lis.begin(0x18)) {
    Serial.println("Could not start LIS3DH");
    while (1);
  }

  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    while (1);
  }

  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Distance,Angle");
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
    while (1);
  }
}

void loop() {
  char serialCharacter;
  float angle;

  lis.read();
  sensors_event_t event;
  lis.getEvent(&event);



  angle = map(atan2(event.acceleration.y, event.acceleration.z) * 180.0 / PI, -90, 90, 0, 180);

  // Flush out any waiting data
  while (Serial.available()) {
    Serial.read();
  }
  while (Serial.read() != 'R') {
    // Wait for distance sensor to be ready
    delayMicroseconds(1);
  }
  char dist[4];
  int nbytes = Serial.readBytes(dist, 3);

  float distance = atof(dist);

  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(distance);
    dataFile.print(",");
    dataFile.println(angle);
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
  }

  Serial.println(distance);
  Serial.println(angle);

  delay(100);
}