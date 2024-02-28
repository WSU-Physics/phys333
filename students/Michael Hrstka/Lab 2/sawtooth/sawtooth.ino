int pin = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
}

void loop() {
  for(int i = 0; i < 256; i++){
    analogWrite(pin, i);
    delayMicroseconds(7812);
  }
}
