// LED buttons
const int BLED = 9;
const int GLED = 10;
const int RLED = 11;
const int BUTTON = 2;

// debounce variables
boolean lastButton = LOW;
boolean currentButton = LOW;

// state + mode
int ledMode = 0;
int numState = 5;

// initialize I/O
void setup() {
  pinMode(BLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);

 // setup interrupt button 
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), interrupt, CHANGE);
}

// debounce button
boolean debounce(boolean last){
  boolean current = digitalRead(BUTTON);
  if(last != current){
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

// set color of LED
void setLED(int r, int g, int b){
  analogWrite(RLED, r);
  analogWrite(GLED, g);
  analogWrite(BLED, b);
}

// interrupt on button press
void interrupt(){
  // interrupt to debounce button
  currentButton = debounce(lastButton);
  if(lastButton == LOW && currentButton == HIGH){
    // next mode
    ledMode++; 
    Serial.println(ledMode);
  }
  lastButton = currentButton;
}

void loop() {
  // check if mode resets
  if(ledMode == numState){
    ledMode = 0;
  }
  // turn LED off
  else if(ledMode == 0){
    setLED(0, 0, 0);
  }
  // blink LED
  else if(ledMode == 1){
    setLED(255, 255, 255);
    delay(500);
    setLED(0, 0, 0);
    delay(500);
  }
  // purple fade
  else if(ledMode == 2){
    for(int i = 0; i < 255; i++){
      delay(10);
      setLED(i, 0, i);
    }
    for(int i = 255; i > 0; i--){
      delay(10);
      setLED(i, 0, i);
    }
  }
  // red -> blue -> red
  else if(ledMode == 3){
    for(int i = 0; i < 255; i++){
      delay(10);
      setLED(255 - i, 0, i);
    }
    for(int i = 0; i < 255; i++){
      delay(10);
      setLED(i, 0, 255 - i);
    }
  }
  // random party mode
  else if(ledMode == 4){
    int ranDelay = 10 + random(1000);
    int ranRed = random(255);
    int ranBlue = random(255);
    int ranGreen = random(255);

    setLED(ranRed, ranGreen, ranBlue);
    delay(ranDelay);
  }
}