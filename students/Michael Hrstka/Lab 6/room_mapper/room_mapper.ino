#include <SD.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>
#include "USART.h"
#include <util/setbaud.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>


const int sdPin = 10;
int distancePin = 0;

char serialCharacter;
// DistanceSensor distanceSensor = DistanceSensor::DistanceSensor();

File logfile;
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void logToSD(int distance, double angle){
  Serial.print(distance);
  Serial.print(" / ");
  Serial.print(angle);
  Serial.print("\n");
  logfile.print(distance);
  logfile.print(", ");
  logfile.print(angle);
  logfile.print(",\n");
  logfile.flush();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
  }
  Serial.println("LIS3DH found!");

  // SD Output
  pinMode(sdPin, OUTPUT);

  if (!SD.begin(sdPin)) {
    Serial.println("No SD card found :(");
    exit(1);
  }

  char filename[] = "scan.csv"; // Should probably use a new file later on, this is fine for now
  logfile = SD.open(filename, FILE_WRITE);
  Serial.print("Writing to file:");
  Serial.print(filename);
  Serial.println();

  if (!logfile) {
    Serial.println("Couldn't create file :(");
    exit(1);
  }

  Wire.begin();  

  logfile.print("Distance, Angle,");
  logfile.print("\n");

  // initUSART();
}

double getDistance() {
  double distance = analogRead(distancePin) * 5.0 / 1023;
  Serial.println(distance); 
  return distance;
}

double getLevel() {
  sensors_event_t event;
  lis.getEvent(&event);
  double z = event.acceleration.z;
  return 180.0 - 180.0*(z/9.8);
}

void loop() {
  delay(200);
  double distance = getDistance();
  double angle = getLevel();
  Serial.println(angle);
  logToSD(distance, angle);
}

// void initUSART(void) { 
//   UBRR0H = UBRRH_VALUE;
//   UBRR0L = UBRRL_VALUE;
// #if USE_2X
//   UCSR0A |= (1 << U2X0);
// #else
//   UCSR0A &= ~(1 << U2X0);
// #endif
//   UCSR0B = (1 << TXEN0) | (1 << RXEN0);
//   UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
// }