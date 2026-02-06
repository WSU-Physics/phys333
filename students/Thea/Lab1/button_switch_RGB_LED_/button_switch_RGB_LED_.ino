
const int BLED = 9;     // Blue LED pin
const int GLED = 10;    // Green LED pin
const int RLED = 11;    // Red LED pin
const int BUTTON = 2;   // Button pin

boolean lastButton = HIGH;
boolean currentButton = HIGH;
int ledMode = 0;

// Set Color Function
void setColor(int redValue, int greenValue, int blueValue);

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP); // Button pressed = LOW
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if (last != current) {
    delay(50);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  currentButton = debounce(lastButton);

  // Detect button press (LOW --> HIGH transition)
  if (lastButton == HIGH && currentButton == LOW) {
    ledMode++;
    if (ledMode > 7) ledMode = 0;
  }

  lastButton = currentButton;

  switch (ledMode) {
    case 0: //OFF
    setColor(0, 0, 0);
    break;           
    case 1: //RED
    setColor(255, 0, 0); 
    break;        
    case 2: //ORANGE
    setColor(255, 30, 0); 
    break;        
    case 3:  //YELLOW
    setColor(130, 50, 0); 
    break;       
    case 4:  //GREEN
    setColor(0, 255, 0); 
    break;    
    case 5:  //TEAL
    setColor(0, 150, 127); 
    break;       
    case 6:  //BLUE
    setColor(0, 0, 255); 
    break;       
    case 7: //PURPLE
    setColor(127, 0, 127); 
    break;     
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RLED, redValue);
  analogWrite(GLED, greenValue);
  analogWrite(BLED, blueValue);
}
