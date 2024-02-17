// Turn on an LED using PWM
// Turn on another LED using our own
// PWM function


const int bLED = 9; // constant for my blue LED

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
void pwm(int pin, double brightness, double period){
  // Calculate Ton and Toff
  double Ton;  // using double precision to avoid overflow
  double Toff;
  Ton = (brightness * period) / 255;
  Toff = period - Ton;
  
  // Turn on
  digitalWrite(pin, HIGH);
  // delay for Ton
  delayMicroseconds(Ton);
  // Turn off
  digitalWrite(pin, LOW);
  // delay for Toff
  delayMicroseconds(Toff);
}

void setup() {
  // set pin mode to output
  pinMode(9, OUTPUT);

}

void loop() {
   double period = 2000000; // 2 seconds 
  
    for (int brightness =0; brightness <= 225; brightness++)// increments the brightness from 0 to 255 and reset 


  pwm(bLED, brightness, period/255);
}
