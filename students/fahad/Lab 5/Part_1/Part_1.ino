void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int number = Serial.read();
    Serial.println("Found:" + String(number));
  }
}
