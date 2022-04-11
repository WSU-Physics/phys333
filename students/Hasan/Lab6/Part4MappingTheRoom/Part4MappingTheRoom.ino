/*
 * Mapping the room 
 * 
 * This script is used to map a room with an ultrasonic sensor and accelerometer
 * 
 * The circcuit is constructed as follows: 
 * 
 * LMS9DS1
 * - GND - Ground
 * - VDD - 3.3 V
 * - SDA - A4
 * - SCL - A5 
 * 
 * LV-EZ1 Ultrasonic distance sensor 
 * - GND(Top right pin) - Ground
 * - 5V - 5 V power line 
 * - TX - bias input of npn transistor before 1000 ohm resistor 
 * 
 * NPN transistor 
 * - top pin - 5 V
 * - middle pin - attached to TX of EZ1 Sensor with 1000 ohm resistor 
 * - bottom bin - attached to ground 
 * 
 * Green and yellow LED
 */

 //import necessary libraries
 #include <SPI.h> 
 #include <SD.h> 
 
 //LMS9DS1 libraries 
 #include <Wire.h> 
 #include <SparkFunLSM9DS1.h>

 //ds1307 for Datashield 
 #include "RTClib.h"

 /*
  * Create objects 
  */
  // Use the LSM9DS1 class to create an object. [imu] can be
  // named anything, we'll refer to that throught the sketch.
  LSM9DS1 imu;
  RTC_DS1307 rtc;
  

/*
 * Instantiating important variables 
 */
 int header = 0;
 // variable for ultrasonic sensor 
 char dist[4]; 
 int ultraSonicData = 0; 

 //Variable for RTC Clock 
 char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

 //SD Card: chip select for arduino is different for datashield 
 const int chipSelect = 10; 

  //Variables for LMS9DS1
  #define PRINT_CALCULATED
  //#define PRINT_RAW
  #define PRINT_SPEED 250 // 250 ms between prints
  static unsigned long lastPrint = 0; // Keep track of print time
  
  // Earth's magnetic field varies by location. Add or subtract
  // a declination to get a more accurate heading. Calculate
  // your's here:
  // http://www.ngdc.noaa.gov/geomag-web/#declination
  #define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

void setup() {
  // put your setup code here, to run once:

  /*
   * Initializing the SD Card 
   */
  Serial.begin(9600); 
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB Port only 
  }

  Serial.print("Initializing SD Card for mapping..."); 

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
    DateTime now = rtc.now();
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
   * Read incoming bytes from the LV-EZ1 UltraSonic Distance Sensor 
   */

   while(Serial.available()){Serial.read();} 
    while(Serial.read() != 82){
      delayMicroseconds(1); 
    }
    int nbytes = Serial.readBytes(dist, 3); 
    
   
  /*
   * End of Read incoming bytes from the LV-EZ1 UltraSonic Distance Sensor 
   */

   /*
    * Begin calculating data for pitch measurement 
    * 
    */
    // put your main code here, to run repeatedly:
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
  

  if ((lastPrint + PRINT_SPEED) < millis())
  {
    printAccel();  // Print"A: ax, ay, az"
    printMag();   // Print "M: mx, my, mz"

    // Print the heading and orientation for fun!
    // Call print attitude. The LSM9DS1's mag x and y 
    // axes are opposite to the accelerometer, so my, mx are 
    // substituted for each other 

    printAttitude(imu.ax, imu.ay, imu.az,
                  -imu.my, -imu.mx, imu.mz);
    Serial.println(); 

    lastPrint = millis(); // Update lastPrint time
  } 
    /*
     * End calculating data for pitch measurement 
     */
   

  
  /*
   * SD Card should begin taking data from sensor on top 
   */

  String columnHeader = "# Date, Time,  Distance, Pitch";
  
  String dataString = ""; 

  // read the timestamp, ultrasonic and the LMS9DS1 sensor to string

  String date = String(now.day()) + "/" + String(now.month())+ "/" + String(now.year())+ " "; 
  dataString += (date + ","); 
  
  //dataString += String("year: " + String(now.year()) + " " ); 

  //dataString += String("month: " +String(now.month())+ " " ); 

  //dataString += String("day: " +String(now.day())+ " " );  

  String time = String(String(now.hour()) + ":" +  String(now.minute()) + ":" + String(now.second()) + " ");
  dataString += (time + ","); 
  //dataString += String("hour: " + String(now.hour())+ " " ); 

  //dataString += String("minute: " + String(now.minute())+ " " ); 

  //dataString += String ("second: " + String(now.second()) + " "); 

  //dataString += String("Distance"); 

  dataString += String(String(dist) + ", "); 

  //dataString += String("Pitch "); 
  
  float pitch = atan2(-1.0*float(imu.ax), sqrt(float(imu.ay) * float(imu.ay) + float(imu.az) * float(imu.az)));
  dataString +=  String(pitch *= 180.0/PI); 

  //dataString += "\n"; 

  //open file. Only one can be open at a time 

  File datafile = SD.open("datalog.txt", FILE_WRITE); 

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
    Serial.println("error opening datalog.txt"); 
  }

  /*
   * SD Card should begin taking data from sensor on top 
   */

}

/*
 * Below are helper functions used to calculate the pitch with the LMS9DS1
 */

   void printAccel()
{
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
  //Serial.print("A: ");
  #ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
  /*
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
  */
  #elif defined PRINT_RAW
  /*
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
  */
  #endif

}

void printMag()
{
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
  //Serial.print("M: ");
 #ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcMag helper function to convert a raw ADC value to
  // Gauss. Give the function the value that you want to convert.
  /*
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
  */
 #elif defined PRINT_RAW
 /*
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
  */
 #endif
}



// Calculate pitch, roll, and heading.
// Pitch/roll calculations take from this app note:
// http://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf?fpsp=1
// Heading calculations taken from this app note:
// http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/Magnetic__Literature_Application_notes-documents/AN203_Compass_Heading_Using_Magnetometers.pdf
void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
{
  float level = 0.0; 
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


// if flat on table, turn green on,turn yellow off 
   if(pitch >= (level - 1.0) && pitch <= (level + 1.0)){
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);  
  }
// if slightly off kilter, turn on yellow turn off green
  else if(pitch >= (level - 5.0) && pitch <= (level+5.0)){
    digitalWrite(8, HIGH); 
    digitalWrite(9, LOW); 
  }

// if outside range, turn off both LED's. 
  else{
    digitalWrite(8, LOW); 
    digitalWrite(9, LOW); 
  }
  }
