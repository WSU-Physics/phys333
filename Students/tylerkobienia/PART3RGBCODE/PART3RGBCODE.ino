//PART3 Lab1

//pin ins
int BLED = 9; 
int GLED = 10; 
int RLED = 11; 
int BUTTON = 2; 

boolean lastButton = LOW; // last button state
boolean currentButton = LOW; // current button state
int ledMode = 0; // cycle between led states

void setup() {
  pinMode(BLED, OUTPUT); // blue led OUTPUT
  pinMode(GLED, OUTPUT); // green led OUTPUT
  pinMode(RLED, OUTPUT); // red led OUTPUT
  pinMode(BUTTON, INPUT); // button INPUT
}


boolean debounce(boolean last) { // debouncing function this ensures a mechaical switch or the buttons state to be reliable when pressed and released 
  boolean current = digitalRead(BUTTON); // read the button state
  if (last != current) { // if it is diffrent 
    delay(5); // wait 5ms a small delay for readings 
    current = digitalRead(BUTTON); // read again
  }
  return current; // returns current value
}

void setMode(int mode) { // int mode allows varible change within the leds to change between states and resets back to 1 which is red 
  
  if (mode == 1) { //red
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  
  }
  else if (mode == 2) {  //green 
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }

  else if (mode == 3) { // blue

    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }

  if (mode == 4) {   // purple, includes red and blue 
    analogWrite(RLED, 127);
    analogWrite(GLED, 0);
    analogWrite(BLED, 127);
  }

  else if (mode == 5) {   // teal, includes green and blue
    analogWrite(RLED, 0);
    analogWrite(GLED, 127);
    analogWrite(BLED, 127);
  }

  else if (mode == 6) {   // yellow a includes red and green
    analogWrite(RLED, 127);
    analogWrite(GLED, 127);
    analogWrite(BLED, 0);
  }

  else if (mode == 7) {  // all colors which create a white color ouput
    analogWrite(RLED, 85);
    analogWrite(GLED, 85);
    analogWrite(BLED, 85);
  }
}

void loop() {
  currentButton = debounce(lastButton); // read debounced state
  if (lastButton == LOW && currentButton == HIGH) { // when button is pressed
    ledMode++; // switch of color 
  }
  lastButton = currentButton; // resets the button value to go to mode 1
  if (ledMode == 8) {
    ledMode = 0;  // if it has cycled through the different options, reset the counter to 0
  }
  setMode(ledMode); // change the state of the led mode 
}