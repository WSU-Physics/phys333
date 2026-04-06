char incomingChar; 
char distanceBuffer[4]; 
int distance; 

void setup() {
  Serial.begin(9600); //baud rate
}

void loop() {
  if(Serial.available()) {
    incomingChar = Serial.read(); 

    if(incomingChar == 'R') {
      while(Serial.available() < 3); 
      for(int i = 0; i<3; i++) {
        distanceBuffer[i] = Serial.read(); 
      }
      distanceBuffer[3] = '\0'; 
      distance = atoi(distanceBuffer); 

      Serial.print("Distance: "); 
      Serial.print(distance); 
      Serial.println(" inches"); 
    }
  }
}
