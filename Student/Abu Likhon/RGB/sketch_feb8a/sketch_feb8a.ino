const int BLED=9; // Blue LED Cathode on Pin 9
const int GLED=10; // Green LED Cathode on Pin 10
const int RLED=11; // Red LED Cathode on Pin 11
const int BUTTON=2; // The Button is connected to pin 2
boolean lastButton = LOW; // Last Button State
boolean currentButton = LOW; // Current Button State
unsigned long lastUpdateTime = 0; // Last update time for non-blocking delays
int ledMode = 0; // Cycle between LED states
int fadeValue = 0; // Current fade value
bool fadingUp = true; // Direction of fade
void setup()
{
 pinMode (BLED, OUTPUT); // Set Blue LED as Output
 pinMode (GLED, OUTPUT); // Set Green LED as Output
 pinMode (RLED, OUTPUT); // Set Red LED as Output
 pinMode (BUTTON, INPUT); // Set button as input (not required)
}
/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last)
{
 boolean current = digitalRead(BUTTON); // Read the button state
 if (last != current) // If it's different...
 {
 delay(5); // Wait 5ms
 current = digitalRead(BUTTON); // Read it again
 }
 return current; // Return the current value
}
/*
* LED Mode Selection
* Pass a number for the LED state and set it accordingly
* Note, since the RGB LED is COMMON ANODE, you must set the
* cathode pin for each color LOW for that color to turn ON.
*/
void blinkWhite() {
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, LOW);
  delay(100);
  digitalWrite(RLED, HIGH);
  digitalWrite(GLED, HIGH);
  digitalWrite(BLED, HIGH);
  delay(100);
}
void fadePurple() {
  // Update fade value only if enough time has passed
  static unsigned long lastUpdate = 0;
  unsigned long timeNow = millis();
  
  if (timeNow - lastUpdate >= 10) { // 10 milliseconds interval
    lastUpdate = timeNow;

    if (fadingUp) {
      fadeValue++;
      if (fadeValue >= 255) { // Reached the maximum brightness
        fadingUp = false; // Change direction to fade down
      }
    } else {
      fadeValue--;
      if (fadeValue <= 0) { // Reached the minimum brightness
        fadingUp = true; // Change direction to fade up
      }
    }

    // Set the current fade value
    analogWrite(RLED, fadeValue);
    analogWrite(BLED, fadeValue);
  }
}
// Red To Blue 
//int fadeValue = 0; // Holds the current fade value (-255 to 255)
//bool fadingUp = true; // Direction of fade: true for increasing, false for decreasing

void redToBlue() {
   static unsigned long lastUpdate = 0;
  unsigned long timeNow = millis();

 if (timeNow - lastUpdate >= 10) { // 10 milliseconds interval
    lastUpdate = timeNow;
    // Update fadeValue based on the direction
    if (fadingUp) {
      fadeValue++;
      if (fadeValue >= 255) fadingUp = false; // Switch direction at peak
    } else {
      fadeValue--;
      if (fadeValue <= -255) fadingUp = true; // Switch direction at bottom
    }

    // Calculate LED intensities
    int Redfade = max(0, fadeValue); // Red fades out first
    int BlueFade = max(0, -fadeValue); // Then blue fades in

    // Update LED outputs
    analogWrite(RLED, Redfade);
    analogWrite(BLED, BlueFade);
  }
}


void setMode(int mode)
{
 //White
 if (mode == 1)
 {
 digitalWrite(RLED,HIGH);
 digitalWrite(GLED, HIGH);
 digitalWrite(BLED, HIGH);
 }
 //White Blinking
 else if (mode == 2)
 {
 blinkWhite();
 }
 //Fade Purpel Bright to low (repate)
 else if (mode == 3)
 {
analogWrite(GLED,0);
fadePurple();
   }
  
 else if (mode == 4){
 redToBlue();
 }
 //Police Siren Light
 else if (mode == 5)
 { 
 digitalWrite(RLED,HIGH);
 delay(100);
 digitalWrite(RLED,LOW);
 digitalWrite(BLED, HIGH);
 delay(50);
 digitalWrite(BLED, LOW);
 
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
 currentButton = debounce(lastButton); // Read debounced state
 if (lastButton == LOW && currentButton == HIGH) // If it was pressed...
 {
 ledMode++; // Increment the LED value
 }
 lastButton = currentButton; // Reset button value
 // If you've cycled through the different options,
 // reset the counter to 0
 if (ledMode == 6) ledMode = 0;
 setMode(ledMode); // Change the LED state
}