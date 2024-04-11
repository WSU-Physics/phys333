int ledR = 3;
int ledG = 5;
int ledB = 6;
int btn = 12;
int state = 0;

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(btn, INPUT);
}

void chkBtn() {
  if (digitalRead(btn) == HIGH) {
    state = state > 4 ? 0 : state + 1;
        while (digitalRead(btn) == HIGH){ // Debounce!
      delay(10);
    }
  }
}

void loop() {
  if(state == 0) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
  } else
  if(state == 1) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    digitalWrite(ledB, LOW);
  } else
  if(state == 2) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, HIGH);
  } else
  if(state == 3) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, HIGH);
    digitalWrite(ledB, HIGH);
  } else
  if(state == 4) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
  }
  chkBtn();
  delay(3);
}


