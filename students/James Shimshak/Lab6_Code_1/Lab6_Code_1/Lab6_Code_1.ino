#include <SPI.h>
#include <SD.h>

/* Sensor test sketch
  for more information see http://www.ladyada.net/make/logshield/lighttemp.html
  */

#define aref_voltage 5         // we tie 3.3V to ARef and measure it with a multimeter!



//TMP36 Pin Variables
int DistPin = 1;        //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
int DistReading;        // the analog reading from the sensor
    
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   

  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);
}


void loop(void) {

  
  DistReading = analogRead(DistPin);  
  
  Serial.print("Dist reading = ");
  Serial.println(DistReading);     // the raw analog reading
  
  // converting that reading to voltage, which is based off the reference voltage
 

 

 
  delay(100);
}