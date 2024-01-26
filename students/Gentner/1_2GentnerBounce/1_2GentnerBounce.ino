const int BLUE=9; // pin 9 is the blue led
const int RED=10;// pin 10 is the red led
const int GREEN=11; // pin 11 is the green led
const int BUTTON=2; // setting the button as an input on pin 2
boolean lastButton = LOW; // variable containing the previous button state
boolean currentButton = LOW; // variable constaing the current button state
int ledMode = 0; // present state of the LED

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

void setMode(int mode)
{
 //RED
 if (mode == 1)
 {
 digitalWrite(RED, LOW);
 digitalWrite(GREEN, HIGH);
 digitalWrite(BLUE, HIGH);
 }
 //GREEN
 else if (mode == 2)
 {
 digitalWrite(RED, HIGH);
 digitalWrite(GREEN, LOW);
 digitalWrite(BLUE, HIGH);
 }
 //BLUE
 else if (mode == 3)
 {
 digitalWrite(RED, HIGH);
 digitalWrite(GREEN, HIGH);
 digitalWrite(BLUE, LOW);
 }
 //PURPLE (RED+BLUE)
 else if (mode == 4)
 {
 analogWrite(RED, 127);
 analogWrite(GREEN, 255);
 analogWrite(BLUE, 127);
 }
 //TEAL (BLUE+GREEN)
 else if (mode == 5)
 {
 analogWrite(RED, 255);
 analogWrite(GREEN, 127);
 analogWrite(BLUE, 127);
 }
 //ORANGE (GREEN+RED)
 else if (mode == 6)
 {
 analogWrite(RED, 127);
 analogWrite(GREEN, 127);
 analogWrite(BLUE, 255);
 }
 //WHITE (GREEN+RED+BLUE)
 else if (mode == 7)
 {
 analogWrite(RED, 170);
 analogWrite(GREEN, 170);
 analogWrite(BLUE, 170);
 }
 //OFF (mode = 0)
 else
 {
 digitalWrite(RED, LOW);
 digitalWrite(GREEN, LOW);
 digitalWrite(BLUE, LOW);
 }
}

void loop() {
currentButton = debounce(lastButton); //Read debounced state
 if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
 {
 ledMode++  ; //Increase the LED state value
 }
 lastButton = currentButton; //Reset button value
 if (ledMode == 8) ledMode=0;
 setMode(ledMode);
}
