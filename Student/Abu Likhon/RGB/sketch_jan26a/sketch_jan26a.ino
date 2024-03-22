const int BLED=9; // Blue LED Cathode on Pin 9
const int GLED=10; // Green LED Cathode on Pin 10
const int RLED=11; // Red LED Cathode on Pin 11
const int BUTTON=2; // The Button is connected to pin 2
boolean lastButton = LOW; // Last Button State
boolean currentButton = LOW; // Current Button State
unsigned long lastUpdateTime = 0; // Last update time for non-blocking delays
int ledMode = 0; // Cycle between LED states
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
  for (int i = 0; i <= 255; i++) {
    analogWrite(RLED, i);
    analogWrite(BLED, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(RLED, i);
    analogWrite(BLED, i);
    delay(10);
  }
}
// Red To Blue 
void redToBlue() {

  for (int i = 0; i <= 255; i++) {
    analogWrite(RLED, i);
   // analogWrite(BLED, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(RLED, i);
   // analogWrite(BLED, i);
    delay(10);
  }
   for (int i = 0; i <= 255; i++) {
    //analogWrite(RLED, i);
    analogWrite(BLED, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    //analogWrite(RLED, i);
    analogWrite(BLED, i);
    delay(10);
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