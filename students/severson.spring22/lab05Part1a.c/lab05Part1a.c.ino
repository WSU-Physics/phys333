/*
   Test the serial Rx/Tx between Arduino Uno R3 and the LV-EZ1 ultrasonic distance sensor.
   Tx from sensor will be RS232 format and should return gibberish.
   Will address the gibberish in part 1b.
*/

#include <SoftwareSerial.h>                   //include serial library
#include <avr/io.h>
#include <util/delay.h>

#define rxPin 10                              //define Rx pin (0 is default on the Arduino Uno R3)
#define txPin 1                               //(unused) define Tx pin (1 is default value on the Arduino Uno R3) (unused)

uint8_t sensorVal;                            //variable for sensor value
int distance[4];

SoftwareSerial sonarSensor (rxPin, txPin);    //define your serial and Rx and Tx pins

void setup() {
  pinMode(rxPin, INPUT);                      //set your sensor pin as input
  sonarSensor.begin(9600);                    //begin serial communication, LV-EZ1 uses 9600 baud
  while (!Serial) {                           //wait for the serial port to connect
  }
}

void loop() {
  while (sonarSensor.available()) {
    sonarSensor.read();
  }
  while(sonarSensor.read() !=82) {
    _delay_us(1);
  }
    sensorVal = sonarSensor.read();           //read the pin value
    sonarSensor.println(sensorVal);           //print the sensor value in the serial monitor
                                              //LV-EZ1 datasheet states RS232 data can be read every 49 ms
}
