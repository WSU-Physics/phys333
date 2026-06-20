#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);

  while (!Serial);

  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int devices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {

    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at 0x");

      if (address < 16)
        Serial.print("0");

      Serial.println(address, HEX);

      devices++;
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found");
  }

  Serial.println();
  delay(3000);
}