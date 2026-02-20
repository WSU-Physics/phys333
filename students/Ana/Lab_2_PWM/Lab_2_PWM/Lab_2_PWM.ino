// Turn on an LED using PWM
// Turn on another LED using our own
// PWM function

const int PIN = 13;

/* function: pwm
 *  
 * Practice writing functions and understanding 
 * PWM by explicitly setting output high/low
 * according to input parameters.
 * Sets pin to HIGH, delays, sets to LOW, delays.
 * 
 * pin: Pin number to execute PWM on
 * brightness: How bright the LED should be.
 *             0 is off, 255 is maximum.
 * period: period of pulse in microseconds
*/
void pwm(int PIN, double duty_cycle, double duration, double period){
  // Calculate Ton and Toff
  //resolution of 10 us
  double Ton;  // using double precision to avoid overflow
  double Toff;

  Ton = (duty_cycle * period) / 255;  //duty cycle = Ton / total period * 100%
  Toff = period - Ton;
  duration = 100 * 1000;  //100ms in us will turn on/off with certain duty cycle

  // Turn on
  digitalWrite(PIN, HIGH);
  // delay for Ton
  delayMicroseconds(Ton);
  // Turn off
  digitalWrite(PIN, LOW);
  // delay for Toff
  delayMicroseconds(Toff);
  

}

void setup() {
  pinMode(PIN, OUTPUT);
}

void loop() {
  double duty_cycle = 125;  //fraction of time that signal spends in active state
  double period = 10 * 1000;  //want 10 ms
  double duration;

  pwm(PIN, duty_cycle, duration, period);
/*  
  // Set yLED brightness
  analogWrite(yLED, brightness);
  // call self-made PWM function
  pwm(bLED, brightness, period);
*/

}