// Function: pwm
// Practice writing functions and understanding 
// PWM by explicitly setting output high/low
// according to input parameters.
// Sets pin to HIGH, delays, sets to LOW, delays.
// 
// pin: Pin number to execute PWM on
// brightness: How bright the LED should be.
//             0 is off, 255 is maximum.
// period: period of pulse in microseconds
void pwm(int pin, double brightness, double period){
  // Calculate Ton and Toff
  double Ton;  // using double precision to avoid overflow
  double Toff;
  Ton = (brightness / 255) * period;
  Toff = period - Ton;
  
  // Turn on
  digitalWrite(pin, HIGH);
  // delay for Ton
  delayMicroseconds((unsigned long)Ton);
  // Turn off
  digitalWrite(pin, LOW);
  // delay for Toff
  delayMicroseconds((unsigned long)Toff);
}

void setup() {
  // Set pin mode to output
  pinMode(9, OUTPUT);
}

void loop() {
  // Vary brightness and period parameters
  double period = 2000000; // 2 seconds in microseconds
  
  for (int brightness = 0; brightness <= 255; brightness++) {
    pwm(9, brightness, period / 255);
  }
}