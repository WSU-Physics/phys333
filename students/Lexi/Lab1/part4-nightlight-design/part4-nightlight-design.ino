const int RLED = 9; 
const int GLED = 10; 
const int BLED = 11; 
const int BUTTON = 2; 

int ledMode = 0; 
boolean lastButton = LOW; 
boolean currentButton = LOW; 

unsigned long previousMillis = 0; //helps eliminate delay() function 
unsigned long fadeMillis = 0; 
int fade = 0; 
int fadedir = 1; 
int lastMode = -1; 

boolean debounce() {
  static unsigned long lastDebounceTime = 0; 
  static boolean lastReading = HIGH; 
  
  boolean reading = digitalRead(BUTTON); 

  if(reading != lastReading) {
    lastDebounceTime = millis(); 
  }

  if ((millis() - lastDebounceTime) > 25) {
    currentButton = reading; 
  } 
  lastReading = reading; 
  return currentButton;  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(RLED, OUTPUT); 
  pinMode(GLED, OUTPUT); 
  pinMode(BLED, OUTPUT); 
  pinMode(BUTTON, INPUT_PULLUP); 
}

void setMode(int mode) {
  //OFF mode
  if (mode == 0) {
    digitalWrite(RLED, LOW); 
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED, LOW);
  } 
  //White light + blinking 
  else if (mode == 1) {
    if (millis() - previousMillis >= 500) {
      previousMillis = millis(); 

      static boolean ledOn = false; 
      ledOn = !ledOn; 

      if (ledOn) {
        analogWrite(RLED, 170); 
        analogWrite(GLED, 170); 
        analogWrite(BLED, 170); 
      } else {
        analogWrite(RLED, 0); 
        analogWrite(GLED, 0); 
        analogWrite(BLED, 0); 
      }
    }
  }

  //fading purple light 
  else if (mode == 2) {
    if (millis() - fadeMillis >= 10) {
      fadeMillis = millis(); 
      fade += fadedir; 

      if(fade >= 25 || fade <= 0) {
        fadedir = -fadedir; 
      }

      analogWrite(RLED, fade); 
      analogWrite(GLED, 0); 
      analogWrite(BLED, fade); //fades blue with red to make purple
    }
  }

  // red to blue 
  else if (mode == 3) {
    if (millis() - fadeMillis >= 10) {
      fadeMillis = millis(); 
      fade += fadedir; 

      if (fade >= 255) {
        fade = 255; 
        fadedir = -1; 
      }
      if (fade <= 0) {
        fade = 0; 
        fadedir = 1; 
      }
      analogWrite(RLED, fade); 
      analogWrite(GLED, 0); 
      analogWrite(BLED, 255 - fade); 
    }
  }

  //rainbow 
  else if (mode == 4) {
    if (millis() - fadeMillis >= 10) {
      fadeMillis = millis(); 
      fade++; 

      if (fade > 1530) fade = 0; 

      if (fade <= 255) {
        analogWrite(RLED, 255); 
        analogWrite(GLED, fade); 
        analogWrite(BLED, 0); 
      } else if (fade <= 510) {
        analogWrite(RLED, 510 - fade); 
        analogWrite(GLED, 255);
        analogWrite(BLED, 0); 
      } else if (fade <= 765) {
        analogWrite(RLED, 0); 
        analogWrite(GLED, 255); 
        analogWrite(BLED, fade - 510); 
      } else if (fade <= 1020) {
        analogWrite(RLED, 0); 
        analogWrite(GLED, 1020 - fade); 
        analogWrite(BLED, 255); 
      } else if (fade <= 1275) {
        analogWrite(RLED, fade - 1020); 
        analogWrite(GLED, 0); 
        analogWrite(BLED, 255); 
      } else {
        analogWrite(RLED, 255); 
        analogWrite(GLED, 0); 
        analogWrite(BLED, 1530 - fade); 
      }
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean buttonState = debounce(); 

  if (lastButton == HIGH && currentButton == LOW) {
    ledMode++; 
    if (ledMode > 4) ledMode = 0; 
  }

  lastButton = buttonState; 

  if(ledMode != lastMode) {
    fade = 0; 
    fadedir = 1; 
    lastMode = ledMode; 
  }
  setMode(ledMode); 
}
