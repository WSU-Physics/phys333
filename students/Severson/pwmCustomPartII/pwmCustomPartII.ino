/*
   A custom PWM function capable of greater precision than analogWrite()
*/

const int ledBlue = 2;  //set pin 2 as ledBlue

void pwm(int pin, double dutyCycle, double duration) { //custom pwm function with the arguments pin, dutyCycle, and duration
  const double T = 10000.;  //sets the period in microseconds
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
  for (double dutyCycle = 0.; dutyCycle <= 1.0; dutyCycle = dutyCycle + .005) { //setting the duty cycle as double precision and incrementing in steps of 0.005 (this value creates a two second period with the duration set correctly)
    double duration = 10000.; //set the duration in microseconds, keep at same value as T above for a two second period sawtooth pattern
    pwm(ledBlue, dutyCycle, duration);  //calling the custom pwm function and incrementing the dutyCycle from 0.0 to 1.0 (off to full brightness, this creates the sawtooth pattern on the oscilliscope)
  }

}
