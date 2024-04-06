#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Adafruit LIS3DH setup
#define LIS3DH_CS 10
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// Timing control
unsigned long lastSwitchTime = 0;
const long switchInterval = 5000; // 5 seconds for each functionality

// State variable to toggle between serial and accelerometer
bool toggleState = false;

void setup(void) {
  Serial.begin(9600);
  // Wait for serial port to open
  while (!Serial) delay(10);

  // Initialize LIS3DH
  if (!lis.begin(0x18)) {   // Change this to 0x19 for an alternative I2C address
    Serial.println("Couldn't start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  // Setup for direct manipulation (as per the first sketch)
  DDRB |= 0b11111100; // Set PB2-PB7 as outputs
}

void loop() {
  // Check if it's time to switch
  unsigned long currentMillis = millis();
  if (currentMillis - lastSwitchTime >= switchInterval) {
    // Save the last switch time
    lastSwitchTime = currentMillis;

    // Toggle the state
    toggleState = !toggleState;
  }

  if (toggleState) {
    // Functionality of the first sketch: Serial communication
    if (Serial.available() > 0) {
      char serialCharacter = Serial.read();
      PORTD = serialCharacter << 2;
      PORTB = serialCharacter >> 6;

      if (serialCharacter == 'R') {
        Serial.println("Inch");
      
      }
      Serial.write(serialCharacter);
    }
  } else {
  
    sensors_event_t event;
    lis.getEvent(&event);
    Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
    Serial.print(" \tY: "); Serial.print(event.acceleration.y);
    Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
    Serial.println(" m/s^2 ");
    Serial.println();
    delay (500);
  }
}
