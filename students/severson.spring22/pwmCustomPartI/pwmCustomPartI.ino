/*
   A custom PWM function capable of greater precision than analogWrite().
*/

const int ledPin = 2;  //set non-PWM pin as ledPin
const double T = 10000.;  //sets the period to 10000 (microseconds)

void pwm(int pin, double dutyCycle, double duration) { //custom pwm function with the arguments pin, dutyCycle, and duration
  double Ton = dutyCycle * T; //calculate time ledPin is on
  double Toff = T - Ton;  //calculate time ledPin is off
  double nLoops = duration / T; //number of loops needed to run during a full duration

  for (int i = 0.; i < nLoops; i++) { //incrementing the number of loops from zero to nLoops
    digitalWrite(ledPin, HIGH);  //set ledPin high
    delayMicroseconds(Ton); //ledPin is on
    digitalWrite(ledPin, LOW); //set ledPin low
    delayMicroseconds(Toff);  //ledPin is off
  }
}

void setup() {  //setup function
  pinMode(ledPin, OUTPUT); //set ledPin as output
}

void loop() { //main loop
  pwm(ledPin, .3333, 1000000.);  //calling the custom pwm function setting the duty cycle between 0.0 (off) and 1.0 (full brightness) and setting the duration value in microseconds
  digitalWrite(ledPin, LOW); //turn ledPin off after a full duration
  delay(3000);  //delay (in milliseconds) before repeating the loop, can be adjusted as desired

}
