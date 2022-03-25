
char incomingData[4];
int nBytes;

  void setup() {

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

}

void loop() {

  if (Serial.available() > 0) {

    if (Serial.read() == 82) {
      
       nBytes = Serial.readBytes(incomingData,3); // read the incoming byte:

       Serial.print(" I received:");

       Serial.print(incomingData);

       Serial.println(" inches");
  
    }
  
  }

}
