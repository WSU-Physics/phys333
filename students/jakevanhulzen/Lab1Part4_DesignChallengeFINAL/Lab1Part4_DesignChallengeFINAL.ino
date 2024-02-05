const int BLED = 9;
const int GLED = 10;
const int RLED = 11;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;
unsigned long previousMillis = 0;
const long interval = 100;

// State variables for fading modes
int purpleBrightness = 0;
int fadeDirection = 5;  // Incremental fade
unsigned long fadeInterval = 20;  // Interval between each step in fading

void setup() {
  pinMode(BLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON); // Read the button state
  if (last != current) {
    delay(5); // Wait 5ms for debouncing
    current = digitalRead(BUTTON);
  }
  return current;
}

void setMode(int mode) {
  unsigned long currentMillis = millis();

  // OFF
  if (mode == 0) {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
  // WHITE BLINKING (GREEN and RED and BLUE)
  else if (mode == 1) {
    static boolean state = LOW;
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      state = !state;
    }
    digitalWrite(RLED, state);
    digitalWrite(GLED, state);
    digitalWrite(BLED, state);
  }
  // Purple light, fades between bright -> dim -> bright, repeat
  else if (mode == 2) {
    if (currentMillis - previousMillis >= fadeInterval) {
      previousMillis = currentMillis;
      purpleBrightness += fadeDirection;

      if (purpleBrightness <= 0 || purpleBrightness >= 255) {
        fadeDirection = -fadeDirection;
      }

      analogWrite(RLED, purpleBrightness);
      analogWrite(GLED, 0);
      analogWrite(BLED, purpleBrightness);
    }
  }
  // Red to Blue fading, repeat
  else if (mode == 3) {
    static int redValue = 255;
    static int blueValue = 0;
    static int fadeAmount = 5;

    if (currentMillis - previousMillis >= fadeInterval) {
      previousMillis = currentMillis;
      redValue -= fadeAmount;
      blueValue += fadeAmount;

      if (redValue <= 0 || blueValue >= 255) {
        redValue = 255;
        blueValue = 0;
      }

      analogWrite(RLED, redValue);
      analogWrite(GLED, 0);
      analogWrite(BLED, blueValue);
    }
  }
  // Party Mode - Flashes different colors
  else if (mode == 4) {
    static boolean state = LOW;
    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      state = !state;
    }

    if (state) {
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
    } else {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, HIGH);
    }
  }
}

void loop() {
  currentButton = debounce(lastButton);
  if (currentButton && !lastButton) {
    ledMode = (ledMode + 1) % 5; // Cycle through modes 0 to 4
  }

  setMode(ledMode);

  lastButton = currentButton;
}