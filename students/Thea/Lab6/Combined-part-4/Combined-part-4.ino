/* Lab 6 combine all pieces for part 4*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

/* -------------Devices-------------- */
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
RTC_DS1307 rtc;
// SD card chip 
const int chipSelect = 10;
//distance
const int pin = 0;
char dist[4];

// CSV
const char *filename = "lab6-scan.csv";

/* ------ Set Up----------*/
void setup() {
  Serial.begin(115200);
  while(!Serial);

  // Accelerometer
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  // RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  // SD Card
   if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

  // CSV File
  File dataFile = SD.open(filename, FILE_WRITE);

      // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("year,month,day,hour,minute,second,distance_in,ax,ay,az,roll,pitch");
    dataFile.close();
  }
      // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
} 

/*-------- Loop ---------*/

void loop() {
  // RTC
  DateTime now = rtc.now();

  // Accelerometer
  lis.read();
  sensors_event_t event;
  lis.getEvent(&event);

  float Ax = event.acceleration.x;
  float Ay = event.acceleration.y;
  float Az = event.acceleration.z;

  float roll = atan2(Ay, Az) * 180 / PI;
  float pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180 / PI;

  // Distance
  while(Serial.available()){Serial.read();}
  while(Serial.read() !=82){
    delayMicroseconds(1000);

  }
  int nbytes = Serial.readBytes(dist,3);

/* ------- Write onto SD Card ---------*/
  File dataFile = SD.open(filename, FILE_WRITE);

  if (dataFile) {
    dataFile.print(now.year());   dataFile.print(",");
    dataFile.print(now.month());  dataFile.print(",");
    dataFile.print(now.day());    dataFile.print(",");
    dataFile.print(now.hour());   dataFile.print(",");
    dataFile.print(now.minute()); dataFile.print(",");
    dataFile.print(now.second()); dataFile.print(",");

    dataFile.print(dist);         dataFile.print(",");
    dataFile.print(Ax, 3);        dataFile.print(",");
    dataFile.print(Ay, 3);        dataFile.print(",");
    dataFile.print(Az, 3);        dataFile.print(",");
    dataFile.print(roll, 2);      dataFile.print(",");
    dataFile.println(pitch, 2);

    dataFile.close();
  }
  else{
    Serial.println("Error for CSV file");
  }

  delay(200);

}
