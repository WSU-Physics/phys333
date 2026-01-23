void setup() {
  // initialize digital pin LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // this part only happens once immediately after the upload completes 
  digitalWrite(LED_BUILTIN, HIGH); // LED turns on
  delay(1000);                     // on for a second
  digitalWrite(LED_BUILTIN, LOW);  // LED turns off
  delay(2000);                     // off for 2 seconds
}

// the loop function starts after the part above, and it will then continue forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on 
  delay(500);                      // wait for 0.5 seconds
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
  delay(250);                      // wait for 0.25 seconds
}

  // First, I copy and pasted the pre-written program, Blink, onto my own sketch.
  // I added a portion in void setup() function that would tell the LED to turn on for 
  // one second and then turn off for two. I wrote it here so that it would only happen
  // one time immediately after the program was uploaded to the Arduino Uno.
  // Then, I modified the loop delay() values so that the LED is on for half 
  // a second and then off for a quarter of a second. This repeats forever.
