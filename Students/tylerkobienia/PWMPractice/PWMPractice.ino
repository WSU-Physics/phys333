// Turn on an LED using PWM
// Turn on another LED using our own
// PWM function

const int yLED = 9;
const int bLED = 8; // constant for my blue LED

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
  pinMode(yLED, OUTPUT);
  // set blue LED pin to output
  pinMode(bLED, OUTPUT);
}

void loop() {
  
  double brightness = ;
  delay(500);
  double period = 2000000;

  
  // Set yLED brightness
  analogWrite(yLED, brightness);
  // call self-made PWM function
  pwm(bLED, brightness, period);
}