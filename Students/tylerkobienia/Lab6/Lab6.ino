#include <Wire.h> // wire library for I2C communication
#include <SPI.h> // SPI library imported
#include <Adafruit_LIS3DH.h> // LIS3DH library imported
#include <Adafruit_Sensor.h> // Distance Sensor library imported
#include <SD.h> // SD card read in library 
#include "RTClib.h" // real time clock imported
 
RTC_DS1307 rtc; // start RTC object
Adafruit_LIS3DH lis = Adafruit_LIS3DH(); // start LIS3DH accelerometer object
const int chipSelect = 10; // defines chip select pin for SD card module
 
void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for Serial Monitor to open
 
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) { // check if SD card initialization fails
    Serial.println("Card failed, or not present"); 
    while (1); // infinite loop if SD card initialization fails
  }
  Serial.println("card initialized.");
 
  if (!rtc.begin()) { // check if RTC initialization fails
    Serial.println("Couldn't find RTC");
    while (1); // infinite loop if RTC initialization fails
  }
 
  if (!rtc.isrunning()) { // check if RTC is running
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // set RTC time to compilation time
  }
 
  if (!lis.begin(0x18)) { / check if LIS3DH accelerometer initialization fails
    Serial.println("Could not start LIS3DH");
    while (1); // infinite loop if LIS3DH initialization fails

  }
  Serial.println("LIS3DH found!");
 
  Serial.print("Range = "); Serial.print(2 << lis.getRange()); // print accelerometer range
  Serial.println("G");
 
  Serial.print("Data rate set to: "); //print accelerometer data
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
  File dataFile = SD.open("LAB6.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  } else {
    Serial.println("error opening datalog.csv");
  }
 
  // Print data to Serial monitor
  Serial.println(dataString);
 
  delay(200); // Adjust delay as needed
}
