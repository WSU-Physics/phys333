
const int LED = 9; 
const int BUTTON=2; 

void setup() {
  // put your setup code here, to run once:
  pinMode (LED, OUTPUT); 
  pinMode (BUTTON, INPUT); 
  //digitalWrite(LED, HIGH); 
}

void loop() {
  // put your main code here, to run repeatedly:
 // for (int i = 0; i<256; i++) {
    //analogWrite(LED, i); 
    //delay(10);   }
  //for (int i = 255; i>=0; i--) {
    //analogWrite(LED, i); 
    //delay(10); }
  
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(LED, LOW); 
  }
  else {
    digitalWrite(LED, HIGH); 
  }
}
