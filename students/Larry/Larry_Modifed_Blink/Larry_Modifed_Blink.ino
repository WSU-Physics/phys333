int LED = 13;
void setup() {
  
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  //turns led on for 1000ms = 1s
  digitalWrite(LED, HIGH);
  delay(1000);
  //turns LED off for 2000ms = 2s
  digitalWrite(LED, LOW);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  // initialize digital pin LED_BUILTIN as an output.


  // the loop function runs over and over again forever

  //LED is on for .5 second
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);     
  // LED is off for .25 second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(250);                       // wait for a second

}
