#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH(); 

const int yellow = 7; 
const int green = 6; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 

  pinMode(yellow, OUTPUT); 
  pinMode(green, OUTPUT); 

  if(!lis.begin(0x18)) {
    Serial.println("FAILED"); 
    while(1); 
  }

  lis.setRange(LIS3DH_RANGE_4_G); 
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t event; 
  lis.getEvent(&event); 

  float x = event.acceleration.x; 
  float y = event.acceleration.y; 
  float z = event.acceleration.z; 

  float angle = acos(z / sqrt(x*x + y*y + z*z)) * 180.0 / PI; 

  Serial.print("Angle: "); 
  Serial.println(angle); 

  if(angle <= 1.0) {
    digitalWrite(green, HIGH); 
    digitalWrite(yellow, LOW); 
  } else if (angle <= 5.0) {
    digitalWrite(green, LOW); 
    digitalWrite(yellow, HIGH); 
  } else {
    digitalWrite(green, LOW); 
    digitalWrite(yellow, LOW); 
  }
  delay(100); 
}
