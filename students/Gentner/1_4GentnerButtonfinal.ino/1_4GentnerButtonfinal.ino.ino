const int BLUE=9; // pin 9 is the blue led
const int RED=10;// pin 10 is the red led
const int GREEN=11; // pin 11 is the green led
const int BUTTON=2; // setting the button as an input on pin 2
boolean lastButton = LOW; // variable containing the previous button state
boolean currentButton = LOW; // variable constaing the current button state
unsigned int ledMode = 0; // present state of the LED
unsigned long previousMillis = 0;
unsigned int brightness = 0;

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

void loop() 
{
  unsigned long currentMillis = millis();
currentButton = debounce(lastButton); //Read debounced state
 if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
 {
 ledMode++  ; //Increase the LED state value
 }
 lastButton = currentButton; //Reset button value
 if (ledMode == 6) ledMode=1;
{
switch (ledMode){ //tells the mode to switch
case 1: // led off
if (ledMode== 1)
{
digitalWrite(RED, LOW);
 digitalWrite(GREEN, LOW);
 digitalWrite(BLUE, LOW);
 break;
}
else {
break;
}
case 2:
if (ledMode==2)
{
if (currentMillis - previousMillis >= 500)
{previousMillis = currentMillis;
if (digitalRead(RED)==LOW)
{
digitalWrite(RED, HIGH);
 digitalWrite(GREEN, HIGH);
 digitalWrite(BLUE, HIGH);
}
else {
 digitalWrite(RED, LOW);
 digitalWrite(GREEN, LOW);
 digitalWrite(BLUE, LOW);
}
 break;
}}
 else {
  break;
 }

 case 3:
if (ledMode==3)
{
if (currentMillis - previousMillis >= 10)
{previousMillis = currentMillis;
if (brightness==0)
{
for (brightness=0; brightness<256; brightness++ )
{
analogWrite(RED, brightness);
 digitalWrite(GREEN, LOW);
 analogWrite(BLUE, brightness);
 delay(10);
}}
else
{
for (brightness =255; brightness>=0; brightness--)
{
 analogWrite(RED, brightness );
 digitalWrite(GREEN, LOW);
 analogWrite(BLUE, brightness);
 delay (10);
 }
 break;
}
else {
  break;
 }}}

case 4:
if (ledMode==4)
{
for (int i=255; i>=0; i-- )
{
analogWrite(RED, i);
 digitalWrite(GREEN, LOW);
 analogWrite(BLUE, 0);
 delay(10);
}
for (int i=0; i<256; i++)
{
 analogWrite(RED, 0 );
 digitalWrite(GREEN, LOW);
 analogWrite(BLUE, i);
 delay (10);
 }
 break;
}
else {
  break;
 }

case 5:
if (ledMode==5)
{
digitalWrite(RED, HIGH);
 digitalWrite(GREEN, LOW);
 digitalWrite(BLUE, LOW);
 delay(2000);
 analogWrite(RED, 200);
 analogWrite(GREEN, 25);
 digitalWrite(BLUE, LOW);
 delay (2000);
 digitalWrite(RED, LOW);
 digitalWrite(GREEN, HIGH);
 digitalWrite(BLUE, LOW);
 delay (2000);
 break;
}
 else {
  break;
 }
}
}
}

