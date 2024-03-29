#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
}

// Will check if the two other axis are near 0 to determine if level
void checkLevel(double x, double y, double z, char *xLevel, char *yLevel, char *zLevel) {
  // 0: Not level, 1: within 5°, 2: within 1°
  if((abs(x) < 0.55) && (abs(y) < 0.55)) {
      *zLevel = 1;
    if((abs(x) < 0.11) && (abs(y) < 0.11))
      *zLevel = 2;
  } else
    *zLevel = 0;

  if(abs(y) < 0.55 && abs(z) < 0.55) {
    *xLevel = 1;
    if(abs(y) < 0.11 && abs(z) < 0.11)
      *xLevel = 2;
  } else
    *xLevel = 0;
  
  if(abs(x) < 0.55 && abs(z) < 0.55) {
    *yLevel = 1;
    if(abs(x) < 0.11 && abs(z) < 0.11)
      *yLevel = 2;
  } else
    *yLevel = 0;

}
template <typename T> void printInfo(T x, T y, T z) {
  Serial.print("X: ");
  Serial.print(abs(x));

  Serial.print("\tY: ");
  Serial.print(abs(y));

  Serial.print("\tZ: ");
  Serial.print(abs(z));
  Serial.println();
}

void loop() {

  sensors_event_t event;
  lis.getEvent(&event);

  double x = event.acceleration.x;
  double y = event.acceleration.y;
  double z = event.acceleration.z;

  printInfo<double>(x, y, z);

  char xLevel;
  char yLevel;
  char zLevel;

  checkLevel(x, y, z, &xLevel, &yLevel, &zLevel);

  printInfo<int>(xLevel, yLevel, zLevel);

  delay(200);
}
