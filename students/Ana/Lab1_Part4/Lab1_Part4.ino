
const int RLED = 9;  // Define LED for pin 9
const int GLED = 10;
const int BLED = 11;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;

void setup() {
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

void setMode(int mode) {
  switch(mode) {
    //LED off
    case 0:
      digitalWrite(RLED, LOW);   
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      break;
    
    //LED white blinking
    case 1: 
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, HIGH);
      delay(100);
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      delay(100);
      break;

    //LED purple fading
    case 2:
       
        for(int i = 0; i < 256; i++) {
          if (analogRead(BUTTON) == 0) { 
            analogWrite(RLED, i);
            analogWrite(BLED, i);
            delay(1);
          }
          else {
            
          }  
        }

        for(int i = 255; i >= 0; i--) {
          if (analogRead(BUTTON) == 0) { 
            analogWrite(RLED, i);
            analogWrite(BLED, i);
            delay(1);
          }
          else {
            
          }  
        }
        break;

    //red fade to blue and back
    case 3:
      for(int i = 255; i >= 0; i--) {
        if (analogRead(BUTTON) != 0) {       
          break;
        }
      analogWrite(RLED, i);
      analogWrite(BLED, 255 - i);
      delay(10);
        
      }
      for(int i = 255; i >= 0; i--) {
        if (analogRead(BUTTON) != 0) {  //instead of sensing zero have it sense above zero otherwise this is constantly reseting
          break;
      
        }
      analogWrite(RLED, 255 - i);
      analogWrite(BLED, i);
      delay(10);
      }    

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
  }
  lastButton = currentButton;
  if (ledMode == 5) ledMode = 0;
  setMode(ledMode);
}


