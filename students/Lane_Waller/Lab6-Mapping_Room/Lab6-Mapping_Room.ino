//////////includes for accelerometer///////////////
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//////////////Includes for SD card datalogger//////////////
#include <SD.h>
const int chipSelect = 10;

//////////////Includes for RTC/////////////////////////
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);     //initiate the serial monitor with the proper baud 

      ///////////////Setup for RTC//////////////////////

      #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));


      ///////////////Setup for Accelerometer////////////

     while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  // lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");

  // lis.setPerformanceMode(LIS3DH_MODE_LOW_POWER);
  Serial.print("Performance mode set to: ");
  switch (lis.getPerformanceMode()) {
    case LIS3DH_MODE_NORMAL: Serial.println("Normal 10bit"); break;
    case LIS3DH_MODE_LOW_POWER: Serial.println("Low Power 8bit"); break;
    case LIS3DH_MODE_HIGH_RESOLUTION: Serial.println("High Resolution 12bit"); break;
  }

  // lis.setDataRate(LIS3DH_DATARATE_50_HZ);
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
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("1.6 Khz Low Power"); break;
  }

  ////Setup for Datalogger////

  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  // put your main code here, to run repeatedly:

  //////////////RTC Code Here///////////////
   DateTime now = rtc.now();
    String time = "";
    time += (now.year());
    time += "/";
    time += (now.month());
    time += "/";
    time += (now.day());
    time += " ";
    time += (now.hour());
    time += ":";
    time += (now.minute());
    time += ":";
    time += (now.second());

  Serial.println(time);
  ///////////Accelerometer Code for Angle///////////////
  lis.read();      // get X Y and Z data at once

  /*get a new sensor event, normalized*/
  sensors_event_t event;
  lis.getEvent(&event);
                            //angle formula = arctan(sqrt(x^2+y^2)/z)  - I'm just squaring x and y by multiplying by itself
  double angleFromVert_rad = atan(sqrt((event.acceleration.x)*(event.acceleration.x)+(event.acceleration.y)*(event.acceleration.y))/event.acceleration.z); 
  double angleFromVertical = angleFromVert_rad*(180/3.141592653);   //Convert radians into degrees

  Serial.println(angleFromVertical);
  Serial.println();


  //////////////Distance Sensor Code//////////////
 char distance[4];

  while (Serial.available()){
    Serial.read();
  }
  while (Serial.read() != 82){
    //Wait for distance sensor to be ready
    delayMicroseconds(1);
  }
  int distanceBytes = Serial.readBytes(distance, 3);
  distance[3] = '\0'; //terminate character string
  Serial.println(distance);


  /////////////Data Logger Code/////////////////
   // make a string for assembling the data to log:
  String dataString = "";
  dataString += String(angleFromVertical);
  dataString += ",";
  dataString += String(distance);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(250); //every quarter second repeat the main loop 
}

