
#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11

//#define BUTTON      PB2
//const int BUTTON = 10;
#define BUTTON_PIN  PINB

// Used for hardware & software SPI
#define LIS3DH_CS 10
const int BUTTON = 8;
const int LED1 = 4;
const int DEBOUNCE_TIME = 1000;
boolean Cb1 = LOW;
boolean Lb1 = LOW;
int mode1 = 0;
const float OneDegreeRange = 0.111111111111111111111111111111111111111;
const float GravConst = 10.5;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 1000;
int i = 1;
float v = 0;
// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();


void setup(void) {



//Accelerometer and LED's------------------------------------------
pinMode (LED1, OUTPUT);
pinMode (BUTTON, OUTPUT);
}

boolean debounce(boolean last)
{
 boolean current = digitalRead(BUTTON); //Read the button state
 if (last != current) //if it's different...
 {
 delay(5); //wait 5ms
 current = digitalRead(BUTTON); //read it again
 }
 return current; //return the current value

 }

void loop() {

 Cb1 = debounce(Lb1); //read deboucned state
 if (Lb1 == LOW && Cb1 == HIGH) //if it was pressed...
 {
 mode1++; //increment the LED value
  
 }
 Lb1 = Cb1; //reset button value
 //if you've cycled through the different options,
  //reset the counter to 0
    
  if (mode1 == 1) {
    analogWrite(LED1, 255);
  }
  if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
    i++;}
Serial.print("mode1: ");
Serial.println(mode1);
delay(100);
 }