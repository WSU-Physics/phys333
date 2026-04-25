#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "RTClib.h"

const int chipSelect = 10;

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

char dist[4];  //

// LIS3DH Setup (I2C)
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup() {
  Serial.begin(9600);

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");


  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop() {

  Serial.println("Loop running");
  delay(1000);
  // to check if the loop is working

  while (Serial.available()) {Serial.read();}

  //while (Serial.read() != 'R') {
  //  delayMicroseconds(1);
  //}

  while (Serial.read() != 82){
  delayMicroseconds(1);
  }
  if(Serial.available() >= 3){
  int nbytes = Serial.readBytes(dist, 3);
  dist[3] = '\0'; 
  }

  lis.read();     
  sensors_event_t event;
  lis.getEvent(&event);

  // --- Print Data ---
  Serial.print("Acc: ");
  Serial.print(event.acceleration.x); Serial.print(" ");
  Serial.print(event.acceleration.y); Serial.print(" ");
  Serial.print(event.acceleration.z); Serial.print(" m/s^2 ");

  Serial.print("Distance: ");
  Serial.println(dist);
  
  delay(100); // Small delay for stability

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

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

}