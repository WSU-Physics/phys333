#include <Arduino.h>

void setup() { // initialize serial communication
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) { // check if there is data available to read from the serial port
    while (Serial.available() > 0) {  // continue reading until there's no more data available
      char sensorData = Serial.read(); // read a byte of data from the serial buffer and store it in a variable 'sensorData'
      Serial.println(sensorData); // print data to monitor 
    }
  }

  delay(1000);
}
