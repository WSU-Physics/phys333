#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
 
// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10
 
// Define LED pins
#define YELLOW_LED 5
#define GREEN_LED 4
 
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
 
void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);    
 
  Serial.println("LIS3DH test!");
 
  if (! lis.begin(0x18)) {   
    Serial.println("Couldn't start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
 
  lis.setRange(LIS3DH_RANGE_4_G);  
 
  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");
 
  lis.setDataRate(LIS3DH_DATARATE_50_HZ);
  Serial.print("Data rate set to: ");
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
 
  // Set up the LED pins
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}
 
void loop() {
  lis.read();      // get X Y and Z data at once
 
  // Then print out the raw data
  Serial.print("X:  "); Serial.print(lis.x);
  Serial.print("  \tY:  "); Serial.print(lis.y);
  Serial.print("  \tZ:  "); Serial.print(lis.z);
 
  /* Or....get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y);
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2 ");
 
  if (abs(event.acceleration.x) <= 5 && abs(event.acceleration.y) <= 5) {
    digitalWrite(YELLOW_LED, HIGH);
  } else {
    digitalWrite(YELLOW_LED, LOW);
  }
 
  if (abs(event.acceleration.x) <= 1 && abs(event.acceleration.y) <= 1) {
    digitalWrite(GREEN_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, LOW);
  }
 
  delay(200);
}