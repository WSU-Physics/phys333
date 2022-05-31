/*
   This sketch uses an IR distance sensor to vary the brightness of a LED.
   Brightness increases as you get closer to an object as a warning.
*/

#include <SharpIR.h>                              //imports the IR library for the sketch

SharpIR sensor(SharpIR::GP2Y0A02YK0F, A0);        //assigns pin A0 (analog in) to the sensor (use the correct model #)
const int ledPin = 9;                             //assigns pin 9 as ledPin

void setup() {
  //Serial.begin(9600);                           //enables serial communication if needed, useful for troubleshooting
  pinMode(ledPin, OUTPUT);                        //assigns pin 9 as output
}

void loop() {
  int distance = sensor.getDistance();            //calculates the distance in cm
  int brightness = distance;                      //create a variable to use for the brightness of the LED
  brightness = map(brightness, 19, 151, 255, 0);  //maps brightness for analogWrite() using the min and max values of distance
  constrain(brightness, 0 , 255);                 //constrains the brightness value to the range useable by analogWrite()
  analogWrite(ledPin, brightness);                //adjusts the LED to the brightness value based on distance
  //Serial.print("Distance: ");                   //
  //Serial.print(distance);                       //will display the distance value in cm if using the serial monitor
  //Serial.println(" cm");                        //

}
