// This code is broken. See if you can fix it.
//Your error was in line 6 where you were setting up your pinMode. I added a semicolon (;) at the end.
const int LED=9;  // Define LED for pin 9

void setup() {
  pinMode(LED, OUTPUT);  // Set the LED pin as an output (the mistake on the code is that we did not add ";" at the end)
  digitalWrite(LED, HIGH);  // Set the LED pin high
}

void loop() {
  // Nothing to loop over
}
