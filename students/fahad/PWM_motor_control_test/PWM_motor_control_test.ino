int out1 = 9;
int val;

void setup() {
  Serial.begin(9600);
  pinMode(out1, OUTPUT);
  pinMode(out1, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    val = Serial.read();
  }

  if (val == '0') {
    analogWrite(out1, 0)  ;
    Serial.println("Speed is = 0");
    val = 10;
  }
  if (val == '1') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 70) ;
    Serial.println("Speed is = 1");
    val = 10;
  }
  if (val == '2') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 90) ;
    Serial.println("Speed is = 2");
    val = 10;
  }
  if (val == '3') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 120);
    Serial.println("Speed is = 3");
    val = 10;
  }
  if (val == '4') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 150);
    Serial.println("Speed is = 4");
    val = 10;
  }
  if (val == '5') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 180);
    Serial.println("Speed is = 5");
    val = 10;
  }
  if (val == '6') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 200);
    Serial.println("Speed is = 6");
    val = 10;
  }
  if (val == '7') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 220);
    Serial.println("Speed is = 7");
    val = 10;
  }
  if (val == '8') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 240);
    Serial.println("Speed is = 8");
    val = 10;
  }
  if (val == '9') {
    analogWrite(out1, 255);
    delay(10);
    analogWrite(out1, 255);
    Serial.println("Speed is = 9");
    val = 10;
  }

}
