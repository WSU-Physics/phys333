/*
   Test the serial Rx/Tx between Arduino Uno R3 and the LV-EZ1 ultrasonic distance sensor.
   Tx from sensor will be RS232 format.
*/


#include <avr/io.h>
#include <util/delay.h>
#include <SoftwareSerial.h>

int sensorVal;                            //variable for sensor value
byte distance[4];

//SoftwareSerial Serial (rxPin, txPin);    //define your serial and Rx and Tx pins

void setup() {
  Serial.begin(9600);                         //begin serial communication, LV-EZ1 uses 9600 baud
  while (!Serial) {                           //wait for the serial port to connect
  }
}

void loop() {
  while (Serial.available()) {
    Serial.read();
  }
  while(Serial.read() !=82) {
    _delay_us(1);
  }
    Serial.readBytes(distance, 3);           //read the pin value
    int x = distance[0];
    int y = distance[1];
    int z = distance[2];
    Serial.print(x);
    Serial.print(y);
    Serial.println(z);
}