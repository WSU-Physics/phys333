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
void checkLevel(int x, int y, int z, bool *xLevel, bool *yLevel, bool *zLevel) {
  if(abs(x) < 0.5 && abs(y) < 0.5)
    *zLevel = true;
  else
    *zLevel = false;

  if(abs(y) < 0.5 && abs(z) < 0.5)
    *xLevel = true;
  else
    *xLevel = false;
  
  if(abs(x) < 0.5 && abs(z) < 0.5)
    *yLevel = true;
  else
    *yLevel = false;

}
template <typename T> void printInfo(T x, T y, T z) {
  Serial.print("X: ");
  Serial.print(x);

  Serial.print("\tY: ");
  Serial.print(y);

  Serial.print("\tZ: ");
  Serial.print(z);
  Serial.println();
}

void loop() {

  sensors_event_t event;
  lis.getEvent(&event);

  double x = event.acceleration.x;
  double y = event.acceleration.y;
  double z = event.acceleration.z;

  printInfo<double>(x, y, z);

  bool xLevel;
  bool yLevel;
  bool zLevel;

  checkLevel(x, y, z, &xLevel, &yLevel, &zLevel);

  printInfo<bool>(xLevel, yLevel, zLevel);

  delay(200);
}
