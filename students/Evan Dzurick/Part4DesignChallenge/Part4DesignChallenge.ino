const int BLED=9; //Blue LED on Pin 9
const int GLED=10; //Green LED on Pin 10
const int RLED=11; //Red LED on Pin 11
const int BUTTON=2; //The Button is connected to pin 2
int previousMillis = 0;
int ledState = 0;

boolean lastButton = LOW; //Last Button State
boolean currentButton = LOW; //Current Button State
int ledMode = 0; //Cycle between LED states

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
void setMode(int mode)


{

 // #1 LED OFF 
 if (mode == 0)
 {
   digitalWrite(RLED, LOW);
   digitalWrite(GLED, LOW);
   digitalWrite(BLED, LOW);
 }
 // #2 WHITE BLINKING
 else if (mode == 1){


  unsigned long currentMillis = millis(); //unsigned long is integers without sign with large range of values 
  if (currentMillis - previousMillis >= 500){
      previousMillis = currentMillis; 

    if (ledState == 0) {
        ledState = 85;
      } else {
        ledState = 0;
      }


  analogWrite(RLED, ledState);
  analogWrite(GLED, ledState);
  analogWrite(BLED, ledState);
  }
 }

 // #3 PURPLE FADES BRIGHT to DIM -> REPEAT
 if (mode == 2){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis <= 3000){

    int brightness = map(currentMillis - previousMillis - 3000, 0, 5000, 255, 0);
      analogWrite(RLED, brightness);
      analogWrite(GLED, 0);
      analogWrite(BLED, brightness);
  }

  else if(currentMillis - previousMillis <= 6000){
    int brightness = map(currentMillis - previousMillis - 3000,0,5000,0,255);

      analogWrite(RLED, brightness);
      analogWrite(GLED, 0);
      analogWrite(BLED, brightness);



  }

else {
      previousMillis = currentMillis;
    }
 }
  

 
 // #4 STARTS RED -> FADES TO BLUE -> BACK TO RED -> REPEAT 
 else if (mode == 3)

  {
 static unsigned long startTime = 0; 
 static unsigned long fade = 5000; 
  
 
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  unsigned long halfFade = fade / 2;
  int brightness;
  
  
  if (elapsedTime < halfFade) {
    brightness = map(elapsedTime, 0, halfFade, 255, 0);
  } else {
    brightness = map(elapsedTime - halfFade, 0, halfFade, 0, 255);
  }
  
  analogWrite(RLED, 255 - brightness);
  analogWrite(GLED, 0);
  analogWrite(BLED, brightness);
  
  if (elapsedTime >= fade) {
    startTime = currentTime;
  }
}

// #5 BLINK WITH GRADUALLY DECREASING TIME INTERVALS UNTIL IT RESETS AND STARTS INCREASING
else if (mode == 4)
{
  static unsigned long previousMillis = 0;
  static unsigned long interval = 1000; 
  static boolean increasingSpeed = true; //boolean can be to values true or false, true is starting increasing 
  unsigned long currentMillis = millis();
  
  
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis; 
    boolean ledState = !digitalRead(BLED); //reads current state of pin connected to LED then assigns opposite
    digitalWrite(BLED, ledState);
    
   
    if (increasingSpeed) {
      interval -= 50;// changes by 50ms every blink  
      if (interval <= 0) {
        interval = 0;
        increasingSpeed = false; 
      }
    } else {
      interval += 50; // changes by 50ms every blink  
      if (interval >= 1000) {
        interval = 1000; 
        increasingSpeed = true; 
      }
    }
 }
}


}

void loop()
{
  currentButton = debounce(lastButton); //read deboucned state
  if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
  {
     ledMode++; //increment the LED value
  }
  lastButton = currentButton; //reset button value
   //if you've cycled through the different options,
   //reset the counter to 0
   if (ledMode == 5) ledMode = 0;
   setMode(ledMode); //change the LED state
}