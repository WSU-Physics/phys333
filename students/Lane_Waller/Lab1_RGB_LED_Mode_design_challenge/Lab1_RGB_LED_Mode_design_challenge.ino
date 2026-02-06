/*
Exploring Arduino, Second Edition
Code Listing 2-6: Toggling RGB LED Nightlight
https://www.exploringarduino.com/content2/ch2

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/
//I took the Blum reference code to start as the framework for my code

const int BLED=9;      // Blue LED Cathode on Pin 9
const int GLED=10;     // Green LED Cathode on Pin 10
const int RLED=11;     // Red LED Cathode on Pin 11
const int BUTTON=2;    // The Button is connected to pin 2

boolean lastButton = LOW;    // Last Button State
boolean currentButton = LOW; // Current Button State
int ledMode = 0;             // Cycle between LED states
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;  

void setup()
{
  pinMode (BLED, OUTPUT);   // Set Blue LED as Output
  pinMode (GLED, OUTPUT);   // Set Green LED as Output
  pinMode (RLED, OUTPUT);   // Set Red LED as Output
  pinMode (BUTTON, INPUT);  // Set button as input (not required)
}

/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);       // Read the button state
  if (last != current)                         // If it's different...
  {
    delay(5);                                  // Wait 5ms
    current = digitalRead(BUTTON);             // Read it again
  }
  return current;                              // Return the current value
}

//LED Mode Selection Bank

void setMode(int mode)
{

  //White light blinking on and off, every second
  if (mode == 1)
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
    delay(500);
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    delay(500);
  }
  //PURPLE fade bright to dim and back to bright, repeat
  else if (mode == 2)
  {
    for (int i=0; i<128; i++) {
      analogWrite(RLED, i);
      analogWrite(BLED, i);
      delay(10);
    }
    for (int i=127; i>=0; i--) {
      analogWrite(RLED, i);
      analogWrite(BLED, i);
      delay(10);
    }
  }
  //fade from red to blue then back to red, repeat
  else if (mode == 3)
  {
    for (int i=127; i>=0; i--) {
      analogWrite(RLED, i);
      analogWrite(BLED, 127-i);
      delay(10);
    }
    for (int i=0; i<128; i++) {
      analogWrite(RLED, i);
      analogWrite(BLED, 127-i);
      delay(10);
    }
    
  }
  //red fade to blue then fade to green then back to red, repeat
  else if (mode == 4)
  {
    for (int i=127; i>=0; i--) {
      analogWrite(RLED, i);
      analogWrite(BLED, 127-i);
      delay(10);
    }
    for (int i=0; i<128; i++) {
      analogWrite(GLED, i);
      analogWrite(BLED, 127-i);
      delay(10);
    }
    for (int i=127; i>=0; i--) {
      analogWrite(GLED, i);
      analogWrite(RLED, 127-i);
      delay(10);
    }
  }
  //OFF (mode = 0)
  else
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
}

void loop()
{
  currentButton = debounce(lastButton);           // Read debounced state
  if (lastButton == LOW && currentButton == HIGH) // If it was pressed...
  {
    ledMode++;                                    // Increment the LED value
  }
  lastButton = currentButton;                     // Reset button value
  // If you’ve cycled through the different options,
  // reset the counter to 0
  if (ledMode == 5) ledMode = 0;
  setMode(ledMode);                               // Change the LED state
  
  unsigned long currentMillis = millis();

  if (currentMillis- previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW){
      // Fill in - relevant variable is ledState
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    
  }
}
