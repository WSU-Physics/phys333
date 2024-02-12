const int BLED=9; //Blue LED on Pin 9
const int GLED=10; //Green LED on Pin 10
const int RLED=11; //Red LED on Pin 11
const int BUTTON=2; //The Button is connected to pin 2
boolean lastButton = LOW; //Last Button State
boolean currentButton = LOW; //Current Button State
int ledMode = 0; //Cycle between LED states
unsigned long previousMillis = 0;
const long interval = 10000;
int i = 0; // brightness integer
int o = 0; //2nd brightness integer
int brightness = 0; // 3rd brightness integer
int brightness2 = 0; // 4th brightness integer
int fadeAmount = 5;  // the amount that the LED is changed by


void setup()
{
 pinMode (BLED, OUTPUT); //Set Blue LED as Output
 pinMode (GLED, OUTPUT); //Set Green LED as Output
 pinMode (RLED, OUTPUT); //Set Red LED as Output
 pinMode (BUTTON, INPUT); //Set button as input (not required)
 Serial.begin(9600);
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
 if (ledMode == 0)
 {
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED,LOW);
 }
 if (ledMode == 1)
 {
  

   if (currentMillis >= previousMillis + .5 * interval) {
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
 
 

 else if (ledMode == 2) {

  analogWrite(RLED, brightness);
  analogWrite(GLED, 0);
  analogWrite(BLED, brightness);

  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
  
}





 
 else if (ledMode == 3) {
  analogWrite(RLED, brightness);
  analogWrite(GLED, 0);
  analogWrite(BLED, brightness2);

  brightness = brightness + fadeAmount;
  brightness2 = -brightness;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
    delay(30);
  } 
  // wait for 30 milliseconds to see the dimming effect
   
 
   /*if (currentMillis >= previousMillis + .5 * interval) {
  i = i++;
  o = o--;
   analogWrite(RLED, o);
   analogWrite(GLED, 0);
   analogWrite(BLED, i);
   delay(10);
   }
   else if(currentMillis <= previousMillis + .5 * interval) {
    i == i++;
    o == o--;
   analogWrite(RLED, i);
   analogWrite(GLED, 0);
   analogWrite(BLED, o);
   delay(10);
   } 
 }*/
 
  if (ledMode == 4) {
   {
  i = 0;

   if (currentMillis >= previousMillis + .5 * interval) {
    //previousMillis = millis();
    i == i++;
    digitalWrite(RLED, i);
    digitalWrite(GLED, i);
    digitalWrite(BLED, i);
   }
    else {
      i = 0;
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    
  }
  }


  
   } 
 }

