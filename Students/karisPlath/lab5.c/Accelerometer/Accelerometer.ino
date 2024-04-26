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

// LEDs
const int gLED = 9;
const int yLED = 10;
const int rLED = 11;

// level
int level;

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");

  // lis.setDataRate(LIS3DH_DATARATE_50_HZ);
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

  pinMode(rLED, OUTPUT);
  pinMode(yLED, OUTPUT);
  pinMode(gLED, OUTPUT);
}

void loop() {
  /* get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);
  
  // print out acceleration info
  Serial.print("x:");
  Serial.print(event.acceleration.x);
  Serial.print(",");
  Serial.print("\ty:");
  Serial.print(event.acceleration.y);
  Serial.print(",");
  Serial.print("\tz:");
  Serial.print(event.acceleration.z);

  Serial.println();

  delay(200);

  // output to LED
  level = abs(event.acceleration.x) + abs(event.acceleration.y) + (9.8 - abs(event.acceleration.z));

  if(level <= 1){
    digitalWrite(gLED, HIGH);
    digitalWrite(yLED, LOW);
    digitalWrite(rLED, LOW);
  }
  else if(level > 1 && level <=5){
    digitalWrite(gLED, LOW);
    digitalWrite(yLED, HIGH);
    digitalWrite(rLED, LOW);
  }
  else{
    digitalWrite(gLED, LOW);
    digitalWrite(yLED, LOW);
    digitalWrite(rLED, HIGH);
  }

}
