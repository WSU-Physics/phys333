// This code is broken. See if you can fix it.
// Modified on 23 Jan 2022 by Adam Severson. Placed missing semi-colon on line 6 (now line 7).

//Fixes required the setup of a circuit to light up the LED, connected to digital pin 9 


const int LED=9;  // Define LED for pin 9

void setup() {
  pinMode(LED, OUTPUT);  // Set the LED pin as an output
  digitalWrite(LED, HIGH);  // Set the LED pin high
 
}

void loop() {
  // Nothing to loop over
}
