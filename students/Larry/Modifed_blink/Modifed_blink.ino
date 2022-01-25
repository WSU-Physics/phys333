/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int led = 9;
int button = 2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);


}



void loop() {

int stat = digitalRead(button);

  if (stat = 1) {
    digitalWrite(led, LOW); 
    
    // turn the LED on (HIGH is the voltage level)
              // wait for a second
  }
  else {
    digitalWrite(led, HIGH);
  }
  Serial.println(stat);
  
  delay(1);
}
