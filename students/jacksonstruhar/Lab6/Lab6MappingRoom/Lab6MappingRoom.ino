#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "RTClib.h"
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
RTC_DS1307 rtc;

const int chipSelect = 10;
const int pinRX = 0;
char dist[4];
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  pinMode(pinRX, INPUT);
  Serial.begin(9600);

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   //i2c address
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

void loop() 
{
  while(Serial.available()){Serial.read();}
  while(Serial.read() != 82)
  {
    delayMicroseconds(1);
  }
  int nbytes = Serial.readBytes(dist, 3);

  sensors_event_t event;
  lis.getEvent(&event);

  float ax = event.acceleration.x; //xyz values
  float ay = event.acceleration.y;
  float az = event.acceleration.z;

  float tilt = atan(sqrt(ax*ax + ay*ay) / az) * 180.0 / PI; //tangent theta equation for 3D space

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
    
    Serial.print("Distance: ");
    Serial.println(dist);

    Serial.print("Angle of Tilt: ");
    Serial.println(tilt);
    Serial.println();
    
    delay(1000);


  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(dist);
    dataFile.print("\t");
    dataFile.println(tilt);    
    dataFile.close();

    // print to the serial port too:
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
