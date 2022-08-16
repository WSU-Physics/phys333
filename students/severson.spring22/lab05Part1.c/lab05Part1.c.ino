/*
   Test the serial Rx/Tx between Arduino Uno R3 and the LV-EZ1 ultrasonic distance sensor.
   Tx from sensor is RS232 format.
*/

#include <util/delay.h>

char distance[4];                          //array for sensor value

void setup() {
  Serial.begin(9600);                      //begin serial communication, LV-EZ1 uses 9600 baud
  while (!Serial) {                        //wait for the serial port to connect
  }
}

void loop() {
  while (Serial.available()) {             //get number of characters available for read from serial port
    Serial.read();                         //read the serial port
  }
  while (Serial.read() != 82) {            //as long as not reading 82 (which is R)
    _delay_us(1);                          //delay
  }
  Serial.readBytes(distance, 3);           //read the Arduino Rx pin value and assign to distance array
  Serial.print(distance[0]);               //print the first number
  Serial.print(distance[1]);               //print second number
  Serial.println(distance[2]);             //print third number then go to a new line
}                                          //repeat loop()
