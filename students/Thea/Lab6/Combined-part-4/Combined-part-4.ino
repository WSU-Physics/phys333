/* Lab 6 combine all pieces for part 4*/

/*-------Preamble------*/

/*----Distance Sensor---*/
const int pin = 0;
char dist[4];

/*---Accelerometer---*/
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

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

/*---Date and Time---*/
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/*---Data Logger---*/
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

/*-------Set Up----------*/

void setup() {

/*---Distance Sensor---*/
  pinMode(pin, INPUT);
  Serial.begin(9600);       //baud rate

/*---Accelerometer---*/  
  //Serial.begin(115200);

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

/*---Date and Time---*/
  //Serial.begin(57600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }


/*---Data Logger---*/

  pinMode(10, OUTPUT);

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

#define DEBUG 0 //enable or disable printing 

/*-------- Loop ---------*/

void loop() {

/*---Distance Sensor---*/

//chatgpt

int nbytes = 0;
dist[3] = '\0';
int distance = -1;

unsigned long startTime = millis();
bool gotR = false;

// wait for 'R'
while (millis() - startTime < 500) {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'R') {
      gotR = true;
      break;
    }
  }
}

if (gotR) {
  nbytes = Serial.readBytes(dist, 3);
  dist[3] = '\0';

  if (nbytes == 3) {
    distance = atoi(dist);
  }
}

/*---Accelerometer---*/
  sensors_event_t event;
  lis.getEvent(&event);

  float Ax = event.acceleration.x;
  float Ay = event.acceleration.y;
  float Az = event.acceleration.z;

  float roll = atan2(Ay, Az) * 180 / PI;
  float pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180 / PI;

/*---Date and Time---*/
    DateTime now = rtc.now();

/*---Data Logger---*/

  File dataFile = SD.open("lab6scan.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(now.year()); dataFile.print(",");
    dataFile.print(now.month()); dataFile.print(",");    
    dataFile.print(now.day()); dataFile.print(",");
    dataFile.print(now.hour()); dataFile.print(",");
    dataFile.print(now.minute()); dataFile.print(",");
    dataFile.print(now.second()); dataFile.print(",");
    dataFile.print(distance); dataFile.print(",");
    dataFile.print(roll, 2); dataFile.print(",");
    dataFile.println(pitch, 2); 
    dataFile.close();

  }

  delay(200);
}
