/*
   A custom PWM function capable of greater precision than analogWrite()
*/

const int ledBlue = 2;  //set pin 2 as ledBlue

void pwm(int pin, double dutyCycle, double duration) { //custom pwm function with the arguments pin, dutyCycle, and duration
  const double T = 10000.;  //sets the period to 10000
  double Ton = dutyCycle * T; //calculate time ledBlue is on
  double Toff = T - Ton;  //calculate time ledBlue is off
  double nLoops = duration / T; //number of loops needed to run during a full duration

  for (int i = 0.; i < nLoops; i++) { //incrementing the number of loops from zero to nLoops
    digitalWrite(ledBlue, HIGH);  //set ledBlue high
    delayMicroseconds(Ton); //ledBlue is on
    digitalWrite(ledBlue, LOW); //set ledBlue low
    delayMicroseconds(Toff);  //ledBlue is off
  }
}

void setup() {  //setup function
  pinMode(ledBlue, OUTPUT); //set pin 2 as output
}

void loop() { //main loop
  pwm(ledBlue, .33, 1000000.);  //calling the custom pwm function setting the duty cycle between 0.0 (off) and 1.0 (full brightness) and setting the duration value in microseconds
  digitalWrite(ledBlue, LOW); //turn ledBlue off after a full duration
  delay(1000);  //delay (in milliseconds) before repeating the loop, can be adjusted as desired

}
