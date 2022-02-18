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

void pwm(int pin, double dutycycle, double period, double duration){
  // Calculate Ton and Toff
  double Ton;  // using double precision to avoid overflow
  double Toff;
  Ton = dutycycle*period;
  Toff = period-Ton;

    for (int N=0; N < duration/period; N++)
     {
      // Turn on
      digitalWrite(pin, HIGH);
      // delay for Ton
      delayMicroseconds(Ton*1000);
      // Turn off
      digitalWrite(pin, LOW);
      // delay for Toff
      delayMicroseconds(Toff*1000);
     }
}

void setup() {
  // set pin mode to output
  //pinMode(yLED, OUTPUT);
  // set blue LED pin to output
  pinMode(bLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  double period = 10;
  double dutycycle = 0.5;
  double duration = 1000;

  pwm(bLED, dutycycle, period, duration);
  //delay(1000);
  //double brightness = 100;

}
