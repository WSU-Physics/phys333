const int BLED = 9;     // Blue LED pin
const int GLED = 10;    // Green LED pin
const int RLED = 11;    // Red LED pin
const int BUTTON = 2;   // Button pin

boolean lastButton = HIGH;
boolean currentButton = HIGH;
int ledMode = 0;

//blink variables
unsigned long pastMillis = 0;
const long blinkTime = 500;  //ms
boolean ledState = false;

//fade variables
int Brightness = 0;
int Step = 5;
const unsigned long fadeTime = 20;

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
    if (ledMode > 7) ledMode = 0;         //Once case 7 is done, switches back to case 0
  }

  lastButton = currentButton;

  switch (ledMode) {
    case 0: //OFF
    setColor(0, 0, 0);
    break;           
    case 1: { //White Blinking 
    unsigned long nowMillis = millis();

    if (nowMillis - pastMillis >= blinkTime) {
      pastMillis = nowMillis;
      ledState = !ledState;
    
    if (ledState) {
      setColor(255, 255, 255); //on
    } else {
      setColor(0,0,0); //off
      }
    }  
    break;
    }

    case 2: {   //fade purple
    unsigned nowMillis = millis();

    if (nowMillis - pastMillis >= fadeTime) {
      pastMillis = nowMillis;
      Brightness += Step;

      setColor(Brightness, 0, Brightness);
    }
    break;
  }
}
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RLED, redValue);
  analogWrite(GLED, greenValue);
  analogWrite(BLED, blueValue);
}

