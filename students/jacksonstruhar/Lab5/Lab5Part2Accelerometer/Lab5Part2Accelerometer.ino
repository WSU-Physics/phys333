
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int yellowLED = 3;
const int greenLED = 2;

void setup(void) {
  Serial.begin(115200);

  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   //i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
}


void loop() {
 
  sensors_event_t event;
  lis.getEvent(&event);

  float ax = event.acceleration.x; //xyz values
  float ay = event.acceleration.y;
  float az = event.acceleration.z;

  float tilt = atan(sqrt(ax*ax + ay*ay) / az) * 180.0 / PI; //tangent theta equation for 3D space

  Serial.print("Angle of Tilt: "); 
  Serial.print(tilt);
  Serial.println(" Degrees");

  //LED values
  if (tilt <= 1) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
  }
  else if (tilt <= 5) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
  }
  else {
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  delay(200);
}
