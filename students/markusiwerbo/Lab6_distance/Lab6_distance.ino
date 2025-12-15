void setup() {
  Serial.begin(9600);
}
 
void loop() {
  char serialCharacter;
  if (Serial.available()) {
    serialCharacter = Serial.read();
    Serial.write(serialCharacter);  
    if(serialCharacter == 'R') {
      Serial.write('\n');  
    }
  }
}