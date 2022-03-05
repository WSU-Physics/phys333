/*
  Exploring Arduino, Second Edition
  Code Listing 2-6: Toggling RGB LED Nightlight
  https://www.exploringarduino.com/content2/ch2

  Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
  Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

const int BLED = 9;    // Blue LED Cathode on Pin 9
const int GLED = 10;   // Green LED Cathode on Pin 10
const int RLED = 11;   // Red LED Cathode on Pin 11
const int BUTTON = 2;  // The Button is connected to pin 2

boolean lastButton = LOW;    // Last Button State
boolean currentButton = LOW; // Current Button State
int ledMode = 0;             // Cycle between LED states

void setup()
{
  pinMode (BLED, OUTPUT);   // Set Blue LED as Output
  pinMode (GLED, OUTPUT);   // Set Green LED as Output
  pinMode (RLED, OUTPUT);   // Set Red LED as Output
  pinMode (BUTTON, INPUT);  // Set button as input (not required)
}

/*
  Debouncing Function
  Pass it the previous button state,
  and get back the current debounced button state.
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

/*
  LED Mode Selection
  Pass a number for the LED state and set it accordingly
  Note, since the RGB LED is COMMON ANODE, you must set the
  cathode pin for each color LOW for that color to turn ON.
*/
void setMode(int mode)
{
  //purple bright then dim
  if (mode == 2)

  {
    for (int i = 0; i < 127; i++)
    {
      if (debounce(lastButton) == true) {
        break;
      }
            
      analogWrite(RLED, i);
      analogWrite(BLED, i);
      delay(10);

      for (int i = 127; i >= 0; i--)
      {
        if (debounce(lastButton) == true) {
        break;
        }
        
        analogWrite(RLED, i);
        analogWrite(BLED, i);
        delay(10);
      }
    }
  }



  //WHITE blinking
 else if (mode == 1)
  {
    analogWrite(RLED, 170);
    analogWrite(GLED, 170);
    analogWrite(BLED, 170);
    delay(50);
    analogWrite(RLED, 0);
    analogWrite(GLED, 0);
    analogWrite(BLED, 0);
    delay(50);
  } 



  //RED fade to Blue
  else if (mode == 3)
  {
    for (int i = 0; i < 256; i++)
    {
       if (debounce(lastButton) == true)
      {
        break;
      }
    
  analogWrite(RLED, i);
  analogWrite(BLED,0);
    delay(10);
  }
  for (int i = 256; i >= 0; i--)
  {
    analogWrite(BLED, i);
    analogWrite(RLED, 0);
    delay(10);

  }
}
 

//flashing LED in different colors
 else if (mode == 4)
  {
    analogWrite(RLED, 170);
    delay(50);
    analogWrite(RLED, 0);
    delay(50);
    analogWrite(BLED, 170);
    delay(50);
    analogWrite(BLED, 0);
    delay(50);
    analogWrite(GLED, 170);
    delay(50);
    analogWrite(GLED, 0);
    delay(50);
  } 
  else if (mode ==5)
  {
    analogWrite(RLED, 0);
    analogWrite(BLED, 0);
    analogWrite(GLED, 0);
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
}
