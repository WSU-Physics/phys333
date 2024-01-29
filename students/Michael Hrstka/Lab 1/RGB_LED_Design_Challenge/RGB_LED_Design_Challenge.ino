int ledR = 3;
int ledG = 5;
int ledB = 6;
int btn = 12;
int state = 0;
int numState = 4;

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(btn, INPUT);
}

void chkBtn() {
  if (digitalRead(btn) == HIGH) {
    state = state >= numState ? 0 : state + 1;
        while (digitalRead(btn) == HIGH){ // Debounce!
      delay(10);
    }
  }
}

bool ledBlink = true;
void whiteLED() {
  digitalWrite(ledR, ledBlink);
  digitalWrite(ledG, ledBlink);
  digitalWrite(ledB, ledBlink);

  ledBlink = !ledBlink;
  delay(100);
}

int fadePurple;
bool fadePurpleIn;
void purpleLED() {
  analogWrite(ledR, fadePurple);
  digitalWrite(ledG, LOW);
  analogWrite(ledB, fadePurple);

  if(fadePurpleIn) {
      fadePurple++;
  } else {
    fadePurple--;
  }

  if (fadePurple >= 255){
    fadePurpleIn = false;
  } else if(fadePurple <= 0){
    fadePurpleIn = true;
  }

  delay(3);
}

int policeFade = 0;
bool policeFadeIn = true;
void policeLED() {
  analogWrite(ledR, 255 - policeFade);
  analogWrite(ledB, policeFade);
  
  if (policeFade < 128){
    analogWrite(ledG, policeFade);
  } else {
    analogWrite(ledG, 255 - policeFade);
  }

  if(policeFadeIn) {
      policeFade++;
  } else {
    policeFade--;
  }

  if (policeFade >= 255){
    policeFadeIn = false;
  } else if(policeFade <= 0){
    policeFadeIn = true;
  }

  delayMicroseconds(50);
}

int gamerColorState = 0;
int gamerFadeState = 0;
void gamerLED() {
  gamerFadeState++;

  if (gamerFadeState >= 256) {
    gamerColorState = gamerColorState >= 3 ? 0 : gamerColorState + 1;
    gamerFadeState = 0;
  }

  switch(gamerColorState) {
    case 0:
      analogWrite(ledR, 255 - gamerFadeState);
      analogWrite(ledG, 0);
      analogWrite(ledB, gamerFadeState);
      break;
    case 1:
      analogWrite(ledR, 0);
      analogWrite(ledG, gamerFadeState);
      analogWrite(ledB, 255 - gamerFadeState);
      break;
    default:
      analogWrite(ledR, gamerFadeState);
      analogWrite(ledG, 255 - gamerFadeState);
      analogWrite(ledB, 0);
      break;
  }
  delay(1);
}

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
  chkBtn();
  delay(3);
}


