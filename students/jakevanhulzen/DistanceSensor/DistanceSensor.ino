void setup() {
  Serial.begin(9600);
}
 
void loop() {
  char serialCharacter;
  if (Serial.available()) {
    serialCharacter = Serial.read();
    Serial.write(serialCharacter);
    // Switching the transistor based on serialCharacter
    if(serialCharacter == 'R') {
      Serial.write('\n');
  
    }
  }
}
