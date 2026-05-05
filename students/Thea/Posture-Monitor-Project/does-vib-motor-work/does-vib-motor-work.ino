const int vibPin = 9;

void setup() {
  pinMode(vibPin, OUTPUT);
}

void loop() {
  digitalWrite(vibPin, HIGH);
  delay(1000);

  digitalWrite(vibPin, LOW);
  delay(1000);
}