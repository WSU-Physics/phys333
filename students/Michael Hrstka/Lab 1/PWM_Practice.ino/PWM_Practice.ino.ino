int led = 3;
int btn = 2;
bool cycleColors = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
}

void chkBtn() {
  if (!digitalRead(btn)) {
    cycleColors = !cycleColors;
  }
}

void loop() {
  int value = 0;
  if(cycleColors) while (value < 256) {
    analogWrite(led, value);
    value++;
    delay(3);
  }

  chkBtn();

  if(cycleColors) while (value > 0) {
    value--;
    analogWrite(led, value);
    delay(3);
  }

  chkBtn();

  if(!cycleColors) {  // Button would read random inputs, adding a delay fixed this.
    delay(3);
  }
}
