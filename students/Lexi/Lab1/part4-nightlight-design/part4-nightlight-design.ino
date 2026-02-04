const int RLED = 9; 
const int GLED = 10; 
const int BLED = 11; 
const int BUTTON = 2; 

int ledMode = 0; 
boolean lastButton = LOW; 
boolean currentButton = LOW; 

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON); 
  if(last!=current){
    delay(5); 
    current = digitalRead(BUTTON); 
  }
  return current; 
}
void setup() {
  // put your setup code here, to run once:
  pinMode(RLED, OUTPUT); 
  pinMode(GLED, OUTPUT); 
  pinMode(BLED, OUTPUT); 
  pinMode(BUTTON, INPUT); 
}

void setMode(int mode) {
  //OFF mode
  if (mode == 1) {
    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW);
  } 
  //White light + blinking 
  else if (mode == 2) {
    digitalWrite(RLED, 170); 
    digitalWrite(GLED, 170); 
    digitalWrite(BLED, 170); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
