/*
   This is a PWM function which is written to be more precise than the analogWrite() function.
*/

const int ledBlue = 2;  //sets pin 2 as ledBlue

void pwmHb(int pin, double dutyCycle, double duration) {  
  const int period = 10000;                               //sets the period as a constant integer of 10000
  double Ton;                                             //creates a float variable, Ton, with double precision
  double Toff;                                            //creates a float variable, Toff, with double precision

  for (dutyCycle = 0.; dutyCycle < 1.; dutyCycle = dutyCycle + .005) {  //sets the duty cycle between 0 and 1 increasing in increments of 0.005
    Ton = dutyCycle * period;                                           //defines Ton in terms of the duty cycle and period
    Toff = period - Ton;                                                //defines Toff in terms of period and Ton
    digitalWrite(ledBlue, HIGH);                                        //turns pin 2 led on
    delayMicroseconds(Ton);                                             //delays for current Ton value
    digitalWrite(ledBlue, LOW);                                         //turns pin 2 led off
    delayMicroseconds(Toff);                                            //delays for current Toff value
  }

}

void setup() {
  pinMode(ledBlue, OUTPUT);   //sets led on pin 2 as output

}

void loop() {
  double dutyCycle = 0.;                  //sets duty cycle to zero
  double duration = 0.;                   // sets duration to zero
  pwmHb(ledBlue, dutyCycle, duration);    //runs the homebrew PWM function

}
