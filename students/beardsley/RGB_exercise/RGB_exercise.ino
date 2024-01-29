const int RLED = 11;  // Red LED pin
const int GLED = 10;  // Green LED pin
const int BLED = 9;  // Blue LED pin
const int BUTTON = 2;  // Button pin
int state = 0;  // variable for which mode we're in

boolean lastButton = LOW;
boolean currentButton = HIGH;


void setup() {
  // put your setup code here, to run once:
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last){
  boolean current = digitalRead(BUTTON);
  if (last != current){
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  // Check for button press
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH){
    state = (state + 1) % 3;
  }
  lastButton = currentButton;

  switch(state){
    case 0:
      // Light is blue
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, HIGH);
      break;

    case 1:
      // Light is green
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, LOW);
      break;

    case 2:
      // Light is red
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      break;
  }
}
