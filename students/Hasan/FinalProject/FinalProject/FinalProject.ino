

/*
 * Final Project: Snake Sensor 
 * 
 * 
 * Uses the accelerometer 
 * 
 * The circcuit is constructed as follows: 
 * 
 * LMS9DS1
 * - GND - Ground
 * - VDD - 3.3 V
 * - SDA - A4
 * - SCL - A5 
 * 

 */

/************************************************
 * Important variable choice here, 
 * 
 * 1 chooses the continuous data collection 
 * 
 * 2 chooses the data collection only when pitch is out of bounds 
 *************************************************/

 //import necessary libraries
 #include <SPI.h> 
 #include <SD.h> 
 
 //LMS9DS1 libraries 
 #include <Wire.h> 
 #include <SparkFunLSM9DS1.h>

 //ds1307 for Datashield 
#include <RTClib.h>

 /*
  * Create objects 
  */
  // Use the LSM9DS1 class to create an object. [imu] can be
  // named anything, we'll refer to that throught the sketch.
  LSM9DS1 imu;
  RTC_DS1307 rtc;
  
  
  int header = 0; 
  int dataOut = 1; 

 //Variable for RTC Clock 
 char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  
  // Earth's magnetic field varies by location. Add or subtract
  // a declination to get a more accurate heading. Calculate
  // your's here:
  // http://www.ngdc.noaa.gov/geomag-web/#declination
  #define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

void setup() {
  // put your setup code here, to run once:
  //SD Card: chip select for arduino is different for datashield 
 const int chipSelect = 10; 
 
  /*
   * Initializing the SD Card 
   */
  Serial.begin(9600); 
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB Port only 
  }
  Serial.print("Initializing SD Card..."); 

  //see if the card is present and can be initialized: 
  if (!SD.begin(chipSelect)){
    Serial.println("Card failed, or not present"); 
    // don't do anything more:
    while(1); 
  }

  Serial.println("card initialized."); 

   /*
   * End of Initializing the SD Card 
   */

  /*
   * Setup of the RTC real time clock 
   */
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
  
    // When time needs to be re-set on a previously configured device, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    
    /*
   * End of Setup of the RTC real time clock 
   */
   
   /*
    * Beginning of the Part 2 Level Reading Setup 
    */

    pinMode(8, OUTPUT); 
    pinMode(9, OUTPUT); 

    Wire.begin(); 

    if (imu.begin() == false) 
    {
      Serial.println("Failed to communicate with the LSM9DS1."); 
      Serial.println("Double-check wiring."); 
      Serial.println("Default settings will work"); 

      while(1); 
    }

    /*
    * End of the Part 2 Level Reading Setup using LMS9DS1
    */

    /*
     * Setup for the UltraSonic Distance Sensor 
     */

     Serial.println("LV-EZ1 Distance sensor ready"); 

      /*
     * Setup for the UltraSonic Distance Sensor 
     */

}

void loop() {
  
  // put your main code here, to run repeatedly:

  /*
   * Read data from Real time clock 
   */
    DateTime now1 = rtc.now(); 
    /*
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


    Serial.println();
    delay(3000);
    */
   /*
    * End of read data from RTC
    */


   /*
    * Begin calculating data for pitch measurement 
    * 
    */
    // put your main code here, to run repeatedly:

  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
  {
    // To read from the gyroscope,  first call the
    // readGyro() function. When it exits, it'll update the
    // gx, gy, and gz variables with the most current data.
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    // To read from the accelerometer, first call the
    // readAccel() function. When it exits, it'll update the
    // ax, ay, and az variables with the most current data.
    imu.readAccel();
  }

  if ( imu.magAvailable() )
  {
    // To read from the magnetometer, first call the
    // readMag() function. When it exits, it'll update the
    // mx, my, and mz variables with the most current data.
    imu.readMag();
  }
  

  
  /*
   * SD Card should begin taking data from sensor on top 
   */

  String columnHeader = "# Date, Time (ms), gx, gy, gz, Ax, Ay, Az,  Pitch";
  
  String dataString = ""; 

  // read the timestamp, ultrasonic and the LMS9DS1 sensor to string

  String date = String(now1.day()) + "/" + String(now1.month())+ "/" + String(now1.year())+ " "; 
  dataString += (date + ","); 
  

  String time = String(millis());
  dataString += (time + ","); 


  float Gx = imu.calcGyro(imu.gx);

  dataString += (String(float(Gx)) + ","); 
  
  float Gy = imu.calcGyro(imu.gy);

  dataString += (String(Gy) + ","); 
  
  float Gz = imu.calcGyro(imu.gz); 

  dataString += (String(Gz) + ","); 

 

  float Ax = imu.calcAccel(imu.ax);

  dataString += (String(Ax) + ","); 

  float Ay = imu.calcAccel(imu.ay); 

  dataString += (String(Ay) + ","); 

  float Az = imu.calcAccel(imu.az); 

  dataString += (String(Az) + ","); 

  
  
  float pitch = atan2(-1.0*float(imu.ax), sqrt(float(imu.ay) * float(imu.ay) + float(imu.az) * float(imu.az)));
  dataString +=  String(pitch *= 180.0/PI); 


  
  //dataString += "\n"; 

  //open file. Only one can be open at a time 

  File datafile = SD.open("snek2.csv", FILE_WRITE); 

  // if the file is available, write to it
   
  if (datafile) {
     

    if(header == 0){
      datafile.println(columnHeader); 
      delay(10); 
      datafile.close(); 
      Serial.println(columnHeader);
      header = 1; 
    }
    
    else{
    datafile.println(dataString); 
    delay(10); 
    datafile.close(); 
    //print to the Serial port
    Serial.println(dataString); 
    
    }
  }
  // if the file isn't open, pop up an error: 
  else {
    Serial.println("error opening snek.csv"); 
  }

  /*
   * SD Card should begin taking data from sensor on top 
   */
  
}
