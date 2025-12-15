#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <SD.h>
#include <RTClib.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
RTC_DS1307 rtc;
File dataFile;

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for Serial to be ready

  if (!lis.begin(0x18)) { // begin the accelerometer
    Serial.println("Could not start LIS3DH");
    while (1);
  }

  if (!rtc.begin()) { // begin the RTC
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Uncomment this line if the RTC is not set
  }

  if (!SD.begin(10)) { // begin the SD card
    Serial.println("SD initialization failed!");
    while (1);
  }

  // Create or open 'data.csv' file and write the header
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Date,Time,Distance,Angle In Radians,X,Y");
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
    while (1);
  }
}

void loop() {
  lis.read(); // read the accelerometer
  sensors_event_t event;
  lis.getEvent(&event);

  // Calculate the angle in radians
  float angleRadians = atan2(event.acceleration.y, event.acceleration.z);

  // Wait for the distance sensor to send data
  while (Serial.available()) {
    Serial.read();
  }
  while (Serial.read() != 'R') {
    delayMicroseconds(1);
  }
  
  // Read the distance from the Serial
  char dist[4];
  int nbytes = Serial.readBytes(dist, 3);
  dist[nbytes] = 0; // Null terminate the string
  float distance = atof(dist);

  // Calculate the X and Y coordinates
  float x = distance * sin(angleRadians);
  float y = distance * cos(angleRadians);

  // Open the 'data.csv' file and write the data along with date and time
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    DateTime now = rtc.now(); // get the current date and time
    
    // Write the current date and time to the file
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(',');
    dataFile.print(now.hour(), DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.print(':');
    dataFile.print(now.second(), DEC);
    dataFile.print(',');
    
    // Write the rest of the data
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

  // Print the data to the Serial monitor as well
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.print(" | Angle: ");
  Serial.print(angleRadians);
  Serial.print(" Radians | X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);

  delay(100);
}
