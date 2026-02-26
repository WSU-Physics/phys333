// Turn on an LED using PWM
// Turn on another LED using our own
// PWM function

const int PIN = 13;
double val;

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
void pwm(int PIN, double duty_cycle, double duration, double period){//double duration,
  // Calculate Ton and Toff
  //resolution of 10 us
  double Ton;  // using double precision to avoid overflow
  double Toff;

  Ton = (duty_cycle * period) / 255;  //duty cycle = Ton / total period * 100%
  Toff = period - Ton;
  duration = 100 * 1000;  //100ms in us will turn on/off with certain duty 
  val = duration / period;  //100ms / 10ms = 10 

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
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
  
}


void loop() {
  for (int i = 0; i < 256; i++) {
    double duty_cycle = i;  //fraction of time that signal spends in active state
    //delay(10) 
    //Serial.println(i);
  
    double period = 10 * 1000;  //want 10 ms
    double duration = 100  * 1000; //100 ms, this is how long so many periods will run

    pwm(PIN, duty_cycle, duration, period);
  }
  double duty_cycle = 0;


}