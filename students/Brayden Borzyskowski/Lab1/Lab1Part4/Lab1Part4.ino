const int BLED=9;  // Blue LED Cathode on Pin 9
const int GLED=10; // Green LED Cathode on Pin 10
const int RLED=11; // Red LED Cathode on Pin 11
const int BUTTON=2;// The Button is connected to pin 2

//values for Purple Fading Light
const int redValue = 255;
const int blueValue = 255;
const int greenValue = 0;

// Variables will change:
int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

unsigned long lastUpdateTime = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

boolean lastButton = LOW; // Last Button State
boolean currentButton = LOW; // Current Button State
int ledMode = 0;            // Cycle between LED states

void setup() 
{
pinMode (RLED, OUTPUT); // Set Red LED as Output
pinMode (GLED, OUTPUT); // Set Green LED as Output
pinMode (BLED, OUTPUT); // Set Blue LED as Output
pinMode (BUTTON, INPUT); // Set button as input (not required)
Serial.begin(9600);
}
 /*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state. 
*/
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);  // Read the button state 
  if (last != current)                    // If it's different...
  {
    delay(3);                             // Wait 5ms
    current = digitalRead(BUTTON);        // Read it again
  }
  return current;                         // Return the current value
}

/*
* LED Mode Selection
* Pass a number for the LED state and set it accordingly
* Note, since the RGB LED is COMMON ANODE, you must set the 
* cathode pin for each color LOW for that color to turn ON. 
*/
void setMode(int mode)
{
//Blinking White
  if (mode == 1)
  { 
    digitalWrite(RLED, HIGH); 
    digitalWrite(GLED, HIGH); 
    digitalWrite(BLED, HIGH);
    delay(300);

    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW);
    delay(300);
   

  }
  //Purple fading
  else if (mode == 2) 
  {
    static unsigned long lastUpdate = 0;
    unsigned long timeNow = millis(); 
         // Fade from bright to dim
         for (int brightness = 255; brightness >= 0; brightness--) 
          {
            analogWrite(RLED, redValue * brightness / 255);
            analogWrite(BLED, blueValue * brightness / 255);
            analogWrite(GLED, greenValue * brightness / 255);

            
          }

         // Fade from dim to bright
         for (int brightness = 0; brightness <= 255; brightness++) 
          {
            analogWrite(RLED, redValue * brightness / 255);
            analogWrite(BLED, blueValue * brightness / 255);
            analogWrite(GLED, greenValue * brightness / 255);
            
          }

  }
  //Start Red then Fade to Blue and back repeating
  else if (mode == 3) 
  {
    analogWrite(GLED, 0);
    static unsigned long lastUpdate = 0;
    unsigned long timeNow = millis(); 
    // Fade from red to blue
    for (int brightness = 0; brightness <= 255; brightness++) 
      {
      analogWrite(RLED, 255 - brightness);
      analogWrite(BLED, brightness);
      }

    // Fade from blue to red
    for (int brightness = 255; brightness >= 0; brightness--) 
      {
      analogWrite(RLED, 255 - brightness);
      analogWrite(BLED, brightness);
      
      }
  }

  else if (mode == 4)
  {
    digitalWrite(RLED, HIGH); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW);
    delay(100);

    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW);
    delay(100);

    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, HIGH); 
    digitalWrite(BLED, LOW);
    delay(100):

    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW);
    delay(100);

    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, HIGH);
    delay(100);

    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW);
    delay(100);
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
    currentButton = debounce(lastButton);           //Read debounced state
    if (lastButton == LOW && currentButton == HIGH) // If it was pressed...
    {
      ledMode++; // Increment the LED value 
    }
    lastButton = currentButton;                     // Reset button value
    // If you've cycled through the different options,
    // reset the counter to 0
    if (ledMode == 5) 
      ledMode = 0;                            // Change the LED state

    setMode(ledMode);
   }
  
