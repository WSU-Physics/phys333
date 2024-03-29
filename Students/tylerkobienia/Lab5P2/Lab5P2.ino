#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

#define YELLOW_LED 5
#define GREEN_LED 3


Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);     

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldn't start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");

  lis.setDataRate(LIS3DH_DATARATE_50_HZ);
  Serial.print("Data rate set to: ");  // print the data rate set for the accelerometer
  switch (lis.getDataRate()) {
    case LIS3DH_DATARATE_1_HZ: Serial.println("1 Hz"); break;
    case LIS3DH_DATARATE_10_HZ: Serial.println("10 Hz"); break;
    case LIS3DH_DATARATE_25_HZ: Serial.println("25 Hz"); break;
    case LIS3DH_DATARATE_50_HZ: Serial.println("50 Hz"); break;
    case LIS3DH_DATARATE_100_HZ: Serial.println("100 Hz"); break;
    case LIS3DH_DATARATE_200_HZ: Serial.println("200 Hz"); break;
    case LIS3DH_DATARATE_400_HZ: Serial.println("400 Hz"); break;

    case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break;
  }


  pinMode(YELLOW_LED, OUTPUT);  // set the LED pins as outputs
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  lis.read();      // get X Y and Z data at once

  Serial.print("X:  "); Serial.print(lis.x);
  Serial.print("  \tY:  "); Serial.print(lis.y);
  Serial.print("  \tZ:  "); Serial.print(lis.z);


  sensors_event_t event;  // get the event data from the accelerometer
  lis.getEvent(&event);


  Serial.print("\t\tX: "); Serial.print(event.acceleration.x); // print the x, y, and z acceleration values in m/s^2
  Serial.print(" \tY: "); Serial.print(event.acceleration.y);
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2 ");

  if (abs(event.acceleration.x) <= 5 && abs(event.acceleration.y) <= 5) {   // control the yellow LED based on accelerometer data
    digitalWrite(YELLOW_LED, HIGH);
  } else {
    digitalWrite(YELLOW_LED, LOW);
  }

  if (abs(event.acceleration.x) <= 1 && abs(event.acceleration.y) <= 1) {   // control the green LED based on accelerometer data
    digitalWrite(GREEN_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, LOW);
  }

  delay(200);
}
