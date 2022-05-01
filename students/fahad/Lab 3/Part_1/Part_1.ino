const int led0 = 0;
const int led1 = 1;
const int led2 = 2;
const int led3 = 3;
const int led4 = 4;
const int led5 = 5;
const int led6 = 6;
const int led7 = 7;
int del = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
}

void loop() {
  digitalWrite(led0, HIGH);
  delay(del);
  digitalWrite(led0, LOW);
  delay(del);
  digitalWrite(led1, HIGH);
  delay(del);
  digitalWrite(led1, LOW);
  delay(del);
  digitalWrite(led2, HIGH);
  delay(del);
  digitalWrite(led2, LOW);
  delay(del);
  digitalWrite(led3, HIGH);
  delay(del);
  digitalWrite(led3, LOW);
  delay(del);
  digitalWrite(led4, HIGH);
  delay(del);
  digitalWrite(led4, LOW);
  delay(del);
  digitalWrite(led5, HIGH);
  delay(del);
  digitalWrite(led5, LOW);
  delay(del);
  digitalWrite(led6, HIGH);
  delay(del);
  digitalWrite(led6, LOW);
  delay(del);
  digitalWrite(led7, HIGH);
  delay(del);
  digitalWrite(led7, LOW);
  delay(del);

}
