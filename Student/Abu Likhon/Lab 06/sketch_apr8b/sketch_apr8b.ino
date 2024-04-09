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
    dataFile.println("Distance,Angle In Radians,X,Y");
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
    while (1);
  }
}

void loop() {
  float angle, angleRadians, x, y;
char serialCharacter;
  lis.read();
  sensors_event_t event;
  lis.getEvent(&event);

  // Calculate angle in degrees
  angle = atan2(event.acceleration.y, event.acceleration.z) * 180.0 / PI;
  
  // Convert angle from degrees to radians
  angleRadians = angle * PI / 180.0;

  // Check for incoming serial data
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

  // Calculate x and y values
  x = distance * sin(angleRadians);
  y = distance * cos(angleRadians);

  // Open file on SD card for writing
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(distance);
    dataFile.print(",");
    dataFile.print(angleRadians);
    dataFile.print(",");
    dataFile.print(x);
    dataFile.print(",");
    dataFile.println(y);
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
  }

  // Print values to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" Inch, Angle: ");
  Serial.print(angle);
  Serial.print(" Or ");
  Serial.print(angleRadians);
  Serial.print(" Radians, X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);

  delay(100);
}
