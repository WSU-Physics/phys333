/*Sketch allowing a button to turn an LED on and off.*/
const int LED=9;  //LED is connected to pin 9
const int BUTTON=2; //button is connected to pin 2

void setup() 
{
  pinMode(LED, OUTPUT); //set the LED pin as an output
  pinMode(BUTTON, INPUT); //set the button as an input
}

void loop()
{
  if (digitalRead(BUTTON) == LOW)
  {
    digitalWrite(LED, LOW);
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
}
