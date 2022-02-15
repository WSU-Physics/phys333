/*Sketch allowing a button to turn an LED on and off.
 * Now with a debounce feature!
*/

const int LED=9;  //LED is connected to pin 9
const int BUTTON=2; //button is connected to pin 2

boolean lastButton = LOW; //variable for the previous button state
boolean currentButton = LOW;  //variable for the current button state
boolean ledOn = false;  //present state of the LED (high/low)

void setup() 
{
  pinMode(LED, OUTPUT); //set the LED pin as an output
  pinMode(BUTTON, INPUT); //set the button as an input
}

/*
 * This is the debouncing function
 */
 boolean debounce(boolean last)
 {
  boolean current = digitalRead(BUTTON);  //read the state of the button
  if (last != current)  //if last is not equal to current
  {
    delay(5); //delay 5ms
    current = digitalRead(BUTTON);  //re-read the button state
    }
    return current; //return the current value
 }
 
void loop()
{
  currentButton = debounce(lastButton);  //read debounced state
  if (lastButton == LOW && currentButton == HIGH) //if the button was pressed
  {
    ledOn = !ledOn; //toggle the LED value
  }
  lastButton = currentButton; //reset the button value

  digitalWrite(LED, ledOn); //change the LED state
}
