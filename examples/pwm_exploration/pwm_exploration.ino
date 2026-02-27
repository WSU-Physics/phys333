// Turn on an LED using PWM
// Turn on another LED using our own
// PWM function

//const int bLED = 8; // constant for my blue LED

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
const int pin = 0;
unsigned long previousMillis = 0;
unsigned long duration = 100;
void pwm(int pin, double dutyCycle){
  // Calculate Ton and Toff
  long Ton;  // using double precision to avoid overflow
  long Toff;
  double period = 10;
  Ton = ((dutyCycle * period) * 100) + 0.5;
  Toff = (period - 10 * Ton / 100) * 100 + 0.5;
  // Turn on
  digitalWrite(pin, HIGH);
  // delay for Ton
  delayMicroseconds(10 * Ton);
  // Turn off
  digitalWrite(pin, LOW);
  // delay for Toff
  delayMicroseconds(10 * Toff);
  
}

void setup() {
  // set blue LED pin to output
  pinMode(pin, OUTPUT);
  
}

void loop() {
   
  unsigned long currentMillis = 0;

  while (currentMillis <= duration) {
    // save the last time you blinked the LED
    pwm(13, 0.25);
    currentMillis = millis();
  }
 delay(1000);
}
