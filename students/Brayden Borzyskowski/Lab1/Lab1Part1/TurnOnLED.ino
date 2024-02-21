// This code is broken. See if you can fix it.

const int LED=9;  // Define LED for pin 9

void setup() {
  pinMode(LED, OUTPUT); // Set the LED pin as an output
  //digitalWrite(LED, HIGH);  // Set the LED pin high
}

void loop() {
  // Nothing to loop over
//   for (int i=100; i<=1000; i=i+100)
// {
//   digitalWrite(LED, HIGH); 
//   delay(i); 
//   digitalWrite(LED, LOW); 
//   delay(i);
// }
  
    analogWrite(LED, 10);
    delay(5000);
    analogWrite(LED, 230);
    delay(1000);
  } 


