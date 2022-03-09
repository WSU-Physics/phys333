const int RLED = 8; 
const int BLED = 9; 
const int GLED = 10; 
const int BUTTON=2; 
boolean lastButton = LOW; // Last Button State
boolean currentButton = LOW; // Current Button State
int ledMode = 0; // Cycle between LED states


void setup() {
  // put your setup code here, to run once:
  pinMode (BLED, OUTPUT); 
  pinMode (GLED, OUTPUT); 
  pinMode (RLED, OUTPUT); 
  pinMode (BUTTON, INPUT); 

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

void setMode(int mode)
{
 //RED
 if (mode == 1)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, HIGH);
 digitalWrite(BLED, HIGH);
 }
 //GREEN
 else if (mode == 2)
 {
 digitalWrite(RLED, HIGH);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, HIGH);
 }
 //BLUE
 else if (mode == 3)
 {
 digitalWrite(RLED, HIGH);
 digitalWrite(GLED, HIGH);
 digitalWrite(BLED, LOW);
 }
 //PURPLE (RED+BLUE)
 else if (mode == 4)
 {
 analogWrite(RLED, 127);
 analogWrite(GLED, 255);
 analogWrite(BLED, 127);
 }
 //TEAL (BLUE+GREEN)
 else if (mode == 5)
 {
 analogWrite(RLED, 255);
 analogWrite(GLED, 127);
 analogWrite(BLED, 127);
 }
 //ORANGE (GREEN+RED)
 else if (mode == 6)
 {
 analogWrite(RLED, 127);
 analogWrite(GLED, 127);
 analogWrite(BLED, 255);
 }
 //WHITE (GREEN+RED+BLUE)
 else if (mode == 7)
 {
 analogWrite(RLED, 170);
 analogWrite(GLED, 170);
 analogWrite(BLED, 170);
 }
 //OFF (mode = 0)
46 Exploring Arduino
 else
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, LOW);
    }
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  currentButton = debounce(lastButton); // Read debounced state
 if (lastButton == LOW && currentButton == HIGH) // If it was pressed...
 {
 ledMode++; // Increment the LED value
 }
 lastButton = currentButton; // Reset button value
 // If you've cycled through the different options,
 // reset the counter to 0
 if (ledMode == 8) ledMode = 0;
 setMode(ledMode); // Change the LED state
}
