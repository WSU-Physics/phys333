#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "RTClib.h"

// Adafruit LIS3DH setup
#define LIS3DH_CS 10
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// RTC setup
RTC_DS1307 rtc;

// SD card setup
const int chipSelect = 10; // Chip select pin for the SD card, adjust as needed

// Timing control
unsigned long lastSwitchTime = 0;
const long switchInterval = 5000; // 5 seconds for each functionality

// State variable to toggle between serial and accelerometer
bool toggleState = false;

void setup(void) {
  Serial.begin(9600);
  // Wait for serial port to open
  while (!Serial) delay(10);

  // Initialize LIS3DH
  if (!lis.begin(0x18)) {   // Change this to 0x19 for an alternative I2C address
    Serial.println("Couldn't start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1) yield();
  }
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set the RTC to the current date and time
  }
  
  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  // Create a file to log data
  String dataLog = "datalog.csv";
  if (!SD.exists(dataLog.c_str())) {
    File dataFile = SD.open(dataLog.c_str(), FILE_WRITE);
    if (dataFile) {
      // Write CSV header
      dataFile.println("Timestamp,X,Y,Z");
      dataFile.close();
    } else {
      Serial.println("Error opening datalog.csv");
    }
  }
  
  // Setup for direct manipulation (as per the first sketch)
  DDRB |= 0b11111100; // Set PB2-PB7 as outputs
}

void loop() {
  // Check if it's time to switch
  unsigned long currentMillis = millis();
  if (currentMillis - lastSwitchTime >= switchInterval) {
    // Save the last switch time
    lastSwitchTime = currentMillis;
    // Toggle the state
    toggleState = !toggleState;
  }

  if (toggleState) {
    // Functionality of the first sketch: Serial communication
    if (Serial.available() > 0) {
      char serialCharacter = Serial.read();
      PORTD = serialCharacter << 2;
      PORTB = serialCharacter >> 6;

      if (serialCharacter == 'R') {
        Serial.println("Inch");
      }
      Serial.write(serialCharacter);
      
    }
  } else {
    // Read from accelerometer and RTC
    sensors_event_t event;
    lis.getEvent(&event);

    DateTime now = rtc.now(); // Get the current time
    
    // Log data to SD card
    File dataFile = SD.open("datalog.csv", FILE_WRITE);
    if (dataFile) {

      dataFile.print(event.acceleration.x); // X acceleration
      dataFile.print(",");
      dataFile.print(event.acceleration.y); // Y acceleration
      dataFile.print(",");
      dataFile.print(event.acceleration.z); // Z acceleration
      dataFile.println();
      dataFile.close();
    } else {
      Serial.println("Error writing to datalog.csv");
    }

    Serial.print("Logged Data: ");
    Serial.print(event.acceleration.x); Serial.print(", ");
    Serial.print(event.acceleration.y); Serial.print(", ");
    Serial.print(event.acceleration.z); Serial.println();
    
    delay(500); // Delay for readability and to not overwhelm the SD card
  }
}