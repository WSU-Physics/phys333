#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>


// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;

///////////////////////////
// Sketch Output Settings//
///////////////////////////

#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. Calculate
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.


//Function definitions
void printAccel();
void printMag();
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT); 

  Wire.begin(); 

  if (imu.begin() == false) 

  {
    Serial.println("Filed to communicate with LSM9DS1."); 
    Serial.println("Double-check wiring."); 
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are."); 
    while(1); 
  }

}

void loop() {
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

   
}

  void printAccel()
{
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
  Serial.print("A: ");
  #ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
  #elif defined PRINT_RAW
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
  #endif

}

void printMag()
{
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
  Serial.print("M: ");
 #ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcMag helper function to convert a raw ADC value to
  // Gauss. Give the function the value that you want to convert.
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
 #elif defined PRINT_RAW
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
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

  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); Serial.println(heading, 2);

// if flat on table, turn green on,turn yellow off 
   if(pitch >= (level - 1.0) && pitch <= (level + 1.0)){
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);  
  }
// if slightly off kilter, turn on yellow turn off green
  else if(pitch >= (level - 5.0) && pitch <= (level+5.0)){
    digitalWrite(12, HIGH); 
    digitalWrite(13, LOW); 
  }

// if outside range, turn off both LED's. 
  else{
    digitalWrite(12, LOW); 
    digitalWrite(13, LOW); 
  }
  }
