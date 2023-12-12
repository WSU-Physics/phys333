// libraries used for the Lab
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <SD.h>
#include "RTClib.h"



const int chipSelect = 10;
char dis[4];
LSM9DS1 imu;
RTC_DS1307 rtc;
int bytes;
// creates a file name of up to 40 bytes of name storage
char filename[40];


void setup() {
  // put your setup code here, to run once:
  //inital baud rate
  Serial.begin(9600);
  // used for distance sensor
  pinMode(0, INPUT);
  
//defined if statement
//checks that this given value is a unique value/ header
//prevent double declaration of variables
  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
//checks that rtc is running and will through the following serial error if its not
// if its not then it will set a date and time
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }

// sets the imu device to I2C mode so that is can
// can be used as an i2c device
  imu.settings.device.commInterface = IMU_MODE_I2C;


  //intitates the accelerometer
  //finds it's values 
    if (!imu.begin()) {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1);
  }
  
//initalizes the SD card and checks that it is present
//if its not then it throws a error in the serial window
   Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // does nothing and returns
    return;
  }
  Serial.println("card created.");

    DateTime now = rtc.now();
// names the file based on its current date and time that it
// was intitalized
  sprintf(filename, "%d%d%d%d.csv",
          now.month(), now.day(), now.hour(), now.minute());
  Serial.print("new filename is:");
  Serial.println(filename);


  
  // add one second delay to give myself time to plug pin 0 wire back in
  delay(1000);

}
bool WaitForWire(){
  /*
   * if wire is detect return True
   * else:
   * return false;
   */
  if(digitalRead(0)== HIGH){
    return true;
    
  }
  else {
    return false;
  }
}

void loop() {
  DateTime now;

  now = rtc.now();

  //char sensor = Serial.read();
  // data for measuring distance
  // will only run when it detects and wire and 
  // is communcating back
  if(WaitForWire()){
    while(Serial.available()){
      Serial.read();
      
    }
    while(Serial.read() != 82){
      delayMicroseconds(1);
    }
    bytes = Serial.readBytes(dis,3);
    Serial.println(dis);
  }
//reads accel data
  if ( imu.accelAvailable() ){
    imu.readAccel();
  }

  delay(1000);
/*
 *code: 
 *Description:
 *sync the the time measurements of the distance and accelormeter together
 *if they have the same time put them together to properly measure the room.
 *measure using seconds they need to have the same time 
 *store their data to SD card.
 *
 *maybe label walls if can be detect or measure based on:
 *center position: 
 *if to the left and to the right.
 *
 *keep track of previously measured values regardless of seconds.
 *and compare the new values
 *
 *
 *
 *
 *get current time rtc.now()
 *place data from both sensors in a excel sheet that has their measurements under the same time;
 *take a new measure every half second
 *
 */

   File dataFile = SD.open(filename, FILE_WRITE);
  // converts the char value of the distance to a floating value
   float distance = atof(dis);
   // will use these values to calulate out and angle magnitude value.
   float x = imu.calcAccel(imu.ax);
   float y = imu.calcAccel(imu.ay);
   float z = imu.calcAccel(imu.az);
   
   unsigned long ltime = millis();
// calculates the angle of the value
   float angle = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
   
  Serial.println(" Millis, distance, angle");
 // Serial.println(rtc.now);
  Serial.println(ltime);
  Serial.println(dis);
  Serial.println(angle);
   Serial.println(distance);
   

    if (dataFile) {
    dataFile.print("time(ms),");
    dataFile.print(ltime);
    dataFile.print(",Distance:, "); dataFile.print(distance, 2);
    dataFile.print(" ,Angle:, "); dataFile.print(angle, 2);
    dataFile.println(",");
    dataFile.close();
  }
 
  else {
    Serial.print("file could not be openned ");
    Serial.println(filename);
  }
  
  // put your main code here, to run repeatedly:

}
