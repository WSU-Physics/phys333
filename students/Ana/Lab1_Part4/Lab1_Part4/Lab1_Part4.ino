/*
  PHYS 333 Lab 1: LED with button and 5 modes
  Due 2/13/26
  Ana Schneider
  Creating 5 states for a LED with a button 
  Case 0 the LED is off
  Case 1 the LED blinks white
  Case 2 fades purple
  Case 3 fades red to blue
  Case 4 blinks the rainbow
*/


const int RLED = 9; 
const int GLED = 10;  
const int BLED = 11;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;
int i = 1;
int val = 1;
int n = 2; 

void setup() {
  Serial.begin(9600);  //baud rate must match in the serial monitor tab

  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if (last != current) {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

unsigned long previous_time_white = 0;
unsigned long previous_time_purple = 0;
unsigned long previous_time_RGB = 0;
int led_state_white = LOW;


void setMode(int mode) {


  unsigned long current_time = millis();

  const long white_blink_pause = 100;  //how long in ms I want the blinking to happen at
  const long purple_pause = 10;        //how long the i value will last before incrementing
  const long red_blue_pause = 10;
  const long RGB_pause = 1000;

  switch (mode) {
    //LED off
    case 0:
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      break;

    //LED white blinking
    case 1:

      if ((current_time - previous_time_white) > white_blink_pause) {

        previous_time_white = current_time;

        led_state_white = !led_state_white;

        digitalWrite(RLED, led_state_white);
        digitalWrite(GLED, led_state_white);
        digitalWrite(BLED, led_state_white);
      }
      break;

    //LED purple fading
    case 2:

      if ((current_time - previous_time_purple) >= purple_pause) {
        if (i % 255 == 0) {  //has it reached max value? if so increment val
          val++;
        }
        if (val % 2 == 0) {  //starting off and turning on
          previous_time_purple = current_time;
          analogWrite(RLED, (i % 255));  //push to pin the value of i mod 255
          analogWrite(GLED, 0);
          analogWrite(BLED, (i % 255));
          //need to use millis instead of delay
          i++;

        } else {  //start on full bright and fade off
          previous_time_purple = current_time;
          analogWrite(RLED, 255 - (i % 255));  //take max mad and subtract off
          analogWrite(GLED, 0);
          analogWrite(BLED, 255 - (i % 255));
          //need to use millis instead of delay
          i++;
        }
      }

      break;

    //red fade to blue and back
    case 3:  //yes it starts at red and yes I should have changed the if cases to starting with it being % 1 == 0 instead of checking % 2 == 0
             //or starting with val = 2 but it works so no I am not going to fix it and yes that is part of my testing process 
      if ((current_time - previous_time_purple) >= red_blue_pause) {
        if (i % 255 == 0) {  //has it reached max value? if so increment val
          val++;
        }
        if (i % 510 == 0) {
          n++;
        }
        
        if (n % 2 == 0) {
          if (val % 2 == 0) {  //starting off and turning on
            previous_time_purple = current_time;
            analogWrite(RLED, 255 - (i % 255));  //push to pin the value of i mod 255
            analogWrite(GLED, 0);
            analogWrite(BLED, 0);
            //need to use millis instead of delay
            i++;

          } else {  //start on full bright and fade off
            previous_time_purple = current_time;
            analogWrite(RLED, (i % 255) );  //take max mad and subtract off
            analogWrite(GLED, 0);
            analogWrite(BLED, 0);
            //need to use millis instead of delay
            i++;
          }
        } else {
          if (val % 2 == 0) {  //starting off and turning on
            previous_time_purple = current_time;
            analogWrite(RLED, 0);  //push to pin the value of i mod 255
            analogWrite(GLED, 0);
            analogWrite(BLED, 255 - (i % 255) );
            //need to use millis instead of delay
            i++;

          } else {  //start on full bright and fade off
            previous_time_purple = current_time;
            analogWrite(RLED, 0);  //take max mad and subtract off
            analogWrite(GLED, 0);
            analogWrite(BLED, (i % 255) );
            //need to use millis instead of delay
            i++;
          }
        }  
        
      }
      break;

    //blink rainbow
    case 4:
      if( (current_time - previous_time_RGB) > RGB_pause) {
        previous_time_RGB = current_time;
        if(i == 1) {
          //flash red
          digitalWrite(RLED, HIGH);
          digitalWrite(GLED, LOW);
          digitalWrite(BLED, LOW);
          i++;

        }else if(i == 2) {
          //flash orange
          analogWrite(RLED, 255);
          analogWrite(GLED, 25);
          analogWrite(BLED, 0);
          i++;

        }else if(i == 3) {
          //flash yellow
          analogWrite(RLED, 255);
          analogWrite(GLED, 40);
          analogWrite(BLED, 0);
          i++;

        }else if(i == 4) {
          //flash green
          digitalWrite(RLED, 0);
          digitalWrite(GLED, 255);
          digitalWrite(BLED, 0);
          i++;

        }else if(i == 5) {
          //flash blue
          digitalWrite(RLED, 0);
          digitalWrite(GLED, 0);
          digitalWrite(BLED, 255);
          i++;

        }else if(i == 6) {
          //flash pruple
          analogWrite(RLED, 255);
          analogWrite(GLED, 0);
          analogWrite(BLED, 255);
          i = 1;

        }

      }
      break;
  }
}


void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) {
    ledMode++;
    i = 1;
    n = 2;
    val = 1;
  }
  lastButton = currentButton;
  if (ledMode == 5) ledMode = 0;
  setMode(ledMode);
}

