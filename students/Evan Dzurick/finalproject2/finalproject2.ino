#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define LIS3DH_ADDR 0x18

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int builtInLed = 25; // Built-in LED pin
const int helmetLed = 3;   // LED pin for the brake light on the helmet

// Define threshold values for engine braking and emergency braking
const float engineBrakingThreshold = 10.3;
const float emergencyBrakingThreshold = 15; 

// Define the normal vector of the helmet plane when held straight up
const float normalX = 4.3; // Normal vector X component
const float normalY = 3.0; // Normal vector Y component
const float normalZ = -8.3; // Normal vector Z component

void setup() {
  Serial.begin(9600); // Initialize serial communication
  Wire.begin();

  if (!lis.begin(LIS3DH_ADDR)) {
    while (1); // Stay in a loop if accelerometer is not found
  }

  pinMode(builtInLed, OUTPUT); 
  pinMode(helmetLed, OUTPUT);  
}

void loop() {
  float sumX = 0.0, sumY = 0.0, sumZ = 0.0;
  int sampleCount = 0;
  unsigned long startTime = millis();

  // Sample accelerometer readings over 100 ms
  while (millis() - startTime < 100) {
    lis.read(); // Read accelerometer data

    sensors_event_t event;
    lis.getEvent(&event);

    sumX += event.acceleration.x;
    sumY += event.acceleration.y;
    sumZ += event.acceleration.z;
    sampleCount++;

    delay(10); // Sampling interval
  }

  // Calculate average acceleration over the sampling period
  float avgX = sumX / sampleCount;
  float avgY = sumY / sampleCount;
  float avgZ = sumZ / sampleCount;

  // Calculate the magnitude of acceleration vector
  float accelerationMagnitude = sqrt(avgX * avgX + avgY * avgY + avgZ * avgZ);

  // Print the average magnitude to the serial monitor
 //   Serial.print("Average Magnitude: ");
 //   Serial.println(accelerationMagnitude);

  // Check if the magnitude is below engine braking threshold and past the helmet plane
 
   if (accelerationMagnitude > engineBrakingThreshold &&
             avgX * normalX + avgY * normalY + avgZ * normalZ < 0) {
    digitalWrite(builtInLed, HIGH); // Turn on built-in LED
    digitalWrite(helmetLed, HIGH);  // Turn on helmet LED
    delay(1000);                     // Minimum duration for engine braking
  } else if (accelerationMagnitude > emergencyBrakingThreshold &&
             avgX * normalX + avgY * normalY + avgZ * normalZ < 0) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(helmetLed, HIGH); // Flash helmet LED
      delay(200);                     // Flash duration
      digitalWrite(helmetLed, LOW);  // Turn off helmet LED
      delay(200);                     // Flash duration
    }
    digitalWrite(helmetLed, HIGH); // Turn on helmet LED after flashing
    delay(2000);                    // Minimum duration for emergency braking
  } else {
    digitalWrite(builtInLed, LOW); // Turn off built-in LED
    digitalWrite(helmetLed, LOW);  // Turn off helmet LED
  }

  delay(100); 
}