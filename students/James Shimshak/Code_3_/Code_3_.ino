int mode1 = 0; // # of reps
int mode2 = 0; // Type of lift
float mode3 = 0; // Time under tension in 1/2 seconds
int mode4 = 0; // Reset modes
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
/*#define BTN2     PB2  //d10
#define BTN1     PB1  //d9
#define BTN3     PB3  //d11
#define BTN4     PB4  //d12 */
#define BUTTON_PIN  PINB
int b1 = 0;  // number of reps
boolean Lb1 = HIGH;
boolean Cb1 = HIGH;
int b2 = 0; // setting for type of lift
boolean Lb2 = HIGH;
boolean Cb2 = HIGH;
float b3 = 0; //total time under tension
boolean Lb3 = HIGH;
boolean Cb3 = HIGH;
int b4 = 0; //Reset button
boolean Lb4 = HIGH;
boolean Cb4 = HIGH;
// Used for hardware & software SPI
#define LIS3DH_CS 10
int reps = 0;
const int RLED = 6;
const int GLED = 5; //5
const int BLED = 4; //4
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

boolean debounce2(boolean last2){
 boolean current2 = digitalRead(BTN2); //Read the button state
 if (last2 != current2) //if it's different...
{    delay(5); //wait 5ms
 current2 = digitalRead(BTN2); //read it again
 }   return current2; //return the current value
 }

boolean debounce3(boolean last3){
 boolean current3 = digitalRead(BTN3); //Read the button state
 if (last3 != current3) //if it's different...
{    delay(5); //wait 5ms
 current3 = digitalRead(BTN3); //read it again
 }   return current3; //return the current value
 }

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
      
      interval = (mode3*500) / 6;


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
 delay(1000);
 analogWrite(RLED,0);
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
if(mode2 == 1){
  //Keep accelerometer running
  lis.read();      // get X Y and Z data at once
  // Then print 
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

        
  
 if(v<8){
  i=0;
  while(1){
    unsigned long currentMillis = millis();
    
    
    if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
    i++;}
  Serial.println(i);
  if(i == 1){
    
    
     
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      
    
    }
    else if (i == 2){
   
      analogWrite(GLED, 155);
      
    }
    else if (i == 3){
      
      analogWrite(GLED, 0);
      analogWrite(BLED, 155);
      analogWrite(RLED, 0);
      
    }
    else if (i == 4){
      
      analogWrite(BLED, 155);
      analogWrite(RLED, 155);
      

      
    }
    else if (i == 5){

      analogWrite(RLED, 155);
      analogWrite(GLED, 155);
      analogWrite(BLED, 155);

      
    }
    else if (i == 6) {
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
      reps++;
      delay(1000);
      i = 0;
      
      if (reps == mode1*2){
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 155);

      delay(100);
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);

      delay(300);
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 155);

      delay(300);
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
      delay(300);
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      analogWrite(BLED, 155);

      delay(1000);  
      mode1 = 0;
      return 0;
      }
    }
    
  }
 }
}

if(mode2 == 2){
  //Keep Accelerometer running
  
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
  
  if(v>12){
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
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 155);
      
    }
    else if (i == 3){
      analogWrite(GLED, 155);
      analogWrite(BLED, 0);
      analogWrite(RLED, 0);
      
    }
    else if (i == 4){
      analogWrite(BLED, 155);
      analogWrite(RLED, 155);
      analogWrite(GLED, 0);
      

      
    }
    else if (i == 5){
      analogWrite(RLED, 155);
      analogWrite(GLED, 155);
      analogWrite(BLED, 155);

      
    }
    else if (i == 6) {
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
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
      return 0;
      }
    }
    
  }
 }

}

}


