/*PHYS 333 Lab 1
  Due 2/13/26
  Ana Schneider
  Creating 5 states for a LED with a button 
*/


const int RLED = 9;  // Define LED for pin 9
const int GLED = 10;
const int BLED = 11;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;
int i = 1;
int val = 1;
int n = 1;

void setup() {
  Serial.begin(9600);  //baud rate must match in the serial monitor tab
  // put your setup code here, to run once:

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

unsigned long previous_time_purple = 0;
unsigned long previous_time_white = 0;
int led_state_white = LOW;


void setMode(int mode) {


  unsigned long current_time = millis();

  const long white_blink_pause = 100;  //how long in ms I want the blinking to happen at
  const long purple_pause = 10;        //how long the i value will last before incrementing
  const long red_blue_pause = 10;

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
          //i++;
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
             //or starting with val = 2 but it works so no I am not going to fix it and yes that is part of my testing process it
      if ((current_time - previous_time_purple) >= purple_pause) {
        if (i % 255 == 0) {  //has it reached max value? if so increment val
          i++;
          n++;
          val++;
        }
        if (val % 2 == 0) {  //starting off and turning on
          previous_time_purple = current_time;
          if(n % 2 != 0) {
            analogWrite(RLED, (i % 255));  //push to pin the value of i mod 255
            analogWrite(GLED, 0);
            analogWrite(BLED, 0);
            //need to use millis instead of delay
            i++;
          } else {
            analogWrite(RLED, 0);  //push to pin the value of i mod 255
            analogWrite(GLED, 0);
            analogWrite(BLED, (i % 255));
            i++;
          }  

        } else {  //start on full bright and fade off
          previous_time_purple = current_time;
          if(n % 2 != 0) {
            analogWrite(RLED, 255 - (i % 255));  //take max mad and subtract off
            analogWrite(GLED, 0);
            analogWrite(BLED, 0);
            //need to use millis instead of delay
            i++;

          } else {
            analogWrite(RLED, 0);  //take max mad and subtract off
            analogWrite(GLED, 0);
            analogWrite(BLED, 255 - (i % 255));
            i++;

          }  
        }
      }

      break;

    case 4:
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, LOW);

      break;
  }
}
//alternates between lighting and dimming red then green theen blue
void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) {
    ledMode++;
    i = 1;
  }
  lastButton = currentButton;
  if (ledMode == 5) ledMode = 0;
  setMode(ledMode);
}
