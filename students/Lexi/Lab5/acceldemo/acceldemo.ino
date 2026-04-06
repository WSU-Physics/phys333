// Basic demo for accelerometer readings from Adafruit LIS3DH

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

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// Low Power 5Khz data rate needs faster SPI, and calling setPerformanceMode & setDataRate
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, 2000000);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//LED yellow and green stuff
const int YLED = 9;
const int GLED = 10;

void setup(void) {
Serial.begin(115200);
while (!Serial) delay(10); // will pause Zero, Leonardo, etc until serial console opens

Serial.println("LIS3DH test!");

if (! lis.begin(0x18)) { // change this to 0x19 for alternative i2c address
Serial.println("Couldnt start");
while (1) yield();
}
Serial.println("LIS3DH found!");

// lis.setRange(LIS3DH_RANGE_4_G); // 2, 4, 8 or 16 G!

Serial.print("Range = "); Serial.print(2 << lis.getRange());
Serial.println("G");

// lis.setPerformanceMode(LIS3DH_MODE_LOW_POWER);
Serial.print("Performance mode set to: ");
switch (lis.getPerformanceMode()) {
case LIS3DH_MODE_NORMAL: Serial.println("Normal 10bit"); break;
case LIS3DH_MODE_LOW_POWER: Serial.println("Low Power 8bit"); break;
case LIS3DH_MODE_HIGH_RESOLUTION: Serial.println("High Resolution 12bit"); break;
}

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
case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("1.6 Khz Low Power"); break;
}

pinMode (YLED, OUTPUT);
pinMode (GLED, OUTPUT);

}

#define DEBUG 0 //enable or disable printing

void loop() {
lis.read(); // get X Y and Z data at once
// Then print out the raw data
#if DEBUG
Serial.print("X: "); Serial.print(lis.x);
Serial.print(" \tY: "); Serial.print(lis.y);
Serial.print(" \tZ: "); Serial.print(lis.z);
#endif

/* Or....get a new sensor event, normalized */
sensors_event_t event;
lis.getEvent(&event);


#if DEBUG
/* Display the results (acceleration is measured in m/s^2) */
Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
Serial.print(" \tY: "); Serial.print(event.acceleration.y);
Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
Serial.println(" m/s^2 ");

Serial.println();
#endif

float Ax = event.acceleration.x;
float Ay = event.acceleration.y;
float Az = event.acceleration.z;

float roll = atan2(Ay, Az) * 180 / PI;
float pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180 / PI;
#if DEBUG
Serial.print("\t\tRoll: "); Serial.print(roll); //tilt along Y-axis
Serial.print(" \tPitch: "); Serial.print(pitch); //tilt along X-axis

Serial.println();
#endif

// Serial Plotter output
Serial.print("X:");
Serial.print(Ax);
Serial.print(" ");

Serial.print("Y:");
Serial.print(Ay);
Serial.print(" ");

Serial.print("Z:");
Serial.print(Az);
//Serial.println(Az);
Serial.print(" ");

Serial.print("Roll:");
Serial.print(roll);
Serial.print(" ");

Serial.print("Pitch:");
Serial.println(pitch);

if ((roll > -2.5 && roll < 2.5) || (pitch > -2.5 && pitch < 2.5)){
analogWrite(GLED, 128);
} else {
analogWrite(GLED, 0);
}

if ((roll > 2.5 && roll < 10) || (roll > -10 && roll < -2.5) || (pitch > 2.5 && pitch < 10) || (pitch > -10 && pitch < -2.5)){
analogWrite(YLED, 128);
} else {
analogWrite(YLED, 0);
}


delay(200);
}

