
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

#define BTN2     PB2  //d10
#define BTN1     PB1  //d9
#define BTN3     PB3  //d11
#define BTN4     PB4  //d12 
#define BUTTON_PIN  PINB
int b1 = 0;  // 1/2 number of reps
boolean Lb1 = LOW;
boolean Cb1 = LOW;
int mode1 = 0;
int b2 = 0; // setting for type of lift
boolean Lb2 = LOW;
boolean Cb2 = LOW;
int mode2 = 0;
float b3 = 0; //total time under tension
boolean Lb3 = LOW;
boolean Cb3 = LOW;
long mode3 = 0;
int b4 = 0; //Reset button
boolean Lb4 = LOW;
boolean Cb4 = LOW;
int mode4 = 0;
// Used for hardware & software SPI
#define LIS3DH_CS 10
int reps = 0;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int DEBOUNCE_TIME = 1000;
const float FiveDegreeRange = 0.555555555555555555555555555555555555555;
const float OneDegreeRange = 0.111111111111111111111111111111111111111;
const float GravConst = 10.5;
unsigned long previousMillis = 0;
long interval = 0;
int i = 1;
float v = 0;

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//Dbounce-----------------------------------------------------------------------------
//Dbounce-----------------------------------------------------------------------------
uint8_t debounce(boolean button) {
  if (bit_is_clear(BUTTON_PIN, button)) {      /* button is pressed now */
   
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, button)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

uint8_t buttonWasPressed = 0;  


void setup(void) {
//Accelerometer and LED's------------------------------------------
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);
  pinMode (LED4, OUTPUT);
  pinMode (LED5, OUTPUT);
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  // lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

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
}

void loop() {
  //Clock
  //--------------------
   
    unsigned long currentMillis = millis();
    
  if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
    i++;}

  interval = mode3 * 500;
  
  //Button Codes
  //-------------------------------------------------------
 Cb1 = debounce(Lb1); //read deboucned state
 if (Lb1 == LOW && Cb1 == HIGH) //if it was pressed...
 {
  mode1 ++;
 }
 Lb1 = Cb1; //reset button value


Cb2 = debounce(Lb2); //read deboucned state
 if (Lb2 == LOW && Cb2 == HIGH) //if it was pressed...
 {
 mode2 ++;
 }
 Lb2 = Cb2; //reset button value

Cb3 = debounce(Lb3); //read deboucned state
 if (Lb3 == LOW && Cb3 == HIGH) //if it was pressed...
 {
 mode3 ++;
 }
 Lb3 = Cb3; //reset button value

 Cb4 = debounce(Lb3); //read deboucned state
 if (Lb4 == LOW && Cb4 == HIGH) //if it was pressed...
 {
 mode1 = 0;
 mode2 = 0;
 mode3 = 0;
 analogWrite(LED3, 255);
 delay(1000);
 }
 Lb4 = Cb4; //reset button value




  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  Serial.print("X:  "); Serial.print(lis.x);
  Serial.print("  \tY:  "); Serial.print(lis.y);
  Serial.print("  \tZ:  "); Serial.print(lis.z);

  /* Or....get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  v = sqrt(pow(event.acceleration.x,2) + pow(event.acceleration.y,2) + pow(event.acceleration.z,2));
  
  //Display the results (acceleration is measured in m/s^2) 
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x); Serial.print(" m/s^2 ");
  Serial.print(" \tY: "); Serial.print(event.acceleration.y);  Serial.print(" m/s^2 ");
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z);  
  Serial.println(" m/s^2 ");

  Serial.println();

 /*Serial.print("X-Acceleration:");
  Serial.print(event.acceleration.x);
  Serial.print(",");
  Serial.print("Y-Acceleration:");
  Serial.println(event.acceleration.y);
  Serial.print(",");
  Serial.print("Z-Acceleration:");
  Serial.println(event.acceleration.z);
  Serial.println(i);*/
  Serial.println(v);
  delay(100);
  Serial.print("Mode1: ");
  Serial.println(mode1);

  Serial.print("Mode2: ");
  Serial.println(mode2);

  Serial.print("Mode3: ");
  Serial.println(mode3);

  Serial.print("Mode4: ");
  Serial.println(mode4);
  
//------------------------------------------------------
while(mode2 == 1){
  //Test LED
 if(v<8){
  while(1){
      
      unsigned long currentMillis = millis();
    
      if (currentMillis >= previousMillis + interval) {
      previousMillis = millis();
      i++;}
  if(i == 1){


     
      analogWrite(LED1, 255);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      
    
    }
    else if (i == 2){
      analogWrite(LED1, 0);
      analogWrite(LED2, 255);
      
    }
    else if (i == 3){
      analogWrite(LED2, 0);
      analogWrite(LED3, 255);
      
    }
    else if (i == 4){
      analogWrite(LED3, 0);
      analogWrite(LED4, 255);
      
    }
    else if (i == 5){
      analogWrite(LED4, 0);
      analogWrite(LED5, 255);
      
    }
    else if (i == 6){
      analogWrite(LED1, 255);
      analogWrite(LED2, 255);
      analogWrite(LED3, 255);
      analogWrite(LED4, 255);
      analogWrite(LED5, 255);
      
    }
    else if (i == 7) {

      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      i = 1;
      reps ++;
      if (reps == mode1*2){
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      delay(100);
      analogWrite(LED1, 100);
      analogWrite(LED2, 100);
      analogWrite(LED3, 100);
      analogWrite(LED4, 100);
      analogWrite(LED5, 100);
      delay(300);
      analogWrite(LED1, 200);
      analogWrite(LED2, 200);
      analogWrite(LED3, 200);
      analogWrite(LED4, 200);
      analogWrite(LED5, 200);
      delay(300);
      analogWrite(LED1, 255);
      analogWrite(LED2, 255);
      analogWrite(LED3, 255);
      analogWrite(LED4, 255);
      analogWrite(LED5, 255);
      delay(1000);  
      mode1 = 0;
      return 0;
      }
    }
    
  }
 }
}

while(mode2 == 2){
   if(v>12){
  while(1){
      
      unsigned long currentMillis = millis();
    
      if (currentMillis >= previousMillis + interval) {
      previousMillis = millis();
      i++;}
  if(i == 1){


     
      analogWrite(LED1, 255);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      
    
    }
    else if (i == 2){
      analogWrite(LED1, 0);
      analogWrite(LED2, 255);
      
    }
    else if (i == 3){
      analogWrite(LED2, 0);
      analogWrite(LED3, 255);
      
    }
    else if (i == 4){
      analogWrite(LED3, 0);
      analogWrite(LED4, 255);
      
    }
    else if (i == 5){
      analogWrite(LED4, 0);
      analogWrite(LED5, 255);
      
    }
    else if (i == 6){
      analogWrite(LED1, 255);
      analogWrite(LED2, 255);
      analogWrite(LED3, 255);
      analogWrite(LED4, 255);
      analogWrite(LED5, 255);
      
    }
    else if (i == 7) {

      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      i = 1;
      reps ++;
      if (reps == mode1){
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      delay(100);
      analogWrite(LED1, 100);
      analogWrite(LED2, 100);
      analogWrite(LED3, 100);
      analogWrite(LED4, 100);
      analogWrite(LED5, 100);
      delay(300);
      analogWrite(LED1, 200);
      analogWrite(LED2, 200);
      analogWrite(LED3, 200);
      analogWrite(LED4, 200);
      analogWrite(LED5, 200);
      delay(300);
      analogWrite(LED1, 255);
      analogWrite(LED2, 255);
      analogWrite(LED3, 255);
      analogWrite(LED4, 255);
      analogWrite(LED5, 255);
      delay(1000);  
      mode1 = 0;
      return 0;
      }
    }
    
  }
 }

}
  /*if (((GravConst - FiveDegreeRange) <= event.acceleration.z) && (event.acceleration.z <= (GravConst + FiveDegreeRange)))
  {
    analogWrite(YLED, 250);
    
  }
  else
  {
    analogWrite(YLED, 250);
    delay(10);
  }

  if (((GravConst - OneDegreeRange) <= event.acceleration.z) && (event.acceleration.z <= (GravConst + OneDegreeRange)))
  {
    analogWrite(GLED,200);
    delay(10);
  }
  else
  {
    analogWrite(GLED,0);
    delay(100);
  }*/
}
}
