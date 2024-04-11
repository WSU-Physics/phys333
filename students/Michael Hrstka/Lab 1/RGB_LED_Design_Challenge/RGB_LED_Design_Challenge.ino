int ledR = 3;
int ledG = 5;
int ledB = 6;
int btn = 12;
int state = 0;
int numState = 4;

void setup() {
  /* Setup pins */
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(btn, INPUT);
}

void chkBtn() {
  if (digitalRead(btn) == HIGH) {
    state = state >= numState ? 0 : state + 1;
    while (digitalRead(btn) == HIGH){ // Debounce! (Wait for release)
      delay(1);
    }
  }
}

/* Rapid white LED flash */
bool ledBlink = true;
void whiteLED() {
  digitalWrite(ledR, ledBlink);
  digitalWrite(ledG, ledBlink);
  digitalWrite(ledB, ledBlink);

  ledBlink = !ledBlink; // BLINK BLINK BLINK!!!
  delay(100);
}

/* Slowly fade purple LED */
int fadePurple;
bool fadePurpleIn;
void purpleLED() {
  analogWrite(ledR, fadePurple);
  digitalWrite(ledG, LOW);
  analogWrite(ledB, fadePurple);

  if(fadePurpleIn) { // Determine direction of fade based on state
      fadePurple++;
  } else {
    fadePurple--;
  }

  if (fadePurple >= 255) { // Change state when fully faded to color (or is off)
    fadePurpleIn = false;
  } else if(fadePurple <= 0) {
    fadePurpleIn = true;
  }

  delay(1);
}

/* Fade Blue to Red and back (with white in between cause then it looks like a police light) */
int policeFade = 0;
bool policeFadeIn = true;
void policeLED() {
  analogWrite(ledR, 255 - policeFade); // Blue and red together always add to 255
  analogWrite(ledB, policeFade);
  
  if (policeFade < 128){ // Green LED should mach the smaller of the two values, helps with turning the LED white
    analogWrite(ledG, policeFade);
  } else {
    analogWrite(ledG, 255 - policeFade);
  }

  if(policeFadeIn) { // Determine direction of fade based on state
      policeFade++;
  } else {
    policeFade--;
  }

  if (policeFade >= 255) { // Change state when fully faded to either color.
    policeFadeIn = false;
  } else if(policeFade <= 0) {
    policeFadeIn = true;
  }

  delayMicroseconds(50);
}

/* RAINBOW LIGHT!!! */
int gamerColorState = 0;
int gamerFadeState = 0;
void gamerLED() {
  gamerFadeState++;

  if (gamerFadeState >= 256) { // Move to next state and reset counter on when faded completely to next color
    gamerColorState = gamerColorState >= 2 ? 0 : gamerColorState + 1;
    gamerFadeState = 0;
  }

  switch(gamerColorState) { // Get current state in the fade cycle and continue
    case 0: // Red -> Blue
      analogWrite(ledR, 255 - gamerFadeState);
      analogWrite(ledG, 0);
      analogWrite(ledB, gamerFadeState);
      break;
    case 1: // Blue -> Green
      analogWrite(ledR, 0);
      analogWrite(ledG, gamerFadeState);
      analogWrite(ledB, 255 - gamerFadeState);
      break;
    default: // Green -> Red
      analogWrite(ledR, gamerFadeState);
      analogWrite(ledG, 255 - gamerFadeState);
      analogWrite(ledB, 0);
      break;
  }
  delay(1);
}

/* OFF */
void offLED() {
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
}

void loop() {
  switch(state) {
  case 0:
    whiteLED();
    break;
  case 1:
    purpleLED();
    break;
  case 2:
    policeLED();
    break;
  case 3:
    gamerLED();
    break;
  default:
    offLED();
  }
  chkBtn(); // Check btn after every loop
  delay(3);
}


