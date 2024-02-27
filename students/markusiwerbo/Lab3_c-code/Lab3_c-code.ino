const int led [] = {13,12,11,10,9,8,7,6};
const int ledcount = 8;

void setup() {
  // put your setup code here, to run once:

for (int i = 0; i < ledcount; i++) {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < ledcount; i++) {
    digitalWrite(led[i], HIGH);
    delay(100);
    digitalWrite(led[i], LOW);
  }
 
  for (int i = ledcount - 1; i >= 0; i--) {
    digitalWrite(led[i], HIGH);
    delay(100);
    digitalWrite(led[i], LOW);
  }
}