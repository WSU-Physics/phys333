
const int LED=9;  // Define LED for pin 9

// synax error is was missing a ; for line 6
void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  // Nothing to loop over
  //firs part of function takes the led variable to the other a value between 0 and 256
  analogWrite(LED, 255) //uses an 8 bit register to set a specfic brightness to the LED
}
