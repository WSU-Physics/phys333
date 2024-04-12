const int BLUE=9; // pin 9 is the blue led
const int RED=10;// pin 10 is the red led
const int GREEN=11; // pin 11 is the green led
const int BUTTON=2; // setting the button as an input on pin 2
boolean lastButton = LOW; // variable containing the previous button state
boolean currentButton = LOW; // variable constaing the current button state
boolean ledOn = false; // present state of the LED
void setup() {
pinMode(9,OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT); //set all pins as an output
pinMode(BUTTON, INPUT); //set the button as an input
}

boolean debounce(boolean last)
{
 boolean current = digitalRead(BUTTON); // Read the button state
 if (last != current) // if it's different...
 {
 delay(5); //Wait 5ms
 current = digitalRead(BUTTON); //Read it again
 }
 return current; //Return the current value
}

void loop() {
currentButton = debounce(lastButton); //Read debounced state
 if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
 {
 ledOn = !ledOn; //Toggle the LED value
 }
 lastButton = currentButton; //Reset button value
 digitalWrite(BLUE, ledOn);
}
