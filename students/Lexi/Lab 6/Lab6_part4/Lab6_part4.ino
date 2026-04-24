#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define LIS3DH_CS 9
#define SD_CS 10

#include <SoftwareSerial.h>
SoftwareSerial sensorSerial(2, 3); 

RTC_DS1307 RTC; 
Adafruit_LIS3DH lis = Adafruit_LIS3DH(); 
File logfile; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  sensorSerial.begin(9600); 
  sensorSerial.setTimeout(50); 

  Serial.print("Starting system "); 

  if (!SD.begin(SD_CS)) {
    Serial.println("SD Fail!!!! and you suck");
    while(1); 
  }

  if(!lis.begin(0x18)) {
    Serial.println("LIS3DH failed suck again");
    while(1); 
  }
  lis.setRange(LIS3DH_RANGE_4_G); 
  Serial.println(F("Scan start: distance, roll, pitch"));
   
}

void loop() {
  if(sensorSerial.available() > 0) {
    int distance = sensorSerial.parseInt(); 

    if(distance > 0) {
      logData(distance); 
    }
  } 
}

void logData(int dist) {
  sensors_event_t event; 
  lis.getEvent(&event); 

  float roll = atan2(event.acceleration.y, event.acceleration.z) * 180 / PI; 
  float pitch = atan2(-event.acceleration.x, sqrt(event.acceleration.y*event.acceleration.y+event.acceleration.z*event.acceleration.z)) * 180 / PI; 

  Serial.print(dist); Serial.print("cm, "); 
  Serial.print("Roll: "); Serial.print(roll); Serial.print(", "); 
  Serial.print("Pitch: "); Serial.println(pitch); 

  logfile = SD.open("Lab6.csv", FILE_WRITE); 
  if (logfile) {
    logfile.print(dist); logfile.print(","); 
    logfile.print(roll); logfile.print(","); 
    logfile.println(pitch); 
    logfile.close(); 
  }
}
