#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <SD.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10); // wait for serial monitor to open

  Serial.println("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");

  if (!lis.begin(0x18)) {
    Serial.println("Could not start LIS3DH");
    while (1);
  }
  Serial.println("LIS3DH found!");

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");

  Serial.print("Data rate set to: ");
  switch (lis.getDataRate()) {
    case LIS3DH_DATARATE_1_HZ: Serial.println("1 Hz"); break;
    case LIS3DH_DATARATE_10_HZ: Serial.println("10 Hz"); break;
    case LIS3DH_DATARATE_25_HZ: Serial.println("25 Hz"); break;
    case LIS3DH_DATARATE_50_HZ: Serial.println("50 Hz"); break;
    case LIS3DH_DATARATE_100_HZ: Serial.println("100 Hz"); break;
    case LIS3DH_DATARATE_200_HZ: Serial.println("200 Hz"); break;
    case LIS3DH_DATARATE_400_HZ: Serial.println("400 Hz"); break;
    case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break;
  }
}

void loop() {
  lis.read();
  String dataString = "";

  // Read accelerometer data
  sensors_event_t event;
  lis.getEvent(&event);

  // Format data string as CSV
  dataString += event.acceleration.x;
  dataString += ",";
  dataString += event.acceleration.y;
  dataString += ",";
  dataString += event.acceleration.z;

  // Write to SD card
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  } else {
    Serial.println("error opening datalog.csv");
  }

  // Print data to Serial monitor
  Serial.println(dataString);

  delay(200); // Adjust delay as needed
}