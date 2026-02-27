const int BLED = 9; 
const int GLED = 10; 
const int RLED = 11; 
const int BUTTON = 2; 

boolean lastButton = LOW; 
boolean currentButton = LOW; 
int ledMode = 0; 

void setup() {
  // put your setup code here, to run once:
  pinMode (BLED, OUTPUT);
  pinMode (GLED, OUTPUT);
  pinMode (RLED, OUTPUT);
  pinMode (BUTTON, INPUT);
}
/* Debouncing Function*/
boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON); 
  if (last != current) {
    delay(5); 
    current = digitalRead(BUTTON); 
  }
  return current; 
}

/* LED Mode Selection*/
void setMode(int mode) {
  //red
  if (mode == 1) {
    digitalWrite(RLED, HIGH); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW); 
  }
  //green
  else if (mode == 2) {
    digitalWrite(GLED, LOW); 
    digitalWrite(GLED, HIGH); 
    digitalWrite(BLED, LOW); 
  }
  //blue
  else if (mode == 3) {
    digitalWrite(BLED, HIGH); 
    digitalWrite(GLED, LOW); 
    digitalWrite(RLED, LOW); 
  }

  //purple 
  else if (mode == 4) {
    analogWrite(RLED, 255); 
    analogWrite(GLED, 0); 
    analogWrite(BLED, 255); 
  }

  //teal 
  else if (mode == 5) {
    analogWrite(RLED, 0); 
    analogWrite(GLED, 255); 
    analogWrite(BLED, 255);
  }

  //orange
  else if (mode == 6) {
    analogWrite(RLED, 255); 
    analogWrite(GLED, 255); 
    analogWrite(BLED, 0);
  }

  //white 
  else if (mode == 7) {
    analogWrite(RLED, 170); 
    analogWrite(GLED, 170); 
    analogWrite(BLED, 170);
  }

  //OFF (mode == 8)
  else {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  currentButton = debounce(lastButton); 
  if (lastButton == LOW && currentButton == HIGH) {
    ledMode++; 
  }
  lastButton = currentButton; 
  if (ledMode == 8) ledMode = 0; 
    setMode(ledMode); 
}
