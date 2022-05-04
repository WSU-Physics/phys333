// library include
#include "RTClib.h"     //real time clock
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SparkFunLSM9DS1.h>

RTC_DS1307 rtc;
LSM9DS1 imu;

//-------------------imu defines,finction and variables--------------------------------------------

#define PRINT_CALCULATED
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

void printAttitude(float ax, float ay, float az, float mx, float my, float mz);

//---------------------------end of imu------------------------------------------------------------------

//----------------------Matibox distance variables---------------------------------------------
const int pwPin1 = 3;
long pulse1, sensor1;
//------------------------end of matibox-----------------------------------------------------------

//-----------------sd card, datalogger variables-----------------------------------------------------
const int chipSelect = 10;
File myFile;    //begin SD
//const char* filename = "mapping.csv"
//---------------------RTC variables-----------------------------------------------------------
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//---------------------------end of RTC variables-------------------------------------------------------




void setup() {
  //--------------------------------int SD card----------------------------------------------------------------
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  File dataFile = SD.open("mapping.txt", FILE_WRITE); //--------------create file --------------
  if (dataFile) {
    Serial.println("--aqua_data-- File created");
    dataFile.println(" Date, Time, Distance, Pitch");
    dataFile.close();
  }


  //---------------------------------end of SD card int----------------------------------------------------

  //------------------------------------int RTC------------------------------------------------------------------
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
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //----------------------------end of RTC int---------------------------------------------------------------------
  //----------------------------int IMU--------------------------------------------
  Wire.begin();

  if (imu.begin() == false) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are.");
    while (1);
  }
  //------------------------------end of IMU int-------------------------


  pinMode(pwPin1, INPUT); //---------Matibox int---------------
  //------------------------SD int-----------------------------


}//--------------------------------SETUP END---------------------------------------

//---------------------functions for matibox--------------------
void read_sensor() {
  String dataString;

  pulse1 = pulseIn(pwPin1, HIGH);
  sensor1 = pulse1 / 147;
  dataString += (sensor1 );

}
void printall() {
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(sensor1);
  Serial.print(" ");
  Serial.print("inches ");
  Serial.println(" ");
}
//--------------------------end----------------------
//----------------------functions for IMU-------------------------
void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
{

  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));

  float heading;
  if (my == 0)
    heading = (mx < 0) ? PI : 0;
  else
    heading = atan2(mx, my);

  heading -= DECLINATION * PI / 180;

  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);

  // Convert everything from radians to degrees:
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;

  String dataString += String(String(pitch + ","));  // add pitch to datafile

  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); Serial.println(heading, 2);
}
//--------------------------------end imu functions------------------------


void loop() {   //================LOOP begins=======================
  // get time
  DateTime now = rtc.now();
  String dataString;

  String date = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " ";
  String time = String(String(now.hour()) + ":" +  String(now.minute()) + ":" + String(now.second()) + " ");
  dataString += String((date + ","));
  dataString += String((time + ","));

  // ---------------matibox distance sensor read-----------
  read_sensor();
  printall();
  delay(500);

  //-----------------get IMU pitch and roll, heading-------------------
  if ( imu.gyroAvailable() )
  {

    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {

    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {

    imu.readMag();
  }

  if ((lastPrint + PRINT_SPEED) < millis())
  {


    printAttitude(imu.ax, imu.ay, imu.az,
                  -imu.my, -imu.mx, imu.mz);
    Serial.println();

    lastPrint = millis(); // Update lastPrint time
  }

  //-----------------------------SD card log---------------------------
  // String header = " Date, Time , Pitch, Distance";
  File dataFile = SD.open("mapping.txt", FILE_WRITE); //--------------create file --------------

  if (dataFile) {
    dataFile.println(dataString);
    Serial.print("printing on SD");
  } else {
    Serial.print("Failed to write to SD");

  }
  dataFile.close();



}
