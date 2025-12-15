
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

const int BTN1 = 8;
const int BTN2 = 9;
const int BTN3 = 2;
const int BTN4 = 3; 

int mode1 = 0; // # of reps
int mode2 = 0; // Type of lift
float mode3 = 0; // Time under tension in 1/2 seconds
int mode4 = 0; // Reset modes

#define BUTTON_PIN  PINB

boolean Lb1 = HIGH;
boolean Cb1 = HIGH;

boolean Lb2 = HIGH;
boolean Cb2 = HIGH;

boolean Lb3 = HIGH;
boolean Cb3 = HIGH;

boolean Lb4 = HIGH;
boolean Cb4 = HIGH;
// Used for hardware & software SPI
#define LIS3DH_CS 10
int reps = 0;
const int RLED = 4;
const int GLED = 5; //5
const int BLED = 6; //4
const int DEBOUNCE_TIME = 1000;
unsigned long previousMillis = 0;
float interval = 0;
int i = -1;
float v = 0;

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//Dbounce-----------------------------------------------------------------------------
boolean debounce1(boolean last1){
 boolean current1 = digitalRead(BTN1); //Read the button state
 if (last1 != current1) //if it's different...
{    delay(5); //wait 5ms
 current1 = digitalRead(BTN1); //read it again
 }   return current1; //return the current value
 }

//Dbounce-----------------------------------------------------------------------------
boolean debounce2(boolean last2){
 boolean current2 = digitalRead(BTN2); //Read the button state
 if (last2 != current2) //if it's different...
{    delay(5); //wait 5ms
 current2 = digitalRead(BTN2); //read it again
 }   return current2; //return the current value
 }

//Dbounce-----------------------------------------------------------------------------
boolean debounce3(boolean last3){
 boolean current3 = digitalRead(BTN3); //Read the button state
 if (last3 != current3) //if it's different...
{    delay(5); //wait 5ms
 current3 = digitalRead(BTN3); //read it again
 }   return current3; //return the current value
 }

//Dbounce-----------------------------------------------------------------------------
boolean debounce4(boolean last4){
 boolean current4 = digitalRead(BTN4); //Read the button state
 if (last4 != current4) //if it's different...
{    delay(5); //wait 5ms
 current4 = digitalRead(BTN4); //read it again
 }   return current4; //return the current value
 }

void setup(void) {
//Accelerometer and LED's------------------------------------------
  pinMode (RLED, OUTPUT);
  pinMode (GLED, OUTPUT);
  pinMode (BLED, OUTPUT);

  pinMode (BTN1, INPUT_PULLUP);
  pinMode (BTN2, INPUT_PULLUP);
  pinMode (BTN3, INPUT_PULLUP);
  pinMode (BTN4, INPUT_PULLUP);
 
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

 

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    
    while (1) yield();
  }



  switch (lis.getDataRate()) {

  }
}

void loop() {
  //Clock
  //--------------------
   
    unsigned long currentMillis = millis();      
    interval = (mode3*500) / 4;

  if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
    i++;} 
  //Button Codes
  //-------------------------------------------------------
 Cb1 = debounce1(Lb1); //read deboucned state
 if (Lb1 == HIGH && Cb1 == LOW) //if it was pressed...
 {
 mode1++; //increment the LED value
 }
 Lb1 = Cb1; //reset button value
 //if you've cycled through the different options,
  //reset the counter to 0  

Cb2 = debounce2(Lb2); //read deboucned state
 if (Lb2 == HIGH && Cb2 == LOW) //if it was pressed...
 {
 mode2++;
 }
 Lb2 = Cb2; //reset button value

Cb3 = debounce3(Lb3); //read deboucned state
 if (Lb3 == HIGH && Cb3 == LOW) //if it was pressed...
 {
 mode3 ++;
 }
 Lb3 = Cb3; //reset button value

 Cb4 = debounce4(Lb3); //read deboucned state
 if (Lb4 == HIGH && Cb4 == LOW) //if it was pressed...
 {
 mode1 = 0;
 mode2 = 0;
 mode3 = 0;
 analogWrite(RLED, 255);
 analogWrite(GLED,0);
 analogWrite(BLED,0);
 delay(1000);
 analogWrite(RLED,0);
 }
 Lb4 = Cb4; //reset button value 




  lis.read();      // get X Y and Z data at once


  /* Or....get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  v = sqrt(pow(event.acceleration.x,2) + pow(event.acceleration.y,2) + pow(event.acceleration.z,2));
  

  Serial.print("v: ");
  Serial.println(v);
  Serial.print("X: ");
  Serial.print(event.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(", Z: ");
  Serial.println(event.acceleration.z);
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
if(mode2 == 1){
  //Keep accelerometer running
  lis.read();      // get X Y and Z data at once


  /* Or....get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  v = sqrt(pow(event.acceleration.x,2) + pow(event.acceleration.y,2) + pow(event.acceleration.z,2));
  
  //Display the results (acceleration is measured in m/s^2) 




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

 if(v>12){
  analogWrite(BLED, 255);
  delay(1500);
  analogWrite(RLED, 0);
  
 }       
  
 else if(v<8){
  i=0;
  while(1){
    unsigned long currentMillis = millis();
    
    
    if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
    i++;}

  if(i == 1){     
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);    
    }
    else if (i == 2){  
      analogWrite(GLED, 155);  
      analogWrite(RLED,0);   
    }
    else if (i == 3){     
      analogWrite(GLED, 155);
      analogWrite(BLED, 0);
      analogWrite(RLED, 155);   
    
    }
    else if (i == 4) {
      analogWrite(RLED, 155);
      analogWrite(GLED, 155);
      analogWrite(BLED, 155);
      reps++;
      delay(1000);
      i = 0;
      
      if (reps == mode1*2){
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      delay(100);
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      delay(300);
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      delay(300);
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
      delay(300);
      analogWrite(RLED, 0);
      analogWrite(GLED, 155);
      analogWrite(BLED, 0);

      delay(1000);  
      mode1 = 0;
      mode2 = 0;
      reps = 0;
      return 0;
      }
    }
  }
 }
}

if(mode2 == 2){
  //Keep Accelerometer running
  
  lis.read();      // get X Y and Z data at once



  /* Or....get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  v = sqrt(pow(event.acceleration.x,2) + pow(event.acceleration.y,2) + pow(event.acceleration.z,2));
  


  Serial.println();
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

      
  unsigned long currentMillis = millis();
 

 if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
    i++;}
  
  if(v<8){
    analogWrite(BLED, 155);
    delay(1500);
    analogWrite(RLED,0);
    
  }
  else if(v>12){
    i=0;
  while(1){
    unsigned long currentMillis = millis();
    
    if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
    i++;}

  if(i == 1){
  
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      
    
    }
    else if (i == 2){
      analogWrite(RLED, 155);
      analogWrite(GLED, 155);
      analogWrite(BLED, 0);
      
    }
    else if (i == 3){
      analogWrite(GLED, 155);
      analogWrite(BLED, 0);
      analogWrite(RLED, 0);
      
    }
           
    
    else if (i == 4) {
      analogWrite(RLED, 155);
      analogWrite(GLED, 155);
      analogWrite(BLED, 155);
      reps++;
      delay(1000);
      i = 0;
      
      if (reps >= mode1*2){
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      delay(100);
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      delay(300);
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      delay(300);
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
      delay(300);
      analogWrite(RLED, 0);
      analogWrite(GLED, 155);
      analogWrite(BLED, 0);

      delay(1000);  
      mode1 = 0;
      mode2 = 0;
      reps = 0;
      return 0;
      }
    }
    
  }
 }

}

}


