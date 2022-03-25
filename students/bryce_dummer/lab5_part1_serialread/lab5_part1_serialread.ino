
char incomingByte1;
char incomingByte2;
char incomingByte3;
char incomingByte4;

  void setup() {

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

}

void loop() {

  if (Serial.available() > 0) {

  incomingByte1 = Serial.read(); // read the incoming byte:
  incomingByte2 = Serial.read();
  incomingByte3 = Serial.read();
  incomingByte4 = Serial.read();
  Serial.print(" I received:");

  Serial.print(incomingByte1);
  Serial.print(incomingByte2);
  Serial.print(incomingByte3);
  Serial.println(incomingByte4);

  while(!Serial.available());
  delay(100);
  
  }

}
