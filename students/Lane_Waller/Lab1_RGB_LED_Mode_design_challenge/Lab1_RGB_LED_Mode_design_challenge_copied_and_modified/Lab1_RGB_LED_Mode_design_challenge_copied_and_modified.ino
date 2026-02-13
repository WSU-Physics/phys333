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

//ledState variable used to set digital LED state in mode 1
int ledState = LOW;             // ledState used to set the LED
int fadeBrightness = 0;         //
int fadeDirection = 1;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;

// constants won't change:

const long whiteBlink = 1000;  //used for mode 1 speed
const long fadeDelay = 10;     //used for mode 2 and mode 3 speed

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
    if(currentMillis - previousMillis >= whiteBlink){
    
    previousMillis = currentMillis;

    ledState = !ledState;

    digitalWrite(RLED, ledState);
    digitalWrite(GLED, ledState);
    digitalWrite(BLED, ledState);
    
    }
  }
  //PURPLE fade bright to dim and back to bright, repeat
  else if (mode == 2)
  {
    if (currentMillis - previousMillis >= fadeDelay){

      previousMillis = currentMillis;
      if (fadeDirection == 1){
        if (fadeBrightness <=127 && fadeBrightness >=0){
          fadeBrightness = fadeBrightness + 1;
        }
        if (fadeBrightness >=127){
          fadeBrightness = fadeBrightness - 1;
          fadeDirection = -1;
        }
      }
      if (fadeDirection == -1){
        if (fadeBrightness <=127 && fadeBrightness >=0){
          fadeBrightness = fadeBrightness - 1;
        }
        if (fadeBrightness <=0){
          fadeBrightness = fadeBrightness + 1;
          fadeDirection = 1;
        }
      }
      analogWrite(RLED, fadeBrightness);
      analogWrite(GLED, 0);
      analogWrite(BLED, fadeBrightness);
    }
  }
  //fade from red to blue then back to red, repeat
  else if (mode == 3)
  {
    if (currentMillis - previousMillis >= fadeDelay){

      previousMillis = currentMillis;
      if (fadeDirection == 1){
        if (fadeBrightness <=127 && fadeBrightness >=0){
          fadeBrightness = fadeBrightness + 1;
        }
        if (fadeBrightness >=127){
          fadeBrightness = fadeBrightness - 1;
          fadeDirection = -1;
        }
      }
      if (fadeDirection == -1){
        if (fadeBrightness <=127 && fadeBrightness >=0){
          fadeBrightness = fadeBrightness - 1;
        }
        if (fadeBrightness <=0){
          fadeBrightness = fadeBrightness + 1;
          fadeDirection = 1;
        }
      }
      analogWrite(RLED, fadeBrightness);
      analogWrite(GLED, 0);
      analogWrite(BLED, 127 - fadeBrightness);
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
  currentMillis = millis();

  currentButton = debounce(lastButton);           // Read debounced state
  if (lastButton == LOW && currentButton == HIGH) // If it was pressed...
  {
    ledMode++;                                    // Increment the LED value
  }
  lastButton = currentButton;                     // Reset button value
  // If you’ve cycled through the different options,
  // reset the counter to 0
  if (ledMode == 5) {
    ledMode = 0;
    fadeDirection = 1;
  }
  setMode(ledMode);                               // Change the LED state
}
