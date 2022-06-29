/*
   Test the serial Rx/Tx between Arduino Uno R3 and the LV-EZ1 ultrasonic distance sensor.
   Tx from sensor will be RS232 format and should return gibberish.
   Will address the gibberish in part 1b.
*/

#include <SoftwareSerial.h>                   //include serial library

#define rxPin 10                              //define Rx pin (0 is default on the Arduino Uno R3)
#define txPin 1                               //(unused) define Tx pin (1 isdefault valueon the Arduino Uno R3)

int sensorVal;                                //variable for sensor value

SoftwareSerial sonarSensor (rxPin, txPin);    //define your serial and Rx and Tx pins

void setup() {
  pinMode(rxPin, INPUT);                      //set your sensor pin as input
  sonarSensor.begin(9600);                    //begin serial communication, LV-EZ1 uses 9600 baud
  delay(500);
  while (!Serial) {                           //wait for the serial port to connect
  }
}

void loop() {
  if (sonarSensor.available() >= 0) {
    sensorVal = sonarSensor.read();            //read the pin value
    sonarSensor.println(sensorVal, BIN);       //print the sensor value in the serial monitor
    delay(25);                                 //LV-EZ1 datasheet states RS232 data can be read every 49 ms
  }
}
