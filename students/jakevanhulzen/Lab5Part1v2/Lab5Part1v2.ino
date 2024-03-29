#include <Arduino.h>

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}
 
void loop() {
  
  if (Serial.available() > 0) {
    char sensorData = Serial.read();
    
    
    Serial.println(sensorData);
    sensorData = Serial.read();
    
    
    Serial.println(sensorData);
    sensorData = Serial.read();
    
    
    Serial.println(sensorData);
    sensorData = Serial.read();
    
    
    Serial.println(sensorData);
  }
  
  delay(1000);  
} 
 