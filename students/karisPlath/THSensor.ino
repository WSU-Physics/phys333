#include <avr/io.h>
#include <util/delay.h>

// button inits 
const int UP = A0;          
const int DWN = A1;           

// init TH sensor
#include "Adafruit_Si7021.h"
Adafruit_Si7021 sensor = Adafruit_Si7021();

// declare servo motor
#include <Servo.h>
Servo myservo;

// define speed/direction for servo
#define OPEN  95
#define CLOSE 65
#define SERV  10

// fan pins
const int fan1 = 6;          
const int fan2 = 7;     

// initialize pins for LCD
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <floatToString.h>    // allows floats to be printed on LCD

// set temp and buttons
uint8_t setTemp = 70;

void setup() {
  lcd.begin(16, 2);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DWN, INPUT_PULLUP);

  Serial.begin(115200);
  while(!Serial){
    delay(10);
  }

  // checks to see if sensor is connected to I2C bus
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  // lcd setup
  lcd.setCursor(0,0);
  lcd.print("Real temp: ");
  lcd.setCursor(0,1);
  lcd.print("Set temp: ");
}

// return temp converted to Fahreinheight
uint8_t chkTemp(){
  uint8_t fTemp = (sensor.readTemperature() * 1.8) + 32;
  return fTemp;
}

// rotate motor to open door
void turnMotor(int direction){
  // attach servo to pin
  myservo.attach(SERV);

  // write speed/direction
  myservo.write(direction);

  // wait until door is openned
  delay(500);

  // stop motor
  myservo.write(90);
}

// toggle fans
void toggleFans(int value){
  // write directly to the fans
  digitalWrite(fan1, value);
  digitalWrite(fan2, value);
}

// writes temp values to LCD
void writeLCD(uint8_t rTemp, uint8_t sTemp){
  // move cursor
  lcd.setCursor(11,0);

  // cast variable and print to LCD
  lcd.print((String)rTemp);

  // display set temp
  lcd.setCursor(11,1);
  lcd.print((String)sTemp);
}

// adjusts setTemp on button click
void adjustTemp(){
if(digitalRead(UP) == LOW){
   delay(5);
   if(digitalRead(UP) == LOW){
    setTemp++;
    }
   while(digitalRead(UP) == LOW){}
  }
  
  if(digitalRead(DWN) == LOW){
    delay(5);
    if(digitalRead(DWN) == LOW){
      setTemp--;
      }
    while(digitalRead(DWN) == LOW){}
  }
}

// when internal temp > set temp
void tooHot(){
  // open door + turn on fans
  turnMotor(OPEN);
  toggleFans(HIGH);

  // delay
  while(chkTemp() > setTemp){
    delay(50);
  }

  // close door + turn off fans
  toggleFans(LOW);
  turnMotor(CLOSE);
}

void loop() {
  // continuously writing to LCD
  writeLCD(chkTemp(), setTemp);

  // checks for button press
  adjustTemp();

  // checks internal temperature
  if(chkTemp() > setTemp + 5){
    tooHot();
  }
}
