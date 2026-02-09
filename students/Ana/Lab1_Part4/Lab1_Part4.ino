
const int RLED = 9;  // Define LED for pin 9
const int GLED = 10;
const int BLED = 11;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;
int i = 0;

void setup() {
  Serial.begin(9600); //baud rate must match in the serial monitor tab
  // put your setup code here, to run once:
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if(last != current) {
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

  const long white_blink_pause = 100; //how long in ms I want the blinking to happen at
  const long purple_pause = 100; //how long the i value will last before incrementing

  switch(mode) {
    //LED off
    case 0:
      digitalWrite(RLED, LOW);   
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      break;
    
    //LED white blinking
    case 1: 
    
      if( ( current_time - previous_time_white ) > white_blink_pause) {
        
        previous_time_white = current_time;

        led_state_white = !led_state_white;

        digitalWrite(RLED, led_state_white);
        digitalWrite(GLED, led_state_white);
        digitalWrite(BLED, led_state_white);
      }
      break;

    //LED purple fading
    case 2:

      if( (current_time - previous_time_purple) >= purple_pause) {
          
          previous_time_purple = current_time;
          analogWrite(RLED, i);
          analogWrite(GLED, 0);
          analogWrite(BLED, i);
          Serial.println(i);
          //need to use millis instead of delay
          i++;
        }  

 
      break;
    
    //red fade to blue and back
    case 3:
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
    /*
      for(int i = 255; i >= 0; i--) {
        if (analogRead(BUTTON) != 0) {       
          break;
        }
      analogWrite(GLED, i);
      analogWrite(BLED, 255 - i);
      delay(10);
        
      }
      for(int i = 255; i >= 0; i--) {
        if (analogRead(BUTTON) != 0) {  //instead of sensing zero have it sense above zero otherwise this is constantly reseting
          break;
      
        }
      analogWrite(GLED, 255 - i);
      analogWrite(BLED, i);
      delay(10);
      }    
      */
      break;
      
    case 4: 
      digitalWrite(GLED, HIGH);

      break;
  
  

  }
}
//alternates between lighting and dimming red then green theen blue
void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) {
    ledMode++;
    i = 0;
  }
  lastButton = currentButton;
  if (ledMode == 5) ledMode = 0;
  setMode(ledMode);
}


