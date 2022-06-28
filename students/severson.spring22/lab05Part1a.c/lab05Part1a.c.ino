/*
   Test the serial Tx/Rx between Arduino Uno R3 and the LV-EZ1 ultrasonic distance sensor.
   Tx from sensor will be RS232 format and should return gibberish.
   Will address the gibberish in part 1b.
*/

#include <SoftwareSerial.h>                   //include serial library

#define sensorPin 10                             //define Rx pin (0 is default on the Arduino Uno R3)
//#define txPin 1                                 //default value (unused)

uint8_t sensorVal;                                 //variable for sensor value

SoftwareSerial sonarSensor (sensorPin, 1);

void setup() {
  pinMode(sensorPin, INPUT);                   //set your sensor pin as input
  sonarSensor.begin(9600);                          //if you want to see the input in the serial monitor, not very interesting
  while (!Serial) {                            //wait for the serial port to connect
    ;
  }
}

void loop() {
  if (sonarSensor.available() > 0) {
    sensorVal = sonarSensor.read();                 //read the pin value
    sonarSensor.println(sensorVal, BIN);            //print the value in binary
    delay(49);                                 //LV-EZ1 datasheet states RS232 data can be read every 49 ms
  }
}
