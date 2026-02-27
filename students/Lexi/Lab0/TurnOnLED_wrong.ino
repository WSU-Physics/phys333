// This code is broken. See if you can fix it.

const int LED=9;  // Define LED for pin 9

void setup() {
  pinMode(LED, OUTPUT);  // THIS LINE WAS MISSING A ;
  digitalWrite(LED, HIGH);  // Set the LED pin high
}

void loop() {
  // Nothing to loop over
}
