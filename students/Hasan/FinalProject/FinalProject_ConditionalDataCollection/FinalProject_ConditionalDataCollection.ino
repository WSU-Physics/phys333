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

  //data array 
  String myStrings[2][9]; 
  
   //Variable for RTC Clock 
 char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

 #define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

void setup() {
  // put your setup code here, to run once:
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



}

void loop() {
  // put your main code here, to run repeatedly:

     Serial.println("Entering program 2"); 
     DateTime now2 = rtc.now();

     //define column header for csv 
     String columnHeader = "# Date, Time, gx, gy, gz, Ax, Ay, Az,  Pitch";


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

  
        // for all rows in csv, copy contents of imu method calls 
        for(int i = 0; i < 3; i++){
     
          String date = String(now2.day()) + "/" + String(now2.month())+ "/" + String(now2.year())+ " ";  
          
        
          String time_2 = String(String(now2.hour()) + ":" +  String(now2.minute()) + ":" + String(now2.second()) + " ");
          
          float Gx = imu.calcGyro(imu.gx); 
          
          float Gy = imu.calcGyro(imu.gy);
          
          float Gz = imu.calcGyro(imu.gz);   
        
          float Ax = imu.calcAccel(imu.ax); 
        
          float Ay = imu.calcAccel(imu.ay); 
        
          float Az = imu.calcAccel(imu.az); 

          float pitch = atan2(-1.0*float(imu.ax), sqrt(float(imu.ay) * float(imu.ay) + float(imu.az) * float(imu.az)));
          pitch =  (pitch*= 180.0/PI);
        

          //Serial.println(date); //+ "," + time_2 + "," + String(float(pitch))); 
        
          
          
          
          myStrings[i][0] = date;
          myStrings[i][1] = time_2; 
          myStrings[i][2] = String(float(Gx));
          myStrings[i][3] = String(float(Gy)); 
          myStrings[i][4] = String(float(Gz)); 
          myStrings[i][5] = String(float(Ax)); 
          myStrings[i][6] = String(float(Ay)); 
          myStrings[i][7] = String(float(Az)); 
          myStrings[i][8] = String(float(pitch));
      
          
          /*
          if(pitch <= -5 || pitch >= 5){
            break;
            dataOut = 0;   
          }
          */
        }

        
      
    

    //open file. Only one can be open at a time 
  
    File datafile2 = SD.open("snek2.csv", FILE_WRITE); 
  
    // if the file is available, write to it
     
    if (datafile2) {
       
      
      if(header == 0){
        datafile2.println(columnHeader); 
        delay(10); 
        datafile2.close(); 
        //Serial.println(columnHeader);
        header = 1; 
      }
      
      else{

  
  
        for(int i = 0; i < 3; i++){

          String dataString = ""; 

          dataString += (myStrings[i][0] + "," + myStrings[i][1] + "," + myStrings[i][2] + "," + myStrings[i][3]+ "," + myStrings[i][4]+ "," + myStrings[i][5]+ "," + myStrings[i][6]+ "," + myStrings[i][7]+ "," + myStrings[i][8]); 

          datafile2.println(dataString); 
          delay(10); 
           
          //print to the Serial port
          //Serial.println(dataString);
        }

        datafile2.close();
            
  
          
           
  
          Serial.println("Program ending.... Going to infinite while loop.... Rerun program to start over"); 
  
          //while(true);
            
          }
        } 
     // if the file isn't open, pop up an error: 
    else {
      Serial.println("error opening snek.csv"); 
      }

    
  }
