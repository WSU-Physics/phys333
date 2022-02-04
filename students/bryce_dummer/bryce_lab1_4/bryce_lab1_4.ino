/*
Exploring Arduino, Second Edition
Code Listing 2-6: Toggling RGB LED Nightlight
https://www.exploringarduino.com/content2/ch2
Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

const int BLED=9;      // Blue LED Cathode on Pin 9
const int GLED=10;     // Green LED Cathode on Pin 10
const int RLED=11;     // Red LED Cathode on Pin 11
const int BUTTON=2;    // The Button is connected to pin 2
const int BUTTON2=3;

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

/*
* LED Mode Selection
* Pass a number for the LED state and set it accordingly
* Note, since the RGB LED is COMMON ANODE, you must set the
* cathode pin for each color LOW for that color to turn ON.
*/
void setMode(int mode)
{
  //white blinking
  if (mode == 1)
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
    delay(1000);
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    delay(1000);
  }
  
  //purple fade
  else if (mode == 2)
  {
    for (int i=0; i<256; i++) //purple light starts off and fades on
    {
      digitalWrite(RLED, i);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, i);
      delay(10);
      break;
    }
    for (int i=255; i>=0; i--) //fades from high to low
    {
      digitalWrite(RLED, i);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, i);
      delay(10);
      break;
    }
  }
  //redblue fade
  else if (mode == 3)
  {
    for (int i=255; i>=0; i--) //red light starts on and fades to off
    {
      digitalWrite(RLED, i);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      delay(10);
          break;
    }
    for (int i=0; i<256; i++) //blue light is off and fades on
    {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, i);
      delay(10);
      break;
    }
    for (int i=255; i>=0; i--) //blue light is on and fades off
    {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, i);
      delay(10);
      break;
    }
    for (int i=0; i<256; i++) //red light is off an fades on
    {
      digitalWrite(RLED, i);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      delay(10);
      break;
    }    
  }
  //blue light with second button
  else if (mode == 4)
  {
    if (BUTTON2 == HIGH)
    {
      analogWrite(RLED, LOW);
      analogWrite(GLED, LOW);
      analogWrite(BLED, HIGH);
    }
    else
    {
      analogWrite(RLED, LOW);
      analogWrite(GLED, LOW);
      analogWrite(BLED, LOW);
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
  if (ledMode == 8) ledMode = 0;
  setMode(ledMode);                               // Change the LED state
}
