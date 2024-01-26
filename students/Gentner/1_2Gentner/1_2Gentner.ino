const int BLUE=9; // pin 9 is the blue led
const int RED=10;// pin 10 is the red led
const int GREEN=11; // pin 11 is the green led
const int BUTTON=2; // setting the button as an input on pin 2
void setup() {
pinMode(9,OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT); //set all pins as an output
pinMode(BUTTON, INPUT);
}

void loop() {
  if (digitalRead(BUTTON)==LOW)
  {digitalWrite(BLUE, LOW);}
  else
  {digitalWrite(BLUE,HIGH);}

}
