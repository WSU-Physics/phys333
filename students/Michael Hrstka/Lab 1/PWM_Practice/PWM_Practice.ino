int led = 3;
int btn = 2;
bool cycleColors = true;
bool fadeIn = true;
int value = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
}

void chkBtn() {
  if (digitalRead(btn) == HIGH) {
    cycleColors = !cycleColors;
    analogWrite(led, 0);  // Shut off right away, otherwise it will hold brightness... Which could be a cool feature, but not a desired one
        while (digitalRead(btn) == HIGH){ // Debounce to prevent flickering (this isn't supposed to be a strobe light -_-)
      delay(10);
    }
  }
}

void loop() {
  if(fadeIn)
    value++;
  else
    value--;

  if(cycleColors)
    analogWrite(led, value);
  else {
    analogWrite(led, 0);
    fadeIn = true;
    value = 0;
  }

  if (value <= 0) {
    fadeIn = true;
    value = 0;
  } else if (value >= 255) {
    fadeIn = false;
    value = 255;
  }

  chkBtn();
  delay(3);
}

