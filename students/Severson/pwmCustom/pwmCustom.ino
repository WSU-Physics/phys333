/*
 * A custom PWM function capable of greater precision than analogWrite()
 */

const int ledBlue = 2;  //set pin 2 as ledBlue

void pwm(int pin, double dutyCycle, double duration){ //custom pwm function with the arguments pin, dutyCycle, and duration
  const double T = 10000.;  //sets the period to 10000 
  double Ton = dutyCycle*T; //calculate time ledBlue is on
  double Toff = T - Ton;  //calculate time ledBlue is off
  double nLoops = duration/T; //number of loops needed to run during a full duration

  for(int i = 0.; i < nLoops; i++){ //incrementing the number of loops from zero to nLoops
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
  for(double dutyCycle = 0.; dutyCycle <= 1.; dutyCycle = dutyCycle + .001){  //incrementing the duty cycle so led goes from off to full brightness then repeats
  pwm(ledBlue, dutyCycle, 10000.);  //calling the custom pwm function and setting the duration value
  }
  digitalWrite(ledBlue, LOW); //turn ledBlue off after a full duty cycle
  delay(1000);  //delays one second before repeating the loop

}
