int dout = 11;
int din = 8;


void setup() {
  Serial.begin(115200);
  pinMode(dout,OUTPUT);
  pinMode(din,INPUT);

}

void loop() {
  analogWrite(dout,128);
  int state = digitalRead(din);
  Serial.println(state);
}
