#include <LiquidCrystal.h>

char dist[4];   //Character array for serial input 
int nbytes = 0;   

const int numReadings = 3;  // Last three reading are averaged to account for bad measurements 
float readings[numReadings]; // Array to store readings
int index = 0;  // Current index in the array
float total = 0; // Variable to store the sum of readings

//---------------Calibrate the distance sensor----------------//
const float calibration = 1.05;   // Readings are 5% low 
//------------------------------------------------------------//

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//--------LED Preamble-------//
int ledpin = 13;
float slow = 20.0;
float medium = 15.0;
float fast = 10.0;
int ledState = LOW;  // ledState used to set the LED
unsigned long previousMillis = 0;  // will store last time LED was updated

// -----Blink intervals--------//
const long interval_s = 600;
const long interval_m = 1000;
const long interval_f = 1000;



void setup() {
  
  lcd.begin(16, 1); //set up the LCD's number of columns and rows
  lcd.print("ArduinoConnected");
  delay(3000);
  Serial.begin(9600);
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
    pinMode(ledpin, OUTPUT);
  }
}


void loop() {
while(Serial.available()){Serial.read();}
while(Serial.read() != 82){
  delay(1);
  lcd.clear();
}
int nbytes = Serial.readBytes(dist,3);
//Serial.println(dist);
float number = atof(dist);

// ------------ Takes the average of the last three readings and prints that as a float-------//
  float avg=number; 
  
  total -= readings[index];   // Subtract the oldest value from the total
  readings[index] = avg;    // Store the new value in the array
  total += readings[index];    // Add the new value to the total
  index = (index + 1) % numReadings;    // Move to the next index, wrap around if needed
  float average = total*calibration / numReadings;     // Calculate the average
  /*
  Serial.print("Average of last ");
  Serial.print(numReadings); 
  */
  Serial.print(" Distance: ");
  Serial.println(average);
  //--------------------------------------------------------------------------------------------//
  
  //----------LCD screen controls----------//
  lcd.setCursor(5, 1); 
  lcd.write(dist);
  lcd.print(" in");
  delay(100);

 unsigned long currentMillis = millis();

 if (average <= 20) {
    if (average <= 10) {
      // If distance is less than 10 inches, blink LED faster
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
    } else {
      // If distance is less than 20 inches but not less than 10 inches, blink LED at a normal rate
      digitalWrite(ledpin, HIGH);
      delay(200);
      digitalWrite(ledpin, LOW);
      delay(200);
    }
  } else {
    // If distance is 20 inches or more, turn off LED
    digitalWrite(ledpin, LOW);
  }
}



