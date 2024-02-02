const int BLED=9; //Blue LED on Pin 9
const int GLED=10; //Green LED on Pin 10
const int RLED=11; //Red LED on Pin 11
const int BUTTON=2; //The Button is connected to pin 2
boolean lastButton = LOW; //Last Button State
boolean currentButton = LOW; //Current Button State
int ledMode = 0; //Cycle between LED states
unsigned long previousMillis = 0;
const long interval = 1000;
void setup()
{
 pinMode (BLED, OUTPUT); //Set Blue LED as Output
 pinMode (GLED, OUTPUT); //Set Green LED as Output
 pinMode (RLED, OUTPUT); //Set Red LED as Output
 pinMode (BUTTON, INPUT); //Set button as input (not required)
}
/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last)
{
 boolean current = digitalRead(BUTTON); //Read the button state
 if (last != current) //if it's different...
 {
 delay(5); //wait 5ms
 current = digitalRead(BUTTON); //read it again
 }
 return current; //return the current value

 }


/*
* LED Mode Selection
* Pass a number for the LED state and set it accordingly.
*/
/*void setMode(int mode) {
unsigned long currentMillis = millis();

 //RED
 if (mode == 1)
 {
  
 while (digitalRead(BUTTON) == LOW) {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
  delay(1000);
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
 
   if (currentMillis = previousMillis + interval) {// try switching it to current-precious >= interval, this may make it easier to modify
    previousMillis = millis();
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
   }
   if (currentMillis = previousMillis + .5 * interval){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    
  }
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
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, HIGH);
 }
 //PURPLE (RED+BLUE)
 if (mode == 4)
 {
 analogWrite(RLED, 255);
 analogWrite(GLED, 0);
 analogWrite(BLED, 0);
 }
 //OFF (mode = 0)
 if (mode == 0)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, LOW);
 }
}*/
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis >= previousMillis + interval) {
    previousMillis = millis();
  }

 currentButton = debounce(lastButton); //read deboucned state
 if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
 {
 ledMode++; //increment the LED value
 }
 lastButton = currentButton; //reset button value
 //if you've cycled through the different options,
  //reset the counter to 0
 if (ledMode == 5) ledMode = 0;

 //setMode(ledMode); //change the LED state
 if (ledMode == 1)
 {
  
 /*while (digitalRead(BUTTON) == LOW) {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
  delay(1000);*/
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
 
   if (currentMillis >= previousMillis + .5 * interval) {// try switching it to current-precious >= interval, this may make it easier to modify
    //previousMillis = millis();
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
   }
    else {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    
  }
  }
 
 //GREEN

 else if (ledMode == 2)
 {
   digitalWrite(RLED, HIGH);
   digitalWrite(GLED, LOW);
   digitalWrite(BLED, HIGH);
 }
 //BLUE
 else if (ledMode == 3)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, HIGH);
 }
 //PURPLE (RED+BLUE)
 if (ledMode == 4)
 {
 analogWrite(RLED, 255);
 analogWrite(GLED, 0);
 analogWrite(BLED, 0);
 }
 //OFF (mode = 0)
 if (ledMode == 0)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, LOW);
 }
}