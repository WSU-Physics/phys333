#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define LIS3DH_CS 10
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// Define LED pins
const int YELLOW_LED_PIN = 2;
const int GREEN_LED_PIN = 3;

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);

  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  if (!lis.begin(0x18)) {
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
}

void loop() {
  lis.read();
  sensors_event_t event;
  lis.getEvent(&event);

  // Calculate the angle of the Z axis from the gravitational vector.
  float angle = acos(event.acceleration.z / sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2))) * 180.0 / PI; // Find the Idea From Internet such as CalculaterHUb, OmniCalculater.

  // Check if we are within 5 degrees of being level
  if (angle <= 5) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else {
    digitalWrite(YELLOW_LED_PIN, LOW);
  }

  // Check if we are within 1 degree of being level
  if (angle <= 1) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);
  }

  Serial.print("Angle to level: "); Serial.println(angle);
  
  delay(200);
}
