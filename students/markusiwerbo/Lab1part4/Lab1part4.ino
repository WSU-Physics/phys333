//Lab 1 - Part 4

// pins
const int BLED = 9;
const int GLED = 10; 
const int RLED = 11; 
const int BUTTON = 2; 

// for debouncing button:
boolean lastButton = LOW; 
boolean currentButton = LOW; 

// for time functions
unsigned long previousMillis = 0;        // will store last time LED was updated


// integer variables and constants for each mode
int ledMode = 0; 
int ledState = LOW; 
int ledState21 = LOW;
int ledState22 = LOW;
int ledState31 = LOW;
int ledState32 = LOW;
int ledState4 = 0;
const long interval = 750;
const long interval2 = 120;
const long interval3 = 500;


void setup() {
pinMode (BLED, OUTPUT);
pinMode (GLED, OUTPUT);
pinMode (RLED, OUTPUT);
pinMode (BUTTON, INPUT); 
}

//Debouncing function:
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if (last!=current)
  {
    delay(5);
    current = digitalRead(BUTTON);
  }
return current; 
}

// Instructions for each mode:
void setMode(int mode) // off is Mode 0 in the code 
  {
    if(mode==1) //blinking white 
    {
      digitalWrite(RLED, ledState);
      digitalWrite(GLED, ledState);
      digitalWrite(BLED, ledState);
    }
    else if (mode==2) //purple fade
    {
      digitalWrite(GLED, LOW);
    }
    else if(mode==3) //red-blue-red
    {
      
      digitalWrite(GLED, LOW);
     
    }
    else if(mode==4) // disco light
    {
      if(ledState4==1){
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
    }
    else if (ledState4==2){
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, LOW);
    }
    else {
       digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, HIGH);
    }
  }
  else {          //This is mode 0
    digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
  }
  }

void loop() 
{
  //button pushes switches mode:
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH)
  {
    ledMode++;
  }
lastButton = currentButton;
if (ledMode == 5) ledMode = 0;
setMode(ledMode);
 unsigned long currentMillis = millis();


//Mode 2 loop:
  if (currentMillis > previousMillis + interval && ledMode==1) {
    // save the last time you blinked the LED
    previousMillis = millis();

    // if the LED is off turn it on and vice-versa:
    ledState = !ledState; // Fill in - relevant variable is ledState

  //Mode 3 loop:  
  }
  if (ledMode == 2) {

  if (currentMillis > previousMillis + interval2) {
    previousMillis = millis();
    if (ledState21 < 240){
    ledState21 = ledState21 + 8;
    analogWrite(RLED, 240-ledState21);
    analogWrite(BLED, 240-ledState21);
    }
    else if (ledState22 < 240) {
      ledState22 = ledState22 + 8;
      analogWrite(RLED, ledState22);
      analogWrite(BLED, ledState22);
    }   
    else {
      ledState21 = LOW;
      ledState22 = LOW;
    }
    
  }
}
//Mode 4 loop:
    if (ledMode == 3) {
       if (currentMillis > previousMillis + interval2) {
    previousMillis = millis();
    if (ledState31 < 240){
    ledState31 = ledState31 + 8;
    analogWrite(RLED, 240-ledState31);
    analogWrite(BLED, ledState31);
    }
    else if (ledState32 < 240) {
      ledState32 = ledState32 + 8;
      analogWrite(RLED, ledState32);
      analogWrite(BLED, 240 - ledState32);
    }   
    else {
      ledState31 = LOW;
      ledState32 = LOW;
    }
    
  }
}
//Mode 5 loop:
if (ledMode == 4) {
  if (currentMillis > previousMillis + interval3) {
    if (ledState4 < 3){
    previousMillis = millis();
    ledState4 = ledState4 + 1;
}
else {
  ledState4 = 0;
}
}
}
}

      

