
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
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int gLED = 2;
const int yLED = 4;


void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

}

void loop() {
  sensors_event_t event;
  lis.getEvent(&event);

  double angle_radian = atan(sqrt( sq(event.acceleration.x) + sq(event.acceleration.y) ) / event.acceleration.z);
  double angle = angle_radian * (180 / 3.13);
  Serial.println(angle);

  if(angle <= 10 && angle >= 0) {
    digitalWrite(gLED, HIGH);
    digitalWrite(yLED, LOW);
  } else if(angle > 10 && angle <= 20) {
    digitalWrite(gLED, LOW);
    digitalWrite(yLED, HIGH);
  } else if(angle > 20) {
    digitalWrite(gLED, LOW);
    digitalWrite(yLED, LOW);
  }


}
